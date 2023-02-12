package main

import "fmt"

func btoi(b bool) int {
    if b { return 1 }
    return 0
}

func main() {
    var h uint
    fmt.Scanf("%d", &h)
    var s string
    fmt.Scanf("%s", &s)

    num := 1
    for i := 0; i < len(s); i++ {
        num = num * 2 + btoi(s[i] == 'R')
    }
    fmt.Println((1 << (h + 1)) - num)
}
