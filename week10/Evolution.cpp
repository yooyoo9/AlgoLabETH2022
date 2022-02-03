///1
#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector

void solve(){
    int n, q; cin >> n >> q;
    map<string, int> smap;
    vc<string> name(n);
    vc<int> age(n);
    vc<vc<int>> tree(n);
    for(int i=0; i<n; i++){
        string cur; cin >> cur; smap[cur] = i;
        name[i] = cur;
        int a; cin >> a; age[i] = a;
    }
    for(int i=0; i<n-1; i++){
        string cur, p; cin >> cur >> p;
        int child = smap[cur], par = smap[p];
        tree[child].push_back(par);
    }
    vc<int> ok(n); bool cont = true; int oidx;
    while(cont){
        for(int i=0; i<n; i++){
            if(ok[i]) continue;
            if(tree[i].size() == 0) {oidx=i; ok[i] = 1; continue;}
            int lastp = tree[i][tree[i].size()-1];
            if(tree[lastp].size() == 0) {ok[i] = 1; continue;}
            int pp = tree[lastp][tree[lastp].size()-1];
            tree[i].push_back(pp);
        }
        cont = false;
        for(auto x : ok) if(!x){cont=true; break;}
    }
    for(int i=0; i<q; i++){
        string curs; cin >> curs;
        int cur = smap[curs];
        int b; cin >> b;
        int idx; string ans;
        if(b >= age[oidx]){cout << name[oidx] << " "; continue;}
        while(true){
            for(int i=0; i< (int) tree[cur].size(); i++){
                if(age[tree[cur][i]] > b){idx=i-1; break;}
            }
            if(idx == -1){ans = name[cur]; break;}
            cur = tree[cur][idx];
        }
        cout << ans << " ";
    }
    cout << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}