#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector

int recurse(int diag, int i1, int i2, int n, vc<vc<int>> &coin, vc<vc<vc<int>>> &dp){
    if(diag == 0) return coin[0][0];
    if(dp[diag][i1][i2] != -1) return dp[diag][i1][i2];
    int j1 = diag - i1;
    int j2 = diag - i2;
    int ans = 0;
    if(i1 > 0 && i2 > 0) ans = max(ans, recurse(diag-1, i1-1, i2-1, n, coin, dp));
    if(i1 > 0 && j2 > 0) ans = max(ans, recurse(diag-1, i1-1, i2, n, coin, dp));
    if(j1 > 0 && i2 > 0) ans = max(ans, recurse(diag-1, i1, i2-1, n, coin, dp));
    if(j1 > 0 && j2 > 0) ans = max(ans, recurse(diag-1, i1, i2, n, coin, dp));
    ans += coin[i1][j1];
    if(i1 != i2 || j1 != j2) ans += coin[i2][j2];
    dp[diag][i1][i2] = ans;
    return ans;
}

void solve(){
    int n; cin >> n;
    vc<vc<int>> coin(n, vc<int>(n));
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) cin >> coin[i][j];
    vc<vc<vc<int>>> dp(2*n, vc<vc<int>>(n, vc<int>(n, -1)));
    int ans = recurse(2*n-1, n-1, n-1, n, coin, dp);
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}
