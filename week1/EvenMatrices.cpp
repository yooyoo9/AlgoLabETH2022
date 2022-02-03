#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector

void solve(){
    int n; cin >> n;
    vc<vc<int>> a(n+1, vc<int>(n+1));
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            int cur; cin >> cur;
            a[i][j] = (cur + a[i-1][j] + a[i][j-1] - a[i-1][j-1])%2;
        }
    }
    int ans = 0;
    for(int i1=0; i1<n; i1++){
        for(int i2=i1+1; i2<=n; i2++){
            vc<int> cur(n+1);
            for(int j=0; j<=n; j++){
                cur[j] = (a[i2][j] - a[i1][j] + 2)%2;
            }
            int nodd = 0;
            for(int j=1; j<=n; j++){
                if(cur[j]){ans += nodd; nodd++;}
                else ans += j-nodd;
            }
        }
    }
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}