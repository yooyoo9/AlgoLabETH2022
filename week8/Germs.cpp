#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;
#define int long
#define vc vector
#define f first
#define s second
#define all(x) x.begin(), x.end()
using pii = pair<int, int>;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;
typedef DT::Edge_iterator EdgeIt;
typedef DT::Vertex_handle Vertex;
typedef DT::Edge Edge;
typedef K::Point_2 P;
typedef K::FT FT;

double calculate(const FT &x){
    if(x <= 0.5) return 0;
    return ceil(sqrt(x - 0.5));
}

int solve(){
    int n; cin >> n;
    if(!n) return 1;
    int l, b, r, t; cin >> l >> b >> r >> t;
    vc<pair<P, int>> pts(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y; 
        pts[i].f = P(x, y); pts[i].s = i;
    }
    DT trig; trig.insert(all(pts));
    vc<double> dist(n);
    for(int i=0; i<n; i++){
        dist[i] = min(r-pts[i].f.x(), min(pts[i].f.x()-l, min(t-pts[i].f.y(), pts[i].f.y() - b)));
    }
    for(EdgeIt e = trig.finite_edges_begin(); e != trig.finite_edges_end(); e++){
        Vertex v1 = e->f->vertex((e->s + 1)%3);
        Vertex v2 = e->f->vertex((e->s + 2)%3);
        double curd = sqrt(CGAL::squared_distance(v1->point(), v2->point())) / 2;
        dist[v1->info()] = min(dist[v1->info()], curd);
        dist[v2->info()] = min(dist[v2->info()], curd);
    }
    sort(all(dist));
    double ansf = calculate(dist[0]);
    double ansm = calculate(dist[n/2]);
    double ansl = calculate(dist[n-1]);
    cout << ansf << " " << ansm << " " << ansl << "\n";
    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    while(1){if(solve()) break;}
    return 0;
}