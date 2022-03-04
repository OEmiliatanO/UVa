import sys

fib = [0, 1]
for n in range(2, 5001):
	fib.append(fib[n - 1] + fib[n - 2])

for n in sys.stdin:
	print("The Fibonacci number for %d is %d" % (int(n), fib[int(n)]))
