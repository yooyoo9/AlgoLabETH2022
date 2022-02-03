#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
#define f first
#define s second
#define all(x) x.begin(), x.end()
using pii = pair<int, int>;

void solve(){
    int n; cin >> n;
    vc<pii> boat(n);
    for(int i=0; i<n; i++){
        cin >> boat[i].s >> boat[i].f;
    }
    sort(all(boat));
    int ans = 0; int cure = LONG_MIN;
    for(int i=0; i<n; i++){
        int best = LONG_MAX; int last=n;
        for(int j=i; j<n; j++){
            if(best <= boat[j].f){last=j; break;}
            int cur = max(cure + boat[j].s, boat[j].f);
            if(best > cur){best = cur;}
        }
        ans++;
        cure = best;
        i = last-1;
    }
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}