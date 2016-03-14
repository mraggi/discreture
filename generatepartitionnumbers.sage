for n in range(100):
	print "{",
	for k in range(n):
		print len(Partitions(n,length=k)), ",",
	print "},"
