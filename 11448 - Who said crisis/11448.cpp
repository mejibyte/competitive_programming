/**
 * Big integer class, optimized for decimal integers.
 * Stores and manipulates integers represented as byte arrays,
 * where each byte is a decimal digit. If you're looking for
 * robust, bug-free, efficient code, keep looking. This is a quick
 * and dirty hack. Some day I'll write a templatized BigInt, where
 * you will be able to select the base in which to store the 
 * number. When that day comes, most of this code will be thrown
 * away.
 *
 * BUGS:
 *      operator-(int) does not work.
 *
 *      BigInt doesn't play nice with long long. Either use int
 *      or string.
 *
 * INVARIANTS:
 *      - capacity is never smaller than 16
 *      - capacity is not the smallest it can be because every
 *         modifying member function first grows digits as much as
 *         it might ever need and then does its job.
 * FIELD TESTING:
 *      - Passed numerous problems on Valladolid, including
 *          107, 288, 324, 424, 465, 485, 495, 560, 619, 623, etc.
 *
 * COMPATIBILITY:
 *      - This class was written for the g++ compiler and uses some
 *          of the g++ extensions (like "long double" and the ">?="
 *          operator). If you want to compile this under Micro$oft's
 *          "compiler", I don't want to talk to you.
 *
 * LAST MODIFIED: October 5, 2005
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2002-2004
 * Contact author:
 *      igor at cs.ubc.ca
 **/

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

#ifndef min
#define min(x,y) ((x) < (y) ? (x) : (y))
#endif

#ifndef max
#define max(x,y) ((x) > (y) ? (x) : (y))
#endif

class BigInt
{
    private:
        char *digits;
        int size;            // number of used bytes (digits)
        int capacity;        // size of digits
        int sign;            // -1, 0 or +1

    public:
        /** Creates a BigInt with initial value n and initial capacity cap **/
        BigInt( int n, int cap );

        /** Creates a BigInt with initial value n **/
        BigInt( int n );

        /** Creates a BigInt with initial value floor( d ) **/
        BigInt( long double d );

        /** Creates a BigInt with value 0 **/
        BigInt();

        /** Creates a BigInt by reading the value from a string **/
        BigInt( string s );

        /** Creates a BigInt by reading the value from a C string **/
        BigInt( const char s[] );

        /** Copy constructor **/
        BigInt( const BigInt &n );

        /** Assignment operators **/
        const BigInt &operator=( const BigInt &n );
        const BigInt &operator=( int n );

        /** Cleans up **/
        ~BigInt();

        /** Removes any leading zeros and adjusts the sign **/
        void normalize();

        /** Returns the sign of n: -1, 0 or 1 **/
        static int sig( int n );

        /** Returns the sign of n: -1, 0 or 1 **/
        static int sig( long double n );

        /** Returns the number of decimal digits **/
        inline int length() { return size; }

        /** Arithmetic **/
        BigInt operator++();
        BigInt operator++( int );
        BigInt operator--();
        BigInt operator--( int );
        BigInt operator-();
        BigInt operator+ ( int n    );
        BigInt operator+ ( BigInt n );
        BigInt&operator+=( int n    );
        BigInt&operator+=( BigInt n );
        BigInt operator- ( int n    );
        BigInt operator- ( BigInt n );
        BigInt&operator-=( int n    );
        BigInt&operator-=( BigInt n );
        BigInt operator* ( int n    );
        BigInt operator* ( BigInt n );
        void   operator*=( int n    );
        void   operator*=( BigInt n );
        BigInt operator/ ( int n    );
        BigInt operator/ ( BigInt n );
        void   operator/=( int n    );
        void   operator/=( BigInt n );
        int    operator% ( int n    );
        BigInt operator% ( BigInt n );
        void   operator%=( int n    );
        void   operator%=( BigInt n );
        int divide( int n );              // Divides storing quotient in *this and returning the remainder
        BigInt divide( BigInt n );        // Divides storing quotient in *this and returning the remainder
        BigInt operator* ( long double n ); // Multiplies by a double and truncates (always under-estimates!)
        void   operator*=( long double n ); // Multiplies by a double and truncates (always under-estimates!)

        /** Bitwise arithmetic **/
        BigInt operator<< ( int n    );
        void   operator<<=( int n    );
        BigInt operator>> ( int n    );   // Works differently for negative numbers
        void   operator>>=( int n    );   // Works differently for negative numbers
/*
        BigInt operator&  ( int n    );
        BigInt operator&  ( BigInt n );
        void   operator&= ( int n    );
        void   operator&= ( BigInt n );
        BigInt operator|  ( int n    );
        BigInt operator|  ( BigInt n );
        void   operator|= ( int n    );
        void   operator|= ( BigInt n );
        BigInt operator^  ( int n    );
        BigInt operator^  ( BigInt n );
        void   operator^= ( int n    );
        void   operator^= ( BigInt n );
        BigInt operator~();
*/
        /** Concatenation ;-) **/
        BigInt operator,( int n );
        BigInt operator,( BigInt n );

