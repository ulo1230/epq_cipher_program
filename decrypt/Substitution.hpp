#pragma once

#include <string>
#include <stdexcept>

class Substitution
{
public:
	std::string Encode(const std::string& plaintext, const std::string& alphabet, const std::string& mapping)
	{
		std::string ciphertext(plaintext.length(), ' ');

		for (size_t i = 0; i < plaintext.size(); i++)
		{
			int charIndex;

			if ((charIndex = alphabet.find(plaintext[i])) == std::string::npos)
				throw std::out_of_range("invalid character in plaintext");
			
			ciphertext[i] = mapping[charIndex];
		}
	}

	std::string Encode(const std::string& ciphertext, const std::string& alphabet, const std::string& mapping)
	{
		std::string plaintext(plaintext.length(), ' ');

		for (size_t i = 0; i < ciphertext.size(); i++)
		{
			int charIndex;

			if ((charIndex = mapping.find(ciphertext[i])) == std::string::npos)
				throw std::out_of_range("invalid character in ciphertext");
			
			plaintext[i] = alphabet[charIndex];
		}
	}
};