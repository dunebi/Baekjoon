#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int N, ans;

int char_to_int(char c) {
	return (int)(c - 'a');
}

class Trie {
private:
	bool isTerminal;
	Trie* children[26]; //소문자 26자로만 이루어짐

public:
	Trie() {
		this->isTerminal = false;
		memset(children, NULL, sizeof(children));
	}
	~Trie() {
		for (int i = 0; i < 26; i++)
			if (children[i] != NULL) delete children[i];
	}

	void insert(const char* key);
	void print();
	void solve(bool isRoot, int cnt);
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	while (true) {
		Trie* root = new Trie();

		cin >> N;
		if (cin.eof() == true) break;

		string temp;
		for (int i = 0; i < N; i++) {
			cin >> temp;
			root->insert(temp.c_str());
		}

		ans = 0;
		root->solve(true, 0);
		cout << fixed;
		cout.precision(2);
		cout << (double)ans / (double)N << '\n';

		delete root;
	}

	return 0;
}

void Trie::insert(const char* key) {
	if (*key == '\0') isTerminal = true;
	else {
		int index = char_to_int(*key);
		if (children[index] == NULL)
			children[index] = new Trie();
		children[index]->insert(key + 1);
	}
}

void Trie::print() {
	for (int i = 0; i < 26; i++) {
		if (children[i] != NULL) {
			cout << (char)(i + 'a') << '\n';
			children[i]->print();
		}
	}
}

void Trie::solve(bool isRoot, int cnt) {
	if (isRoot) {
		for (int i = 0; i < 26; i++) {
			if (children[i] != NULL) children[i]->solve(false, cnt + 1);
		}
	}
	else {
		if (isTerminal == true) {
			ans += cnt;
		}
		vector<int> idx;

		for (int i = 0; i < 26; i++) {
			if (children[i] != NULL) {
				idx.push_back(i);
			}
		}

		if (idx.size() == 1) {
			if (isTerminal == true)
				children[idx[0]]->solve(false, cnt + 1);
			else
				children[idx[0]]->solve(false, cnt);
		}
		else if (idx.size() > 1) {
			for (int i = 0; i < idx.size(); i++)
				children[idx[i]]->solve(false, cnt + 1);
		}
	}

}