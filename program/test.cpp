#include "utils.hpp"

MapType mutate_mapping(const MapType& mapping)
{
    MapType new_mapping = mapping;
    random_integer()
}

int main()
{
    MapType mapping = random_ngram_mapping(1);
    std::string plaintext = get_sample_plaintext("1");
    plaintext = cleanup_plaintext(plaintext);
    
    std::string ciphertext;
    SubstitutionCipher<MapType>::Encode(plaintext, ciphertext, 1, mapping);

}
