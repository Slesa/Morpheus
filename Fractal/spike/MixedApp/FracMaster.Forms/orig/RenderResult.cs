using System;
using System.Threading;
using System.Drawing;

namespace FracMaster
{
    public class RenderResult : IAsyncResult
    {
        public delegate void RenderComplete(Bitmap bmp, int errorCode);
        public delegate void RenderStatus(float pcnt);

        public RenderResult()
        {
            AsyncWaitHandle = new AutoResetEvent(false);
            AsyncState = new object();
            IsCompleted = false;
        }

        public object AsyncState { get; set; }

        public WaitHandle AsyncWaitHandle { get; private set; }

        public bool CompletedSynchronously
        {
            get
            {
                return false;
            }
        }

        public bool IsCompleted { get; set; }
    }
}
