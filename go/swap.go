package main
import ( "fmt" )

func swap (x, y string) string {
    return y + x
}


func main (){
    fmt.Println(swap("world", "hello")) 
}
