import utils
from common import *

def vigenere_encode(text, key):
	text = list(text_cleanup(text, spaces=False))
	key = text_cleanup(key, spaces=False)

	key = [ord(c) - ord("a") for c in key]
	text = [ord(c) - ord("a") for c in text]

	for i, c in enumerate(text):
		kc = key[i % len(key)]
		text[i] = chr((c + kc) % 26 + ord("a"))

	return "".join(text)

def vigenere_decode(text, key):
	text = list(text_cleanup(text, spaces=False))
	key = text_cleanup(key, spaces=False)

	key = [ord(c) - ord("a") for c in key]
	text = [ord(c) - ord("a") for c in text]

	for i, c in enumerate(text):
		kc = key[i % len(key)]
		text[i] = chr((c - kc) % 26 + ord("a"))

	return "".join(text)

def vigenere_factors(text, ngrams=[3, 4, 5], max_factor=30):
	ngrams = all_repeated_ngrams(text, ngrams)
	ngrams = dict((k, v) for k, v in ngrams.items() if len(v) > 3)

	facs = [f for v in ngrams.values() for f in [factors(f) for f in possible_diffs(v)]]
	facs = [f for fl in facs for f in fl]
	facs = [f for f in facs if f <= max_factor]
	facs = list_frequency(facs)

	return facs

def vigenere_frequency(text, key_len):
	freqs = [list_frequency([text[j] for j in range(i, len(text), key_len)]).items() for i in range(key_len)]
	freqs = [sorted(f, key=lambda x: x[1], reverse=True) for f in freqs]

	return freqs

def vigenere_keyword_guess(freqs, order=None):
	order = [0] * len(freqs) if not order else order
	assert(len(order) == len(freqs))

	key = [f[order[i]][0] for i, f in enumerate(freqs)]
	key = [chr(((ord(c) - ord("e")) % 26) + ord("a")) for c in key]

	return "".join(key)

def vigenere_average_ioc(text, key_len):
	iocs = ["".join([text[j] for j in range(i, len(text), key_len)]) for i in range(key_len)]
	iocs = [index_of_coincidence(t) for t in iocs]

	return sum(iocs) / len(iocs)