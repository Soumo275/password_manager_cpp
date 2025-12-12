#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <string>
#include <vector>

class Encryption
{
public:
    static std::string encrypt(const std::string &data, const std::string &password);
    static std::string decrypt(const std::string &data, const std::string &password);

private:
    static std::vector<uint8_t> generateKeystream(const std::string &password, size_t length);
};

#endif
