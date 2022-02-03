#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
using pii = pair<int, int>;

void solve(){
    int n, st; cin >> n >> st; st--;
    vc<vc<int>> g(n, vc<int>(n));
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            int cur; cin >> cur;
            g[i][i+j+1] = cur;
            g[i+j+1][i] = cur;
        }
    }
    vc<int> inn(n); int mst = 0;
    vc<vc<int>> edges(n, vc<int>(n));
    vc<vc<int>> elist(n);
    priority_queue<pair<int, pii>, vc<pair<int, pii>>, greater<pair<int, pii>>> pq;
    pq.push(make_pair(0, make_pair(st, -1)));
    while(!pq.empty()){
        auto cur = pq.top(); pq.pop();
        int idx = cur.second.first; int pidx = cur.second.second;
        if(inn[idx]) continue;
        if(pidx != -1){
            edges[idx][pidx] = edges[pidx][idx] = 1; 
            elist[idx].push_back(pidx);  elist[pidx].push_back(idx);
            mst += g[idx][pidx];
        }
        inn[idx] = 1; 
        for(int i=0; i<n; i++){
            if(inn[i]) continue;
            pq.push(make_pair(g[idx][i], make_pair(i, idx)));
        }
    }
    int ans = LONG_MAX;
    for(int i=0; i<n; i++){
        vc<int> maxw(n, -1); maxw[i] = 0;
        queue<int> q; q.push(i);
        while(!q.empty()){
            int cur = q.front(); q.pop();
            for(int neigh : elist[cur]){
                if(maxw[neigh] != -1) continue;
                maxw[neigh] = max(maxw[cur], g[cur][neigh]);
                q.push(neigh);
            }
        }
        for(int j=i+1; j<n; j++){
            if(edges[i][j]) continue;
            ans = min(ans, mst - maxw[j] + g[i][j]);
        }
    }
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}