#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
#define f first
#define s second
#define all(x) x.begin(), x.end()
using pii = pair<int, int>;

int recurse(int cur, int nb, int h, int n, vc<pii> &pa, vc<vc<vc<int>>> &dp){
    if(n-cur < nb) return -1;
    if(nb==0 && h==0) return 0;
    if(nb==0 && h>0) return -1;
    if(dp[cur][nb][h] != -2) return dp[cur][nb][h];
    int ans1 = recurse(cur+1, nb, h, n, pa, dp);
    int ans2 = recurse(cur+1, nb-1, max( (int) 0, h-pa[cur].s), n, pa, dp);
    if(ans2 != -1) ans2 += pa[cur].f;
    int ans = max(ans1, ans2);
    dp[cur][nb][h] = ans;
    return ans;
}

void solve(){
    int n, m; cin >> n >> m;
    int a, b; cin >> a >> b;
    int p, h, w; cin >> p >> h >> w;
    vc<pii> pa(n); for(int i=0; i<n; i++) cin >> pa[i].f >> pa[i].s;
    vc<int> pb(m); for(int i=0; i<m; i++) cin >> pb[i];
    sort(all(pb)); reverse(all(pb));
    for(int i=1; i<m; i++) pb[i] += pb[i-1];

    // dp[first i potions][at most number potions taken][happiness needed] = max power
    vc<vc<vc<int>>> dp(n, vc<vc<int>>(n+1, vc<int>(h+1, -2)));
    int ans = LONG_MAX;
    for(int i=0; i<m; i++){
        if(pb[i] < w) continue;
        int typea = n;
        if(a > 0) typea = min(n, (pb[i] - w) / a);
        for(int j=0; j<typea; j++){
            int maxp = recurse(0, j+1, h, n, pa, dp);
            if(maxp == -1) continue;
            if(maxp - (i+1) * b >= p){ans = min(ans, i+j+2); break;}
        }
    }
    if(ans == LONG_MAX) ans = -1;
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}