#include <bits/stdc++.h>
#include <CGAL/Gmpz.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>
using namespace std;
#define int long

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program_solution<ET> Sol;
typedef CGAL::Quadratic_program<IT> LP;

double floor_to_double(const CGAL::Quotient<ET> &x){
    double a = floor(CGAL::to_double(x));
    while(a > x) a-=1;
    while(a+1 <= x) a+=1;
    return a;
}

int solve(){
    int n; cin >> n;
    if(!n) return 1;
    int d; cin >> d;
    LP lp(CGAL::SMALLER, false, 0, false, 0);
    for(int i=0; i<n; i++){
        int norm = 0;
        for(int j=0; j<d; j++){
            int cura; cin >> cura;
            lp.set_a(j, i, cura);
            norm += cura * cura;
        }
        norm = (int) sqrt(norm);
        lp.set_a(d, i, norm);
        int curb; cin >> curb;
        lp.set_b(i, curb);
    }
    lp.set_l(d, true, 0);
    lp.set_c(d, -1);
    Sol res = CGAL::solve_linear_program(lp, ET());
    if(res.is_infeasible()) cout << "none\n";
    else if(res.is_unbounded()) cout << "inf\n";
    else cout << floor_to_double(-res.objective_value()) << "\n";
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