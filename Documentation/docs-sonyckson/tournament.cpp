struct tournament {
    vector< int > f;
 
    tournament() { f.resize( 2*off, 0 ); }
 
    int query( int lo, int hi, int a = 0, int b = off, int x = 1 ) {
        if( a >= hi || b <= lo ) return 0;
        if( a >= lo && b <= hi ) return f[x];
 
        int r = query( lo, hi, a, (a+b)/2, 2*x );
        int s = query( lo, hi, (a+b)/2, b, 2*x+1 );
 
        return s ? s : r;
    }
 
    void update( int x, int v ) {
        if( f[off+x] )
            f[off+x] = 0;
        else
            f[off+x] = v;
 
        for( x = ( x+off ) / 2; x > 0; x /= 2 )
            f[x] = ( f[2*x+1] ? f[2*x+1] : f[2*x] );
    }
};
 
tournament T;