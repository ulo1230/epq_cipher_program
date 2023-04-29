import utils
import math
from itertools import combinations

def playfair_encode(text, grid, rows=-1, cols=-1, replace=""):
	text = list(filter(lambda x: x in grid, text))
	t1 = ""

	if rows == -1 or cols == -1:
		rows = cols = int(math.sqrt(len(grid)))

		if rows * cols != len(grid):
			raise "invalid shape"

	for i in range(0, len(text), 2):
		i1 = grid.index(text[i])
		i2 = grid.index(text[i + 1])

		if i1 == i2:
			if len(replace) > 0:
				i2 = grid.index(replace[0])

				if i1 == i2 and replace.length > 1:
					i2 = grid.index(replace[1])

		if i1 == i2:
			i2 = 1 if i2 == 0 else 0

		r1 = int(i1 / rows); c1 = i1 % cols
		r2 = int(i2 / rows); c2 = i2 % cols

		r_1 = 0; c_1 = 0
		r_2 = 0; c_2 = 0

		if r1 == r2:
			r_1 = r1
			c_1 = c1 + 1

			r_2 = r2
			c_2 = c2 + 1

		elif c1 == c2:
			r_1 = r1 + 1
			c_1 = c1

			r_2 = r2 + 1
			c2 = c2

		else:
			r_1 = r1
			c_1 = c2

			r_2 = r2
			c_2 = c1

		r_1 %= rows; c_1 %= cols
		r_2 %= rows; c_2 %= cols

		t1 += grid[r_1 * rows + c_1]
		t1 += grid[r_2 * rows + c_2]

	return t1

def playfair_decode(text, grid, rows=-1, cols=-1, replace=""):
	text = list(filter(lambda x: x in grid, text))
	t1 = ""

	if rows == -1 or cols == -1:
		rows = cols = int(math.sqrt(len(grid)))

		if rows * cols != len(grid):
			raise "invalid shape"

	for i in range(0, len(text), 2):
		i1 = grid.index(text[i])
		i2 = grid.index(text[i + 1])

		if i1 == i2:
			if len(replace) > 0:
				i2 = grid.index(replace[0])

				if i1 == i2 and replace.length > 1:
					i2 = grid.index(replace[1])

		if i1 == i2:
			i2 = 1 if i2 == 0 else 0

		r1 = int(i1 / rows); c1 = i1 % cols
		r2 = int(i2 / rows); c2 = i2 % cols

		r_1 = 0; c_1 = 0
		r_2 = 0; c_2 = 0

		if r1 == r2:
			r_1 = r1
			c_1 = c1 - 1

			r_2 = r2
			c_2 = c2 - 1

		elif c1 == c2:
			r_1 = r1 - 1
			c_1 = c1

			r_2 = r2 - 1
			c2 = c2

		else:
			r_1 = r1
			c_1 = c2

			r_2 = r2
			c_2 = c1

		r_1 %= rows; c_1 %= cols
		r_2 %= rows; c_2 %= cols

		t1 += grid[r_1 * rows + c_1]
		t1 += grid[r_2 * rows + c_2]

	return t1

def playfair_construct(match, shape):
	rows = shape[0]; cols = shape[1]
	grids = [[[' '] * cols for i in range(rows)]]

	coords = [(i, j) for j in range(shape[1]) for i in range(shape[0])]

	for a, b in match.items():
		if len(grids) == 0:
			break

		ng = []

		for grid in grids:
			for c1, c2 in combinations(coords, 2):
				gc1 = [x[:] for x in grid]
				gc2 = [x[:] for x in grid]
				
				gc1[c1[0]][c1[1]] = a[0]; gc1[c2[0]][c2[1]] = a[1]

				if c1[0] == c2[0]:
					if abs(c1[1] - c2[1]) <= 1:
						continue

					gc1[c1[0]][(c1[1] + 1) % cols] = b[0]; gc1[c2[0]][(c2[1] + 1) % cols] = b[1]
				elif c1[1] == c2[1]:
					if abs(c1[0] - c2[0]) <= 1:
						continue

					gc1[(c1[0] + 1) % rows][c1[1]] = b[0]; gc1[(c2[0] + 1) % rows][c2[1]] = b[1]
				else:
					gc1[c1[0]][c2[1]] = b[0]; gc1[c2[0]][c1[1]] = b[1]


				for r in range(rows):
					for c in range(cols):
						if grid[r][c] != ' ' and grid[r][c] != gc1[r][c]:
							gc1 = None
							break

					if gc1 == None:
						break

				for r in range(rows):
					for c in range(cols):
						if grid[r][c] != ' ' and grid[r][c] != gc2[r][c]:
							gc2 = None
							break

					if gc2 == None:
						break

				if gc1:
					ng.append(gc1)

				if gc2:
					ng.append(gc2)

		print(len(grids))

		grids = ng

	return ["".join(["".join(r) for r in g]) for g in grids]