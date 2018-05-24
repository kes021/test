package main

import (
    "fmt"
    "math"
)

func main (){

    const i = 42
    var f float64 =42
    var u uint =uint( f + math.Pi)
    fmt.Printf("The type of u is %T\n", u)
    fmt.Println(i, f, u)
    fmt.Println( float64(i) + math.Pi)
    i++
}
