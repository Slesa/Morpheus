using System;
using System.Threading;
using System.Drawing;

namespace FracMaster
{
    public class RenderResult : IAsyncResult
    {
        public delegate void RenderComplete(Bitmap bmp, int errorCode);
        public delegate void RenderStatus(float pcnt);

        private object _asyncstate = new object();
        private readonly WaitHandle _waitHandle = new AutoResetEvent(false);

        public RenderResult()
        {
            IsCompleted = false;
        }

        public object AsyncState
        {
            get
            {
                return _asyncstate;
            }
            set
            {
                _asyncstate = value;
            }
        }

        public WaitHandle AsyncWaitHandle
        {
            get
            {
                return _waitHandle;
            }
        }

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
