namespace Aufgaben

module Debug = 
    open System.Diagnostics
    let writef fmt = Printf.ksprintf Debug.Write fmt
    let writefn fmt = Printf.ksprintf Debug.WriteLine fmt
