#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
#define pb push_back
#define all(x) x.begin(), x.end()

void solve(){
    int n; cin >> n;
    vc<int> a(n); for(int i=0; i<n; i++) cin >> a[i];
    sort(all(a));
    int maxn = 0; int ans = LONG_MAX;
    vc<int> res;
    int r = 0;
    for(int i=0; i<n; i++){
        while(r<n && a[r] - a[i] <= 200) r++;
        if(maxn > r-i) continue;
        int cur = a[r-1] - a[i] + 1;
        if(maxn == r-i) {
            ans = min(ans, cur/2);
        } else{
            maxn = r-i; ans = cur/2; res.clear();
        }
        res.pb(a[i] + cur/2);
        if(cur%2 == 0) res.pb(a[i] + cur/2 - 1);
    }
    cout << maxn << " " << ans << "\n";
    sort(all(res));
    for(int x : res) cout << x << " ";
    cout << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}