        /** Casting **/
        bool operator!();
        operator bool();
        //operator int();   //XXX: Don't do this!!! It takes precedence over operator+(int,BigInt)
        operator string();

        /** Comparison **/
        bool operator<( BigInt n );
        bool operator>( BigInt n );
        bool operator==( BigInt n );
        bool operator<=( BigInt n );
        bool operator>=( BigInt n );
        bool operator<( int n );
        bool operator>( int n );
        bool operator==( int n );
        bool operator<=( int n );
        bool operator>=( int n );
        int compare( BigInt n );

        /** Returns the lowest value as an integer (watch out for overflow) **/
        int toInt();

        /** Returns the value as a decimal string **/
        string toString();

        /** Outputs decimal value to stdout **/
        void print();

        /** Outputs the decimal value, with commas **/
        void printWithCommas( ostream &out );

    private:
        /** Expansion **/
        void grow();

    /** I/O Friends **/
    friend istream &operator>>( istream &in, BigInt &n );
    friend ostream &operator<<( ostream &out, BigInt n );

    /** Logarithms **/
    friend long double log2( BigInt x, long double epsilon );
    inline friend long double log( BigInt x, long double epsilon );
    inline friend long double log10( BigInt x, long double epsilon );
    inline friend long double lg( BigInt x, long double epsilon );
    inline friend long double ln( BigInt x, long double epsilon );
};

BigInt operator+( int m, BigInt &n )
{
    return n + m;
}

BigInt operator-( int m, BigInt &n )
{
    return -n + m;
}

BigInt operator*( int m, BigInt &n )
{
    return n * m;
}

BigInt operator/( int m, BigInt &n )
{
    return BigInt( m ) / n;
}

BigInt operator%( int m, BigInt &n )
{
    return BigInt( m ) % n;
}

/** Misc **/
inline bool isDigit( int c )
{
    return( c >= ( int )'0' && c <= ( int )'9' );
}

/** Input/Output **/
istream &operator>>( istream &in, BigInt &n )           // FIXME: see inside
{
    n.size = 0;
    n.sign = 1;
    int sign = 1;
    int c;
    while( ( c = in.peek() ) >= 0 &&
           ( c == ' ' || c == '\t' || c == '\r' || c == '\n' ) )
        in.get();
    if( c < 0 || ( c != ( int )'-' && !isDigit( c ) ) )
    {
        in >> c;                // XXX: force in.fail()
        return in;
    }
    if( c == ( int )'-' ) { sign = -1; in.get(); }

    // FIXME: Extremely inefficient! Use a string.
    while( ( c = in.peek() ) >= 0 && isDigit( c ) )
    {
        in.get();
        n *= 10;
        n += ( c - ( int )'0' );
    }
    n.sign = sign;      //XXX: assign n.sign directly after fixing the FIXME
    n.normalize();
    return in;
}

ostream &operator<<( ostream &out, BigInt n )       //FIXME: make more efficient
{
    return out << n.toString();
}

BigInt::BigInt( int n, int cap )
{
    cap = max( cap, ( int )sizeof( n ) * 8 );
    capacity = cap;
    sign = sig( n );
    n *= sign;
    digits = new char[cap];
    memset( digits, 0, cap );
    for( size = 0; n; size++ )
    {
        digits[size] = n % 10;
        n /= 10;
    }
}

BigInt::BigInt( int n )
{
    capacity = 1024;
    sign = sig( n );
    n *= sign;
    digits = new char[capacity];
    memset( digits, 0, capacity );
    size = 0;
    while( n )
    {
        digits[size++] = n % 10;
        n /= 10;
    }
}

BigInt::BigInt( long double d )
{
    capacity = 1024;
    sign = ( d < 0 ? -1 : d > 0 ? 1 : 0 );
    d *= sign;
    digits = new char[capacity];
    memset( digits, 0, capacity );
    size = 0;
    d = floor( d );
    while( d > 0 )
    {
        digits[size++] = 0 >? ( int )( ( d - floor( d / 10 ) * 10 ) + 0.5 ) <? 9;
        d = floor( d / 10 );
    }
}

BigInt::BigInt()
{
    capacity = 128;
    sign = 0;
    digits = new char[capacity];
    memset( digits, 0, capacity );
    size = 0;
}

