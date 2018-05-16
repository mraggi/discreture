def bla():
	X = Combinations(24,12)
	i = 0
	for x in X:
		if (x[3] == 8):
			i += 1
	print i
