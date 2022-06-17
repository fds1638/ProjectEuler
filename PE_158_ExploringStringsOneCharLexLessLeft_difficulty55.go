package main
import "fmt"
import "math"
import "sync"

var wg sync.WaitGroup

// Try computing the combinations without computing the factorials first.
// Computing factorials first doesn't work because 26! overflows.
// I had uint64 in there when trying the factorials, so just left them when I switched to comb.
// I used channels in order to learn about them, even if this runs under a second even without them.

func comb(n,r int) uint64 {
  var retval float64 = 1
  for ii:=r+1; ii<=n; ii++ {
    retval *= float64(ii)/float64(ii-r)
  }
  return uint64(math.Round(retval))
}

// This function does the actual calculation for each value of n.
func with_n_letters(n int, c chan uint64) {
    defer wg.Done()     
    var cursum uint64 = 0
    for ii:=1; ii<n; ii++{
      for jj:=1; jj<=n-ii; jj++ {
        var curval uint64 = comb(n-jj,ii-1)
        cursum += curval
      }
    }
    cursum *= comb(26,n)
    c <- cursum
    // if n==26 { close(c) } // Originally had last channel created close it, but this leads to race conditions.
}

func main() {
  // Need to compute overall max, so set a variable for that.
  // Also, set up the channel with capacity 26 to prevent blocking and since we know we won't overfill the channel.
  var overallmax float64 = 0
  c := make(chan uint64,26)

  // For the 26 different possibilities for n, start the calculation.
  for n:=1; n<=26; n++ {
    wg.Add(1)
    go with_n_letters(n,c)
  }

  //close(c)

  var rc int = 0
  // Read from the channel as the results come in and re-calculate the overall max.
  for fromchannel := range c {
    overallmax = math.Max(overallmax,float64(fromchannel))
    rc += 1
    if rc==26 { close(c) } // Violates rule against receiver closing channel.
  }
  
  // This doesn't seem needed since waiting for last 
  wg.Wait() 

  // Print final result.
  fmt.Println(uint64(overallmax))
}

