#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector

int recurse(int cur, int state, vc<vc<int>> &dp, vc<int> &c, vc<vc<int>> &g){
    // 0: i am covered
    // 1: i need to pay my cost
    // 2: i need to be covered (either my cost or one of my children)
    if(dp[cur][state] != -1) return dp[cur][state];
    int n = g[cur].size();
    if(n == 0){
        if(state==0) return 0;
        else return c[cur];
    }
    int ans = c[cur];
    for(int x : g[cur]){
        ans += recurse(x, 0, dp, c, g);
    }
    if(state == 1){dp[cur][state] = ans; return ans;}
    
    vc<int> covcost(n); int sum = 0;
    for(int i=0; i<n; i++){
        covcost[i] = recurse(g[cur][i], 2, dp, c, g);
        sum += covcost[i];
    }
    int ans1 = ans;
    if(state == 2){
        for(int i=0; i<n; i++){
            int cura = sum - covcost[i];
            cura += recurse(g[cur][i], 1, dp, c, g);
            ans1 = min(ans1, cura);
        }
    } else {
        ans1 = min(ans1, sum);
    }
    dp[cur][state] = ans1;
    return ans1;
}

void solve(){
    int n; cin >> n;
    vc<vc<int>> g(n);
    for(int i=0; i<n-1; i++){
        int x, y; cin >> x >> y; g[x].push_back(y);
    }
    vc<int> c(n);
    for(int i=0; i<n; i++) cin >> c[i];
    vc<vc<int>> dp(n, vc<int>(3, -1));
    int ans = recurse(0, 2, dp, c, g);
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}