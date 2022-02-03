#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
using pii = pair<int, int>;

tuple<int, int, int> recurse(int cur, vc<int> &a, vc<vc<pii>> &g){
    int n = g[cur].size();
    if(n == 0){
        return make_tuple(a[cur], 1, 0);
    }
    vc<tuple<int, int, int, int>> child(n);
    for(int i=0; i<n; i++){
        auto c = recurse(g[cur][i].first, a, g);
        child[i] = make_tuple(get<0>(c), get<1>(c), get<2>(c), g[cur][i].second);
    }
    sort(child.begin(), child.end(), [](tuple<int, int, int, int> &lhs, tuple<int, int, int, int> &rhs){
        return get<1>(lhs) * (get<2>(rhs) + get<3>(rhs)) > get<1>(rhs) * (get<2>(lhs) + get<3>(lhs));
    });
    int ans = a[cur]; int t = 0, nchild = 1, curl = 0;
    for(auto c : child){
        t += get<3>(c);
        ans += get<0>(c) - get<1>(c) * t;
        t += 2*get<2>(c) + get<3>(c);
        nchild += get<1>(c); curl += get<2>(c) + get<3>(c);
    }
    return make_tuple(ans, nchild, curl);
}


void solve(){
    int n; cin >> n; n++;
    vc<int> a(n); for(int i=1; i<n; i++) cin >> a[i];
    vc<vc<pii>> g(n);
    for(int i=0; i<n-1; i++){
        int u, v, l; cin >> u >> v >> l;
        g[u].push_back(make_pair(v, l));
    }
    tuple<int, int, int> res = recurse(0, a, g);
    cout << get<0>(res) << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}