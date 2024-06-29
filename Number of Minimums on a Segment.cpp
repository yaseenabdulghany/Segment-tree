#include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 2e5+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e12+5;
int sz;
struct SegTree {
    struct node{
        int mn ,  cnt ;
        node(){}
        node(int val , int c){
            mn=val;
            cnt=c;
        }
    };
    vector<node> seg;
    SegTree(int n) {
        sz = n;
        seg.assign(4 << __lg(n),{LLONG_MAX,0});
    }
    int mrg(int a , int b){
        return min(a,b);
    }
    node merge_nodes(node l ,node r) {
        node ans;
        if (l.mn == r.mn) {
            ans.mn = l.mn;
            ans.cnt = l.cnt + r.cnt;
            return ans;
        }
        if (l.mn < r.mn) {
            ans.mn = l.mn;
            ans.cnt = l.cnt;
            return ans;
        }
        if (l.mn > r.mn) {
            ans.mn = r.mn;
            ans.cnt = r.cnt;
            return ans;
        }
    }
    void update(int idx, int val ,int st = 1, int end = sz, int p = 1) {
        if (st == end) {
            seg[p].mn=val;
            seg[p].cnt=1;
            return ;
        }
        int mid = (st + end) / 2;
        if (idx <= mid) update(idx, val, st, mid, p * 2);
        else update(idx, val, mid + 1, end, p * 2 + 1);
        node l = seg[2*p] , r= seg[2*p+1];
        if (l.mn == r.mn) {
            seg[p].mn = l.mn;
            seg[p].cnt = l.cnt + r.cnt;
        }
        if (l.mn < r.mn) {
            seg[p].mn = l.mn;
            seg[p].cnt = l.cnt ;
        }
        if (l.mn > r.mn) {
            seg[p].mn = r.mn;
            seg[p].cnt = r.cnt;
        }
    }
    node get(int l, int r, int st = 1, int end = sz, int p = 1) {
        if (st >= l && end <= r){
            return seg[p];// totally inside
        }
        if (st > r || end < l)  return node(LLONG_MAX,1);; // totally outside
        int mid = (st + end) / 2;
        node L = get(l, r, st, mid, 2 * p);
        node R = get(l, r, mid + 1, end, 2 * p + 1);
        if (L.mn == R.mn) {
            return node(L.mn,L.cnt + R.cnt);
        }
        if (L.mn < R.mn) {
            return node(L.mn,L.cnt);
        }
        if (L.mn > R.mn) {
            return node(R.mn,R.cnt);
        }
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
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos, val;
            cin >> pos >> val;
            seg.update(pos+1, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout<<seg.get(l+1,r).mn<<" "<<seg.get(l+1,r).cnt<<"\n";
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
