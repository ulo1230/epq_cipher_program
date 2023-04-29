#pragma once

#include <cmath>
#include <string>

class RailFence
{
public:
	std::string Encode(const std::string& plaintext, int numRails)
	{
		if(numRails == 1)
			return plaintext;

		std::string ciphertext(plaintext.length(), ' ');

		int period = 2 * numRails - 2;
		size_t offset = 0;

		for(size_t i = 0; i < plaintext.length(); i += period)
		{
			ciphertext[offset++] = plaintext[i];
		}

		for(int rail = 1; rail < numRails - 1; rail++)
		{
			for(size_t i = rail, j; i < plaintext.length(); i += period)
			{
				ciphertext[offset++] = plaintext[i];
			
				if((j = i + (period - 2 * rail)) < plaintext.length())
				{
					ciphertext[offset++] = plaintext[j];
				}
			}
		}

		for(size_t i = numRails - 1; i < plaintext.length(); i += period)
		{
			ciphertext[offset++] = plaintext[i];
		}

		return ciphertext;
	}

	std::string Decode(const std::string& ciphertext, int numRails)
	{
		if(numRails == 1)
			return ciphertext;

		std::string plaintext(ciphertext.length(), ' ');

		int period = 2 * numRails - 2;
		size_t offset = 0;

		for(size_t i = 0; i < ciphertext.length(); i += period)
		{
			plaintext[i] = ciphertext[offset++];
		}

		for(size_t rail = 1; rail < numRails - 1; rail++)
		{
			for(size_t i = rail, j; i < ciphertext.length(); i += period)
			{
				plaintext[i] = ciphertext[offset++];

				if((j = i + (period - 2 * rail)) < plaintext.length())
				{
					plaintext[j] = ciphertext[offset++];
				}
			}
		}

		for(size_t i = numRails - 1; i < plaintext.length(); i += period)
		{
			plaintext[i] = ciphertext[offset++];
		}

		return plaintext;
	}
};