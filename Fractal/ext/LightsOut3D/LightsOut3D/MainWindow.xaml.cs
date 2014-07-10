using System;
using System.Collections.Generic;
using System.Reflection;
using System.Windows;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Threading;

namespace LightsOut3D
{
  /// <summary>
  /// Interaktionslogik für MainWindow.xaml
  /// </summary>
  public partial class MainWindow : Window
  {
    const double flipDuration = 500; // Milliseconds
    const int flipPause = 200;
    const int nImages = 12;

    public MainWindow()
    {
      InitializeComponent();

      _random = new Random();
      
      _clickTimer = new DispatcherTimer();
      _clickTimer.Tick += clickTimer_Tick;
      _clickTimer.Interval = TimeSpan.FromMilliseconds(flipDuration + flipPause);
      _finalTimer = new DispatcherTimer();
      _finalTimer.Tick += finalTimer_Tick;
      _watchDogTimer = new DispatcherTimer();
      _watchDogTimer.Tick += _watchDog_Tick;
      _watchDogTimer.Interval = TimeSpan.FromMilliseconds(500);

      InitImageSwapper();
      _idxFront = NextImageIndex();
      _imgFront = GetImage(_idxFront);
      _idxBack = NextImageIndex(_idxFront);
      _imgBack = GetImage(_idxBack);

      _allowInteractive = Properties.Settings.Default.AllowInteractive;
      int difficulty = Properties.Settings.Default.Difficulty;

      if(_allowInteractive) {
        switch(difficulty) {
          case 0: // Leicht
            mosaicRows = 3;
            mosaicColumns = 4;
            break;
          case 1: // Mittel
            mosaicRows = 4;
            mosaicColumns = 5;
            break;
          // Schwer ist Standard
        }
      }
      _isPreview = App.TheApp.Mode == App.RunMode.Preview;
      if(!_isPreview) {
        this.Left = SystemParameters.VirtualScreenLeft;
        this.Top = SystemParameters.VirtualScreenTop;
        this.Width = SystemParameters.VirtualScreenWidth;
        this.Height = SystemParameters.VirtualScreenHeight;
        // Auf Multi-Monitor-Systemen füllt das schwarze Fenster den vollen Desktop aus,
        // die Animation spielt aber nur auf dem primären Display.
        WinApi.RECT rcPrimary;
        if(Monitors.GetPrimaryMonitorRect(out rcPrimary)) {
          viewport3d.Margin = new Thickness(
            rcPrimary.Left - SystemParameters.VirtualScreenLeft,
            rcPrimary.Top - SystemParameters.VirtualScreenTop,
            SystemParameters.VirtualScreenWidth + SystemParameters.VirtualScreenLeft - rcPrimary.Right,
            SystemParameters.VirtualScreenHeight + SystemParameters.VirtualScreenTop - rcPrimary.Bottom);
        }
        this.Topmost = true;
        this.Cursor = Cursors.None;
      }
      else {
        mosaicRows = 3;
        mosaicColumns = 4;
        _allowInteractive = false;

        WinApi.RECT rcParent;
        WinApi.GetClientRect(App.TheApp.ParentHandle, out rcParent);
        this.Left = rcParent.Left;
        this.Top = rcParent.Top;
        this.Width = rcParent.Width;
        this.Height = rcParent.Height;
      }
    }

    Random _random;
    DispatcherTimer _clickTimer, _finalTimer, _watchDogTimer;
    int _idxFront, _idxBack;
    BitmapImage _imgFront, _imgBack;
    BitmapImage[] _images = new BitmapImage[12];
    int[] _seen;
    bool _allowInteractive = false;
    bool _isPreview = false;

    int mosaicRows = 7;
    int mosaicColumns = 10;

