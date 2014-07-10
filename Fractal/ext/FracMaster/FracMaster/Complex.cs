using System;

namespace FracMaster
{	 
    public struct Complex : IComparable 
    {
        static readonly private double halfOfRoot2 = 0.5 * Math.Sqrt(2);
        static readonly public Complex Zero = new Complex(0, 0);
        static readonly public Complex I = new Complex(0, 1);
        static readonly public Complex MaxValue = new Complex(double.MaxValue, double.MaxValue);
        static readonly public Complex MinValue = new Complex(double.MinValue, double.MinValue);	  
      
        public double Re;         
        public double Im;
               
        public Complex(double real, double imaginary)
        {
            this.Re = (double)real;
            this.Im = (double)imaginary;
        }

        public Complex(Complex c)
        {
            this.Re = c.Re;
            this.Im = c.Im;
        }

        static public Complex CreateFromRealAndImaginary(double re, double im)
        {
            Complex c;
            c.Re = (double)re;
            c.Im = (double)im;
            return c;
        }
         
        static public Complex CreateFromModulusAndArgument(double mod, double arg)
        {
            Complex c;
            c.Re = (double)(mod * Math.Cos(arg));
            c.Im = (double)(mod * Math.Sin(arg));
            return c;
        }
    
        static public Complex Sqrt(Complex c)
        {
            double x = c.Re;
            double y = c.Im;
            double modulus = Math.Sqrt(x * x + y * y);

            int sign = (y < 0) ? -1 : 1;

            c.Re = (double)(halfOfRoot2 * Math.Sqrt(modulus + x));
            c.Im = (double)(halfOfRoot2 * sign * Math.Sqrt(modulus - x));

            return c;
        }
                
        static public Complex Pow(Complex c, double exponent)
        {
            double x = c.Re;
            double y = c.Im;

            double modulus = Math.Pow(x * x + y * y, exponent * 0.5);
            double argument = Math.Atan2(y, x) * exponent;

            c.Re = (double)(modulus * System.Math.Cos(argument));
            c.Im = (double)(modulus * System.Math.Sin(argument));

            return c;
        }
            
        public double GetModulus() 
        {
            double	x	= this.Re;
            double	y	= this.Im;
            return	(double) Math.Sqrt( x*x + y*y );
        }
         
        public double GetModulusSquared() 
        {			 
            return (double)this.Re * this.Re + this.Im * this.Im;
        }
     
        public double GetArgument() 
        {
            return (double) Math.Atan2( this.Im, this.Re );
        }
         
        public Complex GetConjugate() 
        {
            return CreateFromRealAndImaginary( this.Re, -this.Im );
        }
      
        public void Normalize() 
        {
            double	modulus = this.GetModulus();
            if( modulus == 0 ) 
            {
                throw new DivideByZeroException();
            }
            this.Re	= (double)( this.Re / modulus );
            this.Im	= (double)( this.Im / modulus );
        }
      
        public static explicit operator Complex ( double d ) 
        {
            Complex c;
            c.Re	= (double) d;
            c.Im	= (double) 0;
            return c;
        }
         
        public static explicit operator double ( Complex c ) 
        {
            return (double) c.Re;
        }
             
        public static bool	operator==( Complex a, Complex b ) 
        {
            return	( a.Re == b.Re ) && ( a.Im == b.Im );
        }
         
        public static bool	operator!=( Complex a, Complex b )
        {
            return	( a.Re != b.Re ) || ( a.Im != b.Im );
        }
     
        public override int	GetHashCode() 
        {
            return	( this.Re.GetHashCode() ^ this.Im.GetHashCode() );
        }
 
        public override bool Equals( object o )
        {
            if( o is Complex ) 
            {
                Complex c = (Complex) o;
                return  ( this == c );
            }
            return	false;
        }
         
        public int	CompareTo( object o ) 
        {
            if( o == null ) 
            {
                return 1; 
            }
            else if( o is Complex ) 
            {
                return	this.GetModulus().CompareTo( ((Complex)o).GetModulus() );
            }
            else if (o is double) 
            {
                return	this.GetModulus().CompareTo( (double)o );
            }
            else if (o is float) 
            {
                return	this.GetModulus().CompareTo( (float)o );
            }
            throw new ArgumentException();
        }
         
        public static Complex operator+( Complex a ) 
        {
            return a;
        }

        public static Complex operator +(Complex a, double f)
        {
            a.Re = (double)(a.Re + f);
            return a;
        }

        public static Complex operator +(double f, Complex a)
        {
            a.Re = (double)(a.Re + f);
            return a;
        }

        public static Complex operator +(Complex a, Complex b)
        {
            a.Re = a.Re + b.Re;
            a.Im = a.Im + b.Im;
            return a;
        }

        public static Complex operator-( Complex a ) 
        {
            a.Re	= -a.Re;
            a.Im	= -a.Im;
            return a;
        }
     
        public static Complex operator-( Complex a, double f ) 
        {
            a.Re	= (double)( a.Re - f );
            return a;
        }
 
        public static Complex operator-( double f, Complex a ) 
        {
            a.Re	= (float)( f - a.Re );
            a.Im	= (float)( 0 - a.Im );
            return a;
        }
     
        public static Complex operator-( Complex a, Complex b ) 
        {
            a.Re	= a.Re - b.Re;
            a.Im	= a.Im - b.Im;
            return a;
        }
         
        public static Complex operator*( Complex a, double f ) 
        {
            a.Re	= (double)( a.Re * f );
            a.Im	= (double)( a.Im * f );
            return a;
        }
             
        public static Complex operator*( double f, Complex a ) 
        {
            a.Re	= (double)( a.Re * f );
            a.Im	= (double)( a.Im * f );			
            return a;
        }
     
        public static Complex operator*( Complex a, Complex b ) 
        {
            double	x = a.Re, y = a.Im;
            double	u = b.Re, v = b.Im;			
            a.Re	= (double)( x*u - y*v );
            a.Im	= (double)( x*v + y*u );
            
            return a;
        }
     
        public static Complex operator/( Complex a, double f ) 
        {
            if( f == 0 ) 
            {
                throw new DivideByZeroException();
            }
            
            a.Re	= (double)( a.Re / f );
            a.Im	= (double)( a.Im / f );
            
            return a;
        }
                 
        public static Complex operator/( Complex a, Complex b ) 
        {
            double	x = a.Re,	y = a.Im;
            double	u = b.Re,	v = b.Im;
            double	denom = u*u + v*v;

            if( denom == 0 ) 
            {
                throw new DivideByZeroException();
            }

            a.Re	= (double)( ( x*u + y*v ) / denom );
            a.Im	= (double)( ( y*u - x*v ) / denom );
            
            return a;
        }
      
        public override string ToString() 
        {
            return	String.Format( "( {0}, {1}i )", this.Re, this.Im );
        }
      
        static public bool IsEqual( Complex a, Complex b, double tolerance )
        {
            return  ( Math.Abs( a.Re - b.Re ) < tolerance ) &&
                    ( Math.Abs( a.Im - b.Im ) < tolerance );
        }

     
    }

}
