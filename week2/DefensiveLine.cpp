#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
#define pb push_back
#define f first
#define s second
using pii = pair<int, int>;

void solve(){
    int n, m, k; cin >> n >> m >> k;
    vc<int> d(n+1); 
    for(int i=1; i<=n; i++){cin >> d[i]; d[i] += d[i-1];}
    vc<pii> itv;
    int r = 1;
    for(int i=0; i<n; i++){
        while(r<=n && d[r] - d[i] < k) r++;
        if(r>n) break;
        if(d[r] - d[i] == k){
            itv.pb(make_pair(i, r));
        }
    }
    int N = itv.size();
    if(N < m){cout << "fail\n"; return;}
    vc<vc<int>> dp(m, vc<int>(N, -1));
    int maxlen = -1;
    for(int i=0; i<N; i++){
        maxlen = max(maxlen, itv[i].s - itv[i].f);
        dp[0][i] = maxlen;
    }
    for(int i=1; i<m; i++){
        int idx = 0;
        for(int j=i; j<N; j++){
            while(idx < j && itv[idx].s <= itv[j].f) idx++;
            dp[i][j] = dp[i][j-1];
            if(idx != 0 && dp[i-1][idx-1] != -1){
                dp[i][j] = max(dp[i][j-1], itv[j].s - itv[j].f + dp[i-1][idx-1]);
            }
        }
    }
    int ans = dp[m-1][N-1];
    if(ans == -1) cout << "fail\n";
    else cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}