    private void Window_Loaded(object sender, RoutedEventArgs e)
    {
      BuildGrid();
      if(_isPreview) {
        // Dieses Fenster zum Child des Bildschirmschoner-Dialogs machen
        WindowInteropHelper wih = new WindowInteropHelper(this);
        WinApi.SetParent(wih.Handle, App.TheApp.ParentHandle);
        WinApi.SetWindowLong(wih.Handle,
          -16,                                    // GWL_STYLE
          WinApi.GetWindowLong(wih.Handle, -16)
            | 0x40000000);                        // WS_CHILD
      }

      CalcRoute();
      PlayRoute();
    }

    Point _lastMousePos;
    DateTime _lastInteraction;
    bool _isInteractive = false;

    private void Window_KeyDown(object sender, KeyEventArgs e)
    {
      if(_isPreview)
        return;
      if(!_allowInteractive || e.Key == Key.Escape)
        this.Close();
      _lastInteraction = DateTime.Now;
      if(!_isInteractive)
        GoInteractive();
    }

    private void Window_MouseMove(object sender, MouseEventArgs e)
    {
      if(_isPreview)
        return;
      _lastInteraction = DateTime.Now;
      var pos = e.GetPosition(this);
      // Versehentliches Ruckeln um 1 oder 2 Pixel unterdrücken
      if(_lastMousePos.X != 0 && _lastMousePos.Y != 0 &&
        (Math.Abs(pos.X - _lastMousePos.X) > 3 || Math.Abs(pos.Y - _lastMousePos.Y) > 3)) {
        if(!_allowInteractive)
          this.Close();
        if(!_isInteractive) {
          GoInteractive();
        }
      }
      _lastMousePos = pos;
    }

    private void Window_MouseDown(object sender, MouseButtonEventArgs e)
    {
      if(_isPreview)
        return;
      if(!_allowInteractive)
        this.Close();
      _lastInteraction = DateTime.Now;
      if(!_isInteractive) {
        GoInteractive();
      }
    }

    private void viewport3d_SizeChanged(object sender, SizeChangedEventArgs e)
    {
      if(camera == null)
        return;
      double aspectImg = (double)mosaicRows / mosaicColumns;
      double aspectWnd = viewport3d.RenderSize.Height / viewport3d.RenderSize.Width;
      double camZ = camera.Position.Z;
      double containerWidth = mosaicColumns / 2.0d;
      double containerHeight = mosaicRows / 2.0d;
      if(aspectWnd >= aspectImg) {
        camera.FieldOfView = 2 * Rad2Deg(Math.Atan(containerWidth / camZ));
      }
      else {
        camera.FieldOfView = 2 * Rad2Deg(Math.Atan((containerHeight / aspectWnd) / camZ));
      }
      _lastMousePos = new Point(0, 0);
    }

    private void InitImageSwapper()
    {
      _images = new BitmapImage[nImages];

      _seen = new int[nImages];
      for(int i = 0; i < nImages; i++) {
        _seen[i] = 1;
      }
    }

    private int NextImageIndex(int exclude = -1)
    {
      int i;
      int sum = 0;
      int maxSeen = -1;
      for(i = 0; i < nImages; i++) {
        sum += _seen[i];
        if(_seen[i] > maxSeen)
          maxSeen = _seen[i];
      }
      int rnd = _random.Next(nImages * (maxSeen + 1) - sum);
      sum = 0;
      int idx = -1;
      for(i = 0; i < nImages; i++) {
        sum += maxSeen - _seen[i] + 1;
        if(sum > rnd) {
          idx = i;
          break;
        }
      }
      if(idx == exclude)
        ++idx;
      if(idx >= nImages)
        idx = 0;
      ++_seen[idx];
      return idx;
    }

    private BitmapImage GetImage(int idx)
    {
      if(_images[idx] == null) {
        string path = string.Format("Images/img{0:D2}.jpg", idx + 1);
        string appName = Assembly.GetCallingAssembly().GetName().Name;
        Uri uri = new Uri(@"pack://application:,,,/" + appName + ";component/" + path, UriKind.Absolute);
        _images[idx] = new BitmapImage(uri);
      }
      return _images[idx];
    }

