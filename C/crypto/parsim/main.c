h#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// SDL_MAIN_HANDLED: lets us create out own main function
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <CL/opencl.h>

#include "gl_core_4_5.h"

#include "vectors.h"
#include "matrices.h"

#define NUM_PARTICLES 1000000

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

float dt = 0.001;
float Fd = 0.0;
float Fr = 1.0;

vec2 dim = {
    SCREEN_WIDTH, SCREEN_HEIGHT
};

bool apply_div_force = false;
bool apply_rot_force = false;

vec2 mouse;

SDL_Window          *window                 = NULL;
SDL_GLContext       gl_context_handle       = NULL;

GLuint              gl_program              = 0;
GLuint              gl_vertex_buffer[2];

cl_device_id        cl_selected_device_id   = NULL;
cl_context          cl_context_handle       = NULL;
cl_command_queue    cl_command_queue_handle = NULL;
cl_program          cl_physics_program      = NULL;
cl_kernel           cl_move_kernel          = NULL;
cl_mem              cl_vertex_buffer[2];

const char *physics_program_src =
    "__kernel void move(\n"
    "    float dt, float2 dim, \n"
    "    float Fd, float Fr, float2 g, \n"
    "    __global float4 *r_in,\n"
    "    __global float4 *r_out\n"
    ") {\n"
    "    unsigned int gid = get_global_id (0);\n"
    "\n"
    "    float4 r = r_in[gid];"
    "\n"
    "    float2 p = r.s01;\n"
    "    float2 v = r.s23;\n"
    "    float2 dir  = p - g;\n"
    "    float dist = fast_length (dir);\n"
    "\n"
    "    // clamp the value inside the box\n"
    "    float2 F = 0;\n"
    "    F += Fd * dir / (dist + (float) 0.001);\n"
    "    F += Fr * (float2) (-dir.y, dir.x) / (dist + (float) 0.001);\n"
    "    p += dt * v + ((float) 0.5) * F * dt * dt;\n"
    "    v += dt * F;\n"
    "\n"
    "    r_out[gid] = (float4) (p, 0.999f * v);\n"
    "}";

const char *vertex_shader_source =
    "#version 440\n"
    "\n"
    "layout(location = 0) uniform mat4 projection;\n"
    "layout(location = 1) uniform float rel;"
    "layout(location = 0) in vec2 p;\n"
    "layout(location = 1) in vec2 v;\n"
    "\n"
    "out vec3 color;\n"
    "\n"
    "void main(void) {\n"
    "   color = (length (v) / rel) * vec3(0.5, 0.9, 0.2);//0.5 * vec3 (v.x, v.y, v.x + v.y) + 0.5;\n"
    "   gl_Position = projection * vec4(p, 0.0, 1.0);\n"
    "\n"
    "}";

const char *fragment_shader_source =
    "#version 440\n"
    "\n"
    "in vec3 color;\n"
    "\n"
    "layout (location = 0) out vec4 out_Color;\n"
    "\n"
    "void main(void) {\n"
    "   out_Color = vec4(color, 1.0);\n"
    "\n"
    "}";

void CL_CALLBACK cl_error_callback(const char * msg, const void *data, size_t size, void *user)
{
    SDL_Log ("OpenCL Error Callback: %s", msg);
}

bool sdl_handle_events ()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }

        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                int x, y;

                SDL_GL_GetDrawableSize (window, &x, &y);
                dim.x = x;
                dim.y = y;
                glViewport (0, 0, x, y);
            }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                apply_div_force = true;
            }

            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                apply_rot_force = true;
            }
        }

        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                apply_div_force = false;
            }

            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                apply_rot_force = false;
            }
        }
    }

    return true;
}