BigInt::BigInt( string s )
{
    capacity = max( ( int )s.size(), 16 );
    sign = 0;
    digits = new char[capacity];
    memset( digits, 0, capacity );

    istringstream in( s );
    in >> ( *this );
}

BigInt::BigInt( const char s[] )
{
    capacity = max( ( int )strlen( s ), 16 );
    sign = 0;
    digits = new char[capacity];
    memset( digits, 0, capacity );

    istringstream in( s );
    in >> ( *this );
}

BigInt::BigInt( const BigInt &n )
{
    capacity = n.capacity;
    sign = n.sign;
    size = n.size;
    digits = new char[capacity];
    memcpy( digits, n.digits, capacity );
}

const BigInt &BigInt::operator=( const BigInt &n )
{
    if( &n != this )
    {
        if( capacity < n.size )
        {
            capacity = n.capacity;
            delete [] digits;
            digits = new char[capacity];
        }
        sign = n.sign;
        size = n.size;
        memcpy( digits, n.digits, size );
        memset( digits + size, 0, capacity - size );
    }
    return *this;
}

const BigInt &BigInt::operator=( int n )
{
    sign = sig( n );
    n *= sign;
    for( size = 0; n; size++ )
    {
        digits[size] = n % 10;
        n /= 10;
    }
    return *this;
}

BigInt::~BigInt()
{
    delete [] digits;
}

void BigInt::normalize()
{
    while( size && !digits[size-1] ) size--;
    if( !size ) sign = 0;
}

int BigInt::sig( int n )
{
    return( n > 0 ? 1 : ( n == 0 ? 0 : -1 ) );
}

int BigInt::sig( long double n )
{
    return( n > 0 ? 1 : ( n == 0 ? 0 : -1 ) );
}

int BigInt::toInt()
{
    int result = 0;
    for( int i = size - 1; i >= 0; i-- )
    {
        result *= 10;
        result += digits[i];
        if( result < 0 ) return sign * 0x7FFFFFFF;
    }
    return sign * result;
}

string BigInt::toString()
{
    string s = ( sign >= 0 ? "" : "-" );
    for( int i = size - 1; i >= 0; i-- )
        s += ( digits[i] + '0' );
    if( size == 0 ) s += '0';
    return s;
}

void BigInt::print()        //FIXME: make more efficient
{
    cout << toString();
}

void BigInt::printWithCommas( ostream &out )
{
    if( sign < 0 ) out.put( '-' );
    for( int i = size - 1; i >= 0; i-- )
    {
        out.put( digits[i] + '0' );
        if( !( i % 3 ) && i ) out.put( ',' );
    }
    if( size == 0 ) out.put( '0' );
}

void BigInt::grow()
{
    char *olddigits = digits;
    int oldCap = capacity;
    capacity *= 2;
    digits = new char[capacity];
    memcpy( digits, olddigits, oldCap );
    memset( digits + oldCap, 0, oldCap );
    delete [] olddigits;
}

BigInt BigInt::operator++()
{
    operator+=( 1 );
    return *this;
}

BigInt BigInt::operator++( int )
{
    return operator++();
}

BigInt BigInt::operator--()
{
    operator-=( 1 );
    return *this;
}

BigInt BigInt::operator--( int )
{
    return operator--();
}

BigInt BigInt::operator-()
{
    BigInt result( *this );
    result.sign *= -1;
    return result;
}

BigInt BigInt::operator+( int n )
{
    BigInt result( *this );
    result += n;
    return result;
}

BigInt BigInt::operator+( BigInt n )
{
    BigInt result( *this );
    result += n;
    return result;
}

BigInt &BigInt::operator+=( int n )
{
    if( size == capacity ) grow();

    int nsign = sig( n );
    if( !nsign ) return *this;
    if( !sign ) sign = nsign;
    if( sign == nsign )
    {
        n *= nsign;
        int carry = 0;
        int i;
        for( i = 0; n || carry; i++ )
        {
            int dig = n % 10;
            int newdig = digits[i] + dig + carry;
            digits[i] = newdig % 10;
            carry = newdig / 10;
            n /= 10;
        }
        size = max( i, size );
    }
    else operator-=( -n );
    return *this;
}

BigInt &BigInt::operator+=( BigInt n )
{
    int maxS = max( size, n.size ) + 1;
    while( maxS >= capacity ) grow();        //FIXME: this is stupid

    if( !n.sign ) return *this;
    if( !sign ) sign = n.sign;
    if( sign == n.sign )
    {
        int carry = 0;
        int i;
        for( i = 0; i < maxS - 1 || carry; i++ )
        {
            int newdig = carry;
            if( i < size ) newdig += digits[i];
            if( i < n.size ) newdig += n.digits[i];
            digits[i] = newdig % 10;
            carry = newdig / 10;
        }
        size = max( i, size );
    }
    else
    {
        n.sign *= -1;
        operator-=( n );
        n.sign *= -1;
    }
    return *this;
}

