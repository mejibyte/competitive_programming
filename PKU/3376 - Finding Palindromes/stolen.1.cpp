// Stolen from http://hi.baidu.com/billdu/blog/item/a748eb1eb15f1173f624e412.html

#include <stdio.h>
#define count 0
#define dcount 1

char data[4200010];
char *str[2100010], palind[2100010];
int len[2100010];
int kmp[2100010], trie[4200010][2], triemr;

typedef struct {
    char letter;
    int son, next;
} graphnode;
graphnode graph[8400010];
int grapmr;

void insert(char *a, int len) {
    int cur = 0, nxt, i, p, c, t;
    for (i = 1; i <= len; i++) {
        nxt = -1;
        for (c = graph[cur].next; c != -1; c = graph[c].next) {
            if (graph[c].letter == a[len - i]) {
                nxt = graph[c].son;
                break;
            }
        }
        if (nxt == -1)
            break;
        else
            cur = nxt;
    }
    for (; i <= len; i++) {
        p = triemr++;
        trie[p][count] = 0;
        trie[p][dcount] = 0;
        graph[p].son = cur;
        graph[p].next = -1;
        for (c = cur; graph[c].next != -1; c = graph[c].next);
        t = grapmr++;
        graph[t].letter = a[len - i];
        graph[t].son = p;
        graph[t].next = -1;
        graph[c].next = t;
        cur = p;
    }
    trie[cur][count]++;
    return;
}

void dinsert(char *a, int len) {
    int cur = 0, nxt, i, p, c, t;
    for (i = 0; i < len; i++) {
        nxt = -1;
        for (c = graph[cur].next; c != -1; c = graph[c].next) {
            if (graph[c].letter == a[i]) {
                nxt = graph[c].son;
                break;
            }
        }
        if (nxt == -1)
            break;
        else
            cur = nxt;
    }
    for (; i < len; i++) {
        p = triemr++;
        trie[p][count] = 0;
        trie[p][dcount] = 0;
        graph[p].son = cur;
        graph[p].next = -1;
        for (c = cur; graph[c].next != -1; c = graph[c].next);
        t = grapmr++;
        graph[t].letter = a[i];
        graph[t].son = p;
        graph[t].next = -1;
        graph[c].next = t;
        cur = p;
    }
    trie[cur][dcount]++;
    return;
}

int sink(char *a, int len, int *pl) {
    int cur = 0, nxt, i, c;
    for (i = 0; i < len; i++) {
        nxt = -1;
        for (c = graph[cur].next; c != -1; c = graph[c].next) {
            if (graph[c].letter == a[i]) {
                nxt = graph[c].son;
                break;
            }
        }
        if (nxt == -1) {
            pl -= (len - i);
            return cur;
        } else {
            cur = nxt;
        }
    }
    return cur;
}

int dsink(char *a, int len, int *pl) {
    int cur = 0, nxt, i, c;
    for (i = 1; i <= len; i++) {
        nxt = -1;
        for (c = graph[cur].next; c != -1; c = graph[c].next) {
            if (graph[c].letter == a[len - i]) {
                nxt = graph[c].son;
                break;
            }
        }
        if (nxt == -1) {
            pl += (len + 1 - i);
            return cur;
        } else {
            cur = nxt;
        }
    }
    return cur;
}

int main() {
    char *nowp;
    int n, i, j, k;
    long long ans;
    trie[0][count] = 0;
    trie[0][dcount] = 0;
    graph[0].son = -1;
    graph[0].next = -1;
    triemr = 1;
    grapmr = 4200010;
    nowp = data;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %s", &len[i], nowp);
        str[i] = nowp;
        insert(nowp, len[i]);
        dinsert(nowp, len[i]);
        nowp = nowp + len[i] + 1;
    }
    ans = 0;
    for (i = 0; i < n; i++) {
        kmp[0] = -1;
        for (j = 1; j <= len[i]; j++) {
            k = kmp[j - 1];
            while (k > -1 && str[i][len[i] - j] != str[i][len[i] - k - 1])
                k = kmp[k];
            kmp[j] = k + 1;
        }
        for (j = 0; j < len[i]; j++) {
            palind[j] = 0;
        }
        
        k = 0;
        for (j = 0; j < len[i]; j++) {
            while (k > -1 && str[i][j] != str[i][len[i] - k - 1])
                k = kmp[k];
            k++;
        }
        while (k > 0) {
            palind[len[i] - k] = 1;
            k = kmp[k];
        }
        j = len[i] - 1;
        k = sink(str[i], len[i], &j);
        ans += trie[k][count];
        for (; j > 0; j--) {
            k = graph[k].son;
            if (palind[j])
                ans += trie[k][count];
        }

        kmp[0] = -1;
        for (j = 1; j <= len[i]; j++) {
            k = kmp[j - 1];
            while (k > -1 && str[i][j - 1] != str[i][k])
                k = kmp[k];
            kmp[j] = k + 1;
        }
        for (j = 0; j < len[i]; j++)
            palind[j] = 0;
        k = 0;
        for (j = len[i] - 1; j >= 0; j--) {
            while (k > -1 && str[i][j] != str[i][k])
                k = kmp[k];
            k++;
        }
        while (k > 0) {
            palind[k - 1] = 1;
            k = kmp[k];
        }
        j = 0;
        k = dsink(str[i], len[i], &j);
        for (; j < len[i] - 1; j++) {
            k = graph[k].son;
            if (palind[j])
                ans += trie[k][dcount];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
