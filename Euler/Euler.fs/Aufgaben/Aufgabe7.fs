namespace Aufgaben

// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
//
// What is the 10 001st prime number?

[<Interface>]
type Loesung7 =

    abstract member Calculate : int -> int64

type Aufgabe7() =

    let numbers = new Numbers()

    let isPrime value =
        (numbers :> INumbers).IsPrime64 value

    let rec findNextPrime current =
        if isPrime current then current
        else findNextPrime (current+1L)

    let rec findPrime limit current =
//        Debug.writefn "%d: %d" limit current
        if limit=1 then current
        else
            let prime = findNextPrime (current+1L)
            let result = findPrime (limit-1) prime
            result

    interface Loesung7 with

        member this.Calculate limit =
            let result = findPrime limit 2L
            result

    interface Aufgabe with

        member this.Title = "Aufgabe 7"
        member this.Run() =
            let result = (this :> Loesung7).Calculate 10001
            result.ToString()

