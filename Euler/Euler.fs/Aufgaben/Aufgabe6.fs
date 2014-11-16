namespace Aufgaben

// The sum of the squares of the first ten natural numbers is,

// 1^2 + 2^2 + ... + 10^2 = 385
// The square of the sum of the first ten natural numbers is,

// (1 + 2 + ... + 10)^2 = 552 = 3025
// Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

// Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

[<Interface>]
type Loesung6 =

    abstract member Calculate : int -> int

type Aufgabe6() =

    let square a = a*a
    let sum max = (max*(max+1))/2

    let rec sumsquares max =
        match max with
        | 1 -> 1
        | a -> (square a) + sumsquares (a-1)

    let squaresum max = 
        square (sum max)

    interface Loesung6 with

        member this.Calculate max =
            squaresum max - sumsquares max

    interface Aufgabe with
        member this.Title = "Aufgabe 6"
        member this.Run() =
            let result = (this :> Loesung6).Calculate 100
            result.ToString()

                