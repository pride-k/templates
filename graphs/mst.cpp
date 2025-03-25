
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
class undigraph : public graph<T> {
    public:
        using graph<T>::edges;
        using graph<T>::g;
        using graph<T>::n;

        undigraph(int _n) : graph<T>(_n) {

        }

        int add(int from, int to, T cost = 1) {
            assert(0 <= from && from < n && 0 <= to && to < n);
            int id = (int) edges.size();
            g[from].push_back(id);
            g[to].push_back(id);
            edges.push_back({from, to, cost});
            return id;
        }
};


class dsu {
    public:
        vector<int> p;
        int n;

        dsu(int _n) : n(_n) {
            p.resize(n);
            iota(p.begin(), p.end(), 0);
        }

        inline int get(int x) {
            return (x == p[x] ? x : (p[x] = get(p[x])));
        }

        inline bool unite(int x, int y) {
            x = get(x);
            y = get(y);
            if (x != y) {
                p[x] = y;
                return true;
            }
            return false;
        }
};


template <typename T>
vector<int> find_mst(const undigraph<T> &g, T &ans) {
    vector<int> order(g.edges.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&g](int a, int b) {
        return g.edges[a].cost < g.edges[b].cost;
    });
    dsu d(g.n);
    vector<int> ans_list;
    ans = 0;
    for (int id : order) {
        auto &e = g.edges[id];
        if (d.get(e.from) != d.get(e.to)) {
            d.unite(e.from, e.to);
            ans_list.push_back(id);
            ans += e.cost;
        }
    }
    return ans_list;
    // returns edge ids of minimum "spanning" forest
}


