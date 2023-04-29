import re
from collections import Counter


def words(text, ch):
	return re.findall(f"[{ch}]+", text.lower())

text = open("dict/big_fr.txt").read()

fr = "a-zàâçéèêëîïôûùüÿñæœ"
en = "a-z"

dictionary = Counter(words(text, fr))

for k, v in dictionary.items():
	print(k, v)