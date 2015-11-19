#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int T; cin >> T;

	while (T--) {
		int h, w; cin >> h >> w;
		int m;
		vector< vector<int> > grid, DP;
		grid = DP = vector< vector<int> >(h, vector<int>(w));

		for (int r = 0; r < h; r++) {
			for (int c = 0; c < w; c++) {
				cin >> m;
				grid[r][c] = m;
			}
		}

		DP[0] = grid[0];
		for (int r = 1; r < h; r++) {
			for (int c = 0; c < w; c++) {
				vector<int>::iterator DPBegin = DP[r-1].begin();
				if (c == 0) {
					DP[r][0] = *max_element(DPBegin, DPBegin + 2);
				} else if (c == w - 1) {
					DP[r][c] = *max_element(DPBegin + (c - 1), DPBegin + (c + 1));
				} else {	
					DP[r][c] = *max_element(DPBegin + (c - 1), DPBegin + (c + 2));
				}

				DP[r][c] += grid[r][c];
			}
		}

		cout << *max_element(DP[h-1].begin(), DP[h-1].end()) << endl;
	}
}
