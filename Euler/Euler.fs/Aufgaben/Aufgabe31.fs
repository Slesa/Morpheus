namespace Aufgaben

// In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:
//
// 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
// It is possible to make £2 in the following way:
//
// 1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
// How many different ways can £2 be made using any number of coins?

[<Interface>]
type Loesung31 =
    abstract member Calculate : int -> int list -> int

type Aufgabe31() =

    let rec dispense amount coins : int =
        let result = match coins with
        | [] -> 1
        | head :: tail -> 
            let mutable sum = 0
            let count = (int) (amount / head)
            for i=0 to count do
                let newAmount = amount - (count * head)
                sum = sum + (dispense newAmount tail)
            sum
        result

    interface Loesung31 with
        member this.Calculate amount coins =
            dispense amount coins

    interface Aufgabe with

        member this.Title = "Aufgabe 31"
        member this.Run() = 
            let coins = [ 200; 100; 50; 20; 10; 5; 2; ];
            let result = (this :> Loesung31).Calculate 200 coins
            result.ToString()
            