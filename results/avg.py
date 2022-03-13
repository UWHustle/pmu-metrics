import sys

filename = sys.argv[1]
f = open(filename, 'r')
found = False
l = []
for line in f:
	if not found and line[0] != 'N':
		continue
	elif not found:
		found = True
		l = []
		continue
	l.append(int(line))
	if len(l) == 10:
		l = sorted(l)
		print sum(l[1:9])/8.0
		found = False
		l = []
