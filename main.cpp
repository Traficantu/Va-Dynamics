// Author: @Alexandru Mihaila
// Data: 09/07/2021

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include<string>

using namespace std;

class address{
    private:
    string iStreet;
    string iTown;
    string iCountry;

    public: address(string street, string town, string country)
    {
        iStreet = street;
        iTown = town;
        iCountry = country;
    }


    string getaddress(){
        return  iStreet + ", " + iTown + ", " + iCountry;
    }

        void setStreet(string street)
        {
            street = street;
        }

        void setTown (string town)
        {
            town = town;
        }

        void setCountry (string country)
        {
            country = country;
        }

};


class individual{
    public:
    string iFirstName;
    string iSurname;
    string iEmail;
    string iPhoneNumber;
    vector<address> individualAddresses;
    int value;


    individual(string name,string surname, string email, string phone)
    {
        iFirstName = name;
        iSurname = surname;
        iEmail = email;
        iPhoneNumber = phone;
        value = 0;
    }

    individual(int i)
    {
        value = i;

    }

    void addAddress(address add)
    {
        individualAddresses.push_back(add);
    }



};


class addressBook{

        private:
        addressBook() {};
        static addressBook instance;

        public:
        vector<individual> individuals;
        static addressBook getInstance()
        {
            return instance;
        };

        void addIndividual(individual ind)
        {
            individuals.push_back(ind);
        }

        void deleteIndividual(string name,string surname)
        {
            for(int i =0; i < individuals.size(); i++)
            {
                if(individuals[i].iFirstName == name && individuals[i].iSurname == surname)
                {
                    individuals.erase(individuals.begin() + i);
                }
            }

        }

        individual searchBook(string info)
        {
            int counter = 0;
            individual invaliduser(-1);


            for(int i =0; i < individuals.size(); i++)
            {
                if(individuals[i].iFirstName == info || individuals[i].iSurname == info || individuals[i].iEmail == info || individuals[i].iPhoneNumber == info)
                {
                    return individuals[i];
                    counter++;
                }
            }
            if(counter == 0 )
                {


                    return invaliduser;
                }

        }

        string getIndividualDetails(individual ind)
        {
           return ind.iFirstName + " " + ind.iSurname + " " + ind.iEmail+ " " + ind.iPhoneNumber + " ";

        }


};

    addressBook addressBook::instance;

    string transformLower(string my_str)
    {
        transform(my_str.begin(), my_str.end(), my_str.begin(), ::tolower);

        return my_str;
    }

    void save(addressBook book)
    {

        std::ofstream output("addressbook.txt");
            output << book.individuals.size() << endl;
        for(int i = 0; i < book.individuals.size(); i++)
        {
            individual person = book.individuals[i];
            output << book.getIndividualDetails(person) << endl;
            output << person.individualAddresses[0].getaddress() << endl;

        }

    }

    addressBook load(addressBook book)
    {
        string firstName,surname,email,phoneNumber,street,town,country;
        int numbers,counter=0;
        std::ifstream input("addressbook.txt");

        input >> numbers;

        while(counter < numbers)
        {
            input >> firstName >> surname >> email >> phoneNumber >> street >> town >> country;

            individual person(firstName,surname,email,phoneNumber);
            address add(street,town,country);

            person.addAddress(add);
            book.addIndividual(person);

            individual person2 = book.searchBook(firstName);
            address person2Address = person2.individualAddresses[0];


            firstName = "", surname = "", email = "", phoneNumber = "", street = "", town = "", country = "";
            counter++;
        }
        return book;
    }


int main()
{
    std::string input;
    bool exit = false;
    string commands= "\n help - see the help commands\n exit - exit the program and save the current contacts\n delete - removes a person from the address book\n add - adds a new person to the address book\n search - searches the\
 address book for a person with the given parameters(first name, surname, phone number, email)";

    addressBook book = addressBook::getInstance();

    book = load(book);
    cout << "Hello, you currently have ";
    cout << book.individuals.size();
    cout << " contacts Please use help to see the commands\n" << endl;

    while(!exit)
    {


        std::getline(std::cin, input);
        input = transformLower(input);

        if(input.find("help") != std::string::npos)
        {
            cout << commands << endl;
        }
        else if(input.find("add") != std::string::npos)
        {
            string firstName = "",surname = "",email = "",street = "",town = "",country = "",phoneNumber= "";

            while(firstName.empty())
            {
                cout << "Please input the person's First name:" << endl;
                std::getline(std::cin, firstName);
            }

            while(surname.empty())
            {
                cout << "Please input the person's surname:" << endl;
                std::getline(std::cin, surname);
            }
            while(email.empty())
            {
                cout << "Please input the person's email:" << endl;
                std::getline(std::cin, email);
            }
            while(phoneNumber.length() < 11)
            {
                cout << "Please input the person's phone number(minimum 11 characters):" << endl;
                cin >> phoneNumber;
            }
            while(street.empty())
            {
                cout << "Please input the person's street name:" << endl;
                cin >> street;
            }
            while(town.empty())
            {
                cout << "Please input the person's town:" << endl;
                cin >> town;
            }
            while(country.empty())
            {
                cout << "Please input the person's country:" << endl;
                cin >> country;
            }

            individual person(firstName,surname,email,phoneNumber);
            address add(street,town,country);

            person.addAddress(add);
            book.addIndividual(person);

            individual person2 = book.searchBook(firstName);
            address person2Address = person2.individualAddresses[0];
            cout << "added, " + book.getIndividualDetails(person2) + " sucessfully."<< endl;
            cout << "address:  " + person2Address.getaddress() +  " sucessfully."<< endl;
            save(book);


        }
        else if(input.find("delete") != std::string::npos)
        {
            string fName;
            string sName;

            while(fName.empty())
            {
                cout << "please enter the first name of the person you want to delete" << endl;
                cin >> fName;
            }
            while(sName.empty())
            {
                cout << "please enter the surname name of the person you want to delete" << endl;
                cin >> sName;
            }

            individual p = book.searchBook(fName);
            if(p.value < 0)
            {
                cout << "The person specified does not exist in your contacts!" << endl;
            }
            else{

            int i = book.individuals.size();
            book.deleteIndividual(fName,sName);
            int k = book.individuals.size();

            if(k < i)
            cout << "successfully deleted individual" << endl;

            }

        }
        else if(input.find("search") != std::string::npos)
        {
            string info;

            while(info.empty())
            {
                cout << "please enter a search variable (phone number, email, firstname or surname)" << endl;
                cin >> info;

            }

            individual person = book.searchBook(info);
            if(person.value > -1)
            {
                cout <<"found a match:" << endl;
                cout << "with info: " + book.getIndividualDetails(person) << endl;
                cout << "with addres: " + person.individualAddresses[0].getaddress() << endl;
            } else
                {
                    cout << "no matches found" << endl;
                }
        }
        else if(input.find("exit") != std::string::npos)
        {
            exit = true;
            save(book);
            cout <<"exited and saved addressbook successfully" << endl;
        }
    }



    return 0;
}



