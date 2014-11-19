namespace Aufgaben

// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
//
// Find the sum of all the primes below two million.

[<Interface>]
type Loesung10 =

    abstract member Calculate : int64 -> int64

type Aufgabe10() =

    let numbers = new Numbers()

    let findNextPrime current =
        (numbers :> INumbers).FindNextPrime64 current

    let rec findPrime limit current =
        let prime = findNextPrime current
        if prime>=limit then 0L
        else
            prime

    let sumPrimes limit current =
//         Debug.writefn "sum %d: %d" limit current
         let mutable sum = 0L
         let mutable prime = findPrime limit current
         while prime<>0L do
//            Debug.writefn "primt %d" prime
            sum <- (sum + prime)
            prime <- findPrime limit (prime+1L)
         sum
        
    interface Loesung10 with

        member this.Calculate limit =
            let result = sumPrimes limit 2L
            result

    interface Aufgabe with
        
        member this.Title = "Aufgabe 10"
        member this.Run() =
            let result = (this :> Loesung10).Calculate 2000000L
            result.ToString()
