#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> values, sizes;
	int S, N; cin >> S >> N;

	// slot these in for easy array access; 
	// values themselves won't be used.
	sizes.push_back(-1);
	values.push_back(-1);

	int sz, val;

	for (int i = 0; i < N; i++) {
		cin >> sz >> val;
		sizes.push_back(sz);
		values.push_back(val);
	}

	vector< vector<int> > P(N + 1, vector<int>(S + 1, 0));

	for (int i = 1; i <= N; i++) { // i is scope of items in consideration
		for (int j = 1; j <= S; j++) { // j is max size of bag
			if (sizes[i] > j) {
				P[i][j] = P[i - 1][j];
			} else {
				P[i][j] = max(P[i - 1][j], values[i] + P[i - 1][j - sizes[i]]);
			}
		}
	}

	cout << P[N][S];
}
