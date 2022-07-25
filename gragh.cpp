#include <bits/stdc++.h>

using namespace std;

typedef double DB;
typedef long long LL;
typedef pair<int, int> P;

const int N = 1e6 + 7;

int n ,m, s, cnt, h[N];

class edge {
    public:
        int nxt, to, len;
} e[N];

void add(int u, int v, int w) {
    e[++cnt] = {h[u], v, w};
    h[u] = cnt;
}

/*
class edge {
    public:
        int nxt, to;
} e[N];

void add(int u, int v) {
    e[++cnt] = {h[u], v};
    h[u] = cnt;
}
*/

int dis[N];
bool vis[N];
priority_queue<P, vector<P>, greater<P>> heap;
void dijkstra(int s) {
    memset(dis, 0x7f, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[s] = 0;
    heap.push({0, s});
    while (!heap.empty()) {
        int d = heap.top().first;
        int u = heap.top().second;
        heap.pop(); 
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = h[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            int w = e[i].len;
            if (dis[v] > d + w) {
                dis[v] = d + w;
                heap.push({dis[v], v});
            }
        }
    }
}

int num, id, top;
int dfn[N], low[N], ID[N], st[N], size[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++num;
    st[++top] = u;
    for (int i = h[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!ID[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        id++;
        do {
            ID[st[top]] = id;
            size[id]++;
        } while (st[top--] != u);
    }
}

queue<int> q;
int tot, tpn[N], in[N];
void topoSort() {
    for (int i = 1; i <= n; i++)
        if (!in[i]) {
            q.push(i);
            tpn[++tot] = i;
        }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = h[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            in[v]--;
            if (!in[v]) {
                q.push(v);
                tpn[++tot] = v;
            }
        }
    }
}

const int logN = 20;
int deep[N], f[N][logN+1];
void dfs(int u, int p) {
    deep[u] = deep[p] + 1;
    for (int i = 0; i < logN; i++)
        f[u][i+1] = f[f[u][i]][i];
    for (int i = h[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == p) continue;
        f[v][0] = u;
        dfs(v, u);
    }
}

int lca(int x, int y) {
    if (deep[x] < deep[y])
        swap(x, y);
    for (int i = logN; ~i; i--) {
        if (deep[f[x][i]] >= deep[y])
            x = f[x][i];
        if (x == y) return x;
    }
    for (int i = logN; ~i; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    /*
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
        in[v]++;
    }

    cin >> s;
    dijkstra(s);
    
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    
    topoSort();

    cin >> q;
    dfs(1, 0);
    while (q--) {
        int x, y;
        cout << lca(x, y) << '\n';
    }
    */
    return 0;
}
