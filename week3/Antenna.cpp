#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
using namespace std;
#define int long
#define vc vector
#define all(x) x.begin(), x.end()

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;
typedef K::FT FT;

double ceil_to_double(FT &x){
    double a = ceil(CGAL::to_double(x));
    while(a < x) a+=1;
    while(a-1 >= x) a-=1;
    return a;
}

int solve(){
    int n; cin >> n;
    if(!n) return 1;
    vc<P> pts(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y; pts[i] = P(x, y);
    }
    Min_circle mc(all(pts), true);
    Traits::Circle c = mc.circle();
    auto dist = CGAL::sqrt(c.squared_radius());
    cout << ceil_to_double(dist) << "\n";
    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(0);
    while(1){
        if(solve()) break;
    }
    return 0;
}
