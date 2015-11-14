#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int main()
{
	const int N_MAX = 20000001;
	int *DP = new int[N_MAX];
	DP[1] = 0;

	for (int i = 2; i < N_MAX; i++) {
		int minimum =  1 + DP[i - 1];
		if (i % 3 == 0) minimum = min(minimum, 1 + DP[i/3]);
		if (i % 2 == 0) minimum = min(minimum, 1 + DP[i/2]);

		DP[i] = minimum;
	}

	int T, N; cin >> T;
	int c = 1;
	while (T--) {
		cin >> N;
		cout << "Case " << c++ << ": " << DP[N] << endl;
	}

	delete[] DP;
}
