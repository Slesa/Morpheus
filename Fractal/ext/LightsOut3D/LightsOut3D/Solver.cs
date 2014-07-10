using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightsOut3D
{
  public class Solver
  {
    // Original solver by Norio Kato, http://www.ueda.info.waseda.ac.jp/~n-kato/lightsout/ 
    // Modified 2014 by Oliver Lau <ola@ct.de>
    // Ported to C# 2014 by Hajo Schulz <hos@ct.de>

    public static List<int[][]> Solve(int[][] puzzle, int states)
    {
      return new Solver(puzzle, states).Solved();
    }

    Solver(int[][] puzzle, int states)
    {
      cells = puzzle;
      N = cells.Length;
      M = cells[0].Length;
      nStates = states;
    }

    int[][] mat;
    int[] cols;
    int m;                   // count of rows of the matrix
    int n;                   // count of columns of the matrix
    int np;                  // count of columns of the enlarged matrix
    int r;                   // minimum rank of the matrix
    int maxr;                // maximum rank of the matrix
    int nStates = 2;         // number of states: 0 or 1
    int M, N; int[][] cells; // integer[N][M], current states of tiles

    int a(int i, int j)
    {
      return mat[i][cols[j]];
    }

    void setmat(int i, int j, int val)
    {
      mat[i][cols[j]] = modulate(val);
    }

    int modulate(int x)
    {
      if(x >= 0)
        return x % nStates;
      x = (-x) % nStates;
      if(x == 0)
        return 0;
      return nStates - x;
    }

    int gcd(int x, int y)
    {
      if(y == 0)
        return x;
      if(x == y)
        return x;
      if(x > y)
        x = x % y;
      while(x > 0) {
        y = y % x;
        if(y == 0)
          return x;
        x = x % y;
      }
      return y;
    }

    int invert(int value)
    {
      int a = 1;
      int b = 0;
      int c = 0;
      int d = 1;
      int x, y = nStates;
      if(value <= 1)
        return value;
      x = value;
      int seed = gcd(value, nStates);
      if(seed != 1)
        return 0;
      while(x > 1) {
        int tmp = y / x;
        y -= x * tmp;
        c -= a * tmp;
        d -= b * tmp;
        tmp = a; a = c; c = tmp;
        tmp = b; b = d; d = tmp;
        tmp = x; x = y; y = tmp;
      }
      return a;
    }

    void initMatrix()
    {
      maxr = Math.Min(m, n);
      mat = new int[n][];
      for(int x = 0; x < N; ++x) {
        for(int y = 0; y < M; ++y) {
          int i = y * N + x;
          var line = new int[n + 1];
          mat[i] = line;
          for(int j = 0; j < n; ++j)
            line[j] = 0;
          line[i] = 1;
          if(x > 0)
            line[i - 1] = 1;
          if(y > 0)
            line[i - N] = 1;
          if(x < N - 1)
            line[i + 1] = 1;
          if(y < M - 1)
            line[i + N] = 1;
        }
      }
      cols = new int[np];
      for(int j = 0; j < np; ++j)
        cols[j] = j;
    }

    private bool SolvedProblem(int goal)
    {
      int size = N * M, x, y;
      m = size;
      n = size;
      np = n + 1;
      initMatrix();
      for(x = 0; x < N; ++x)
        for(y = 0; y < M; ++y)
          mat[y * N + x][n] = modulate(goal - cells[x][y]);
      return sweep();
    }

    bool sweep()
    {
      for(r = 0; r < maxr; r++) {
        if(!sweepStep())
          return false;
        if(r == maxr)
          break;
      }
      return true;
    }

    bool sweepStep()
    {
      int i, j;
      bool finished = true;
      for(j = r; j < n; ++j) {
        for(i = r; i < m; ++i) {
          int aij = a(i, j);
          if(aij != 0)
            finished = false;
          int inv = invert(aij);
          if(inv != 0) {
            for(int jj = r; jj < np; ++jj)
              setmat(i, jj, a(i, jj) * inv);
            doBasicSweep(i, j);
            return true;
          }
        }
      }
      if(finished) {
        maxr = r;
        for(j = n; j < np; ++j)
          for(i = r; i < m; ++i)
            if(a(i, j) != 0)
              return false;
        return true;
      }
      return false;
    }

    void swap<T>(IList<T> array, int x, int y)
    {
      T tmp = array[x];
      array[x] = array[y];
      array[y] = tmp;
    }

    void doBasicSweep(int pivoti, int pivotj)
    {
      int i, j, air;
      if(r != pivoti)
        swap(mat, r, pivoti);
      if(r != pivotj)
        swap(cols, r, pivotj);
      for(i = 0; i < m; ++i) {
        if(i != r) {
          air = a(i, r);
          if(air != 0)
            for(j = r; j < np; ++j)
              setmat(i, j, a(i, j) - a(r, j) * air);
        }
      }
    }
    List<int[][]> Solved()
    {
      var solutions = new List<int[][]>();
      for(int goal = 0; goal < nStates; ++goal) {
        int[][] solution = new int[N][];
        for(int i = 0; i < N; ++i)
          solution[i] = new int[M];
        if(SolvedProblem(goal)) {
          int[] anscols = new int[n];
          for(int j = 0; j < n; ++j)
            anscols[cols[j]] = j;
          for(int x = 0; x < N; ++x) {
            for(int y = 0; y < M; ++y) {
              int j = anscols[y * N + x];
              solution[x][y] = a(j, n);
            }
          }
          solutions.Add(solution);
        }
      }
      return solutions;
    }

  }
}
