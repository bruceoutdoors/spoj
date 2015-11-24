#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;

		vector<char> stick;
		vector< vector<int> > DP (n, vector<int>(n, 0));
		
		char x;
		for (int i = 0; i < n; i++) {
			cin >> x;
			stick.push_back(x);
		}

		int q = n - 1;
		for (int w = q; w >= 0; w--) {
			int p = q - w;
			for (int j = q; j >= p; j--) {
				int i = j - p;
				if (i == j) {
					if (stick[i] == '1') DP[i][j] = 1;
					else continue;
				} else if (count_if(stick.begin() + i, stick.begin() + j + 1,
					[](char a)->bool { return a == '1'; }) > (j - i + 1)/2
					) {
					DP[i][j] = j - i + 1;
				} else {
					for (int k = i; k < j; k++) {
						DP[i][j] = max(DP[i][j], DP[i][k] + DP[k+1][j]);
					}
				}
			}
		}

		cout << DP[0][q] << endl;
	}
}
