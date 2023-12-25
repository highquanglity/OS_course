/**
 * @author Nghiem Van Quang
 * '''g++ main.cpp -o main
    ./main'''
 * @github https://github.com/highquanglity/OS_course/tree/main/Week9
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

// Information of each contact
struct Contact
{
    std::string name;
    std::string phone;
};

// Write Phonebook to Binary File
void Wrtie2BinFile(const std::vector<Contact>& contacts, const std::string& filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Cannot open file " << filename << " to write" << std::endl;
        return;
    }

    // Write number of contacts to file
    int numContacts = contacts.size();
    file.write(reinterpret_cast<char*>(&numContacts), sizeof(int));

    // Write contacts to file
    for (const auto& contact : contacts)
    {
        int nameSize = contact.name.size();
        file.write(reinterpret_cast<char*>(&nameSize), sizeof(int));
        file.write(contact.name.c_str(), nameSize);

        int phoneSize = contact.phone.size();
        file.write(reinterpret_cast<char*>(&phoneSize), sizeof(int));
        file.write(contact.phone.c_str(), phoneSize);
    }

    file.close();
}

// Find contact with name in phonebook
void FindContact(const std::string& name, const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Can't open file " << filename << " to read" << std::endl;
        return;
    }

    // Read number of contacts from file
    int numContacts;
    file.read(reinterpret_cast<char*>(&numContacts), sizeof(int));

    // Find contact with name
    bool found = false;
    for (int i = 0; i < numContacts; i++)
    {
        int nameSize;
        file.read(reinterpret_cast<char*>(&nameSize), sizeof(int));
        std::string contactName(nameSize, '\0');
        file.read(&contactName[0], nameSize);

        int phoneSize;
        file.read(reinterpret_cast<char*>(&phoneSize), sizeof(int));
        std::string contactPhone(phoneSize, '\0');
        file.read(&contactPhone[0], phoneSize);

        if (contactName == name)
        {
            std::cout << "Contact with name " << contactName << " exists in ContactPhoneBook" << std::endl;
            std::cout << "Name: " << contactName << "\nPhone number: " << contactPhone << std::endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        std::cout << "Can't find Contact with given name " << name << " in ContactPhoneBook!" << std::endl;
    }

    file.close();
}

int main()
{
    std::vector<Contact> contacts;

    // Get Contact information from PhoneBook
    contacts.push_back({"Nghiem Van Quang", "0395646128"});
    contacts.push_back({"Nguyen Tuan Anh", "0123456788"});
    contacts.push_back({"Nguyen Pham Trung HIeu", "0123456787"});
    contacts.push_back({"Ha Dinh Dat", "0123456790"});

    // Write PhoneBook file
    Wrtie2BinFile(contacts, "ContactPhoneBook.bin");
    // Find Contact with name and print phone number
    FindContact("Nghiem Van Quang", "ContactPhoneBook.bin");
    std::cout<<"================================================="<<std::endl;
    // Find Contact not exist in PhoneBook
    FindContact("Nghiem Van Qang", "ContactPhoneBook.bin");

    return 0;
}
