#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
#define f first
#define s second
using pii = pair<int, int>;

int recurse(int l, int r, int m, vc<int> &a, vc<vc<int>> &dp){
    if(r-l+1 <= m) return max(a[l], a[r]);
    if(dp[l][r] != -1) return dp[l][r];
    int ansr, ansl, ans=LONG_MAX;
    for(int i=0; i<=m; i++){
        if(i==0) ansr = recurse(l, r-m, m, a, dp) + a[r];
        else if(i==m) ansl = recurse(l+m, r, m, a, dp) + a[l];
        else ans = min(ans, recurse(l+i, r-m+i, m, a, dp));
    }
    ans = max(min(ans + a[r], ansr), min(ans + a[l], ansl));
    dp[l][r] = ans;
    return ans;
}

void solve(){
    int n, m, k; cin >> n >> m >> k;
    vc<int> a(n); for(int i=0; i<n; i++) cin >> a[i];
    vc<vc<int>> dp(n, vc<int>(n, -1));
    int ans = LONG_MAX;
    for(int i=0; i<=k; i++){
        ans = min(ans, recurse(i, n-1-k+i, m, a, dp));
    }
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}