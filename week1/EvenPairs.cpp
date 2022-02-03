#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector

void solve(){
    int n; cin >> n;
    vc<int> odd(n+1);
    for(int i=0; i<n; i++){
        int x; cin >> x;
        odd[i+1] = (odd[i] + x)%2;
    }
    int nodd = 0;
    int ans = 0;
    for(int i=1; i<=n; i++){
        if(odd[i]) {ans += nodd; nodd++;}
        else ans += i-nodd;
    }
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}