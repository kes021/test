package main

import "fmt"


func main (){

    var a [10]int
    for i:=0; i < 10; i++{
        a[i] = 2*i
    }
    for i:=0; i < 10; i++{
        fmt.Println(a[i])
    }

    var b [2]string
    b[0] = "Fuck"
    b[1] = "You!"

    fmt.Printf("%s ",b[0])
    fmt.Printf("%s\n",b[1])
    fmt.Println(b)
}
