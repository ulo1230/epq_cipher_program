
table = {
	"a": ".-",
	"b": "-...",
	"c": "-.-.",
	"d": "-..",
	"e": ".",
	"f": "..-.",
	"g": "--.",
	"h": "....",
	"i": "..",
	"j": ".---",
	"k": "-.-",
	"l": ".-..",
	"m": "--",
	"n": "-.",
	"o": "---",
	"p": ".--.",
	"q": "--.-",
	"r": ".-.",
	"s": "...",
	"t": "-",
	"u": "..-",
	"v": "...-",
	"w": ".--",
	"x": "-..-",
	"y": "-.--",
	"z": "--..",
}

reverse_table = dict((v, k) for k, v in table.items())

def morse_decode(text, error=True):
	text = text.split(" ")
	t1 = []

	for c in text:
		c = c.lower()
		
		if c in reverse_table:
			t1.append(reverse_table[c])
		elif error:
			raise Exception("invalid morse code chr: " + c)

	return "".join(t1)

def morse_encode(text):
	t1 = []

	for c in text:
		c = c.lower()
		
		if c in table:
			t1.append(table[c])

	return " ".join(t1)