BigInt BigInt::operator-( int n )
{
    BigInt result( *this );
    result -= n;
    return result;
}

BigInt BigInt::operator-( BigInt n )
{
    BigInt result( *this );
    result -= n;
    return result;
}

BigInt &BigInt::operator-=( int n )
{
    if( size == capacity ) grow();

    int nsign = sig( n );
    if( !nsign ) return *this;
    if( !sign ) sign = 1;
    if( sign == nsign )
    {
        BigInt bin = n;
        if( sign >= 0 && *this < bin || sign < 0 && *this > bin )
        {
            // Subtracting a bigger number
            operator=( toInt() - n );
            return *this;
        }

        n *= nsign;
        int carry = 0;
        int i;
        for( i = 0; n || carry; i++ )
        {
            int dig = n % 10;
            int newdig = digits[i] - dig + carry;
            if( newdig < 0 ) newdig += 10, carry = -1;
            else carry = 0;
            digits[i] = newdig;
            n /= 10;
        }
        normalize();
    }
    else operator+=( -n );
    return *this;
}

BigInt &BigInt::operator-=( BigInt n )
{
    int maxS = max( size, n.size ) + 1;
    while( maxS >= capacity ) grow();        //FIXME: this is stupid

    if( !n.sign ) return *this;
    if( !sign ) sign = 1;
    if( sign == n.sign )
    {
        if( sign >= 0 && *this < n || sign < 0 && *this > n ) 
        {
            // Subtracting a bigger number
            BigInt tmp = n;
            tmp -= *this;
            *this = tmp;
            sign = -sign;
            return *this;
        }

        int carry = 0;
        int i;
        for( i = 0; i < maxS - 1; i++ )
        {
            int newdig = carry;
            if( i < size ) newdig += digits[i];
            if( i < n.size ) newdig -= n.digits[i];
            if( newdig < 0 ) newdig += 10, carry = -1;
            else carry = 0;
            digits[i] = newdig;
        }
        if( carry )     // Subtracted a bigger number, need to flip sign
        {
            if( i ) digits[0] = 10 - digits[0];
            size = ( i ? 1 : 0 );
            for( int j = 1; j < i; j++ )
            {
                digits[j] = 9 - digits[j];
                if( digits[i] ) size = j + 1;
            }
            sign *= -1;
        }
        normalize();
    }
    else
    {
        n.sign *= -1;
        operator+=( n );
        n.sign *= -1;
    }
    return *this;
}

BigInt BigInt::operator*( int n )
{
    BigInt result( 0, size + ( int )sizeof( n ) * 8 );
    int nsign = sig( n );
    n *= nsign;
    result.sign = sign * nsign;
    if( !result.sign ) return result;

    int i, j;
    for( i = 0; n; i++ )
    {
        int dig = n % 10;
        if( dig )
        {
            int carry = 0;
            for( j = 0; j < size || carry; j++ )
            {
                int newDig = result.digits[i + j] + ( j < size ? dig * digits[j] : 0 ) + carry;
                result.digits[i + j] = newDig % 10;
                carry = newDig / 10;
            }
        }
        n /= 10;
    }
    result.size = i + j - 1;
    return result;
}

BigInt BigInt::operator*( BigInt n )
{
    BigInt result( 0, size + n.size );

    result.sign = sign * n.sign;
    if( !result.sign ) return result;

    int i, j;
    for( i = 0; i < n.size; i++ )
    {
        if( n.digits[i] )
        {
            int carry = 0;
            for( j = 0; j < size || carry; j++ )
            {
                int newDig =
                    result.digits[i + j] +
                    ( j < size ? n.digits[i] * digits[j] : 0 ) +
                    carry;
                result.digits[i + j] = newDig % 10;
                carry = newDig / 10;
            }
        }
    }
    result.size = i + j - 1;

    return result;
}

void BigInt::operator*=( int n )
{
    operator=( operator*( n ) );
}

void BigInt::operator*=( BigInt n )
{
    operator=( operator*( n ) );
}

BigInt BigInt::operator/( int n )
{
    if( !n ) n /= n;        //XXX: force a crash

    BigInt result( *this );
    result /= n;
    return result;
}

BigInt BigInt::operator/( BigInt n )
{
    if( !n ) n.size /= n.size;       //XXX: force a crash

    BigInt result( *this );
    result /= n;
    return result;
}

void BigInt::operator/=( int n )
{
    divide( n );
}

void BigInt::operator/=( BigInt n )
{
    divide( n );
}

