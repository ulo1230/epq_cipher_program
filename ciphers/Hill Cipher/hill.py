import math
import numpy as np

default_alphabet = [chr(ord("a") + c) for c in range(26)]

def egcd(a, b):
	if a == 0:
		return (b, 0, 1)
	g, y, x = egcd(b%a,a)
	return (g, x - (b//a) * y, y)

def modinv(a, m):
	g, x, y = egcd(a, m)
	if g != 1:
		raise Exception("No modular inverse")
	return x%m

def hill_encode(text, matrix, alphabet=None):
	alphabet = default_alphabet if alphabet == None else alphabet
	n = math.sqrt(len(matrix))

	if int(n) != n:
		return None

	n = int(n)

	text = text[:math.floor(len(text)/n) * n]
	text = [alphabet.index(c) for c in text if c in alphabet]

	matrix = np.reshape(matrix, (n, n))

	t1 = ""

	for i in range(0, len(text), n):
		t = text[i:i+n]

		t = np.dot(matrix, np.reshape(t, (n, 1)))
		t = [c % len(alphabet) for c in t.flatten()]

		t1 += "".join([alphabet[c] for c in t])

	return t1

def hill_decode(text, matrix, alphabet=None):
	alphabet = default_alphabet if alphabet == None else alphabet
	n = math.sqrt(len(matrix))

	if int(n) != n:
		return None

	n = int(n)

	text = text[:math.floor(len(text)/n) * n]
	text = [alphabet.index(c) for c in text if c in alphabet]

	# print(text)

	p = len(alphabet)
	matrix = np.reshape(matrix, (n, n))

	det = np.linalg.det(matrix)
	matrix = np.linalg.inv(matrix)
	matrix *= det
	matrix *= modinv(det % len(alphabet), len(alphabet))
	matrix = np.mod(matrix, len(alphabet))

	t1 = ""

	for i in range(0, len(text), n):
		t = text[i:i+n]

		t = np.dot(matrix, np.reshape(t, (n, 1)))
		t = [int(round(c) % len(alphabet)) for c in t.flatten()]

		t1 += "".join([alphabet[c] for c in t])

	return t1


print(hill_decode("aldcfzfz", (2, 3, 5, 7)))
# print(modinv(1000, 233))