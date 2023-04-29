#pragma once

#include <cmath>
#include <string>
#include <vector>
#include "Matrix.hpp"

class Hill
{
public:
	std::string Encode(const std::string& plaintext, const std::vector<std::vector<int>>& key, const std::string& alphabet)
	{
		int keysize = key.size();
		int mod = alphabet.length();

		Matrix<int> matrix(keysize, keysize, key);

		std::string ciphertext(plaintext.length() - plaintext.length() % keysize, ' ');
		std::vector<int> text(keysize), newText(keysize);
		int charIndex;

		for (size_t i = 0; i < ciphertext.length(); i += keysize)
		{
			for (size_t j = 0; j < keysize; j++)
			{				
				if ((charIndex = alphabet.find(plaintext[i + j])) == std::string::npos)
					throw std::out_of_range("invalid character in plaintext");

				text[j] = charIndex;
			}

			matrix.MultiplyVector(newText, text);

			for (size_t j = 0; j < keysize; j++)
			{
				ciphertext[i + j] = alphabet[Mod(newText[j], mod)];
			}
		}

		return ciphertext;
	}

	std::string Decode(const std::string& ciphertext, const std::vector<std::vector<int>>& key, const std::string& alphabet)
	{
		int keysize = key.size();
		int mod = alphabet.length();

		Matrix<int> matrix(keysize, keysize, key);
		Matrix<int> inverse = matrix.Adjoint();
		int det = ModInv(Mod(matrix.DeterminantFromAdjoint(inverse), mod), mod);

		for (auto& r : inverse.mat)
		{
			for (auto& c : r)
			{
				c = Mod(det * Mod(c, mod), mod);
			}
		}

		if (det == 0)
			throw std::domain_error("determinant must be non-zero");

		std::string plaintext(ciphertext.length() - ciphertext.length() % keysize, ' ');
		std::vector<int> text(keysize), newText(keysize);
		int charIndex;

		for (size_t i = 0; i < plaintext.length(); i += keysize)
		{
			for (size_t j = 0; j < keysize; j++)
			{				
				if ((charIndex = alphabet.find(ciphertext[i + j])) == std::string::npos)
					throw std::out_of_range("invalid character in ciphertext");

				text[j] = charIndex;
			}

			inverse.MultiplyVector(newText, text);

			for (size_t j = 0; j < keysize; j++)
			{
				plaintext[i + j] = alphabet[Mod(newText[j], mod)];
			}
		}

		return plaintext;
	}

	bool IsValidKey(const std::vector<std::vector<int>>& key, int alphabetLength)
	{
		int keySize = key.size();
		Matrix<int> matrix(keySize, keySize, key);
		return ModInv(Mod(matrix.Determinant(), alphabetLength), alphabetLength) == 0 ? false : true;
	}

private:
	static int Mod(int x, int mod)
	{
		return (mod + (x % mod)) % mod;
	}

	static int ModInv(int x, int m)
	{
		int old_r = x, r = m;
		int old_s = 1, s = 0;
		int old_t = 0, t = 1;

		while (r > 0)
		{
			int q = trunc(double(old_r) / r);
			int new_r = old_r - q * r;
			int new_s = old_s - q * s;
			int new_t = old_t - q * t;

			old_r = r, r = new_r;
			old_s = s, s = new_s;
			old_t = t, t = new_t;
		}

		if (old_r == 1)
			return old_s;

		return 0;
	}
};