    ModelUIElement3D[,] _tileMap;
    bool[,] _flipped;

    private void BuildGrid()
    {
      _tileMap = new ModelUIElement3D[mosaicRows, mosaicColumns];
      _flipped = new bool[mosaicRows, mosaicColumns];
      double tileWidth = _imgFront.PixelWidth / mosaicColumns;
      double tileHeight = _imgFront.PixelHeight / mosaicRows;
      for(int c = 0; c < mosaicColumns; c++) {
        for(int r = 0; r < mosaicRows; r++) {
          var newTile = new ModelUIElement3D();
          var model = new GeometryModel3D();
          var geometry = new MeshGeometry3D();

          // geometry.Positions
          var vertices = new Point3DCollection(4);
          double x0 = c - mosaicColumns / 2.0d;
          double x1 = x0 + 0.995;
          double y0 = r - mosaicRows / 2.0d;
          double y1 = y0 + 0.995;
          vertices.Add(new Point3D(x0, y0, 0));
          vertices.Add(new Point3D(x0, y1, 0));
          vertices.Add(new Point3D(x1, y0, 0));
          vertices.Add(new Point3D(x1, y1, 0));
          geometry.Positions = vertices;

          // geometry.TextureCoordinates
          var texCoords = new PointCollection(4);
          texCoords.Add(new Point(0, 1));
          texCoords.Add(new Point(0, 0));
          texCoords.Add(new Point(1, 1));
          texCoords.Add(new Point(1, 0));
          geometry.TextureCoordinates = texCoords;

          // geometry.TriangleIndices
          geometry.TriangleIndices = new Int32Collection() { 0, 2, 1, 2, 3, 1 };
          model.Geometry = geometry;

          // model.Material
          var tileArea = new Int32Rect((int)(c * tileWidth), (int)((mosaicRows - r - 1) * tileHeight), (int)(tileWidth), (int)(tileHeight));
          CroppedBitmap cb = new CroppedBitmap(_imgFront, tileArea);
          var brush = new ImageBrush(cb);
          model.Material = new DiffuseMaterial(brush);

          // model.BackMaterial
          cb = new CroppedBitmap(_imgBack, tileArea);
          brush = new ImageBrush(cb);
          brush.RelativeTransform = new ScaleTransform(-1, 1, 0.5, 0.5);
          model.BackMaterial = new DiffuseMaterial(brush);

          newTile.Model = model;
          newTile.MouseDown += Tile_MouseDown;
          newTile.MouseUp += Tile_MouseUp;
          newTile.Transform = new RotateTransform3D(new AxisAngleRotation3D(new Vector3D(0, 1, 0), 0), (x0 + x1) / 2, (y0 + y1) / 2, 0);
          tileContainer.Children.Add(newTile);
          _tileMap[r, c] = newTile;
          _flipped[r, c] = false;
        }
      }
    }

    private void LoadMaterial(bool front)
    {
      BitmapImage img = front ? _imgFront : _imgBack;
      double tileWidth = img.PixelWidth / mosaicColumns;
      double tileHeight = img.PixelHeight / mosaicRows;
      for(int c = 0; c < mosaicColumns; c++) {
        for(int r = 0; r < mosaicRows; r++) {
          var tile = _tileMap[r, c];
          var model = tile.Model as GeometryModel3D;
          var geometry = model.Geometry as MeshGeometry3D;

          var tileArea = new Int32Rect((int)(c * tileWidth), (int)((mosaicRows - r - 1) * tileHeight), (int)(tileWidth), (int)(tileHeight));
          CroppedBitmap cb = new CroppedBitmap(img, tileArea);
          var brush = new ImageBrush(cb);
          if(front) {
            model.Material = new DiffuseMaterial(brush);
          }
          else {
            brush.RelativeTransform = new ScaleTransform(-1, 1, 0.5, 0.5);
            model.BackMaterial = new DiffuseMaterial(brush);
          }
        }
      }
    }

