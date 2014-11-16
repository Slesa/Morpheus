namespace Aufgaben

// The prime factors of 13195 are 5, 7, 13 and 29.
//
// What is the largest prime factor of the number 600851475143 ?

[<Interface>]
type Loesung3 =

    abstract member Calculate : int64 -> int64
    abstract member FindPrimes : int64 -> seq<int64>

type Aufgabe3() =

    let numbers = new Numbers();

    let isPrime value =
        (numbers :> INumbers).IsPrime64 value

    let findDivisors max =
        let limit = int64(sqrt(float(max))) 
        let sequence = seq { limit.. -1L .. 2L }
        let divisors = Seq.filter (fun a -> Number.Divides64 max a) sequence
        divisors

    let rec findPrimes (values : seq<int64>) : seq<int64> =
        let sequence = seq {
            for value in values do
                if isPrime value then 
                    yield value
                else
                   let divisors = findDivisors value
                   let primes = findPrimes divisors
                   yield! primes  }
        sequence
            
    interface Loesung3 with

        member this.FindPrimes value =
            let divisors = findDivisors value
            let result = findPrimes divisors
            Seq.distinct result

        member this.Calculate max =
            let divisors = findDivisors max
            let primes = findPrimes divisors
            let sortprimes = Seq.sort primes
//            let result = maximum (Seq.toList divisors)
            let result = Seq.last sortprimes
            result
            
                

    interface Aufgabe with
        
        member this.Title = "Aufgabe 3"
        member this.Run() =
            let result = (this :> Loesung3).Calculate 600851475143L
            result.ToString()

