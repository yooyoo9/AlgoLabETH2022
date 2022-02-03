#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Gmpz.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>
using namespace std;
#define int long
#define vc vector

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> LP;
typedef CGAL::Quadratic_program_solution<ET> Sol;
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;
typedef DT::Vertex_handle Vertex;
typedef K::Point_2 P;
typedef K::FT FT;

double floor_to_double(const CGAL::Quotient<ET> &x){
    double a = floor(CGAL::to_double(x));
    while(a > x) a-=1;
    while(a+1 <= x) a+=1;
    return a;
}

void solve(){
    int n, m, c; cin >> n >> m >> c;
    
    vc<P> wh(n); vc<int> supply(n); vc<int> content(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y >> supply[i] >> content[i];
        wh[i] = P(x, y); 
    }
    vc<P> st(m); vc<int> demand(m); vc<int> lim(m);
    for(int i=0; i<m; i++){
        int x, y; cin >> x >> y >> demand[i] >> lim[i];
        st[i] = P(x, y);
    }
    vc<vc<int>> rev(n, vc<int>(m));
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) cin >> rev[i][j];
    
    vc<int> empty(c, 1);
    vc<pair<P, int>> contour(c); vc<FT> rad(c);
    DT trig; 
    trig.insert(wh.begin(), wh.end());
    trig.insert(st.begin(), st.end());
    for(int i=0; i<c; i++){
        int x, y, r; cin >> x >> y >> r;
        contour[i].second = i;
        FT curr = FT(r) * FT(r); P curp(x, y);
        rad[i] = curr; contour[i].first = curp;
        Vertex cur = trig.nearest_vertex(curp);
        if(CGAL::squared_distance(cur->point(), curp) <= curr) empty[i] = 0;
    }
    
    vc<vc<int>> ncont(n, vc<int>(m));
    for(int i=0; i<c; i++){
        if(empty[i]) continue;
        P curc = contour[i].first; FT curr = rad[i];
        for(int j=0; j<n; j++){
            P curwh = wh[j];
            bool jin = CGAL::squared_distance(curc, curwh) <= curr;
            for(int k=0; k<m; k++){
                bool kin = CGAL::squared_distance(curc, st[k]) <= curr;
                if((jin && !kin) || (!jin && kin)) ncont[j][k]++;
            }
        }
    }
    
    LP lp(CGAL::SMALLER, true, 0, false, 0);
    int idx = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) lp.set_a(i*m+j, idx, 1);
        lp.set_b(idx, supply[i]); idx++;
    }
    for(int j=0; j<m; j++){
        for(int i=0; i<n; i++) lp.set_a(i*m+j, idx, 1);
        lp.set_b(idx, demand[j]); idx++;
        for(int i=0; i<n; i++) lp.set_a(i*m+j, idx, -1);
        lp.set_b(idx, -demand[j]); idx++;
        for(int i=0; i<n; i++) lp.set_a(i*m+j, idx, content[i]);
        lp.set_b(idx, 100*lim[j]); idx++;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            lp.set_c(i*m+j, -100*rev[i][j] + ncont[i][j]);
        }
    }
    Sol res = CGAL::solve_linear_program(lp, ET());
    if(res.is_infeasible()){
        cout << "RIOT!\n";
    } else {
        CGAL::Quotient<ET> sol = -res.objective_value() / 100;
        cout << floor_to_double(sol) << "\n";
    }
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}