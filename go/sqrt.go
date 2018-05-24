package main

import "fmt"


func sqrt (x float64, prec int) float64 {
    var sqrt_x, failure float64 = x, 1

    for failure > 1 / float64(prec) || failure < - 1 / float64(prec) {
        sqrt_x -= failure / (2 * sqrt_x)
        failure = sqrt_x * sqrt_x - x
    }
    return sqrt_x
}


func main (){
    var x float64 = 3
    var prec int = 100
    fmt.Println(sqrt(x,prec))
}
