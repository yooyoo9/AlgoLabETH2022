#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
#define pb push_back

int recurse(int cur, vc<int> &steps, vc<vc<int>> &g){
    if(steps[cur] != -1) return steps[cur];
    int ans = LONG_MAX;
    int n = g.size();
    for(int x : g[cur]){
        if(x == n-1){steps[cur]=1; return 1;}
        int maxi = 0;
        for(int y : g[x]) maxi = max(maxi, recurse(y, steps, g));
        ans = min(ans, maxi);
    }
    ans += 2;
    steps[cur] = ans;
    return ans;
}

void solve(){
    int n, m; cin >> n >> m;
    int r, b; cin >> r >> b; r--; b--;
    vc<vc<int>> g(n);
    for(int i=0; i<m; i++){
        int x, y; cin >> x >> y; g[x-1].pb(y-1);
    }
    // pos_r, pos_b, s_m, r_b
    vc<int> steps(n, -1); steps[n-1] = 0;
    int r1 = recurse(r, steps, g);
    int b1 = recurse(b, steps, g);

    int ans = b1 < r1 || (b1==r1 && r1%2==0);
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}