#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <boost/pending/disjoint_sets.hpp>
using namespace std;
#define int long
#define vc vector
using pii = pair<int, int>;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;
typedef DT::Vertex_handle Vertex;
typedef DT::Face_handle Face;
typedef K::Point_2 P;
typedef K::FT FT;

double ceil_to_double(const FT &x){
    double a = ceil(CGAL::to_double(x));
    while(a < x) a+=1;
    while(a-1 >= x) a-=1;
    return a;
}

int find(int cur, vc<int> rep){
    while(rep[cur] != cur) cur = rep[cur];
    return cur;
}

void solve(){
    int n, m, p; cin >> n >> m >> p;
    vc<pair<P, int>> pts(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y;
        pts[i] = make_pair(P(x, y), i);
    }
    DT trig; trig.insert(pts.begin(), pts.end());
    vc<pair<FT, pii>> edges;
    for(auto e = trig.finite_edges_begin(); e != trig.finite_edges_end(); e++){
        Vertex v1 = e->first->vertex((e->second + 1)%3);
        Vertex v2 = e->first->vertex((e->second + 2)%3);
        FT curd = CGAL::squared_distance(v1->point(), v2->point());
        edges.push_back(make_pair(curd, make_pair(v1->info(), v2->info())));
    }
    for(int i=0; i<m; i++){
        int x, y; cin >> x >> y; P p1(x, y);
        cin >> x >> y; P p2(x, y);
        Vertex v1 = trig.nearest_vertex(p1);
        Vertex v2 = trig.nearest_vertex(p2);
        FT curd1 = 4 * CGAL::squared_distance(p1, v1->point());
        FT curd2 = 4 * CGAL::squared_distance(p2, v2->point());
        edges.push_back(make_pair(curd1, make_pair(v1->info(), n+2*i)));
        edges.push_back(make_pair(curd2, make_pair(v2->info(), n+2*i+1)));
    }
    sort(edges.begin(), edges.end());
    int nb_mis = 0;
    boost::disjoint_sets_with_storage<> uf(n);
    vc<unordered_set<int>> g(n);
    FT allmis(0), smallestp(0);
    vc<FT> mission(m);
    for(auto cure : edges){
        FT curd = cure.first; int idx1 = cure.second.first; int idx2 = cure.second.second;
        int rep1 = uf.find_set(idx1);
        if(idx2 >= n){ // mission
            int mission_idx = (idx2-n) / 2;
            if(g[rep1].find(mission_idx) != g[rep1].end()){
                nb_mis++;
                g[rep1].erase(mission_idx);
                mission[mission_idx] = curd;
            } else {
                g[rep1].insert(mission_idx);
            }
        } else {
            int rep2 = uf.find_set(idx2);
            if(rep1 == rep2) continue;
            uf.link(rep1, rep2);
            int inew = uf.find_set(idx1); int iold = inew == rep1 ? rep2 : rep1;
            for(int x : g[iold]){
                if(g[inew].find(x) != g[inew].end()){
                    nb_mis++; 
                    mission[x] = curd;
                    g[inew].erase(x);
                } else g[inew].insert(x);
            }
        }
        if(nb_mis == m){allmis = curd; break;}
    }
    for(auto x : mission){
        if(x <= p) {cout << "y"; smallestp = max(smallestp, x);}
        else cout << "n";
    }
    cout << "\n";
    cout << ceil_to_double(allmis) << "\n" << ceil_to_double(smallestp) << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}