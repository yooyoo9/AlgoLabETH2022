#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
using namespace std;
#define int long
#define vc vector
#define all(x) x.begin(), x.end()

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;
typedef K::Segment_2 S;
typedef K::FT FT;

double floor_to_double(FT x){
    double a = floor(CGAL::to_double(x));
    while(a > x) a-=1;
    while(a+1 <= x) a+=1;
    return a;
}

int solve(){
    int n; cin >> n;
    if(!n) return 1;
    int x, y, a, b; cin >> x >> y >> a >> b; 
    P orig(x, y);
    R ray(orig, P(a, b));
    vc<S> seg(n); 
    for(int i=0; i<n; i++){
        int r, s, t, u; cin >> r >> s >> t >> u;
        seg[i] = S(P(r, s), P(t, u));
    }
    random_shuffle(all(seg));
    P ans; 
    FT dist = FT(LONG_MAX) * FT(LONG_MAX);
    for(int i=0; i<n; i++){
        S cur = seg[i];
        FT curd = CGAL::squared_distance(orig, cur);
        if(dist < curd) continue;
        auto inter = CGAL::intersection(ray, cur);
        if(inter){
            if(const S* curs = boost::get<S>(&* inter)){
                FT curd1 = CGAL::squared_distance(orig, curs->source());
                FT curd2 = CGAL::squared_distance(orig, curs->target());
                if(curd1 < dist && curd1 < curd2){dist=curd1; ans = curs->source();}
                else if(curd2 < dist){dist=curd2; ans = curs->target();}
            } else {
                const P* p = boost::get<P>(&* inter);
                FT curd1 = CGAL::squared_distance(orig, *p);
                if(curd1 < dist){
                    dist = curd1; ans=*p;
                }
            }
        }
    }
    if(dist == FT(LONG_MAX) * FT(LONG_MAX)) cout << "no\n";
    else cout << floor_to_double(ans.x()) << " " << floor_to_double(ans.y()) << "\n";
    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(0);
    while(true){
        if(solve()) break;
    }
    return 0;
}