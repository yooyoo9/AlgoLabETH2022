#include <bits/stdc++.h>
using namespace std;
#define int long
#define vc vector
#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
using pii = pair<int, int>;

void solve(){
    int n, m, d, t; cin >> n >> m >> d >> t;
    vc<pii> mov(n);
    for(int i=0; i<n; i++) cin >> mov[i].f >> mov[i].s;
    vc<int> p(m); for(int i=0; i<m; i++) cin >> p[i];
    int N1 = n/2, N2 = n-n/2;
    vc<vc<pii>> maxd1(N1+1), maxd2(N2+1);
    for(int subset=0; subset < (1<<N1); subset++){
        int curd=0, curt=0, nb=0;
        for(int i=0; i<N1; i++){
            if(curt >= t) break;
            int take = (subset >> i) & 1;
            if(take){curd += mov[i].f; curt += mov[i].s; nb++;}
        }
        if(curt < t) maxd1[nb].pb(make_pair(curt, min(d, curd)));
    }
    for(int subset=0; subset < (1<<N2); subset++){
        int curd=0, curt=0, nb=0;
        for(int i=N1; i<n; i++){
            if(curt >= t) break;
            int take = (subset >> (i-N1)) & 1;
            if(take){curd += mov[i].f; curt += mov[i].s; nb++;}
        }
        if(curt < t) maxd2[nb].pb(make_pair(curt, min(d, curd)));
    }
    
    for(int i=0; i<=N1; i++) {
        if(maxd1[i].size() == 0) continue;
        sort(all(maxd1[i]));
        vc<pii> cur;
        int curn = maxd1[i].size();
        for(int j=0; j<curn; j++){
            int idx = j;
            while(idx+1 < curn && maxd1[i][idx].f == maxd1[i][idx+1].f) idx++;
            cur.pb(maxd1[i][idx]);
            j = idx;
        }
        for(int j=1; j< (int) cur.size(); j++) cur[j].s = max(cur[j].s, cur[j-1].s);
        maxd1[i] = cur;
    }
    for(int i=0; i<=N2; i++) {
        if(maxd2[i].size() == 0) continue;
        sort(all(maxd2[i]));
        vc<pii> cur;
        for(int j=0; j< (int) maxd2[i].size(); j++){
            int idx = j;
            while(idx+1 < (int) maxd2[i].size() && maxd2[i][idx].f == maxd2[i][idx+1].f) idx++;
            cur.pb(maxd2[i][idx]);
            j = idx;
        }
        for(int j=1; j< (int) cur.size(); j++) cur[j].s = max(cur[j].s, cur[j-1].s);
        maxd2[i] = cur;
    }
    
    int l=-1, r=m+1;
    while(l+1 != r){
        int mid = l + (r-l)/2; int curp = mid==0 ? 0 : p[mid-1];
        int pos = 0;
        for(int i=0; i<=N1; i++){
            for(pii cura : maxd1[i]){
                int curt = cura.f, curd = cura.s;
                for(int j=0; j<=N2; j++){
                    if(i==0 && j==0) continue;
                    int ll=-1, rr=maxd2[j].size();
                    while(ll+1 != rr){
                        int midd = ll + (rr-ll)/2;
                        if(curt + maxd2[j][midd].f >= t) rr = midd;
                        else ll = midd;
                    }
                    if(ll!=-1 && curd + maxd2[j][ll].s + (i+j)*curp>= d){pos = 1; break;}
                }
                if(pos) break;
            }
            if(pos) break;
        }
        if(pos) r = mid;
        else l = mid;
    }
    if(r == m+1) cout << "Panoramix captured\n";
    else cout << r << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}