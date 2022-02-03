#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
#define all(x) x.begin(), x.end()
#define f first
#define s second
using pii = pair<int, int>;

void solve(){
    int n; cin >> n;
    vc<pii> a(n); 
    for(int i=0; i<n; i++){
        cin >> a[i].f; a[i].s = i;
    }
    sort(all(a));
    vc<int> act(n, 1);
    for(int i=(n-3)/2; i>=0; i--){
        act[i] = act[2*i+1] + act[2*i+2] + 1;
    }
    int curt = 0; int pos = 1;
    for(int i=0; i<n; i++){
        int cur = a[i].s;
        if(!act[cur]) continue;
        curt += act[cur];
        if(curt > a[i].f){pos=0; break;}
        int p = cur-1;
        while(p>=0){p/=2; act[p]-=act[cur]; p--;}
        act[cur] = 0;

        queue<int> child;
        if(2*cur+1 < n) child.push(2*cur+1);
        if(2*cur+2 < n) child.push(2*cur+2);
        while(!child.empty()){
            int idx = child.front(); child.pop();
            if(act[idx] == 0) continue;
            act[idx] = 0;
            if(2*idx+1 < n) child.push(2*idx+1);
            if(2*idx+2 < n) child.push(2*idx+2);
        }
    }
    if(pos) cout << "yes\n";
    else cout << "no\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}