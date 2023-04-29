import utils
from common import *

default_grid = [
	["a", "b", "c", "d", "e"],
	["f", "g", "h", "ij", "k"],
	["l", "m", "n", "o", "p"],
	["q", "r", "s", "t", "u"],
	["v", "w", "x", "y", "z"],
]

def polybius_encode(text):
	pass

def polybius_decode(text, grid=default_grid, reverse=False):
	allow = [str(i) for i in range(10)]
	text = list(filter(lambda x: x in allow, text))
	t1 = ""

	for i in range(int(len(text) / 2)):
		t = [int(c) - 1 for c in text[i*2 : i*2 + 2]]
		if reverse:
			t[0], t[1] = t[1], t[0]

		t1 += grid[t[0]][t[1]][0]

	return t1