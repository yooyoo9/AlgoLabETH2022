#include <bits/stdc++.h>
#include <CGAL/Gmpz.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
using namespace std;
#define int long
#define vc vector
#define f first
#define s second
using pii = pair<int, int>;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> LP;
typedef CGAL::Quadratic_program_solution<ET> Sol;

double floor_to_double(const CGAL::Quotient<ET> &x){
    double a = floor(CGAL::to_double(x));
    while(a > x) a-=1;
    while(a+1 <=x) a+=1;
    return a;
}

int solve(){
    int n, m; cin >> n >> m;
    if(!n && !m) return 1;
    vc<pii> needed(n);
    for(int i=0; i<n; i++) cin >> needed[i].f >> needed[i].s;
    vc<int> price(m);
    vc<vc<int>> nutri(n, vc<int>(m));
    for(int i=0; i<m; i++){
        cin >> price[i];
        for(int j=0; j<n; j++) cin >> nutri[j][i];
    }
    LP lp(CGAL::SMALLER, true, 0, false, 0);
    int idx = 0;
    for(int i=0; i<m; i++) lp.set_c(i, price[i]);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            lp.set_a(j, idx, nutri[i][j]);
        }
        lp.set_b(idx, needed[i].s);
        idx++;

        for(int j=0; j<m; j++){
            lp.set_a(j, idx, -nutri[i][j]);
        }
        lp.set_b(idx, -needed[i].f);
        idx++;
    }
    Sol res = CGAL::solve_linear_program(lp, ET());
    if(res.is_infeasible()) cout << "No such diet.\n";
    else cout << floor_to_double(res.objective_value()) << "\n";
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