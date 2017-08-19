#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <iomanip> 
#include <algorithm>
#include <stdlib.h> 

using namespace std;

const double DOUBLE_MAX = numeric_limits<double>::max();

struct Point
{
	double x;
	double y;
	int idx;
	
	string toString() 
	{
		return "(" + to_string(x) + ", " + to_string(y) + ")";
	}
};

struct Answer
{
	double dist;
	Point *a;
	Point *b;
};

double euclideanDist(Point &a, Point &b)
{
	double x = a.x - b.x;
	double y = a.y - b.y;
	
	return sqrt(x*x + y*y);
}

Answer closestPairBruteforce(vector<Point> &points, int start, int end)
{
	Answer min_dist = {DOUBLE_MAX, nullptr, nullptr};
	for (int i = start; i < end; ++i) {
		for (int j = i + 1; j < end; ++j) {
			double dist = euclideanDist(points[i], points[j]);
			if (dist < min_dist.dist) {
				min_dist.dist = dist;
				min_dist.a = &(points[i]);
				min_dist.b = &(points[j]);
			}
		}
	}
	
	return min_dist;
}

Answer closestPairBruteforce(vector<Point> &points)
{
	return closestPairBruteforce(points, 0, points.size());
}

Answer closestSplitPair(
	vector<Point> &points, int start, 
	int end, int m, double d) 
{
	Point *p_m = &(points[m]);
	// start:
	int st = m;
	double anchor = p_m->x - d;
	while (st > start && points[st - 1].x > anchor) st -= 1;
	// end:
	int ed = m;
	anchor = p_m->x + d;
	--end;
	while (ed < end && points[ed + 1].x < anchor) ed += 1;
	
	++ed;
	vector<Point*> splittedPoints;
	splittedPoints.reserve(ed - st);
	for (int i = st; i < ed; ++i) {
		splittedPoints.push_back(&(points[i]));
	}
	
	// sort by y-coordinates
	sort(splittedPoints.begin(), splittedPoints.end(), 
		[](const Point *a, const Point *b) -> bool 
		{ 
			return a->y > b->y; 
		});

	Answer min_dist = {DOUBLE_MAX, nullptr, nullptr};
	int l = splittedPoints.size();
	int i_end = l - 1;
	for (int i = 0; i < i_end; ++i) {
		int j_end = min(i + 5, l);
		for (int j = i + 1; j < j_end; ++j) {
			double dist = euclideanDist(*(splittedPoints[i]), *(splittedPoints[j]));
			if (dist < min_dist.dist) {
				min_dist.dist = dist;
				min_dist.a = splittedPoints[i];
				min_dist.b = splittedPoints[j];
			}
		}
	}
	
	return min_dist;
}

Answer closestPair(vector<Point> &points, int start, int end)
{
	if (end - start <= 3) {
		return closestPairBruteforce(points, start, end);
	}
	
	int m = (end + start) >> 1;
	Answer dleft = closestPair(points, start, m);
	Answer dright = closestPair(points, m + 1, end);
	Answer d = (dleft.dist < dright.dist) ? dleft : dright;
	Answer dsplit = closestSplitPair(points, start, end, m, d.dist);
	
	return (d.dist < dsplit.dist) ? d : dsplit;
}

Answer closestPair(vector<Point> &points)
{
	// sort by x:
	sort(points.begin(), points.end(),
		[](const Point &a, const Point &b) -> bool 
		{ 
			return a.x > b.x; 
		});
		
	return closestPair(points, 0, points.size());
}

bool precisionCompare(double a, double b, int precision=6)
{
	int zeros = 1;
	while (precision--) zeros *= 10;
	double ai = round(a * zeros);
	double bi = round(b * zeros);
	
	return ai == bi;
}

int main()
{
	unsigned int n;
	double x, y;
	int idx = 0;
	cin >> n;
	vector<Point> points;
	points.reserve(n);
	while (n--) {
		cin >> x >> y;
		points.push_back({x, y, idx++});
	}
	
	//~ for (auto p : points) {
		//~ cout << p.x << " " << p.y << ", ";
	//~ }
	//~ cout << endl;
	
	Answer ans = closestPair(points);
	
	//~ // index a must be more than b
	if (ans.a->idx > ans.b->idx) {
		swap(ans.a, ans.b);
	}
	
	//~ Answer naiv = closestPairBruteforce(points);
	//~ cout << naiv.a->idx << " " << naiv.b->idx << " "
		 //~ << setprecision(6) << fixed << naiv.dist << endl;
	
	cout << ans.a->idx << " " << ans.b->idx << " "
		 << setprecision(6) << fixed << ans.dist;
	
	// STRESS TEST:
	
	//~ std::random_device rd;  //Will be used to obtain a seed for the random number engine
    //~ std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    //~ const long long int r = 100;
    //~ std::uniform_int_distribution<> dis(-r, r); 
    
	//~ while (true) {
		//~ int n = 100;
		//~ int idx = 0;
		//~ vector<Point> points;
		//~ points.reserve(n);
		//~ cout << n << endl;
		//~ while (n--) {
			
			//~ long long int x = dis(gen);
			//~ long long int y = dis(gen);
			//~ cout << x << " " << y << endl;
			//~ Point p = {x, y, idx++};
			//~ points.push_back(p);
		//~ }
		//~ Answer fast = closestPair(points);
		//~ Answer naive = closestPairBruteforce(points);
		//~ if (precisionCompare(fast.dist, naive.dist)) {
			//~ cout << naive.dist << endl;
		//~ } else {
			//~ cout << "ERROR: " << naive.dist << " " << fast.dist << endl;
			//~ break;
		//~ }
		//~ cout << "----------------------------" << endl;
	//~ }
	
	
}