    private Point TilePos(ModelUIElement3D elem)
    {
      for(int r = 0; r < mosaicRows; r++) {
        for(int c = 0; c < mosaicColumns; c++) {
          if(_tileMap[r, c] == elem) {
            return new Point(c, r);
          }
        }
      }
      throw new ArgumentException("Elem not found in map.");
    }

    private void GoInteractive()
    {
      this.Cursor = Cursors.Arrow;
      _clickTimer.Stop();
      _finalTimer.Stop();
      // btnSolve.Visibility = Visibility.Visible;
      _lastInteraction = DateTime.Now;
      _watchDogTimer.Start();
      _isInteractive = true;
    }

    private void LeaveInteractive()
    {
      this.Cursor = Cursors.None;
      _watchDogTimer.Stop();
      _isInteractive = false;
      CalcRoute();
      PlayRoute();
    }

    ModelUIElement3D _clickedTile = null;

    private void Tile_MouseDown(object sender, MouseButtonEventArgs e)
    {
      if(_isPreview)
        return;
      if(!_allowInteractive)
        this.Close();
      _lastInteraction = DateTime.Now;
      if(!_isInteractive) {
        GoInteractive();
      }
      else {
        var clicked = sender as ModelUIElement3D;
        if(clicked != null) {
          _clickedTile = clicked;
        }
      }
    }

    private void Tile_MouseUp(object sender, MouseButtonEventArgs e)
    {
      if(_isPreview)
        return;
      if(!_allowInteractive)
        this.Close();
      _lastInteraction = DateTime.Now;
      var clicked = sender as ModelUIElement3D;
      if(clicked != null && clicked == _clickedTile) {
        _clickTimer.Stop();
        _finalTimer.Stop();
        FlipTiles(clicked);
        _clickedTile = null;
        if(IsSolved())
          PlayFinal(1);
      }
    }

    private void FlipTiles(ModelUIElement3D centerTile)
    {
      Point pos = TilePos(centerTile);
      int c = (int)pos.X;
      int r = (int)pos.Y;
      FlipTile(r, c);
      if(c > 0)
        FlipTile(r, c - 1);
      if(r > 0)
        FlipTile(r - 1, c);
      if(c < mosaicColumns - 1)
        FlipTile(r, c + 1);
      if(r < mosaicRows - 1)
        FlipTile(r + 1, c);
    }

    private void FlipAll()
    {
      for(int r = 0; r < mosaicRows; r++) {
        for(int c = 0; c < mosaicColumns; c++) {
          FlipTile(r, c);
        }
      }
    }

    private void FlipTile(int row, int column)
    {
      var tile = _tileMap[row, column];
      var rot = tile.Transform as RotateTransform3D;
      if(rot != null) {
        var anim = new Rotation3DAnimationUsingKeyFrames();
        if(_flipped[row, column]) {
          anim.KeyFrames.Add(
            new SplineRotation3DKeyFrame(
              new AxisAngleRotation3D(new Vector3D(0, 1, 0), 270),
              KeyTime.FromTimeSpan(TimeSpan.FromMilliseconds(flipDuration / 2)),
              new KeySpline(0.3, 0.0, 1.0, 0.7)));
          anim.KeyFrames.Add(
            new SplineRotation3DKeyFrame(
              new AxisAngleRotation3D(new Vector3D(0, 1, 0), 360),
              KeyTime.FromTimeSpan(TimeSpan.FromMilliseconds(flipDuration)),
              new KeySpline(0.0, 0.3, 0.7, 1.0)));
          _flipped[row, column] = false;
        }
        else {
          anim.KeyFrames.Add(
            new SplineRotation3DKeyFrame(
              new AxisAngleRotation3D(new Vector3D(0, 1, 0), 90),
              KeyTime.FromTimeSpan(TimeSpan.FromMilliseconds(flipDuration / 2)),
              new KeySpline(0.3, 0.0, 1.0, 0.7)));
          anim.KeyFrames.Add(
            new SplineRotation3DKeyFrame(
              new AxisAngleRotation3D(new Vector3D(0, 1, 0), 180),
              KeyTime.FromTimeSpan(TimeSpan.FromMilliseconds(flipDuration)),
              new KeySpline(0.0, 0.3, 0.7, 1.0)));
          _flipped[row, column] = true;
        }
        rot.BeginAnimation(RotateTransform3D.RotationProperty, anim);
      }
    }

