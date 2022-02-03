#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
using namespace std;
#define int long
#define vc vector
#define f first
#define s second
#define pb push_back
using pii = pair<int, int>;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::FT FT;

void solve(){
    int n; cin >> n;
    vc<pair<pii, pair<int, FT>>> a(n);
    for(int i=0; i<n; i++){
        int y0, x1, y1; cin >> y0 >> x1 >> y1;
        FT slope(CGAL::abs(FT(y1 - y0) / FT(x1)));
        int up = y1 > y0 ? 1 : y1 == y0 ? 0 : -1;
        a[i] = make_pair(make_pair(i, y0), make_pair(up, slope));
    }
    sort(a.begin(), a.end(), [](auto &lhs, auto &rhs){
        FT s0 = lhs.s.s, s1 = rhs.s.s;
        return (s0 < s1 || 
            ( s0 == s1 && lhs.s.f == -1 && rhs.s.f == -1 && lhs.f.s > rhs.f.s) ||
            ( s0 == s1 && lhs.s.f == 1 && rhs.s.f == 1 && lhs.f.s < rhs.f.s) ||
            ( s0 == s1 && lhs.s.f == 1 && rhs.s.f == -1));
    });
    vc<int> ans(1, a[0].f.f);
    int ymax(a[0].f.s); int ymin(a[0].f.s);
    for(int i=1; i<n; i++){
        int idx=a[i].f.f; int y0(a[i].f.s); int d = a[i].s.f;
        if(d==0){ans.pb(idx);}
        else if(d==1 && y0 > ymax){ans.pb(idx);}
        else if(d==-1 && y0 < ymin){ans.pb(idx);}
        ymax = max(ymax, y0);
        ymin = min(ymin, y0);
    }
    sort(ans.begin(), ans.end());
    for(int x : ans) cout << x << " ";
    cout << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}