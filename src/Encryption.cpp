#include "Encryption.hpp"
#include <vector>
#include <string>
#include <cstdint>

static uint32_t rotl(uint32_t x, int n)
{
    return (x << n) | (x >> (32 - n));
}

// Simple ChaCha-like keystream (NOT real ChaCha, but safe for demo)
std::vector<uint8_t> Encryption::generateKeystream(const std::string &password, size_t length)
{
    uint32_t state[4];

    // Initialize state from password bytes
    uint32_t seed = 0;
    for (char c : password)
        seed = seed * 131 + c;

    state[0] = 0x61707865 ^ seed;
    state[1] = 0x3320646e ^ rotl(seed, 7);
    state[2] = 0x79622d32 ^ rotl(seed, 13);
    state[3] = 0x6b206574 ^ rotl(seed, 18);

    std::vector<uint8_t> stream;
    stream.reserve(length);

    for (size_t i = 0; i < length; i++)
    {
        // Mix the state
        state[0] += state[1];
        state[3] = rotl(state[3] ^ state[0], 16);
        state[2] += state[3];
        state[1] = rotl(state[1] ^ state[2], 12);
        state[0] += state[1];
        state[3] = rotl(state[3] ^ state[0], 8);
        state[2] += state[3];
        state[1] = rotl(state[1] ^ state[2], 7);

        uint32_t block = state[0] ^ state[1] ^ state[2] ^ state[3];
        stream.push_back((uint8_t)(block & 0xFF));
    }

    return stream;
}

std::string Encryption::encrypt(const std::string &data, const std::string &password)
{
    auto ks = generateKeystream(password, data.size());
    std::string out = data;

    for (size_t i = 0; i < data.size(); i++)
        out[i] = data[i] ^ ks[i];

    return out;
}

std::string Encryption::decrypt(const std::string &data, const std::string &password)
{
    return encrypt(data, password); // XOR is reversible
}
