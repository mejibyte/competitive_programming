// Sample solution of NWERC-2004-Pipes by Ola Hugosson
#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;

#define D(x) cout << #x " = " << (x) << endl

#define NONE  0
#define IN    1
#define OUT   2
#define FEDECOST 0xfede
#define MAXSTATES 5798 // pre-calculated
#define GETTYPE(sidx,i) (((sidx)>>(2*(i)))&3)
#define SETTYPE(type,i) (((type)<<(2*(i))))

int state[MAXSTATES], newstate[MAXSTATES], map[MAXSTATES];
short invmap[1<<(2*11)];

// calculate a map used to enumerate all valid boundaries
int genmap(int c, int n, int i, int nest, int sidx)
{
    printf("c = %d, n = %d, i = %d, nest = %d, sidx = %x\n", c, n, i, nest, sidx);
    if (nest>=0 && i<=c) {
        n=genmap(c,n,i+1,nest,  sidx|SETTYPE(NONE,i));
        n=genmap(c,n,i+1,nest+1,sidx|SETTYPE(IN,i));
        n=genmap(c,n,i+1,nest-1,sidx|SETTYPE(OUT,i));
    }
    else if (nest==0){
        map[n++]=sidx;
        printf("mask = %X, nest = 0\n", sidx);
    }
    assert(n<=MAXSTATES);
    return n;
}

int main(){
    int floors, r, c, x, y, n, i, j, sidx, left, up, right, down, cost, prevcost;
    char lrwall[30],udwall[30];
    for( scanf("%d",&floors); floors--;) {
        scanf("%d %d\n",&r,&c);
        gets(udwall); //dummy-input
        n=genmap(c,0,0,0,0);
        
        for (int i = 0; i < n; ++i){
            int mask = map[i];
            printf("mask = %X\n", mask);
            for (int j = 0; j <= c; ++j){
                int what = GETTYPE(mask, j);
                switch (what){
                    case NONE:
                    cout << "NONE ";
                    break;
                    case IN:
                    cout << "IN ";
                    break;
                    case OUT:
                    cout << "OUT ";
                    break;
                }
            }
            cout << endl;
        }
        
        for(i=0; i<n; i++) {
            invmap[map[i]]=i;
            newstate[i]=FEDECOST;
        }
        newstate[invmap[0]]=0;
        for(y=0; y<r; y++) {
            gets(lrwall);
            gets(udwall);
            for(x=0; x<c; x++) {
                for(i=0; i<n; i++) {
                    state[i]=newstate[i];
                    newstate[i]=FEDECOST;
                }
                for(i=0; i<n; i++) {
                    static const char lut[3][3][3] =
                        {{{1, IN,   OUT }, {2, NONE, IN  }, {2, NONE, OUT }},
                        {{2, NONE, IN  }, {1, NONE, NONE}, {0, NONE, NONE}}, // the 0 prevents internal loops
                        {{2, NONE, OUT }, {1, NONE, NONE}, {1, NONE, NONE}}}; 
                    prevcost = (x>0 ? state[i] : ((map[i]&3)==NONE) ? state[invmap[map[i]>>2]] : FEDECOST);
                    if (prevcost>=FEDECOST)  
                        continue; // speed up somewhat
                    sidx=map[i];
                    left=GETTYPE(sidx,x);
                    up  =GETTYPE(sidx,x+1);
                    for(j=0; j<lut[left][up][0]; j++) {
                        down =lut[left][up][1+j];
                        right=lut[left][up][2-j];
                        cost = prevcost + (right==NONE ? 0 : lrwall[2*x+2]-'0') + 
                            (down ==NONE ? 0 : udwall[2*x+1]-'0');
                        if (left==up && left!=NONE) { // find matching IN/OUT pair
                            int nest=0, xx=(left==OUT)? x : x+1;
                            while(nest += GETTYPE(sidx,xx)==OUT ? -1 : GETTYPE(sidx,xx)==IN ? +1 : 0)
                                xx += nest<0 ? -1 : 1;
                            sidx ^= SETTYPE(3,xx);  // toggle IN<->OUT
                        }
                        sidx = sidx & ~SETTYPE(15,x) | SETTYPE(down,x) | SETTYPE(right,x+1);
                        if (cost<newstate[invmap[sidx]])
                            newstate[invmap[sidx]]=cost;
                    }
                }
            }
        }
        printf("%d\n",state[invmap[(IN<<(2*c-2))|(OUT<<(2*c))]]);
    }
    return 0;
}
