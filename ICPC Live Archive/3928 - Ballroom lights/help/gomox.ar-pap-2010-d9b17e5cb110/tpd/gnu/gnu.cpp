#include <vector>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

typedef unsigned long long int lluint;

typedef vector<lluint> Row;
typedef vector<Row> Mat;

#define forsn(i, s, n)	for (int i = (s); i < (n); i++)
#define forn(i, n)	forsn (i, 0, n)

void mat_mult(const Mat& m1, const Mat& m2, Mat& res) {
    const int n = m1.size();
    const int m = m2.size();
    const int p = m2[0].size();
    assert(m1[0].size() == m && res.size() == n && res[0].size() == p);
    forn (i, n) forn (j, p) {
        lluint s = 0;
        forn (k, m) s += m1[i][k] * m2[k][j];
        res[i][j] = s;
    }
}

void mat_identity(Mat& mt) {
    const int n = mt.size();
    assert(n == mt[0].size());
    forn (i, n) forn (j, n) {
        mt[i][j] = i == j;
    }
}

void mat_copy(const Mat& in, Mat& out) {
    const int n = in.size();
    const int m = in[0].size();
    assert(out.size() == in.size() && out[0].size() == in[0].size());
    forn (i, n) forn (j, m) out[i][j] = in[i][j];
}

void mat_pow(const Mat& mt, int pow, Mat& res) {
    const int n = mt.size();
    vector<Mat> acc(2, Mat(n, Row(n, 0)));
    mat_identity(res);
    mat_copy(mt, acc[false]);
    bool cur = false;
    for (;;) {
        if (pow & 1) {
            mat_copy(res, acc[!cur]);
            mat_mult(acc[!cur], acc[cur], res);
        }
        pow >>= 1;
        if (pow == 0) break;
        mat_mult(acc[cur], acc[cur], acc[!cur]);
        cur = !cur;
    }
}

void mat_print(const Mat& mt) {
    const int n = mt.size();
    const int m = mt[0].size();
    forn (i, n) {
        forn (j, m) {
            cout << mt[i][j] << " ";
        }
        cout << endl;
    }
}

#define MIN_CHAR	32
#define MAX_CHAR	127
#define N		(MAX_CHAR - MIN_CHAR + 1)

#define in_range(Char)	(MIN_CHAR <= (Char) <= MAX_CHAR)
#define charcode(Char)	((Char) - MIN_CHAR)

#define Max_rule	1024
int main() {
    int ncases;
    char buf[Max_rule];
    char chr;
    scanf("%u\n", &ncases);
    forn (ci, ncases) {
        int nrules;
        scanf("%u\n", &nrules);

        // rules[i][j] = cantidad de ocurrencias de Ai en la regla Aj -> ...
        Mat rules(N, Row(N, 0));

        mat_identity(rules);
        forn (ri, nrules) {
            scanf("%c->%s\n", &chr, buf);
            assert(in_range(chr));
            forn (i, N) rules[i][charcode(chr)] = 0;
            const int rule_len = strlen(buf);
            forn (i, rule_len) {
                assert(in_range(buf[i]));
                rules[charcode(buf[i])][charcode(chr)]++;
            }
        }

        int nqueries;
        int pow;
        scanf("%u\n", &nqueries);
        forn (qi, nqueries) {
            Mat input(N, Row(1, 0));
            scanf("%s %c %u\n", buf, &chr, &pow);
            // procesar regla
            const int input_len = strlen(buf);
            forn (i, input_len) {
                assert(in_range(buf[i]));
                input[charcode(buf[i])][0]++;
            }

            Mat pow_rules(N, Row(N, 0));
            mat_pow(rules, pow, pow_rules);

            Mat result(N, Row(1, 0));
            mat_mult(pow_rules, input, result);

            cout << result[charcode(chr)][0] << endl;
        }
    }
    return 0;
}