bool initialise_sdl ()
{
    // This is required, since we use our own main function
    SDL_SetMainReady ();
    if (SDL_InitSubSystem (SDL_INIT_VIDEO) != 0)
    {
        SDL_Log ("Could not initialise SDL: %s", SDL_GetError ());
        return false;
    }

    // Request an OpenGL 4.5 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow (
        "Bunga Bunga Party!",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (window == NULL)
    {
        SDL_Log ("Could not create window: %s", SDL_GetError ());
        return false;
    }

    // Dont use SDL_Renderer as we need full access to opengl context
    if ((gl_context_handle = SDL_GL_CreateContext(window)) == NULL)
    {
        SDL_Log ("Could not create OpenGL context: %s", SDL_GetError ());
        return false;
    }

    // load the opengl 4.5 function pointers
    if(ogl_LoadFunctions () != ogl_LOAD_SUCCEEDED)
    {
        SDL_Log ("Could not load OpenGL functions.");
        return false;
    }

    return true;
}

void sdl_finalise ()
{
    SDL_GL_DeleteContext (gl_context_handle);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool opencl_initialise ()
{
    cl_uint num_platforms;
    clGetPlatformIDs (0, 0, &num_platforms);

    if (num_platforms == 0)
    {
        SDL_Log ("OpenCL: no platforms found.");
        return false;
    }

    // just take the first device available
    cl_platform_id platform_id;
    clGetPlatformIDs (1, &platform_id, 0);
    cl_uint num_devices;
    clGetDeviceIDs (platform_id, CL_DEVICE_TYPE_DEFAULT, 0, 0, &num_devices);
    clGetDeviceIDs (platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &cl_selected_device_id, 0);

    SDL_SysWMinfo syswm;
    SDL_VERSION(&syswm.version);
    SDL_GetWindowWMInfo (window, &syswm);

    // Now the only platform specific part starts.
    // OpenCL needs system related handles to acquire openGL object.
    // Thankfully SDL provides a function to obtain those.

    switch (syswm.subsystem)
    {
        #define CASE(s) case s: puts (#s); break;

        CASE(SDL_SYSWM_WINDOWS)
        CASE(SDL_SYSWM_X11)
        CASE(SDL_SYSWM_DIRECTFB)
        CASE(SDL_SYSWM_WAYLAND)
        CASE(SDL_SYSWM_MIR)
        CASE(SDL_SYSWM_WINRT)
        CASE(SDL_SYSWM_ANDROID)
        CASE(SDL_SYSWM_VIVANTE)
        default:
            puts ("Unknown subsystem.");
    }

#ifdef _WIN32
    cl_context_properties context_properties[] = {
        CL_CONTEXT_PLATFORM,    (cl_context_properties)     platform_id,
        CL_GL_CONTEXT_KHR,      (cl_context_properties)     gl_context_handle,
        CL_WGL_HDC_KHR,         (cl_context_properties)     syswm.info.win.hdc,
        0
    };

#elif __linux__
    cl_context_properties context_properties[] = {
        CL_CONTEXT_PLATFORM,    (cl_context_properties)     platform_id,
        CL_GL_CONTEXT_KHR,      (cl_context_properties)     gl_context_handle,
        CL_GLX_DISPLAY_KHR,     (cl_context_properties)     syswm.info.x11.display,
        0
    };
#else
    #error Platform is not supported.
#endif

    int error;
    cl_context_handle = clCreateContext (context_properties, 1, &cl_selected_device_id, &cl_error_callback, 0, &error);

    if (cl_context_handle == NULL)
    {
        SDL_Log ("OpenCL: context creation failed: %d", error);
        return false;
    }

    cl_command_queue_handle = clCreateCommandQueue (cl_context_handle, cl_selected_device_id, 0, &error);
    if (cl_command_queue_handle == NULL)
    {
        SDL_Log ("OpenCL: command queue creation failed: %d", error);
        return false;
    }

    return true;
}

void opencl_finalise ()
{
    clReleaseCommandQueue (cl_command_queue_handle);
    clReleaseContext (cl_context_handle);
}

bool opencl_initialise_programs ()
{
    int error;

    cl_physics_program = clCreateProgramWithSource (cl_context_handle, 1, &physics_program_src, 0, &error);
    if (cl_physics_program == NULL)
    {
        SDL_Log ("OpenCL: program creation failed: %d", error);
        return false;
    }


    error = clBuildProgram (cl_physics_program, 1, &cl_selected_device_id, "", 0, 0);
    if (error != CL_SUCCESS)
    {
        SDL_Log ("OpenCL: build program failed: %d", error);

        size_t log_length;
        clGetProgramBuildInfo (cl_physics_program, cl_selected_device_id, CL_PROGRAM_BUILD_LOG, 0, 0, &log_length);

        char logs[log_length + 1];
        clGetProgramBuildInfo (cl_physics_program, cl_selected_device_id, CL_PROGRAM_BUILD_LOG, log_length, logs, 0);

        SDL_Log ("OpenCL: error log: %s", logs);
        return false;
    }

    cl_move_kernel = clCreateKernel (cl_physics_program, "move", &error);
    if (cl_move_kernel == NULL)
    {
        SDL_Log ("OpenCL: kernel creation failed: %d", error);
        return false;
    }

    return true;
}

bool opengl_check_shader (GLuint shader)
{
    GLint compile_status, log_length;


    glGetShaderiv (shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE)
    {
        glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 0)
        {
            char logs[log_length];

            glGetShaderInfoLog (shader, log_length, 0, logs);
            SDL_Log ("OpenGL: shader compilation failed: %s", logs);
        };

        return false;
    };

    return true;
}

