package main

import "fmt"

type Vertex struct {
    X int
    Y int
}


func add (v_1, v_2 Vertex) Vertex{
    var v_sum Vertex
    v_sum.X = v_1.X + v_2.X
    v_sum.Y = v_1.Y + v_2.Y
    return v_sum
}

func mult (v_1, v_2 Vertex) Vertex{
    var v_prod Vertex
    v_prod.X = (v_1.X * v_2.X) - (v_1.Y * v_2.Y)
    v_prod.Y = (v_1.X * v_2.Y) + (v_1.Y * v_2.X)
    return v_prod
}


func main() {
    var v_1 = Vertex{1,2}
    var v_2 = Vertex{3,1}

    p_1 := &v_1
    p_2 := &v_2

    fmt.Println(add(v_1,*p_2))
    fmt.Println(mult(*p_1,v_2))
}
