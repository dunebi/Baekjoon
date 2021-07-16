#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct Edge {
	int start, end, wei;
	Edge(int _start, int _end, int _wei)
	{
		start = _start;
		end = _end;
		wei = _wei;
	}
}Edge;

bool weiSort(Edge e1, Edge e2)
{
	return e1.wei < e2.wei;
}

int Find(int r[], int x)
{
	if (r[x] == x) return x;
	else return Find(r, r[x]);
}

void Union(int r[], int x, int y)
{
	x = Find(r, x);
	y = Find(r, y);

	if (x == y) return;
	r[x] = y;
}

bool makeCycle(int r[], Edge e)
{
	return Find(r, e.start) == Find(r, e.end);
}

int main()
{
	int n, e, start, end, wei;
	cin >> n >> e;

	int* Root = new int[n + 1];
	vector<Edge> v, t;
	for (int i = 0; i < e; i++)
	{
		cin >> start >> end >> wei;
		Edge e(start, end, wei);
		v.push_back(e);
	}
	for (int i = 1; i <= n; i++) Root[i] = i;
	sort(v.begin(), v.end(), weiSort);

	int i = 0;
	while (t.size() < n - 1)
	{
		Edge te = v[i]; i++;
		if (!makeCycle(Root, te))
		{
			t.push_back(te);
			Union(Root, te.start, te.end);
		}
	}

	int sum = 0;
	for (int i = 0; i < t.size(); i++)
	{
		sum += t[i].wei;
	}
	cout << sum << '\n';

	return 0;
}