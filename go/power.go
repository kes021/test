package main

import (
    "fmt"
    "math"
)

func power (x float64, n int) float64 {
    if n == 0 {
        return 1
    }
    if n == 1 {
        return x
    }
    if n % 2 == 0 {
        return power(x * x, n / 2)
    }
    return x * power(x * x, n / 2)
}

func power_loop (x float64, n int) float64 {
    var y float64 = 1
    for i := 0; ; i++ {
        if j := i; j < n {
            y *= x;
        } else {
            break
        }
    }
    return y
}

func break_func (x float64) float64{
    var i int = 0
    for {
        i++
        if i < 10 {
            fmt.Println(i)
            continue
        }
        if i == 11 {
            break
        }
    }
    return float64(i)
}

func main (){
    var x float64 = math.Pi
    var n int = 3

    fmt.Println(power(x,n))
    fmt.Println(power_loop(x,n))
    fmt.Println(break_func(1))
}
