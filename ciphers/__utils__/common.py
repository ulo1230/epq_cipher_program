import morse
import re
import random

def text_cleanup(text, spaces=False, allow=[]):
	text = text.lower()

	def key(c):
		if c in allow: return True
		c = ord(c)
		if c in range(ord("a"), ord("z") + 1): return True
		if spaces and c in [ord(" "), ord("\n"), ord("\t")]: return True
		return False

	return "".join(list(filter(key, list(text))))

def text_substitute(text, sub):
	return "".join([(sub[c].upper() if c in sub else c) for c in text])

def text_shift(text, n):
	text = text.lower()

	def f(s):
		c = ord(s) - ord("a")
		if c not in range(26):
			return s
		return chr((c + n) % 26 + ord("a"))

	return "".join([f(c) for c in text])

def list_substitute(l, sub):
	return "".join([(l[c] if c in sub else c) for c in l])

def alphabetic_frequency(text, relative=False):
	text = text.lower()
	freq = {}

	for i in range(ord("a"), ord("z") + 1):
		freq[chr(i)] = 0

	for c in text:
		if ord(c) in range(ord("a"), ord("z") + 1):
			freq[c] += 1

	if relative:
		total = sum(freq.values())

		if total != 0:
			freq = dict((k, v / total) for k, v in freq.items())

	return freq

def text_split(text, n):
	return [text[i:i+n] for i in range(0, len(text), n)]

def list_frequency(l, relative=False):
	d = {}
	for x in l:
		if x not in d: d[x] = 0
		d[x] += 1

	if relative:
		t = sum(d.values())
		for k in d:
			d[k] /= t

	return d

def index_of_coincidence(text):
	text = text_cleanup(text, spaces=False)
	freq = list_frequency(list(text))

	t = len(text)
	ioc = 0

	for f in freq.values():
		ioc += (f / t) * ((f-1) / (t-1))

	return ioc

def list_ioc(l):
	freq = list_frequency(l)

	t = len(text)
	ioc = 0

	for f in freq.values():
		ioc += (f / t) * ((f-1) / (t-1))

	return ioc

def random_str(l):
	import random
	return "".join([chr(random.randrange(0, 26) + ord("a")) for i in range(l)])

def repeated_ngrams(text, n):
	l = {}

	for i in range(len(text) - n + 1):
		s = text[i:i+n]

		if s not in l: l[s] = []
		l[s].append(i)

	return l

def repeated_ngrams_count(text, n):
	l = {}

	for i in range(len(text) - n + 1):
		s = text[i:i+n]

		if s not in l: l[s] = 0
		l[s] += 1

	return l

def all_repeated_ngrams(text, lens):
	n = {}
	[n.update(repeated_ngrams(text, l)) for l in lens]
	return n

def possible_diffs(l):
	x = []
	for i in range(len(l) - 1):
		for j in range(i + 1, len(l)):
			x.append(abs(l[i] - l[j]))
	return x

def factors(x):
	l = []
	for i in range(2, x + 1):
		if x % i == 0:
			l.append(i)
	return l

def arrange_text(text, arrange_type, block):
	t1 = ""
	gap = int(len(text) / block)
	
	if arrange_type == "column":
		for i in range(gap):
			for j in range(block):
				t1 += text[j*gap + i]
			t1 += "\n"

	elif arrange_type == "row":
		for i in range(gap):
			for j in range(block):
				t1 += text[i*block + j]
			t1 += "\n"

	return t1[:-1]

def unarrange_text(text, arrange_type, block):
	t1 = ""
	text = text.replace("\n", "")
	gap = int(len(text) / block)

	if arrange_type == "column":
		for j in range(block):
			for i in range(gap):
				t1 += text[i*block + j]

	elif arrange_type == "row":
		for i in range(gap):
			for j in range(block):
				t1 += text[i*block + j]

	return t1

def reorder_columns(text, order, block):
	t1 = ""
	text = text.replace("\n", "")
	gap = int(len(text) / block)
	columns = ["".join([text[j*block + i] for j in range(gap)]) for i in range(block)]
	new_columns = [columns[order[i]] for i in range(block)]

	for i in range(gap):
		for c in new_columns:
			t1 += c[i]
		t1 += "\n"

	return t1