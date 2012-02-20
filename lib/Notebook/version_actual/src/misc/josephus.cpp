// Recursivo:
// n <= 2500
// Es O(n), pero mejor usar la versión iterativa
// para evitar stack overflows.
int joseph(int n, int k) {
    assert(n >= 1);
    if (n == 1) return 0;
    return (joseph(n - 1, k) + k) % n;
}

// Iterativo:
// n <= 10^6, k <= 2^31 - 1
int joseph(int n, int k) {
    int ans = 0;
    for (int i = 2; i <= n; ++i) {
        ans = (ans + k) % i;
    }
    return ans;
}

// Más rápido:
// n <= 10^18, k <= 2500
// Posiblemente se puede incrementar k un poco más
// si se cambia la línea marcada con *** por la versión
// iterativa, para evitar stack overflows.
long long joseph(long long n, int k) {
    assert(n >= 1);
    if (n == 1) return 0LL;
    if (k == 1) return n - 1;
    if (n < k) return (joseph(n - 1, k) + k) % n; // ***
    long long w = joseph(n - n / k, k) - n % k;
    if (w < 0) return w + n;
    return w + w / (k - 1);
}
