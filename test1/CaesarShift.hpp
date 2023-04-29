#pragma once

#include <string>
#include <stdexcept>

class CaesarShift
{
public:
	std::string Encode(const std::string& alphabet, const std::string& plaintext, int shift)
	{
		std::string ciphertext(plaintext.length(), ' ');
		int charIndex;

		for (size_t i = 0; i < plaintext.length(); i++)
		{
			if ((charIndex = alphabet.find(plaintext[i])) == std::string::npos)
				throw std::out_of_range("invalid character in plaintext");

			ciphertext[i] = alphabet[(charIndex + shift) % alphabet.length()];
		}

		return ciphertext;
	}

	std::string Decode(const std::string& ciphertext, int shift, const std::string& alphabet)
	{
		shift = Mod(-shift, alphabet.length());

		std::string plaintext(ciphertext.length(), ' ');
		int charIndex;

		for (size_t i = 0; i < ciphertext.length(); i++)
		{
			if ((charIndex = alphabet.find(ciphertext[i])) == std::string::npos)
				throw std::out_of_range("invalid character in ciphertext");

			plaintext[i] = alphabet[(charIndex + shift) % alphabet.length()];
		}

		return plaintext;
	}

private:
	static int Mod(int a, int b)
	{
		return ((a % b) + b) % b;
	}
};