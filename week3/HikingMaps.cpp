#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
using namespace std;
#define int long
#define vc vector
#define pb push_back
#define all(x) x.begin(), x.end()

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Triangle_2 T;
typedef K::Line_2 L;

int get_idx(CGAL::Orientation x){
    if(x == CGAL::LEFT_TURN) return -1;
    else if(x == CGAL::RIGHT_TURN) return 1;
    return 0;
}

bool in_trig(vc<P> &a, P p){
    auto o1 = CGAL::orientation(a[0], a[1], p);
    auto o2 = CGAL::orientation(a[1], a[2], p);
    auto o3 = CGAL::orientation(a[2], a[0], p);
    int x = get_idx(o1), y = get_idx(o2), z = get_idx(o3);
    return (x*y != -1) && (y*z != -1) && (z*x != -1);
}

void solve(){
    int m, n; cin >> m >> n;
    vc<P> path(m);
    for(int i=0; i<m; i++){
        int x, y; cin >> x >> y; path[i] = P(x, y);
    }
    vc<vc<int>> g(m-1);
    for(int i=0; i<n; i++){
        vc<P> cur(6);
        for(int j=0; j<6; j++){
            int x, y; cin >> x >> y; cur[j] = P(x, y);
        }
        vc<P> vert(3);
        for(int j=0; j<3; j++){
            L l1(cur[(2*(j+1))%6], cur[(2*(j+1)+1)%6]);
            L l2(cur[(2*(j+2))%6], cur[(2*(j+2)+1)%6]);
            auto inter = CGAL::intersection(l1, l2);
            const P *p = boost::get<P>(&*inter);
            vert[j] = *p;
        }
        bool out = !in_trig(vert, path[0]);
        for(int j=1; j<m; j++){
            bool curout = !in_trig(vert, path[j]);
            if(!out && !curout){
                g[j-1].pb(i);
            }
            out = curout;
        }
    }
    vc<int> idx(m-1);
    int ans = n;
    for(int i=0; i<n; i++){
        int done = false;
        int cur = 0;
        for(int j=0; j<m-1; j++){
            while(idx[j] < (int)(g[j].size()) && g[j][idx[j]] < i) idx[j]++;
            if(idx[j] == (int)(g[j].size())){done=true; break;}
            cur = max(cur, g[j][idx[j]]);
        }
        if(done) break;
        ans = min(ans, cur - i + 1);
    }
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}