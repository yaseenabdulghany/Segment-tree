#include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 2e5+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e12+5;
int sz;
struct node {
    int sum, mx, pre, suff;
};
struct SegTree {

    int mn = -1e16 + 5;
    node temp = {mn, mn, mn, mn};
    vector<node> seg;

    SegTree(int n) {
        sz = n;
        seg.assign(4 << __lg(n), temp);
    }

    node merge_nodes(node l, node r) {
        node ans = temp;
        ans.sum = l.sum + r.sum;
        ans.pre = max(l.pre, l.sum + r.pre);
        ans.suff = max(r.suff, l.suff + r.sum);
        ans.mx = max({l.mx, r.mx, l.suff + r.pre, l.sum + r.sum});
        return ans;
    }

    void update(int idx, node val, int st = 1, int end = sz, int p = 1) {
        if (st == end) {
            seg[p] = val;
            return;
        }
        int mid = (st + end) >> 1;
        if (idx <= mid) update(idx, val, st, mid, p * 2);
        else update(idx, val, mid + 1, end, p * 2 + 1);
        node l = seg[2 * p], r = seg[2 * p + 1];
        seg[p] = merge_nodes(l, r);
    }

    node get(int l, int r, int st = 1, int end = sz, int p = 1) {
        if (st >= l && end <= r)return seg[p];           // totally inside
        if (st > r || end < l) return temp;             // totally outside
        int mid = (st + end) >> 1;
        node L = get(l, r, st, mid, 2 * p);
        node R = get(l, r, mid + 1, end, 2 * p + 1);
        return merge_nodes(L, R);
    }
};
void solve() {
    int n , q ;
    cin >> n ;
    SegTree seg(n);
    for (int i = 1; i <= n; ++i) {
        int x ;
        cin >> x ;
        seg.update(i,{x,x,x,x});
    }
    cin >> q ;
    while (q--) {
        int pos, val;
        cin >> pos >> val;
        cout<<seg.get(pos,val).mx<<"\n";
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
