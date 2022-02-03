#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;
#define int long
#define vc vector
#define all(x) x.begin(), x.end()

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> DT;
typedef K::Point_2 P;

int solve(){
    int n; cin >> n;
    if(!n) return 1;
    vc<P> pts(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y; pts[i] = P(x, y);
    }
    DT trig; trig.insert(all(pts));
    int m; cin >> m;
    for(int i=0; i<m; i++){
        int x, y; cin >> x >> y;
        P cur(x, y);
        int curd = CGAL::squared_distance(cur, trig.nearest_vertex(cur)->point());
        cout << curd << "\n";
    }
    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    while(1){if(solve()) break;}
    return 0;
}
