package main

import "fmt"

func test (p *int) *int {
    *p *= 2
    return p
}


func main () {
    var p *int
    var i int = 8
    p = &i
    p = test(p)
    fmt.Println(i)
}
