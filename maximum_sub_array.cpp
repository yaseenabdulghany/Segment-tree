#include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 2e5+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e12+5;
int sz;
struct SegTree {
    struct node {
        int sum, mx, pre, suff;

        node() : pre(0), suff(0), mx(0), sum(0) {}

        node(int v) : sum(v), mx(max(v, 0LL)), suff(max(v, 0LL)), pre(max(v, 0LL)) {}
    };

    vector<node> seg;

    SegTree(int n) {
        sz = n;
        seg.assign(4 << __lg(n), 0);
    }

    node merge_nodes(node l, node r) {
        node ans;
        ans.sum = l.sum + r.sum;
        ans.mx = max({l.mx, r.mx, l.suff + r.pre});
        ans.pre = max(l.pre, l.sum + r.pre);
        ans.suff = max(r.suff, l.suff + r.sum);
        return ans;
    }

    void update(int idx, int val, int st = 1, int end = sz, int p = 1) {
        if (st == end) {
            seg[p] = {val};
            return;
        }
        int mid = (st + end) / 2;
        if (idx <= mid) update(idx, val, st, mid, p * 2);
        else update(idx, val, mid + 1, end, p * 2 + 1);
        node l = seg[2 * p], r = seg[2 * p + 1];
        seg[p] = merge_nodes(l, r);
    }

    int query() {
        return seg[1].mx;
    }
};
void solve() {
    int n , q ;
    cin >> n >> q ;
    SegTree seg(n);
    for (int i = 1; i <= n; ++i) {
        int x ;
        cin >> x ;
        seg.update(i,x);
    }
    cout<<seg.query()<<"\n";
    while (q--) {
        int pos, val;
        cin >> pos >> val;
        seg.update(pos+1, val);
        cout<<seg.query()<<"\n";
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
