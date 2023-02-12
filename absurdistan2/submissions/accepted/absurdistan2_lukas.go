package main

import "fmt"
import "math"

func main() {
    var n int
    fmt.Scanf("%d", &n)

    var p [150] float64
    var c [150][150] float64

    for i := 0; i <= n; i++ {
        c[i][0] = 1
        for j := 1; j <= i; j++ {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1]
        }

        p[i] = math.Pow(float64(i - 1), float64(i))
        for j := 2; j < i - 1; j++ {
            p[i] -= math.Pow(float64(i - j - 1), float64(i - j)) * c[i - 1][j - 1] * p[j]
        }
    }

    fmt.Printf("%.9f\n", (p[n] / math.Pow(float64(n - 1), float64(n))))
}
