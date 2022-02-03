#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector

void solve(){
    int n; cin >> n;
    int ans = 0;
    int cur = 1;
    for(int i=0; i<n; i++){
        int x; cin >> x;
        if(cur == 0) continue;
        cur = max(cur-1, x - 1);
        ans++;
    }
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}