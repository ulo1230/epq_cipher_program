#pragma once

#include <string>
#include <string_view>
#include <cassert>
#include <iostream>

template <typename MapType>
class SubstitutionCipher
{
public:
    static void Encode(
        const std::string& plaintext,
        std::string& ciphertext,
        const int degree,
        const MapType& mapping
    ) {
        assert(plaintext.size() % degree == 0);
        const std::string_view& plaintext_sv(plaintext);
        ciphertext.resize(plaintext.size());

        for (size_t i = 0; i < plaintext.size(); i += degree)
        {
            auto it = mapping.find(plaintext.substr(i, degree));
            assert(it != mapping.end());
            ciphertext.replace(i, degree, it->second);
        }
    }

    static void Decode(
        const std::string& ciphertext,
        std::string& plaintext,
        const int degree,
        const MapType& reverseMapping
    ) {
        assert(ciphertext.size() % degree == 0);
        const std::string_view& ciphertext_sv(plaintext);
        plaintext.resize(ciphertext.size());

        for (size_t i = 0; i < ciphertext.size(); i += degree)
        {
            auto it = reverseMapping.find(ciphertext.substr(i, degree));
            assert(it != reverseMapping.end());
            plaintext.replace(i, degree, it->second);
        }
    }
};