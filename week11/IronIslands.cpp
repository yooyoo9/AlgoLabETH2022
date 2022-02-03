#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
using pii = pair<int, int>;

void solve(){
    int n, k, w; cin >> n >> k >> w;
    vc<int> a(n); for(int i=0; i<n; i++) cin >> a[i];
    map<int, vc<pii>> g;
    int ans = 0;
    for(int i=0; i<w; i++){
        int l; cin >> l;
        vc<int> b(l+1);
        int sum = 0;
        for(int j=0; j<l; j++){
            int cur; cin >> cur;
            b[j+1] = a[cur] + b[j];
            sum += a[cur];
            if(g.find(sum) == g.end()){
                g[sum] = vc<pii>(1, make_pair(j, i));
            } else {
                g[sum].push_back(make_pair(j, i));
            }
        }
        int idx = 0;
        for(int j=0; j<=l; j++){
          while(idx <= l && b[idx] - b[j] < k) idx++;
          if(idx <= l && b[idx] - b[j] == k) ans = max(ans, idx-j);
          if(idx > l) break;
        }
    }
    for(auto cur : g){
        sort(cur.second.begin(), cur.second.end());
        reverse(cur.second.begin(), cur.second.end());
        g[cur.first] = cur.second;
    }
    if(g.find(k) != g.end()) ans = g[k][0].first;
    for(auto cur : g){
        int n1 = cur.first;
        int n2 = k-n1+a[0];
        if(g.find(n2) == g.end()) continue;
        pii p1 = g[n1][0], q1 = g[n2][0];
        if(p1.second != q1.second) {
            ans = max(ans, p1.first + q1.first + 1);
        } else {
            if(g[n1].size() > 1){
                pii p2 = g[n1][1];
                ans = max(ans, p2.first + q1.first + 1);
            }
            if(g[n2].size() > 1){
                pii q2 = g[n2][1];
                ans = max(ans, p1.first + q2.first + 1);
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