namespace Aufgaben

// If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

// If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

// NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. 
// The use of "and" when writing out numbers is in compliance with British usage.

[<Interface>]
type Loesung17 =
    abstract GetLineFor : int -> string
    abstract GetLinesUntil : int -> seq<string>
    abstract member CalculateFor : int -> int
    abstract member CalculateUntil : int -> int

type Aufgabe17() =

    //               3      3       5       4       4       3       5        5       4                                            = 36
    let einer = [| "one"; "two"; "three"; "four"; "five"; "six"; "seven"; "eight"; "nine"; |];
    //                3       6         6           8           8          7          7          9             8           8      = 70
    let zehner = [| "ten"; "eleven"; "twelve"; "thirteen"; "fourteen"; "fifteen"; "sixteen"; "seventeen"; "eighteen"; "nineteen" |];
    //                    6         6         6         5        5         7          6         6                                 = 46
    let zwanziger = [| "twenty"; "thirty"; "forty"; "fifty"; "sixty"; "seventy"; "eighty"; "ninety" |];

    let GetEinerLineFor value =
        let calcValue = value % 100
        if calcValue>=10 && calcValue<20 then ""
        else
        let index = value % 10;
        if index.Equals(0) then ""
        else
            einer.[index-1] 

    let GetZehnerLineFor value =
        let calcValue = value % 100
        if calcValue<10 then ""
        else
        match calcValue with
        | x when x>=10 && x<20 -> 
            let index = calcValue % 10
            zehner.[index]
        | _ ->
            let index = (calcValue / 10) - 2
            zwanziger.[index]

    let GetHunderterLineFor value =
        let calcValue = value % 1000
        if calcValue<100 then ""
        else
            let index = calcValue / 100
            let result = einer.[index-1] + " hundred"
            match calcValue % 100 with
            | 0 -> result
            | _ -> result + " and"

    let GetTausenderLineFor value =
        if value<1000 then ""
        else
            let index = value / 1000
            let result = einer.[index-1] + " thousand"
            result


    let AppendText buffer text =
        let bufferLen = String.length buffer
        let textLen = String.length text
        if bufferLen.Equals 0 || textLen.Equals 0 then
            buffer + text
        else
            buffer + " " + text
            
    interface Loesung17 with

        member this.GetLineFor value = 
            let tausender = GetTausenderLineFor value
            let hunderter = GetHunderterLineFor value
            let zehner = GetZehnerLineFor value
            let einer = GetEinerLineFor value
            AppendText tausender (AppendText hunderter (AppendText zehner einer))

        member this.GetLinesUntil limit =
            let values = Array.init 
            seq { for value in 1..limit do yield (this :> Loesung17).GetLineFor value }

        member this.CalculateFor value =
            let line = (this :> Loesung17).GetLineFor value
            let result = line.Replace(" ", "").Length
            result

        member this.CalculateUntil limit =
            let lines = (this :> Loesung17).GetLinesUntil limit
            let sumSeq sequence = Seq.fold (fun acc (elem:string) -> acc + elem.Replace(" ", "").Length) 0 sequence
            let result = lines |> sumSeq
            result
            
    interface Aufgabe with

        member this.Title = "Aufgabe 17"

        member this.Run() =
            let result = (this :> Loesung17).CalculateUntil 1000
            result.ToString()
