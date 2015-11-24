#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define SMOKE 0
#define COLOR 1

int main()
{
	int t;
	while (cin >> t) {
		vector<int> c;

		int x;
		while (t--) {
			cin >> x;
			c.push_back(x);
		}

		vector< vector< vector<int> > > DP(c.size(),
			vector< vector<int> >(c.size(),
				vector<int>(2, 0)
				)
			);

		int m = c.size() - 1;

		for (int w = m; w >= 0; w--) {
			int p = m - w;
			for (int j = m; j > p - 1; j--) {
				int i = j - p;
				if (i == j) {
					DP[i][j][COLOR] = c[i];
				} else {
					DP[i][j][SMOKE] = INT_MAX;
					for (int k = i; k < j; k++) {
						int totalSmoke = DP[i][k][SMOKE] + DP[k + 1][j][SMOKE] + 
									DP[i][k][COLOR] * DP[k + 1][j][COLOR];

						if (totalSmoke < DP[i][j][SMOKE]) {
							DP[i][j][SMOKE] = totalSmoke;
							DP[i][j][COLOR] = (DP[i][k][COLOR] + DP[k + 1][j][COLOR]) % 100;
						}
					}
				}
			}
		}

		cout << DP[0][m][SMOKE] << endl;
	}
}
