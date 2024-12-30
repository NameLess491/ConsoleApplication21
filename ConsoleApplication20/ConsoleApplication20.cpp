#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Клас "Фірма"
class Firm {
public:
    std::string name;
    std::string owner;
    std::string phone;
    std::string address;
    std::string activity;

    Firm(std::string name, std::string owner, std::string phone,
        std::string address, std::string activity)
        : name(name), owner(owner), phone(phone), address(address), activity(activity) {}

    void display() const {
        std::cout << "Name: " << name << "\nOwner: " << owner
            << "\nPhone: " << phone << "\nAddress: " << address
            << "\nActivity: " << activity << "\n---\n";
    }
};

// Клас "Довідник"
class Directory {
private:
    std::vector<Firm> firms;
    const std::string filename = "firms.txt";

public:
    Directory() {
        loadFromFile();
    }

    void addFirm(const Firm& firm) {
        firms.push_back(firm);
        saveToFile();
    }

    void searchByName(const std::string& name) const {
        search([name](const Firm& firm) { return firm.name == name; });
    }

    void searchByOwner(const std::string& owner) const {
        search([owner](const Firm& firm) { return firm.owner == owner; });
    }

    void searchByPhone(const std::string& phone) const {
        search([phone](const Firm& firm) { return firm.phone == phone; });
    }

    void searchByActivity(const std::string& activity) const {
        search([activity](const Firm& firm) { return firm.activity == activity; });
    }

    void displayAll() const {
        for (const auto& firm : firms) {
            firm.display();
        }
    }

private:
    void saveToFile() const {
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Error: Unable to open file for writing.\n";
            return;
        }

        for (const auto& firm : firms) {
            outFile << firm.name << "\n" << firm.owner << "\n" << firm.phone
                << "\n" << firm.address << "\n" << firm.activity << "\n";
        }
    }

    void loadFromFile() {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "No file found. Starting with an empty directory.\n";
            return;
        }

        std::string name, owner, phone, address, activity;
        while (std::getline(inFile, name) && std::getline(inFile, owner) &&
            std::getline(inFile, phone) && std::getline(inFile, address) &&
            std::getline(inFile, activity)) {
            firms.emplace_back(name, owner, phone, address, activity);
        }
    }

    template <typename Predicate>
    void search(Predicate predicate) const {
        for (const auto& firm : firms) {
            if (predicate(firm)) {
                firm.display();
            }
        }
    }
};

// Меню
void menu() {
    Directory directory;

    while (true) {
        std::cout << "\nDirectory Menu:\n";
        std::cout << "1. Add Firm\n";
        std::cout << "2. Search by Name\n";
        std::cout << "3. Search by Owner\n";
        std::cout << "4. Search by Phone\n";
        std::cout << "5. Search by Activity\n";
        std::cout << "6. Display All Firms\n";
        std::cout << "7. Exit\n";
        std::cout << "Select an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 7) break;

        std::string input;
        switch (choice) {
        case 1: {
            std::string name, owner, phone, address, activity;
            std::cout << "Enter Name: ";
            std::getline(std::cin, name);
            std::cout << "Enter Owner: ";
            std::getline(std::cin, owner);
            std::cout << "Enter Phone: ";
            std::getline(std::cin, phone);
            std::cout << "Enter Address: ";
            std::getline(std::cin, address);
            std::cout << "Enter Activity: ";
            std::getline(std::cin, activity);
            directory.addFirm(Firm(name, owner, phone, address, activity));
            break;
        }
        case 2:
            std::cout << "Enter Name: ";
            std::getline(std::cin, input);
            directory.searchByName(input);
            break;
        case 3:
            std::cout << "Enter Owner: ";
            std::getline(std::cin, input);
            directory.searchByOwner(input);
            break;
        case 4:
            std::cout << "Enter Phone: ";
            std::getline(std::cin, input);
            directory.searchByPhone(input);
            break;
        case 5:
            std::cout << "Enter Activity: ";
            std::getline(std::cin, input);
            directory.searchByActivity(input);
            break;
        case 6:
            directory.displayAll();
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
