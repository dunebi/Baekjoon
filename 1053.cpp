#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[50][50];

int solve(int l, int r, string s)
{
	if (dp[l][r] != -1) return dp[l][r];
	if (l >= r) return 0;
	int& ret = dp[l][r];

	ret = min({ solve(l + 1, r, s) + 1, solve(l, r - 1, s) + 1, solve(l + 1, r - 1, s) + (s[l] != s[r]) });

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	string str;
	cin >> str;

	int strSize = str.size();
	memset(dp, -1, sizeof(dp));
	int ans = solve(0, strSize - 1, str);
	
	for (int i = 0; i < strSize; i++)
		for (int j = i + 1; j < strSize; j++)
		{
			//str[i]와 str[j]를 맞바꾼다
			memset(dp, -1, sizeof(dp));
			string s = str;
			char temp = s[i];
			s[i] = s[j];
			s[j] = temp;
			ans = min(ans, solve(0, strSize - 1, s) + 1);
		}

	cout << ans << '\n';

	return 0;
}