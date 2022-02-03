#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <boost/pending/disjoint_sets.hpp>
using namespace std;
#define int long
#define vc vector
using pii = pair<int, int>;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_with_info_2<int, K> Fb;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;
typedef K::Point_2 P;
typedef K::FT FT;

void solve(){
    int n, m; FT s; int k; cin >> n >> m >> s >> k;
    vc<pair<P, int>> pts(n);
    for(int i=0; i<n; i++){
        int x, y; cin >> x >> y;
        pts[i] = make_pair(P(x, y), i);
    }
    DT trig; trig.insert(pts.begin(), pts.end());
    vc<pair<FT, pii>> edges;
    for(auto e = trig.finite_edges_begin(); e != trig.finite_edges_end(); e++){
        auto v1 = e->first->vertex((e->second + 1)%3);
        auto v2 = e->first->vertex((e->second + 2)%3);
        FT curd = CGAL::squared_distance(v1->point(), v2->point());
        edges.push_back(make_pair(curd, make_pair(v1->info(), v2->info())));
    }
    for(int i=0; i<m; i++){
        int x, y; cin >> x >> y; P p(x, y);
        auto v = trig.nearest_vertex(p);
        FT curd = 4 * CGAL::squared_distance(p, v->point());
        edges.push_back(make_pair(curd, make_pair(v->info(), n+i)));
    }
    sort(edges.begin(), edges.end());
    boost::disjoint_sets_with_storage<> uf(n);
    vc<int> nb_tree(n); int maxn = 0;
    bool foundb = false; int a; FT q;
    for(auto cure : edges){
        FT curd = cure.first; int idx1 = cure.second.first, idx2 = cure.second.second;
        int rep1 = uf.find_set(idx1);
        if(idx2 >=n){ // bone
            nb_tree[rep1]++; 
            maxn = max(nb_tree[rep1], maxn);
        } else {
            int rep2 = uf.find_set(idx2);
            if(rep1 == rep2) continue;
            uf.link(rep1, rep2);
            int ni = uf.find_set(idx1);
            int oi = ni == rep1 ? rep2 : rep1;
            nb_tree[ni] += nb_tree[oi];
            maxn = max(maxn, nb_tree[ni]);
        }
        if(!foundb && k <= maxn){
            foundb = true; q = curd;
        }
        if(curd <= s) a = maxn;
    }
    cout << a << " " << (int) round(CGAL::to_double(q)) << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
    return 0;
}