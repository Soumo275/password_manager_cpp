#include "App.h"
#include <iostream>

void App::run()
{
    std::string master;
    std::cout << "Enter master password: ";
    std::getline(std::cin, master);

    Vault vault(master);

    while (true)
    {
        std::cout << "\n1. Add Entry\n2. View Entries\n3. Delete Entry\n4. Exit\nChoose: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1)
        {
            Entry e;
            std::cout << "Website: ";
            std::getline(std::cin, e.website);
            std::cout << "Username: ";
            std::getline(std::cin, e.username);
            std::cout << "Password: ";
            std::getline(std::cin, e.password);

            vault.addEntry(e);
        }
        else if (choice == 2)
        {
            vault.listEntries();
        }
        else if (choice == 3)
        {
            int index;
            std::cout << "Delete which entry? ";
            std::cin >> index;
            vault.deleteEntry(index);
        }
        else
            break;
    }
}
