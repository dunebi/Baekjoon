#include <iostream>
#include <vector>
#include <algorithm>
#define INF 2147483647

using namespace std;

int N;
int ans_max = -INF, ans_min = INF;
vector<int> v;
char op[4] = { '+', '-', '*', '/' };
int op_cnt[4];

int calc(int a, int b, char op) {
	if (op == '+') return a + b;
	else if (op == '-') return a - b; //a - b 순서 주의
	else if (op == '*') return a * b;
	else return a / b; //a/b 순서주의
}

void dfs(int idx, int size, int now) { //0 ~ (N - 1), a = v[idx] b= v[idx + 1]
	if (size == 0) {
		ans_max = max(ans_max, now);
		ans_min = min(ans_min, now);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (op_cnt[i] == 0) continue;
		op_cnt[i]--;
		dfs(idx + 1, size - 1, calc(now, v[idx + 1], op[i]));
		op_cnt[i]++;
	}
}


int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> N;

	int temp;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		v.push_back(temp);
	}

	int size = 0;
	for (int i = 0; i < 4; i++) {
		cin >> temp;
		op_cnt[i] += temp;
		size += temp;
	}

	dfs(0, size, v[0]);

	cout << ans_max << '\n';
	cout << ans_min << '\n';

	return 0;
}