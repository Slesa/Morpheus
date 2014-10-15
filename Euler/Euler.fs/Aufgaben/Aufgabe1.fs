namespace Aufgaben

// If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
// Find the sum of all the multiples of 3 or 5 below 1000.

[<Interface>]
type Loesung1 = 
    abstract member Calculate : int -> int

type Aufgabe1() = 

    let rec Calc result number limit : int =
        if limit = 0 then 
            0
        else
            let toAdd = 
                match (limit % number) with
                | 0 -> limit
                | _ -> 0
            toAdd + Calc result number (limit-1) 
         
    let Add number limit =
        Calc 0 number limit 

    interface Loesung1 with
        member this.Calculate limit = 
            let by5 = Add 5 (limit-1)
            let by3 = Add 3 (limit-1)
            let sub = Add 15 (limit-1)
            let result = by5 + by3 - sub
//            let result = by5 + by3 
            result

    interface Aufgabe with

        member this.Title = "Aufgabe 1"
        member this.Run() =
            let result = (this :> Loesung1).Calculate 1000
            result.ToString()


