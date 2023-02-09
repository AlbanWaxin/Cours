# My own Python script, written by John. All rights reserved to John.
import unittest
 
def print_lcm(l, p, q):
	print(f'Least common multiple of {p} and {q} is {l}')

def lcm(p, q):
	p, q = abs(p), abs(q)
	m = p * q
	while True:
		p %= q
		if not p:
			return m // q
		q %= p
		if not q:
			return m // p

def lcm_better(p, q):
	p, q = abs(p), abs(q)
	m = p * q
	h = p % q
	while h != 0:
		p = q
		q = h
		h = p % q
	h = m / q
	return h

def lcm_faulty(p, q):
	r, m = 0, 0
	r = p * q
	while (r > p) and (r > q):
		if (r % p == 0) and (r % q == 0):
			m = r
		r = r - 1
	return m

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
	print('Starting to calculate lcm(s) with various methods')
	print('LCM')
	print_lcm(lcm(40, 50), 40, 50)
	print('LCM BETTER')
	print_lcm(lcm_better(40, 50), 40, 50)
	print('LCM FAULTY')
	print_lcm(lcm_faulty(40, 50), 40, 50)
