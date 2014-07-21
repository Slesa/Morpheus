namespace Fractals

module Helpers =

    let measureTime f x =
        let timer = new System.Diagnostics.Stopwatch();
        timer.Start();
        try f x finally
        System.Diagnostics.Debug.WriteLine("Took %dms", timer.ElapsedMilliseconds);

    let ImageCentre (drawings: IFractalDrawing) = float drawings.Width / 2.0
