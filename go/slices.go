package main

import "fmt"

func printSlice(s []int) {
    fmt.Printf("len=%d cap=%d %v\n", len(s), cap(s), s)
    if s == nil{
        fmt.Printf("This is nil! \n")
    }
}

func main() {
    var q []int

    printSlice(q)
}
