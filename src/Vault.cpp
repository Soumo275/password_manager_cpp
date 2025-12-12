#include "Vault.h"
#include "Encryption.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <direct.h> // _mkdir
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

// Simple hash function for unique filenames
static std::string simpleHash(const std::string &key)
{
    unsigned long hash = 5381;
    for (char c : key)
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

// Constructor: set masterKey and vault file path
Vault::Vault(const std::string &key)
{
    masterKey = key;

    // Ensure vault folder exists
#ifdef _WIN32
    if (_mkdir("vault") != 0)
    {
        // folder exists or error, ignore
    }
#else
    mkdir("vault", 0777); // permissions: rwxrwxrwx
#endif

    filePath = "vault/vault_" + simpleHash(masterKey) + ".dat";

    load();
}

// Load vault file and decrypt entries
void Vault::load()
{
    std::ifstream fin(filePath, std::ios::binary);
    if (!fin.is_open())
        return;

    std::stringstream ss;
    ss << fin.rdbuf();
    std::string encrypted = ss.str();

    std::string decrypted = Encryption::decrypt(encrypted, masterKey);

    std::stringstream data(decrypted);
    std::string line;

    while (std::getline(data, line))
    {
        std::stringstream l(line);
        Entry e;
        std::getline(l, e.website, ',');
        std::getline(l, e.username, ',');
        std::getline(l, e.password, ',');
        entries.push_back(e);
    }
}

// Save vault entries (encrypt)
void Vault::save()
{
    std::stringstream ss;
    for (auto &e : entries)
    {
        ss << e.website << "," << e.username << "," << e.password << "\n";
    }

    std::string plain = ss.str();
    std::string encrypted = Encryption::encrypt(plain, masterKey);

    std::ofstream fout(filePath, std::ios::binary);
    fout << encrypted;
}

// Add a new entry
void Vault::addEntry(const Entry &e)
{
    entries.push_back(e);
    save();
}

// List all entries
void Vault::listEntries()
{
    if (entries.empty())
    {
        std::cout << "No entries.\n";
        return;
    }

    for (size_t i = 0; i < entries.size(); i++)
    {
        std::cout << i + 1 << ". "
                  << entries[i].website << " | "
                  << entries[i].username << " | "
                  << entries[i].password << "\n";
    }
}

// Delete an entry by index
void Vault::deleteEntry(int index)
{
    if (index < 1 || index > (int)entries.size())
    {
        std::cout << "Invalid index.\n";
        return;
    }
    entries.erase(entries.begin() + index - 1);
    save();
}
