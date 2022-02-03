#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/connected_components.hpp>
using namespace std;
using namespace boost;
#define int long
#define vc vector

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  DT;
typedef K::Point_2 P;
typedef DT::Vertex_handle Vertex;

typedef adjacency_list< vecS, vecS, undirectedS > Graph;

void solve(){
    int n, m, r; cin >> n >> m >> r;
    int rad = r * r;
    vc<pair<P, int>> pts(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y;
        pts[i] = make_pair(P(x, y), i);
    }
    DT trig; trig.insert(pts.begin(), pts.end());
    Graph G(n);
    for(auto v = trig.finite_vertices_begin(); v != trig.finite_vertices_end(); v++){
        queue<Vertex> q; q.push(v);
        P curp = v->point(); int idx = v->info();
        set<int> vis; vis.insert(idx);
        while(!q.empty()){
            Vertex cur = q.front(); q.pop();
            auto neigh = cur->incident_vertices();
            do{
                if(!trig.is_infinite(neigh) && vis.find(neigh->info()) == vis.end()
                    && CGAL::squared_distance(curp, neigh->point()) <= rad){
                        q.push(neigh); 
                        vis.insert(neigh->info());
                        if(idx < neigh->info()) add_edge(idx, neigh->info(), G);
                    }
            }while(++neigh != cur->incident_vertices());
        }
    }
    bool bipartite = is_bipartite(G);
    vc<int> comp(n);
    connected_components(G, &comp[0]);

    for(int i=0; i<m; i++){
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if(!bipartite){cout << "n"; continue;}
        P p1(x1, y1), p2(x2, y2);
        if(CGAL::squared_distance(p1, p2) <= rad){cout << "y"; continue;}
        auto v1 = trig.nearest_vertex(p1);
        auto v2 = trig.nearest_vertex(p2);
        int d1 = CGAL::squared_distance(p1, v1->point());
        int d2 = CGAL::squared_distance(p2, v2->point());
        if(d1 > rad || d2 > rad) cout << "n";
        else if(comp[v1->info()] != comp[v2->info()]) cout << "n";
        else cout << "y";
    }
    cout << "\n";
}

signed main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int t; cin >> t; while(t--) solve();
  return 0;
}