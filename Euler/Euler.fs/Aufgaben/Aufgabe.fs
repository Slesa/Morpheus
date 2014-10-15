namespace Aufgaben

[<Interface>]
type Aufgabe = 
    abstract member Title : string
    abstract member Run : unit -> string