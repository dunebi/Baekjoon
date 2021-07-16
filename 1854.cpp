#include <iostream>
#include <queue>
#include <vector>
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

int N, M, K;
int a, b, c;
Node* n;
priority_queue<int>* heap;

void dijkstra(int s)
{
	priority_queue<pair<int, int>> pq; //(경로값, 노드값)
	pq.push(make_pair(0, s));
	heap[s].push(0);

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

			if (heap[next].size() < K)
			{
				heap[next].push(dest_cost);
				pq.push(make_pair(-dest_cost, next));
			}
			else if (heap[next].top() > dest_cost)
			{
				heap[next].pop();
				heap[next].push(dest_cost);
				pq.push(make_pair(-dest_cost, next));
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> K;

	n = new Node[N + 1];
	heap = new priority_queue<int>[N + 1];
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b >> c;
		n[a].put_e(b, c);
	}

	dijkstra(1);

	for (int i = 1; i <= N; i++)
	{
		if (heap[i].size() != K) cout << -1 << '\n';
		else cout << heap[i].top() << '\n';
	}

	return 0;
}