int BigInt::operator%( int n )
{
    BigInt tmp( *this );
    return tmp.divide( n );
}

void BigInt::operator%=( int n )
{
    operator=( divide( n ) );
}

BigInt BigInt::operator%( BigInt n )
{
    BigInt tmp( *this );
    return tmp.divide( n );
}

void BigInt::operator%=( BigInt n )
{
    operator=( divide( n ) );
}

int BigInt::divide( int n )
{
    if( !n ) n /= n;        //XXX: force a crash

    int nsign = sig( n );
    n *= nsign;
    if( !sign ) return 0;
    sign *= nsign;

    int tmp = 0;
    for( int i = size - 1; i >= 0; i-- )
    {
        tmp *= 10;
        tmp += digits[i];
        digits[i] = tmp / n;
        tmp -= digits[i] * n;
    }
    normalize();
    return tmp;
}

BigInt BigInt::divide( BigInt n )
{
    if( !n ) n.size /= n.size;         //XXX: force a crash

    if( !sign ) return 0;
    sign *= n.sign;

    int oldSign = n.sign;
    n.sign = 1;

    BigInt tmp( 0, size );
    for( int i = size - 1; i >= 0; i-- )
    {
        tmp *= 10;
        tmp += digits[i];
        digits[i] = 0;
        while( tmp >= n ) { tmp -= n; digits[i]++; }
    }
    normalize();

    n.sign = oldSign;

    return tmp;
}

// This is only exact to the first 15 or so digits, but it is
// never an over-estimate
BigInt BigInt::operator*( long double n )
{
    // the number of digits after the decimal point to use
    int DIGS_AFTER_DOT = 15;

    int nsign = sig( n );
    n *= nsign;
    int ndigs = n >= 1 ? ( int )log10( n ) + 1 : 0;
    BigInt result( 0, size + ndigs );
    result.sign = sign * nsign;
    if( !result.sign ) return result;

    if( n >= 1 ) for( int i = 0; i < ndigs; i++ ) n /= 10;
    result.size = 0;

    char afterDot[DIGS_AFTER_DOT + 1];
    memset( afterDot, 0, sizeof( afterDot ) );

    // Keep going until the DIGS_AFTER_DOT'th digit after the decimal point
    for( int i = ndigs - 1; i >= -DIGS_AFTER_DOT; i-- )
    {
        n *= 10;
        int dig = ( int )floor( n );
        n -= dig;
        if( !dig ) continue;

        int carry = 0;
        for( int j = 0; j < size || carry; j++ )
        {
            int newdig =
                ( i + j < 0 ? afterDot[-( i + j )] : result.digits[i + j] )
                + dig * digits[j]
                + carry;
            ( i + j < 0 ? afterDot[-( i + j )] : result.digits[i + j] ) = newdig % 10;
            if( i + j >= 0 && result.digits[i + j] ) result.size >?= i + j + 1;
            carry = newdig / 10;
        }
    }
    if( !result.size ) result.sign = 0;
    return result;
}

void BigInt::operator*=( long double n )
{
    operator=( operator*( n ) );
}

BigInt BigInt::operator<<( int n )
{
    BigInt result( *this );
    result <<= n;
    return result;
}

void BigInt::operator<<=( int n )
{
    if( n < 0 ) operator>>=( -n );
    else if( n > 0 )
    {
        BigInt mult( 1, 4 * n );
        for( int i = ( 1 << 30 ); i; i >>= 1 )
        {
            mult *= mult;
            if( n & i ) mult *= 2;
        }
        operator*=( mult );
    }
}

BigInt BigInt::operator>>( int n )
{
    BigInt result( *this );
    result >>= n;
    return result;
}

void BigInt::operator>>=( int n )
{
    if( n < 0 ) operator<<=( -n );
    else if( n > 0 )
    {
        BigInt mult( 1, 4 * n );
        for( int i = ( 1 << 30 ); i; i >>= 1 )
        {
            mult *= mult;
            if( n & i ) mult *= 2;
        }
        operator/=( mult );
    }
}
/*
BigInt BigInt::operator&( int n )
{
}

BigInt BigInt::operator&( BigInt n )
{
}

void BigInt::operator&=( int n )
{
}

void BigInt::operator&=( BigInt n )
{
}

BigInt BigInt::operator|( int n )
{
}

BigInt BigInt::operator|( BigInt n )
{
}

void BigInt::operator|=( int n )
{
}

void BigInt::operator|=( BigInt n )
{
}

BigInt BigInt::operator^( int n )
{
}

BigInt BigInt::operator^( BigInt n )
{
}

void BigInt::operator^=( int n )
{
}

void BigInt::operator^=( BigInt n )
{
}

BigInt BigInt::operator~()
{
}
*/
BigInt BigInt::operator,( int n )
{
    BigInt result( 0, size + ( int )sizeof( n ) * 8 );
    for( result.size = 0; n; result.size++ )
    {
        result.digits[result.size] = n % 10;
        n /= 10;
    }
    memcpy( result.digits + result.size, digits, size * sizeof( digits[0] ) );
    result.size += size;
    result.sign = 1;
    result.normalize();
    return result;
}

