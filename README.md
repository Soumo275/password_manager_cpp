# password_manager_cpp

A secure, multi-user password manager in C++ that encrypts each user’s vault and stores entries in per-user files.

**Features:**

- Add, list, and delete password entries
- Per-user encrypted vaults (one vault file per master password)
- Secure storage using custom XOR-based encryption
- Automatic creation of `vault/` folder

**How to Compile:**

`g++ -std=c++17 src/*.cpp -o manager.exe`

**How to Run:**

`./manager.exe # Windows: manager.exe`
