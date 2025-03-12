#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class shopping
{
private:
    int productcode;
    float price;
    float discount;
    string productname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void removee();
    void list();
    void receipt();
};

void shopping::menu()
{
    int choice;
    string email;
    string password;

    cout << " _______________________________" << endl;
    cout << "|                               |" << endl;
    cout << "|     Supermarket Main Menu     |" << endl;
    cout << "|_______________________________|" << endl;
    cout << "                                " << endl;
    cout << "*    [1] Administrator          *" << endl;
    cout << "*                               *" << endl;
    cout << "*    [2] Cart                   *" << endl;
    cout << "*                               *" << endl;
    cout << "*    [3] Exit                   *" << endl;
    cout << "*                               *" << endl;
    cout << "*-------------------------------*" << endl;
    cout << "    Please Select : ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
    case 1:
        cout << "Enter Login Details" << endl;
        cout << "Email : ";
        cin >> email;
        cout << "Password : ";
        cin >> password;

        if (email == "paritosh@gmail.com" && password == "paritosh")
        {
            administrator();
        }
        else
        {
            cout << "Invalid Email/Password" << endl;
        }
        break;

    case 2:
        buyer();
        break;

    case 3:
        cout << "---------------------------------" << endl;
        cout << "\n............Thank You............" << endl;
        exit(0);

    default:
        cout << "Select From Given Options" << endl;
    }

    menu(); // Loop back to the menu
}

void shopping::administrator()
{
    int choice;
    cout << "\n Administer Menu" << endl;
    cout << "--------------------------" << endl;
    cout << "[1] Add new product    " << endl;
    cout << "[2] Modify product     " << endl;
    cout << "[3] Delete product     " << endl;
    cout << "[4] Back to Main Menu  " << endl;
    cout << " Enter the Choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        edit();
        break;

    case 3:
        removee();
        break;

    case 4:
        menu();
        break;

    default:
        cout << "Invalid..!!...Select From Given Options" << endl;
    }

    administrator();
}

void shopping::buyer()
{
    int choice;
    cout << "\n Buyer" << endl;
    cout << "--------------------------" << endl;
    cout << "[1] Buy the Product    " << endl;
    cout << "[2] Back to Main Menu  " << endl;
    cout << "Enter the Choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();
        break;

    default:
        cout << "Select From Given Options" << endl;
    }

    buyer();
}

void shopping::add()
{
    fstream data;
    int userProductCode;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n Add New Product" << endl;
    cout << "--------------------------" << endl;

    cout << "Enter Product Code: ";
    cin >> userProductCode;

    data.open("database.txt", ios::in);

    if (!data)
    {
        data.open("database.txt", ios::app | ios::out);
        data << userProductCode << " " << productname << " " << price << " " << discount << endl;
        data.close();
    }
    else
    {
        data >> productcode >> n >> p >> d;

        while (!data.eof())
        {
            if (userProductCode == productcode)
            {
                token++;
            }
            data >> productcode >> n >> p >> d;
        }

        data.close();

        if (token == 1)
        {
            cout << "Duplicate Product Code. Please try again..." << endl;
            return;
        }
        else
        {
            data.open("database.txt", ios::app | ios::out);

            cout << "Enter Product Name: ";
            cin >> productname;
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Discount: ";
            cin >> discount;

            data << userProductCode << " " << productname << " " << price << " " << discount << endl;
            data.close();
        }
    }
    cout << "Record Inserted Successfully" << endl;
}

void shopping::edit()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << " Modify the Record" << endl;
    cout << "--------------------------" << endl;
    cout << "Product code : ";
    cin >> pkey;

    data.open("database.txt", ios::in);

    if (!data)
    {
        cout << "File Doesn't Found" << endl;
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);

        data >> c >> n >> p >> d;

        while (!data.eof())
        {
            if (pkey == c)
            {
                cout << "Product Name : ";
                cin >> n;
                cout << "Price : ";
                cin >> p;
                cout << "Discount : ";
                cin >> d;
                data1 << pkey << " " << n << " " << p << " " << d << endl;
                cout << "Record Updated" << endl;
                token++;
            }
            else
            {
                data1 << c << " " << n << " " << p << " " << d << endl;
            }
            data >> c >> n >> p >> d;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");
    }

    if (token == 0)
    {
        cout << "Record Not Found" << endl;
    }
}

void shopping::removee()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "Delete the Product" << endl;
    cout << "--------------------------" << endl;
    cout << "Product Code : ";
    cin >> pkey;
    data.open("database.txt", ios::in);
    data1.open("database1.txt", ios::app | ios::out);

    if (!data)
    {
        cout << "File Not Found" << endl;
    }
    else
    {
        while (data >> productcode >> productname >> price >> discount)
        {
            if (productcode == pkey)
            {
                cout << "Product Deleted Successfully";
                token++;
            }
            else
            {
                data1 << productcode << " " << productname << " " << price << " " << discount << endl;
            }
        }

        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");
    }

    if (token == 0)
    {
        cout << "Record Not Found" << endl;
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "Product List" << endl;
    cout << "--------------------------" << endl;
    cout << "Product no. \tName \t\tPrice \t\tDiscount" << endl;
    while (data >> productcode >> productname >> price >> discount)
    {
        cout << productcode << "\t\t" << productname << "\t\t" << price << "\t\t" << discount << endl;
    }
    data.close();
}

void shopping::receipt()
{
    fstream data;
    int arrayofcode[100];
    int arrayofquantity[100];
    int counter = 0;
    float total = 0;

    cout << "RECEIPT" << endl;
    cout << "--------------------------" << endl;
    data.open("database.txt", ios::in);

    if (!data)
    {
        cout << "| Empty Cart...Add something |" << endl;
        cout << "|From Administer menu        |" << endl;
    }
    else
    {
        data.close();

        list();
        cout << "--------------------------" << endl;
        cout << "*   Place the Order      *" << endl;
        cout << "--------------------------" << endl;

        do
        {
        m:
            cout << "Enter Product Code : ";
            cin >> arrayofcode[counter];
            cout << "Enter Product Quantity : ";
            cin >> arrayofquantity[counter];
            for (int i = 0; i < counter; i++)
            {
                if (arrayofcode[counter] == arrayofcode[i])
                {
                    cout << "Duplicate Product Code. Please try again..." << endl;
                    goto m;
                }
            }
            counter++;
            cout << "Do you want to buy another product ? (y/n) : ";
            char choice;
            cin >> choice;
            cout << endl;
            if (choice == 'n')
            {
                break;
            }
        } while (counter < 100);

        cout << "------------------------RECEIPT-----------------------" << endl;
        cout << "Product Code \tQuantity \tPrice \t\tAmount" << endl;

        data.open("database.txt", ios::in);

        for (int i = 0; i < counter; i++)
        {
            bool found = false;
            data.clear(); // Clear the EOF flag
            data.seekg(0, ios::beg);

            while (data >> productcode >> productname >> price >> discount)
            {
                if (productcode == arrayofcode[i])
                {
                    float amount = price * arrayofquantity[i];
                    total += amount;
                    cout << productcode << "\t\t" << arrayofquantity[i] << "\t\t" << price << "\t\t" << amount << endl;
                    found = true;
                    break; // Break the loop after finding the product
                }
            }

            if (!found)
            {
                cout << arrayofcode[i] << "\t\tProduct not found" << endl;
            }
        }
    }

    cout << "--------------------------" << endl;
    cout << "Total Amount : " << total << endl;

    data.close();
}

int main()
{
    shopping s;
    s.menu();
    return 0;
}
