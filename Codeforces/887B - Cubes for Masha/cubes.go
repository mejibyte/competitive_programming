package main

import (
  "fmt"
)

func search(formed, usedMask int32, cubes [][]int32, found map[int32]bool) {
  found[formed] = true
  for i := uint(0); i < uint(len(cubes)); i++ {
    if (usedMask & (1 << i)) != 0 {
      continue
    }

    for k := int32(0); k < 6; k++ {
      search(formed * 10 + cubes[i][k], usedMask | (1 << i), cubes, found)
    }
  }
}


func main() {
  var n int
  fmt.Scanf("%d\n", &n)
  cubes := make([][]int32, n)

  for i := 0; i < n; i++ {
    cubes[i] = make([]int32, 6)
    for k := 0; k < 6; k++ {
      if _, err := fmt.Scanf("%d", &cubes[i][k]); err != nil {
        fmt.Printf("failed to read: %q\n", err)
      }
    }
    fmt.Scanf("\n") // This works in Go 1.8 but breaks in 1.9 for some fucking reason.
  }

  found := make(map[int32]bool)
  search(0, 0, cubes, found)

  max := int32(0)
  for i := int32(1); found[i]; i++ {
    max = i
  }
  fmt.Printf("%d\n", max)
}
