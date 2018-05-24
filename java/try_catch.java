public class try_catch {
    public static void main(String[] args) {
        try {
            int[] arr = new int[10];
            System.out.println(arr[9001]);
        } catch (Exception e) {
            System.error.println(e);
            System.out.println("An error occured!");
        }
    }
}
