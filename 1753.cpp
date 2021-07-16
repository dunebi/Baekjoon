#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#define MAX 987654321
using namespace std;

typedef struct Node
{
	vector<pair<int, int>> e; //pair(������, ����ġ)
	void put_e(int dest, int wei)
	{
		e.push_back(make_pair(dest, wei));
	}
	int getSize()
	{
		return e.size();
	}
}Node;

int V, E, K;
int u, v, w;
Node* n;
int* arr;

void dijkstra(int s)
{
	priority_queue<pair<int, int>> pq; //(��ΰ�, ��尪)
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
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> V >> E >> K;

	n = new Node[V + 1];
	arr = new int[V + 1];
	for (int i = 1; i <= V; i++) arr[i] = MAX;

	for (int i = 0; i < E; i++)
	{
		cin >> u >> v >> w;
		n[u].put_e(v, w);
	}

	dijkstra(K);
	for (int i = 1; i <= V; i++)
	{
		if (arr[i] != MAX) cout << arr[i] << '\n';
		else cout << "INF" << '\n';
	}

	return 0;
}