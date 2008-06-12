//retorna (b^p)mod(m)
// 0 <= b,p <= 2147483647
// 1 <= m <= 46340
long f(long b, long p, long m){
  long mask = 1;
  long pow2 = b % m;
  long r = 1;

  while (mask){
    if (p & mask)
      r = (r * pow2) % m;
    pow2 = (pow2*pow2) % m;
    mask <<= 1;
  }
  return r;
}
