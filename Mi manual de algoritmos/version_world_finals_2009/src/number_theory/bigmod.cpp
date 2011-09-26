//retorna (b^p)mod(m)
// 0 <= b,p <= 2147483647
// 1 <= m <= 46340
int bigmod(int b, int p, int m){
  int mask = 1;
  int pow2 = b % m;
  int r = 1;
  while (mask){
    if (p & mask) r = (r * pow2) % m;
    pow2 = (pow2 * pow2) % m;
    mask <<= 1;
  }
  return r;
}
// Si se cambian los int por long longs los
// valores de entrada deben cumplir:
// 0 <= b,p <= 9223372036854775807
// 1 <= m <= 3037000499
// Si se cambian por unsigned long longs:
// 0 <= b,p <= 18446744073709551615
// 1 <= m <= 4294967295
