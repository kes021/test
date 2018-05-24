package main

import(
    "fmt"
)

func add(x int, y int) int {
    return x + y
}

func main() {
    fmt.Println("5 + 7 = ", add(5,7))
}