bool opengl_check_program (GLuint program)
{
    GLint linker_status, log_length;

    glGetProgramiv (program, GL_LINK_STATUS, &linker_status);
    if (linker_status != GL_TRUE)
    {
        glGetShaderiv (program, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 0)
        {
            char logs[log_length];

            glGetProgramInfoLog (program, log_length, 0, logs);
            SDL_Log ("OpenGL: program linking failed: %s", logs);
        };

        return false;
    };
}

void sdl_update_mouse ()
{
    int x, y;
    SDL_GetMouseState (&x, &y);

    mouse.x = x;
    mouse.y = dim.y - y;

}

void opengl_initialise_shaders ()
{
    GLuint vertex_shader = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vertex_shader, 1, &vertex_shader_source, 0);
    glCompileShader (vertex_shader);
    opengl_check_shader (vertex_shader);

    GLuint fragment_shader = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fragment_shader, 1, &fragment_shader_source, 0);
    glCompileShader (fragment_shader);
    opengl_check_shader (fragment_shader);

    gl_program = glCreateProgram ();
    glAttachShader (gl_program, vertex_shader);
    glAttachShader (gl_program, fragment_shader);
    glLinkProgram (gl_program);
    opengl_check_program (gl_program);

    glDeleteShader (vertex_shader);
    glDeleteShader (fragment_shader);
}

