#Uses python3
import sys
import math

class Point:
	def __init__(self, idx,  x, y):
		self.x = x
		self.y = y
		self.idx = idx
		
	def __repr__(self):
		return "<{}: {} {}>".format(self.idx, self.x, self.y)

def euclidean_dist(a, b):
	x = a.x - b.x
	y = a.y - b.y
	return math.sqrt(x*x + y*y)

def closest_pair_bruteforce(points, start=None, end=None):
	if start == None:
		start = 0
		end = len(points)
		
	min_dist = (float("inf"), -1, -1)
	for i in range(start, end):
		for j in range(i+1, end):
			dist = euclidean_dist(points[i], points[j])
			if dist < min_dist[0]:
				min_dist = (dist, points[i], points[j])
	return min_dist
	
def closest_pair(points, start=None, end=None):
	if start == None:
		start = 0
		end = len(points)
		points.sort(key=lambda b: b.x) # sort by x
		
	if end - start <= 3:
		return closest_pair_bruteforce(points, start, end)
	m = (end + start) >> 1
	dleft = closest_pair(points, start, m)
	dright = closest_pair(points, m + 1, end)
	d = dleft if dleft[0] < dright[0] else dright
	dsplit = closest_split_pair(points, start, end, m, d[0])
	return d if d[0] < dsplit[0] else dsplit
	
def closest_split_pair(points, start, end, mid, d):
	st, ed = get_range_within_dist(points, start, end, mid, d, key=lambda b:b.x)
	splitted_points = points[st:ed+1]
	splitted_points.sort(key=lambda b:b.y) # sort by y-coordinates
	min_dist = (float("inf"), -1, -1)
	l = len(splitted_points)
	for i in range(0, l - 1):
		for j in range(i + 1, min(i + 6, l)): # consider only 5 points after
			dist = euclidean_dist(splitted_points[i], splitted_points[j])
			if dist < min_dist[0]:
				min_dist = (dist, splitted_points[i], splitted_points[j])
	return min_dist

# assuming the points are sorted with key
def get_range_within_dist(points, start, end, m, d, key):
	p_m = points[m]
	# start:
	st = m
	anchor = key(p_m) - d
	while st > start and key(points[st - 1]) > anchor:
		st -= 1
	# end:
	ed = m
	anchor = key(p_m) + d
	end -= 1
	while ed < end and key(points[ed + 1]) < anchor:
		ed += 1
		
	return (st, ed+1)

if __name__ == '__main__':
	input = sys.stdin.read()
	data = list(map(int, input.split()))
	n = data[0]
	points = [Point(idx, data[item], data[item+1]) for idx, item in enumerate(range(1, len(data), 2))]
	ans = closest_pair(points)
	
	a, b = ans[1].idx, ans[2].idx
	if a > b: a, b = b, a
	print(a, b, "{0:.6f}".format(ans[0]))
	
