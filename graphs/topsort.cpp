
//	https://github.com/the-tourist/algo/
//	https://github.com/p1k4-piyush/templates/


template <typename T>
class graph {
    public:
        struct edge {
            int from;
            int to;
            T cost;
        };

        vector<edge> edges;
        vector<vector<int>> g;
        int n;

        graph(int _n) : n(_n) {
            g.resize(n);
        }

        virtual int add(int from, int to, T cost) = 0;
};


template <typename T>
class digraph : public graph<T> {
    public:
        using graph<T>::edges;
        using graph<T>::g;
        using graph<T>::n;

        digraph(int _n) : graph<T>(_n) {

        }

        int add(int from, int to, T cost = 1) {
            assert(0 <= from && from < n && 0 <= to && to < n);
            int id = (int) edges.size();
            g[from].push_back(id);
            edges.push_back({from, to, cost});
            return id;
        }

        digraph<T> reverse() const {
            digraph<T> rev(n);
            for (auto &e : edges) {
                rev.add(e.to, e.from, e.cost);
            }
            return rev;
        }
};





template <typename T>
vector<int> find_topsort(const digraph<T> &g) {
    vector<int> deg(g.n, 0);
    for (int id = 0; id < (int) g.edges.size(); id++) {
        deg[g.edges[id].to]++;
    }
    vector<int> x;
    for (int i = 0; i < g.n; i++) {
        if (deg[i] == 0) {
            x.push_back(i);
        }
    }
    for (int ptr = 0; ptr < (int) x.size(); ptr++) {
        int i = x[ptr];
        for (int id : g.g[i]) {
            auto &e = g.edges[id];
            int to = e.to;
            if (--deg[to] == 0) {
            x.push_back(to);
            }
        }
    }
    if ((int) x.size() != g.n) {
        return vector<int>();
    }
    return x;
}