void opengl_set_render_parameters ()
{
    glVertexAttribFormat (0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexAttribBinding (0, 0);
    glEnableVertexAttribArray (0);

    glVertexAttribFormat (1, 2, GL_FLOAT, GL_TRUE, 2 * sizeof (float));
    glVertexAttribBinding (1, 0);
    glEnableVertexAttribArray (1);

    /*
     *  Setup clipping control.
     */
    glClipControl (GL_LOWER_LEFT, GL_ZERO_TO_ONE);

    /*
     * Setup blend mode
     */
    glEnable(GL_BLEND);
    glBlendFunc (GL_ONE, GL_ONE);

    glUseProgram (gl_program);
}

float frand(float min, float max)
{
    return (max - min) * ((float) rand() / ((float) RAND_MAX + 1.)) + min;
}

void fill_particle_buffer (vec4 *mem)
{
    for (size_t k = 0; k < NUM_PARTICLES; k++)
    {
        float angle = frand (0, 2 * M_PI);
        float radius = frand (50, 150);

        mem[k].z = .0;
        mem[k].w = .0;
        mem[k].x = radius * cos (angle) + SCREEN_WIDTH / 2;
        mem[k].y = radius * sin (angle) + SCREEN_HEIGHT / 2;
    }
}

void opengl_initialise_buffers ()
{
    glCreateBuffers (2, gl_vertex_buffer);
    int error;

    for (int k = 0; k < 2; k++)
    {
        glNamedBufferStorage (gl_vertex_buffer[k], NUM_PARTICLES * sizeof(vec4), 0, GL_MAP_WRITE_BIT);
        cl_vertex_buffer[k] = clCreateFromGLBuffer (cl_context_handle, CL_MEM_READ_WRITE, gl_vertex_buffer[k], &error);

        if (cl_vertex_buffer[k] == NULL)
            SDL_Log ("OpenCL: could not create buffer from OpenGL handle: %d", error);
    }

    vec4 *memptr = glMapNamedBuffer (gl_vertex_buffer[0], GL_WRITE_ONLY);
    fill_particle_buffer (memptr);

    glUnmapNamedBuffer (gl_vertex_buffer[0]);
}

void opengl_release_buffers ()
{
    clReleaseMemObject (cl_vertex_buffer[0]);
    clReleaseMemObject (cl_vertex_buffer[1]);

    glDeleteBuffers (2, gl_vertex_buffer);
}

void opengl_free_shaders ()
{
    glDeleteProgram (gl_program);
}

void opencl_release_programs ()
{
    clReleaseKernel (cl_move_kernel);
    clReleaseProgram (cl_physics_program);
}

int main (int argc, char *argv[])
{

    if (!initialise_sdl ())
        return 0;


    if (!opencl_initialise ())
        return 0;

    opencl_initialise_programs ();

    opengl_initialise_shaders ();

    opengl_initialise_buffers ();

    opengl_set_render_parameters ();


    // set an orthogonal projection matrix
    mat4 projection;
    orthogonal_matrix4 (projection, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1.0, 1.0);

    int j = 0;


    while (sdl_handle_events ())
    {

        clock_t t = clock ();
        sdl_update_mouse ();

        Fd = apply_div_force ? -200.0 : 0.0;
        Fr = apply_rot_force ? 50.0 : 0.0;

        orthogonal_matrix4 (projection, 0, dim.x, 0, dim.y, -1.0, 1.0);

        cl_event acquire_event, execute_event, release_event;
        clEnqueueAcquireGLObjects (cl_command_queue_handle, 2, cl_vertex_buffer, 0, 0, &acquire_event);

        clSetKernelArg (cl_move_kernel, 0, sizeof(cl_float), &dt);
        clSetKernelArg (cl_move_kernel, 1, sizeof(cl_float2), &dim);

        clSetKernelArg (cl_move_kernel, 2, sizeof(cl_float), &Fd);
        clSetKernelArg (cl_move_kernel, 3, sizeof(cl_float), &Fr);
        clSetKernelArg (cl_move_kernel, 4, sizeof(cl_float2), &mouse);

        clSetKernelArg (cl_move_kernel, 5, sizeof(cl_mem), &cl_vertex_buffer[j]);
        clSetKernelArg (cl_move_kernel, 6, sizeof(cl_mem), &cl_vertex_buffer[1-j]);


        size_t global_work_size = NUM_PARTICLES;

        clEnqueueNDRangeKernel (cl_command_queue_handle, cl_move_kernel, 1, NULL, &global_work_size, NULL, 1, &acquire_event, &execute_event);

        clEnqueueReleaseGLObjects (cl_command_queue_handle, 2, cl_vertex_buffer, 1, &acquire_event, &release_event);
        clWaitForEvents (1, &release_event);

        clReleaseEvent (acquire_event);
        clReleaseEvent (execute_event);
        clReleaseEvent (release_event);

        float rel = length2 (&dim);

        // draw all points
        glClear (GL_COLOR_BUFFER_BIT);
        glProgramUniformMatrix4fv (gl_program, 0, 1, GL_FALSE, projection);
        glProgramUniform1f (gl_program, 1, rel);
        glBindVertexBuffer (0, gl_vertex_buffer[1-j], 0, sizeof(vec4));
        glDrawArrays (GL_POINTS, 0, NUM_PARTICLES);
        SDL_GL_SwapWindow (window);

        j = 1 - j;

        dt = (float) (clock () - t) / CLOCKS_PER_SEC;
    }

    opengl_release_buffers ();

    opengl_free_shaders ();

    opencl_release_programs ();

    opencl_finalise ();
    sdl_finalise ();

    return 0;
}
