
def rail_fence_encode(count, text):
	period = 2 * (count - 1)
	rails = [[] for i in range(count)]

	for i, c in enumerate(list(text)):
		r = i % period
		r = (period - r) if r > period / 2 else r
		rails[r].append(c)

	return "".join(["".join(r) for r in rails])

def rail_fence_decode(count, text):

	return None