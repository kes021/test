package main

import ("fmt")

func sum(y int) (x, z int) {
    x = y - 2
    z = y + 2
    return
}

func main(){
    var x, z int
    fmt.Println(x, z)
    for i := 0; i < 10; i++{
        x, z = sum(i)
        fmt.Printf("%2d, %2d, %2d\n",x, z, (x+z)/2)
    }
}
