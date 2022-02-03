#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
using pii = pair<int, int>;

void solve(){
    int n, k; cin >> n >> k;
    vc<pii> a(n);
    for(int i=0; i<n; i++) cin >> a[i].first >> a[i].second;
    vc<int> price(k+1, LONG_MAX); price[0] = 0;
    vc<set<int>> state(k+1);
    for(int i=0; i<=k; i++){
        if(price[i] == LONG_MAX) continue;
        for(int j=0; j<n; j++){
            int newv = min(i + a[j].second, k);
            set<int> cur = state[i]; cur.insert(j);
            int curc = price[i] + a[j].first;
            if(curc < price[newv] || cur.size() > state[newv].size()){
                price[newv] = curc; state[newv] = cur;
            }
        }
    }
    cout << price[k] << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}