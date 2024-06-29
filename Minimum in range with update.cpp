#include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 2e5+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e12+5;
int sz ;
struct SegTree {
    vector<int> seg;
    int temp=1e9+1;
    SegTree(int n) {
        sz = n;
        seg.assign(4 << __lg(n),temp);
    }
    int mrg(int a , int b){
        return min(a,b);
    }
    void update(int idx, int val, int st = 1, int end = sz, int p = 1) {
        if (st == end) {
            seg[p] = val;
            return;
        }
        int mid = (st + end) / 2;
        if (idx <= mid) update(idx, val, st, mid, p * 2);
        else update(idx, val, mid + 1, end, p * 2 + 1);

        seg[p] = mrg(seg[2 * p], seg[2 * p + 1]);
    }
    int get(int l, int r, int st = 1, int end = sz, int p = 1) {
        if (st >= l && end <= r)return seg[p];       // totally inside
        if (st > r || end < l) return temp; // totally outside
        int mid = (st + end) / 2;
        int L = get(l, r, st, mid, 2 * p);
        int R = get(l, r, mid + 1, end, 2 * p + 1);
        return mrg(L, R);
    }
};
void solve() {
    int n , q ;
    cin >> n >> q ;
    SegTree se(n);
    for (int i = 1; i <= n; ++i) {
        int x ;
        cin >> x ;
        se.update(i,x);
    }
    while (q--){
        int type ;
        cin >> type ;
        if(type==1){
            int pos , val ;
            cin >> pos >> val ;
            se.update(pos+1,val);
        }
        else {
            int l , r ;
            cin >> l >> r ;
            cout<<se.get(l+1,r)<<"\n";
        }
    }

}

int32_t main(){
    FAST_DOT_COM
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    int t=1 ;
//    cin>>t ;
    while (t--) solve();
    return 0;
}
