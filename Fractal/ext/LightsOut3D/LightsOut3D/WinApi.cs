using System;
using System.Runtime.InteropServices;

namespace LightsOut3D
{
  public static class WinApi
  {
    [StructLayout(LayoutKind.Sequential)]
    public struct RECT
    {
      public int Left;
      public int Top;
      public int Right;
      public int Bottom;
      public int Width
      {
        get { return Right - Left; }
      }
      public int Height
      {
        get { return Bottom - Top; }
      }
    }

    [DllImport("user32.dll")]
    public static extern bool GetClientRect(IntPtr hWnd, out RECT lpRect);

    [DllImport("user32.dll", SetLastError = true)]
    public static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

    [DllImport("user32.dll", SetLastError = true)]
    public static extern UInt32 GetWindowLong(IntPtr hWnd, int nIndex);

    [DllImport("user32.dll")]
    public static extern int SetWindowLong(IntPtr hWnd, int nIndex, UInt32 dwNewLong);

    public delegate bool EnumMonitorsDelegate(IntPtr hMonitor, IntPtr hdcMonitor, ref RECT lprcMonitor, IntPtr dwData);

    [DllImport("user32.dll")]
    public static extern bool EnumDisplayMonitors(IntPtr hdc, IntPtr lprcClip,
       EnumMonitorsDelegate lpfnEnum, IntPtr dwData);

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
    public struct MONITORINFOEX
    {
      public uint cbSize;
      public RECT rcMonitor;
      public RECT rcWork;
      public uint dwFlags; // 1 : MONITORINFOF_PRIMARY
      [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
      public string szDevice;

      public void Init()
      {
        this.cbSize = (uint)Marshal.SizeOf(this);
        this.szDevice = string.Empty;
      }
    }

    [DllImport("user32.dll", CharSet = CharSet.Auto)]
    public static extern bool GetMonitorInfo(IntPtr hMonitor, ref MONITORINFOEX lpmi);
  }

  public class Monitors
  {
    public static bool GetPrimaryMonitorRect(out WinApi.RECT rcPrimary)
    {
      WinApi.RECT rcResult = new WinApi.RECT();
      bool result = WinApi.EnumDisplayMonitors(IntPtr.Zero, IntPtr.Zero,
       delegate(IntPtr hMonitor, IntPtr hdcMonitor, ref WinApi.RECT lprcMonitor, IntPtr dwData)
       {
         var mi = new WinApi.MONITORINFOEX();
         mi.Init();
         bool success = WinApi.GetMonitorInfo(hMonitor, ref mi);
         if(success) {
           if((mi.dwFlags & 1) != 0) {
             rcResult = mi.rcMonitor;
           }
         }
         return true;
       }, IntPtr.Zero);
      rcPrimary = rcResult;
      return result;
    }

  }
}
