#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector

void solve(){
    int n; cin >> n;
    vc<int> a(n); for(int i=0; i<n; i++) cin >> a[i];
    vc<vc<int>> dp(n, vc<int>(n));
    for(int i=0; i<n; i++){
        dp[i][i] = a[i];
        if(i==n-1) continue;
        dp[i][i+1] = max(a[i], a[i+1]);
        if(i==n-2) continue;
        dp[i][i+2] = max(a[i] + min(a[i+1], a[i+2]), a[i+2] + min(a[i], a[i+1]));
    }

    for(int l=3; l<=n; l++){
        for(int i=0; i+l-1<n; i++){
            int j = i+l-1;
            int p1 = a[i] + min(dp[i+1][j-1], dp[i+2][j]);
            int p2 = a[j] + min(dp[i+1][j-1], dp[i][j-2]);
            dp[i][j] = max(p1, p2);
        }
    }
    
    cout << dp[0][n-1] << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}