BigInt BigInt::operator,( BigInt n )
{
    BigInt result( 0, size + n.size );
    memcpy( result.digits, n.digits, n.size * sizeof( n.digits[0] ) );
    memcpy( result.digits + n.size, digits, size * sizeof( digits[0] ) );
    result.size = size + n.size;
    result.sign = 1;
    result.normalize();
    return result;
}

bool BigInt::operator!()
{
    return !size;
}

BigInt::operator bool()
{
    return size;
}

//BigInt::operator int()
//{
//    return toInt();
//}

BigInt::operator string()
{
    return toString();
}

bool BigInt::operator<( BigInt n )
{
    return( compare( n ) < 0 );
}

bool BigInt::operator>( BigInt n )
{
    return( compare( n ) > 0 );
}

bool BigInt::operator==( BigInt n )
{
    return( compare( n ) == 0 );
}

bool BigInt::operator<=( BigInt n )
{
    return( compare( n ) <= 0 );
}

bool BigInt::operator>=( BigInt n )
{
    return( compare( n ) >= 0 );
}

bool BigInt::operator<( int n )
{
    return( compare( BigInt( n ) ) < 0 );
}

bool BigInt::operator>( int n )
{
    return( compare( BigInt( n ) ) > 0 );
}

bool BigInt::operator==( int n )
{
    return( compare( BigInt( n ) ) == 0 );
}

bool BigInt::operator<=( int n )
{
    return( compare( BigInt( n ) ) <= 0 );
}

bool BigInt::operator>=( int n )
{
    return( compare( BigInt( n ) ) >= 0 );
}

int BigInt::compare( BigInt n )
{
    if( sign < n.sign ) return -1;
    if( sign > n.sign ) return 1;
    if( size < n.size ) return -sign;
    if( size > n.size ) return sign;
    for( int i = size - 1; i >= 0; i-- )
    {
        if( digits[i] < n.digits[i] ) return -sign;
        else if( digits[i] > n.digits[i] ) return sign;
    }
    return 0;
}

long double log2( BigInt x, long double epsilon = 0.000000000000001 )
{
    static /* const */ long double O = 0.0;
    if( x.sign <= 0 ) return O / O;     // Return NaN

    long double y = 0.0, z = 1.0, f = 0.0;
    while( x >= 2 )
    {
        if( x.divide( 2 ) ) f += 1.0;
        f /= 2.0;
        y++;
    }
    f += 1.0;
    while( z > epsilon )
    {
        f *= f;
        z /= 2.0;
        if( f >= 2.0 )
        {
            y += z;
            f /= 2.0;
        }
    }
    return y;
}

inline long double log( BigInt x, long double epsilon = 0.000000000000001 )
{
    return log2( x, epsilon ) * 0.6931471805599;
}

inline long double log10( BigInt x, long double epsilon = 0.000000000000001 )
{
    return log2( x, epsilon ) * 0.301029995664;
}

inline long double lg( BigInt x, long double epsilon = 0.000000000000001 )
{
    return log2( x, epsilon );
}

inline long double ln( BigInt x, long double epsilon = 0.000000000000001 )
{
    return log( x, epsilon );
}


