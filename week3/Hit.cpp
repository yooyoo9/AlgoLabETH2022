#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
using namespace std;
#define int long
#define vc vector

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;
typedef K::Segment_2 S;

int solve(){
    int n; cin >> n;
    if(n == 0) return 1;
    int x, y, a, b; cin >> x >> y >> a >> b;
    R phileas(P(x, y), P(a, b));
    int hit = 0;
    for(int i=0; i<n; i++){
        int r, s, t, u; cin >> r >> s >> t >> u;
        S cur(P(r, s), P(t, u));
        if(CGAL::do_intersect(phileas, cur)){hit=1; break;}
    }
    if(hit) cout << "yes\n";
    else cout << "no\n";
    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    while(true){
        if(solve()) break;
    }
    return 0;
}
