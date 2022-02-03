#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vc vector
#define f first
#define s second
#define pb push_back
using pii = pair<int, int>;

void solve(){
    int n, m, x, k; cin >> n >> m >> x >> k;
    vc<vc<pii>> g(n);
    for(int i=0; i<m; i++){
        int u, v, p; cin >> u >> v >> p;
        g[u].push_back(make_pair(v, p));
    }
    vc<vc<int>> dp(k+1, vc<int>(n, 0));
    for(int i=1; i<=k; i++){
        for(int j=0; j<n; j++){
            int cur = 0;
            int idx = g[j].size() == 0 ? 0 : j;
            for(auto neigh : g[idx]){
                cur = max(cur, dp[i-1][neigh.first] + neigh.second);
            }
            dp[i][j] = cur;
        }
    }
    if(dp[k][0] < x){cout << "Impossible\n"; return;}
    for(int i=0; i<=k; i++){
        if(dp[i][0] >= x){cout << i << "\n"; return;}
    }
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}