int main()
{
  int n;
  cin >> n;
  while (n--){
    string a, b;
    cin >> a >> b;
    BigInt x(a), y(b);
    cout << (x - y) << endl;
  }
  /*
    cout << "Constructors and copy constructors:" << endl;
    cout << "12345000 = " << BigInt( 12345000 ) << endl;
    BigInt b = BigInt( 12345000 );
    cout << "12345000 = " << b << endl;
    BigInt c; c = b;
    cout << "12345000 = " << c << endl;
    cout << "1234567890 = " << BigInt( ( long double )1234567890.49999 ) << endl;
    cout << endl;

    cout << "Addition and subtraction:" << endl;
    cout << "123 + 234 = " << ( BigInt( 123 ) + 234 ).toInt() << endl;
    cout << "243 + 999 = " << ( BigInt( 243 ) + BigInt( 999 ) ) << endl;
    cout << "-123 + -321 = " << ( BigInt( -123 ) + BigInt( -321 ) ) << endl;
    cout << "-123 + 321 = " << ( BigInt( -123 ) + BigInt( 321 ) ) << endl;
    cout << "-2 + 5 = " << ( BigInt( -2 ) + 5 ) << endl;
    cout << "-2 + 5 = " << ( BigInt( -2 ) + BigInt( 5 ) ) << endl;
    cout << "-2 + -5 = " << ( BigInt( -2 ) + -5 ) << endl;
    cout << "-2 + -5 = " << ( BigInt( -2 ) + BigInt( -5 ) ) << endl;
    cout << "0 + -5 = " << ( BigInt( 0 ) + -5 ) << endl;
    cout << "0 + -5 = " << ( BigInt( 0 ) + BigInt( -5 ) ) << endl;
    cout << "4567 - 1234 = " << ( 4567 - BigInt( 1234 ) ) << endl;
    cout << "345 - 46 = " << ( BigInt( 345 ) - BigInt( 46 ) ) << endl;
    cout << "2 - 6 = " << ( BigInt( 2 ) - BigInt( 6 ) ) << endl;
    cout << "2 - 6 = " << ( BigInt( 2 ) - 6 ) << endl;
    cout << "0 - 5 = " << ( BigInt( 0 ) - 5 ) << endl;
    cout << "0 - 5 = " << ( BigInt( 0 ) - BigInt( 5 ) ) << endl;
    cout << "0 - -5 = " << ( BigInt( 0 ) - -5 ) << endl;
    cout << "0 - -5 = " << ( BigInt( 0 ) - BigInt( -5 ) ) << endl;
    cout << "10000 - 10000 = " << ( BigInt( 10000 ) - 10000 ) << endl;
    cout << "10000 - 10110 = " << ( BigInt( 10000 ) - 10110 ) << endl;
    cout << "4567 - 4568 = " << ( BigInt( 4567 ) - 4568 ) << endl;
    cout << "-4567 - -4568 = " << ( BigInt( -4567 ) - BigInt( -4568 ) ) << endl;
    cout << "999 - 9999 = " << ( BigInt( 999 ) - 9999 ) << endl;
    cout << "2000000000 + 2000000000 + 2000123456 = " << ( BigInt( 2000000000 ) + 2000000000 + BigInt( 2000123456 ) ) << endl;
    cout << "-34567 + 34568 = " << ( BigInt( -34567 ) + BigInt( 34568 ) ) << endl;
    cout << "10 - 1 = " << ( BigInt( 10 ) - 1 ) << endl;
    cout << "1 - 10 = " << ( BigInt( 1 ) - 10 ) << endl;
    cout << "Fib( 613 ) + Fib( 614 ) = " << (
        BigInt( "57535841731394367586444934959935162731893485882113791734636043664022186311322175066312007025864665068095897804714985049873571833" )
        +
        BigInt( "93094947492730684688120544687306111880728698574224279139760379700550384193434187688727692133714165658764281830930007773906603177" )
        ) << endl;
    cout << endl;
    cout << "Multiplication/division:" << endl;
    cout << "128 * 512 = " << ( BigInt( 128 ) * 512 ) << endl;
    cout << "0 * 12345 = " << ( BigInt( 0 ) * 12345 ) << endl;
    cout << "-123 * 0 = " << ( BigInt( -123 ) * 0 ) << endl;
    cout << "-12345 * 1000001 = " << ( BigInt( -12345 ) * BigInt( 1000001 ) ) << endl;
    cout << "-1 * -1 = " << ( BigInt( -1 ) * BigInt( -1 ) ) << endl;
    cout << "1024 / 2 = " << ( BigInt( 1024 ) / 2 ) << endl;
    cout << "-525474 / -789 = " << ( BigInt( -525474 ) / -789 ) << endl;
    cout << "-81 / 27 = " << ( BigInt( -81 ) / 27 ) << endl;
    cout << "0 / -888 = " << ( BigInt( 0 ) / -888 ) << endl;
    cout << "1024 / 2 = " << ( BigInt( 1024 ) / BigInt( 2 ) ) << endl;
    cout << "-525474 / -789 = " << ( BigInt( -525474 ) / BigInt( -789 ) ) << endl;
    cout << "-81 / 27 = " << ( BigInt( -81 ) / BigInt( 27 ) ) << endl;
    cout << "0 / -888 = " << ( BigInt( 0 ) / BigInt( -888 ) ) << endl;
    BigInt q = 1023;
    int rem = q.divide( 2 );
    cout << "1023 / 2 = " << q << " + " << rem << "/2" << endl;
    q = 1219255159;
    rem = q.divide( 98765 );
    cout << "1219255159 / 98765 = " << q << " + " << rem << "/98765" << endl;
    q = 121;
    rem = q.divide( 11 );
    cout << "121 / 11 = " << q << " + " << rem << "/11" << endl;
    q = 1023;
    BigInt rem2 = q.divide( BigInt( 2 ) );
    cout << "1023 / 2 = " << q << " + " << rem2 << "/2" << endl;
    q = 1219255159;
    rem2 = q.divide( BigInt( 98765 ) );
    cout << "1219255159 / 98765 = " << q << " + " << rem2 << "/98765" << endl;
    q = 121;
    rem2 = q.divide( BigInt( 11 ) );
    cout << "121 / 11 = " << q << " + " << rem2 << "/11" << endl;
    q = 9999;
    rem2 = q.divide( BigInt( 9 ) );
    cout << "9999 / 9 = " << q << " + " << rem2 << "/9" << endl;
    cout << "1024 * 15.37 = " << BigInt( 1024 ) * 15.37l << endl;
    cout << "100 * 0.5 = " << BigInt( 100 ) * 0.5l << endl;
    cout << "123456789 * 0.123456789 = " << BigInt( 123456789 ) * 0.123456789l << endl;
    cout << "4286 * -0.5 = " << BigInt( 4286 ) * -0.5l << endl;
    cout << "29384723 * 1.0 = " << BigInt( 29384723 ) * 1.0l << endl;
    cout << "29384723 * -1.0 = " << BigInt( 29384723 ) * -1.0l << endl;
    cout << "3874928345 * 0.0 = " << BigInt( "3874928345" ) * 0.0l << endl;
    BigInt n = 1000;
    cout << "n = 1000: n*n*(8+n*(12+n*(3+n*n))) = " << n*n*(8+n*(12+n*(3+n*n))) << endl;
    
    cout << endl;
    cout << "Concatenation:" << endl;
    cout << "123,456 = " << ( BigInt( 123 ), 456 ) << endl;
    cout << "9999,55 = " << ( BigInt( 9999 ), BigInt( 55 ) ) << endl;
    cout << "0,1 = " << ( BigInt( 0 ), BigInt( 1 ) ) << endl;
    cout << "0,0 = " << ( BigInt( 0 ), 0 ) << endl;
    cout << "0,0 = " << ( BigInt( 0 ), BigInt( 0 ) ) << endl;
    cout << endl;
    cout << "Reflection:" << endl;
    BigInt x = 11;
    cout << "11 + 11 = " << ( x + x ) << endl;
    cout << "11 * 11 = " << ( x * x ) << endl;
    x += x;
    cout << "11 + 11 = " << x << endl;
    x *= x;
    cout << "22 * 22 = " << x << endl;
    cout << endl;
    cout << "Bitwise operations:" << endl;
    cout << "1 << 10 = " << ( 1 << 10 ) << " = " << ( BigInt( 1 ) << 10 ) << endl;
    cout << "-7 << 2 = " << ( -7 << 2 ) << " = " << ( BigInt( -7 ) << 2 ) << endl;
    cout << "3 << 8 = " << ( 3 << 8 ) << " = " << ( BigInt( 3 ) << 8 ) << endl;
    cout << "3 << 9 = " << ( 3 << 9 ) << " = " << ( BigInt( 3 ) << 9 ) << endl;
    cout << "1024 >> 9 = " << ( 1024 >> 9 ) << " = " << ( BigInt( 1024 ) >> 9 ) << endl;
    cout << "-1 >> 4 = " << (-1 >> 4) << " = " << ( BigInt( -1 ) >> 4 ) << endl;
    cout << endl;
    cout << "Input:" << endl;
    istringstream in( "1234567890" );
    in >> x;
    cout << "1234567890 = " << x << endl;
    istringstream in2( " \t\n\r01234 -00009876\t" );
    in2 >> x >> rem2;
    cout << "1234 = " << x << endl;
    cout << "-9876 = " << rem2 << endl;
    cout << endl;
    cout << "Exhaustion:" << endl;
    BigInt *table = new BigInt[10240];
    table[0] = 0; table[1] = 1;
    for( int i = 2; i < 10240; i++ )
        table[i] = table[i - 1] + table[i - 2];
    cout << "Fibonacci( 615 )  = " << table[615] << endl;
    cout << "Fibonacci( 10000 )  = " << table[10000] << endl;
    delete [] table;
    cout << endl;
    cout << "Logarithms" << endl;
    cout << "log2( 1024 ) = " << log2( BigInt( 1024 ) ) << endl;
    cout << "log2( 6 ) = " << log2( BigInt( 6 ) ) << endl;
    cout << "log( 0 ) = " << log( BigInt( 0 ) ) << endl;
    cout << "log10( 1000000 ) = " << log10( BigInt( 10000000 ) ) << endl;
    cout << "log( 1234567 ) = " << log( BigInt( 1234567 ) ) << endl;
  */
    return 0;
}

