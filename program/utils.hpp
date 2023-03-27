#include <unordered_map>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

#include "substitution_cipher.hpp"

typedef std::unordered_map<std::string, std::string> MapType;

std::random_device random_device;
std::mt19937 rg(random_device());


MapType random_ngram_mapping(int degree)
{
    MapType mapping = {};
    std::vector<std::string> ngrams(std::pow(26, degree));

    std::string ngram(degree, ' ');
    for (int i = 0; i < ngrams.size(); i++)
    {
        for (int j = 0, k = 1; j < degree; j++, k *= 26)
        {
            char c = 'a';
            c += (i / k) % 26;
            ngram[j] = c;
        }

        ngrams[i] = ngram;
    }

    std::vector<std::string> reordered_ngrams(ngrams);
    std::shuffle(reordered_ngrams.begin(), reordered_ngrams.end(), rg);

    for (int i = 0; i < ngrams.size(); i++)
        mapping[ngrams[i]] = reordered_ngrams[i];

    return mapping;
}

template<typename T>
T to_lower(T);

template<>
char to_lower<char>(char c)
{
    return ('A' <= c && c <= 'Z') ? (c - 'A' + 'a') : c;
}

template<typename T>
bool is_alpha(T);

template<>
bool is_alpha<char>(char c)
{
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

std::string cleanup_plaintext(const std::string& plaintext)
{
    std::string output;
    for (int i = 0; i < plaintext.size(); i++)
    {
        char c = to_lower(plaintext[i]);
        if (c < 'a' || c > 'z')
            continue;
        output += c;
    }
    return output;
}

std::string get_sample_plaintext(const std::string& name)
{
    std::fstream file("samples/" + name + ".txt");
    assert(file);
    std::ostringstream ss;
    ss << file.rdbuf();
    file.close();
    return ss.str();
}

std::vector<std::pair<int, char>> non_alpha_positions(
    const std::string& text
) {
    std::vector<std::pair<int, char>> positions;

    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];
        if (!is_alpha(c))
            positions.push_back(std::make_pair(i, c));
    }

    return positions;
}

std::string insert_characters(
    const std::string& text,
    std::vector<std::pair<int, char>> positions
) {
    int text_offset = 0;
    int prev_position = 0;
    int total = 0;
    std::string output(text.size() + positions.size(), ' ');
    std::cout << output.size() << std::endl;

    std::string_view text_view(text);

    for (auto [position, c] : positions)
    {
        int section_length = position - prev_position;
        output.replace(prev_position, section_length, text_view.substr(text_offset, section_length));
        output[prev_position + section_length] = c;
        prev_position = position + 1;
        text_offset += section_length;
        total += section_length;
    }

    int section_length = text.size() - total;
    output.replace(prev_position, section_length, text_view.substr(text_offset, section_length));
    
    return output;
}

int random_integer(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rg);
}