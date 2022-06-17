package main
import "fmt"
import "math"

// Try computing the combinations without computing the factorials first.
func comb(n,r int) uint64 {
  var retval float64 = 1
  for ii:=r+1; ii<=n; ii++ {
    retval *= float64(ii)/float64(ii-r)
  }
  return uint64(math.Round(retval))
}

func main() {

  var overallmax float64 = 0

  for n:=1; n<=26; n++ {
    var cursum uint64 = 0
    for ii:=1; ii<n; ii++{
      for jj:=1; jj<=n-ii; jj++ {
        var curval uint64 = comb(n-jj,ii-1)
        cursum += curval
      }
    }
    cursum *= comb(26,n)
    overallmax = math.Max(overallmax,float64(cursum))
  }
  fmt.Println(uint64(overallmax))
}

