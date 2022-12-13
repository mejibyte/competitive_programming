#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
ll arr[1000005]={0};
ll tree[1000005]={0};
ll lazy[1000005]={0};
void build(int node,int start,int end){
	//Leaf node
	if(start==end){
		tree[node]=arr[start];
		return;
	}
	int mid=(start+end)>>1;
	build(2*node,start,mid);
	build(2*node+1,mid+1,end);
	tree[node]=tree[2*node]+tree[2*node+1];
}
void updateRange(int node, int start, int end, int l, int r, ll val)
{
    if(lazy[node] != 0)
    { 
        // This node needs to be updated
        tree[node] += (end - start + 1) * lazy[node];    // Update it
        if(start != end)
        {
            lazy[node*2] += lazy[node];                  // Mark child as lazy
            lazy[node*2+1] += lazy[node];                // Mark child as lazy
        }
        lazy[node] = 0;                                  // Reset it
    }
    if(start > end or start > r or end < l)              // Current segment is not within range [l, r]
        return;
    if(start >= l and end <= r)
    {
        // Segment is fully within range
        tree[node] += (end - start + 1) * val;
        if(start != end)
        {
            // Not leaf node
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);        // Updating left child
    updateRange(node*2 + 1, mid + 1, end, l, r, val);   // Updating right child
    tree[node] = tree[node*2] + tree[node*2+1];        // Updating root with max value 
}

ll queryRange(int node, int start, int end, int l, int r)
{
    if(start > end or start > r or end < l)
        return 0;         // Out of range
    if(lazy[node] != 0)
    {
        // This node needs to be updated
        tree[node] += (end - start + 1) * lazy[node];            // Update it
        if(start != end)
        {
            lazy[node*2] += lazy[node];         // Mark child as lazy
            lazy[node*2+1] += lazy[node];    // Mark child as lazy
        }
        lazy[node] = 0;                 // Reset it
    }
    if(start >= l and end <= r)             // Current segment is totally within range [l, r]
        return tree[node];
    int mid = (start + end) / 2;
    ll p1 = queryRange(node*2, start, mid, l, r);         // Query left child
    ll p2 = queryRange(node*2 + 1, mid + 1, end, l, r); // Query right child
    return (p1 + p2);
}
int main() {
	fastio()
    int t,n,c,p,q,v,inp;
    cin>>t;
    while(t--){
        cin>>n>>c;
        memset(tree,0,sizeof(tree));
        memset(lazy,0,sizeof(tree));
        memset(arr,0,sizeof(tree));
        while(c--){
            cin>>inp;
            if(!inp){
                cin>>p>>q>>v;
                updateRange(1,0,n-1,p-1,q-1,v);
            }
            else{
                cin>>p>>q;
                ll ans=queryRange(1,0,n-1,p-1,q-1);
                cout<<ans<<endl;

            }

        }
    }
    
}
