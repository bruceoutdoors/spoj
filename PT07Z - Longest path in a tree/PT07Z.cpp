#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

class Graph
{
public:
	Graph(const int &v) : m_v(v)
	{
		m_g.reserve(m_v);
		for (int i = 0; i < m_v; ++i) m_g.push_back({});
	}

	bool hasEdge(const int &v, const int &w) { return m_g[v].find(w) == m_g[v].end() ? false : true; }

	void addEdge(const int &v, const int &w)
	{
		m_g[v].insert(w);
		m_g[w].insert(v);
	}

	set<int> adj(const int &v) const { return m_g[v]; }

	int getSize() const { return m_v; }

	void print()
	{
		for (int i = 0; i < m_v; ++i) {
			cout << i << " : ";
			for (const auto &v : adj(i)) cout << v << " ";

			cout << endl;
		}
	}

private:
	const int m_v;
	vector< set<int> > m_g;
};

int maxLen = 0;
int leaf;
Graph g(10001);


void dfs(bool markArr[], const int &v, const int &depth = 0)
{
	markArr[v] = true;
	
	if (depth > maxLen) {
		maxLen = depth;
		leaf = v;
	}

	for (const auto &w : g.adj(v)) {
		if (markArr[w]) continue;
		dfs(markArr, w, depth + 1);
	}
}
bool marked[10001];
bool marked2[10001];
int main() 
{
	int n; cin >> n;
	int x, y;
	

	while (n--) {
		cin >> x >> y;
		g.addEdge(x, y);
	}

	dfs(marked, 1);
	dfs(marked2, leaf);

	cout << maxLen;
}
