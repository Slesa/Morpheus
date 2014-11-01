namespace Aufgaben

open System.Globalization

// A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

// Find the largest palindrome made from the product of two 3-digit numbers.

[<Interface>]
type Loesung4 =
    abstract member IsPalindrom : string -> bool
    abstract member FindMaximum : int -> int -> string
    abstract member CalcMaximum : int -> int -> int seq

type Aufgabe4() =

    let reverse str =
        StringInfo.ParseCombiningCharacters(str)
        |> Array.rev
        |> Seq.map (fun i -> StringInfo.GetNextTextElement(str, i))
        |> String.concat ""

    interface Loesung4 with
        
        member this.CalcMaximum max min =
            seq {
                let sequence = seq { 
                    for y=max-1 downto min do for x=max-1 downto min do
//                        Debug.writefn "%d x %d" x y
                        yield x*y}
                let result = Seq.tryFind(fun a -> 
                    let valueStr = a.ToString()
                    let isPalindrom = (this :> Loesung4).IsPalindrom(valueStr)
                    isPalindrom) sequence
                match result with
                | None -> yield 0
                | Some a -> yield a}

        member this.IsPalindrom (text:string) =
            let splitPos = (int) text.Length/2
            let leftStr = text.Substring(0, splitPos)
            let rightStr = text.Substring (text.Length-splitPos)
            let reverse = reverse rightStr
            leftStr = reverse

        member this.FindMaximum max min =
            let result = (this :> Loesung4).CalcMaximum max min
            let max = Seq.max result
            max.ToString()

    interface Aufgabe with

        member this.Title = "Aufgabe 4"

        member this.Run() =
            (this :> Loesung4).FindMaximum 1000 900