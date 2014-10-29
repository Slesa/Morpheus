namespace Aufgaben

module Debug = 
    open System.Diagnostics
    let writef fmt = Printf.ksprintf Debug.Write fmt
    let writefn fmt = Printf.ksprintf Debug.WriteLine fmt

// In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:
//
// 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
// It is possible to make £2 in the following way:
//
// 1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
// How many different ways can £2 be made using any number of coins?

[<Interface>]
type Loesung31 =
    abstract member Calculate : int -> int list -> string seq

type Aufgabe31() =

    let rec dispense amount coins : 's seq =
        match coins with
        | [] -> Seq.empty
        | [a] -> 
            let count = (int) (amount / a)
            Debug.writefn "Single: %d x %d = %d" count a amount
//            let newAmount = amount - (count * a)
            let line = sprintf "%d x %d" count a
            match count with
            | 0 -> Seq.empty
            | _ -> 
                Debug.writefn "Line: %s" line
                seq { yield line }
//                yield List.append changes line
//                dispense newAmount tail
        | head :: tail -> 
            let count = (int) (amount / head)
            Debug.writefn "List: %d : %d" count amount
            let line = sprintf "%d x %d" count head
//            let line = sprintf "%d x %d" count head
//                let list = List.append changes line
                
            seq { 
//                Debug.writefn "%s" line
                yield line

                let otherCoins = dispense amount tail
                yield! otherCoins

                for i=0 to count-1 do
                    let newAmount = amount - (i * head)
                    Debug.writefn "Loop: %d : %d" i newAmount
                    let newChanges = dispense newAmount tail 
                    yield! newChanges }


    interface Loesung31 with

        member this.Calculate amount coins =
            dispense amount coins

    interface Aufgabe with

        member this.Title = "Aufgabe 31"
        member this.Run() = 
            let coins = [ 200; 100; 50; 20; 10; 5; 2; 1; ];
            let result = (this :> Loesung31).Calculate 200 coins
            result.ToString()
            