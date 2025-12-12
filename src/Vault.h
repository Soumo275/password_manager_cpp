#pragma once
#include <vector>
#include <string>
#include "Entry.h"

class Vault
{
private:
    std::vector<Entry> entries;
    std::string masterKey;
    std::string filePath;

public:
    Vault(const std::string &key);

    void load();
    void save();

    void addEntry(const Entry &e);
    void listEntries();
    void deleteEntry(int index);
};