    private bool IsSolved()
    {
      bool target = _flipped[0, 0];
      for(int r = 0; r < mosaicRows; r++) {
        for(int c = 0; c < mosaicColumns; c++) {
          if(_flipped[r, c] != target)
            return false;
        }
      }
      return true;
    }

    static double Rad2Deg(double rad)
    {
      return rad * 180 / Math.PI;
    }

    List<Point>[] _routes = new List<Point>[2];
    int _routeIdx;

    private void CalcRoute()
    {
      int[][] solverMatrix = new int[mosaicColumns][];
      for(int c = 0; c < mosaicColumns; ++c) {
        solverMatrix[c] = new int[mosaicRows];
        for(int r = 0; r < mosaicRows; r++) {
          solverMatrix[c][r] = _flipped[r, c] ? 1 : 0;
        }
      }
      var result = Solver.Solve(solverMatrix, 2);
      for(int l = 0; l < 2; ++l) {
        _routes[l] = new List<Point>();
        for(int r = 0; r < mosaicRows; ++r) {
          for(int c = 0; c < mosaicColumns; ++c) {
            if(result[l][c][r] != 0)
              _routes[l].Add(new Point(c, r));
          }
        }
      }
      if(_routes[0].Count == 0) {
        _routeIdx = 1;
      }
      else if(_routes[1].Count == 0 || _routes[0].Count <= _routes[1].Count) {
        _routeIdx = 0;
      }
      else {
        _routeIdx = 1;
      }
    }

    void clickTimer_Tick(object sender, EventArgs e)
    {
      var route = _routes[_routeIdx];
      Point p = route[_random.Next(route.Count)];
      FlipTiles(_tileMap[(int)p.Y, (int)p.X]);
      route.Remove(p);
      if(route.Count == 0) {
        _clickTimer.Stop();
        PlayFinal(3);
      }
    }

    private void PlayRoute()
    {
      _clickTimer.Start();
    }

    int _finalPhase;

    private void PlayFinal(int wait)
    {
      _finalPhase = 0;
      _finalTimer.Interval = TimeSpan.FromMilliseconds(wait * flipDuration);
      _finalTimer.Start();
    }

    private void finalTimer_Tick(object sender, EventArgs e)
    {
      switch(_finalPhase) {
        case 0:
          _finalTimer.Stop();
          FlipAll();
          _finalPhase = 1;
          _finalTimer.Interval = TimeSpan.FromMilliseconds(flipDuration + flipPause);
          _finalTimer.Start();
          break;
        case 1:
          _finalTimer.Stop();
          FlipAll();
          _finalPhase = 2;
          _finalTimer.Interval = TimeSpan.FromMilliseconds(3 * flipDuration);
          _finalTimer.Start();
          break;
        case 2:
          _finalTimer.Stop();
          bool flipped = _flipped[0, 0];
          if(flipped) {
            _idxFront = NextImageIndex(_idxBack);
            _imgFront = GetImage(_idxFront);
          }
          else {
            _idxBack = NextImageIndex(_idxFront);
            _imgBack = GetImage(_idxBack);
          }
          LoadMaterial(flipped);
          if(!_isInteractive) {
            CalcRoute();
            PlayRoute();
          }
          break;
      }
    }

    private void _watchDog_Tick(object sender, EventArgs e)
    {
      if((DateTime.Now - _lastInteraction).TotalSeconds > 10)
        LeaveInteractive();
    }


  }
}
