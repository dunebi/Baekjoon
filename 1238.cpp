#include <iostream>
#include <queue>
#include <vector>
#define INF 987654321
#define MAX(a, b) a > b ? a : b
using namespace std;

typedef struct Node
{
	vector<pair<int, int>> e; //pair(목적지, 가중치)
	void put_e(int dest, int wei)
	{
		e.push_back(make_pair(dest, wei));
	}
	int getSize()
	{
		return e.size();
	}
}Node;

int N, M, X;
int u, v, w;
Node* n;
int* arr;

void init()
{
	for (int i = 1; i <= N; i++) arr[i] = INF;
}

int dijkstra(int s, int e)
{
	init();
	priority_queue<pair<int, int>> pq; //(경로값, 노드값)
	pq.push(make_pair(0, s));
	arr[s] = 0;

	while (!pq.empty())
	{
		int now = pq.top().second;
		int dest = -pq.top().first;
		pq.pop();

		int nSize = n[now].getSize();
		for (int i = 0; i < nSize; i++)
		{
			int next = n[now].e.at(i).first;
			int weight = n[now].e.at(i).second;
			int dest_cost = dest + weight;

			if (dest_cost < arr[next])
			{
				pq.push(make_pair(-dest_cost, next));
				arr[next] = dest_cost;
			}
		}
	}

	return arr[e];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin >> N >> M >> X;

	n = new Node[N + 1];
	arr = new int[N + 1];
	for (int i = 0; i < M; i++)
	{
		cin >> u >> v >> w;
		n[u].put_e(v, w);
	}

	int max_time = 0;
	for (int i = 1; i <= N; i++)
	{
		if (i == X) continue;
		max_time = MAX(max_time, dijkstra(i, X) + dijkstra(X, i));
	}

	cout << max_time << '\n';

	return 0;
}