#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

using namespace std;
void returnRentedCar();
void addNewCarModel();
void displayCustomerList();
void showrent(const string &carModel, int daysToRent, int rentalfee);

class Admin
{
public:
    void adminLogin()
    {
        string password;
        cout << "Enter the admin password: ";

        // Hide password input by displaying ****
        char ch;
        while ((ch = _getch()) != '\r')
        { // '\r' is the enter key
            if (ch == '\b')
            { // '\b' is the backspace key
                if (!password.empty())
                {
                    cout << "\b \b";
                    password.pop_back();
                }
            }
            else
            {
                cout << '*';
                password += ch;
            }
        }

        if (password == "admin")
        {
            cout << "\nAccess granted. Welcome, Admin!\n";
            adminMenu();
        }
        else
        {
            cout << "Incorrect password. Access denied.\n";
            // Redirect user to the main function
            return;
        }
    }
    void adminMenu()
    {
        sleep(1);
        system("CLS");
        char choice;
        do
        {
            cout << "\n\n";
            cout << "Admin Menu:\n";
            cout << "1. Display Customer List\n";
            cout << "2. Add New Car Model\n";
            cout << "3. Display Car List\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case '1':
                sleep(1);
                system("CLS");
                displayCustomerList();
                break;
            case '2':
                sleep(1);
                system("CLS");
                addNewCarModel();
                break;
            case '3':
                sleep(1);
                system("CLS");
                displayCarList(); // Call the function to display the car list
                break;
            case '4':
                cout << "Exiting Admin Menu...\n";
                sleep(1);
                system("CLS");
                return;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        } while (choice != '4');
    }
    void displayCarList()
    {
        cout << "=== Car List ===\n";

        ifstream carFile("Cars.txt");
        if (carFile)
        {
            string line;
            while (getline(carFile, line))
            {
                cout << line << endl;
            }
            carFile.close();
        }
        else
        {
            cout << "Unable to open Cars.txt file.\n";
        }
    }
};

class customer
{
public:
    string customername;
    string customeraddress;
    string adhaarnumber;
    string mobileno;
    string createpassword;

    bool customerlogin()
    {
        string username, password;
        cout << "\n\n";
        cout << "=== Customer Login ===\n";
        cout << "Enter your Customer Name: ";
        cin >> username;
        cout << "Enter your Password: ";
        cin >> password;

        ifstream inFile("customers.txt");
        bool loggedIn = false;
        if (inFile)
        {
            string line;
            while (getline(inFile, line))
            {
                if (line.find("Customer Name: " + username) != string::npos)
                {
                    getline(inFile, line); // Read the Customer Address line
                    getline(inFile, line); // Read the Aadhaar Number line
                    getline(inFile, line); // Read the Mobile Number line
                    getline(inFile, line); // Read the Create Password line

                    string savedPassword = line.substr(line.find(": ") + 2);
                    if (password == savedPassword)
                    {
                        loggedIn = true;
                        break;
                    }
                }
            }
            inFile.close();
        }
        else
        {
            cout << "Unable to open customers.txt file for reading.\n";
        }

        return loggedIn;
    }
    void signUp()
    {
        cout << "=== Customer Signup ===\n";
        cout << "Please provide the following information:\n";

        cout << "Customer Name: ";
        cin >> customername;

        cout << "Customer Address: ";
        cin.ignore();
        getline(cin, customeraddress);

        cout << "Aadhaar Number: ";
        cin >> adhaarnumber;

        cout << "Mobile Number: ";
        cin >> mobileno;

        cout << "Create Password: ";
        cin >> createpassword;

        ofstream outFile("customers.txt", ios::app);
        if (outFile)
        {
            outFile << "Customer Name: " << customername << endl;
            outFile << "Customer Address: " << customeraddress << endl;
            outFile << "Aadhaar Number: " << adhaarnumber << endl;
            outFile << "Mobile Number: " << mobileno << endl;
            outFile << "Create Password: " << createpassword << endl;
            outFile << "\n\n";
            outFile << "============================================\n";
            outFile << "\n\n";

            cout << "Signup successful. Customer details saved.\n";
            outFile.close();
        }
        else
        {
            cout << "Unable to open customers.txt file for writing.\n";
        }
    }

    void displayCustomerMenu()
    {
        int choice;
        do
        {
            cout << "\n\n";
            cout << "=== Customer Menu ===\n";
            cout << "1. Book a new car\n";
            cout << "2. Return a rented car\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                sleep(1);
                system("CLS");
                bookNewCar();
                break;
            case 2:
                sleep(1);
                system("CLS");
                returnRentedCar();
                break;
            case 3:
                // cout << "Thank you for using our car rental system. Goodbye!\n";
                sleep(1);
                system("CLS");
                return;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        } while (choice != 3);
    }

    void bookNewCar()
    {
        cout << "=== Book a New Car ===\n";

        // Display the car options from car.txt
        ifstream carFile("Cars.txt");
        if (carFile)
        {
            string line;
            while (getline(carFile, line))
            {
                cout << line << endl;
            }
            carFile.close();

            string selectedCarModel;
            cout << "Enter the car model: ";
            cin >> selectedCarModel;

            // Take input for km to travel and number of days to rent
            int kmToTravel, daysToRent;
            cout << "Enter the kilometers to travel: ";
            cin >> kmToTravel;
            cout << "Enter the number of days to rent: ";
            cin >> daysToRent;

            // Calculate the rental fee based on selectedCarModel, kmToTravel, and daysToRent
            int rentalfee = daysToRent * 100;

            // Call the showrent() function to display the rental invoice
            showrent(selectedCarModel, daysToRent, rentalfee);
        }
        else
        {
            cout << "Unable to open Cars.txt file.\n";
        }
    }
};

void showrent(const string &carModel, int daysToRent, int rentalfee)
{
    cout << "\n                       Car Rental - Customer Invoice                  " << endl;
    cout << "    /////////////////////////////////////////////////////////" << endl;
    cout << "    | Invoice No. :"
         << "------------------|" << setw(10) << "#Cnb81353"
         << " |" << endl;
    cout << "    | Car Model :"
         << "--------------------|" << setw(10) << carModel << " |" << endl;
    cout << "    | Number of days :"
         << "---------------|" << setw(10) << daysToRent << " |" << endl;
    cout << "    | Your Rental Amount is :"
         << "--------|" << setw(10) << rentalfee << " |" << endl;
    cout << "    | Caution Money :"
         << "----------------|" << setw(10) << "0"
         << " |" << endl;
    cout << "    | Advanced :"
         << "---------------------|" << setw(10) << "0"
         << " |" << endl;
    cout << "     ________________________________________________________" << endl;
    cout << "\n";
    cout << "    | Total Rental Amount is :"
         << "-------|" << setw(10) << rentalfee << " |" << endl;
    cout << "     ________________________________________________________" << endl;
    cout << "     # This is a computer generated invoice and it does not" << endl;
    cout << "     require an authorised signature #" << endl;
    cout << " " << endl;
    cout << "    /////////////////////////////////////////////////////////" << endl;
    cout << "    You are advised to pay up the amount before the due date." << endl;
    cout << "    Otherwise, a penalty fee will be applied." << endl;
    cout << "    /////////////////////////////////////////////////////////" << endl;

    system("PAUSE");

    system("CLS");
}

class welcome
{
public:
    void welcum()
    {
        system("PAUSE");
        system("CLS");
        ifstream inArt("carArt.txt");

        if (!inArt)
        {
            cout << "Cannot open input file.\n";
        }
        char strArt[5000];
        while (inArt)
        {

            inArt.getline(strArt, 2000);
            if (inArt)
                cout << strArt << endl;
        }
        inArt.close();
        sleep(1);
        cout << "\nStarting the program please wait....." << endl;
        sleep(1);
        cout << "\nloading up files....." << endl;
        sleep(1);
        system("CLS");
    }
};

int main()
{
    welcome obj1;
    obj1.welcum();
    customer customer;
    int choice;

    do
    {
        cout << "\n\n";
        cout << "=== Main Menu ===\n";
        cout << "1. Admin Access\n";
        cout << "2. Customer Login\n";
        cout << "3. Customer Signup\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Admin menu options
            // Implement the admin menu functionality here
            cout << "Admin access selected!\n";
            Admin A;
            sleep(1);
            system("CLS");
            A.adminLogin();
            break;
        case 2:
            sleep(1);
            system("CLS");
            if (customer.customerlogin())
            {
                // Customer menu options
                // Implement the customer menu functionality here
                cout << "Customer login successful!\n";
                sleep(1);
                system("CLS");
                customer.displayCustomerMenu();
            }
            else
            {
                cout << "Invalid username or password entered.\n";
            }
            break;
        case 3:
            sleep(1);
            system("CLS");
            customer.signUp();
            break;
        case 4:
            cout << "Exiting the program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

        cout << endl;
    } while (choice != 4);

    ifstream inf("thanks.txt");
    if (inf)
    {
        string line;
        while (getline(inf, line))
        {
            cout << line << endl;
        }
        inf.close();
        sleep(2);
    }
    else
    {
        cout << "Unable to open thanks.txt file.\n";
    }

    return 0;
}

void addNewCarModel()
{
    ofstream outFile("Cars.txt", ios::app);
    if (!outFile)
    {
        cout << "Error opening file.\n";
        return;
    }

    cout << "Enter the details of the new car model:\n";
    string carModel, carNumber, carColor, fuelType, gearType;
    int trunkSpace, mileage, kmsTravelled, rating = 0;

    cout << "Car Model: ";
    cin >> carModel;
    cout << "Car Number: ";
    cin >> carNumber;
    cout << "Car Color: ";
    cin >> carColor;
    cout << "Fuel Type: ";
    cin >> fuelType;
    cout << "Trunk Space (in liters): ";
    cin >> trunkSpace;
    cout << "Mileage: ";
    cin >> mileage;
    cout << "Gear Type (Automatic/Manual): ";
    cin >> gearType;

    outFile << "Car Model: " << carModel << endl;
    outFile << "Car Number: " << carNumber << endl;
    outFile << "Car Color: " << carColor << endl;
    outFile << "Fuel Type: " << fuelType << endl;
    outFile << "Trunk Space: " << trunkSpace << " liters" << endl;
    outFile << "Mileage: " << mileage << endl;
    outFile << "Gear Type: " << gearType << endl;
    outFile << "Kilometers Travelled: " << kmsTravelled << " km" << endl;
    outFile << "Ratings: " << rating << " star" << endl;
    outFile << "\n\n";
    outFile << "============================================\n";
    outFile << "\n\n";

    cout << "New car model added successfully!\n";
    outFile.close();
}

void displayCustomerList()
{
    ifstream inFile("customers.txt");
    if (!inFile)
    {
        cout << "No customer data found.\n";
        return;
    }

    cout << "Customer List:\n";
    cout << "------------------------\n";

    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    inFile.close();
}

void returnRentedCar()
{
    cout << "=== Return Rented Car ===\n";
    // Take ratings and kilometers travelled from the user
    string carModel;
    cout << "Please enter the Car Model of the car you are returning: ";
    cin >> carModel;
    // cout<<"Please provide the Car number of the car you are returning: ";
    // string carNumber;
    // cin>>carNumber;
    int rating;
    cout << "Please provide your ratings (out of 5 stars) for the rented car: ";
    cin >> rating;

    int kmTraveled;
    cout << "Please enter the kilometers traveled with the car: ";
    cin >> kmTraveled;

    // Update the car's details in Cars.txt
    ifstream inFile("Cars.txt");
    ofstream tempFile("temp.txt");
    if (inFile && tempFile)
    {
        string line;
        bool carFound = false;
        while (getline(inFile, line))
        {
            if (line.find("Car Model: " + carModel) != string::npos)
            {
                carFound = true;
                tempFile << line << endl;
                getline(inFile, line); // Car Number
                tempFile << line << endl;
                getline(inFile, line); // Car Color
                tempFile << line << endl;
                getline(inFile, line); // Fuel Type
                tempFile << line << endl;
                getline(inFile, line); // Trunk Space
                tempFile << line << endl;
                getline(inFile, line); // Mileage
                tempFile << line << endl;
                getline(inFile, line); // Gear Type
                tempFile << line << endl;
                // tempFile << line << endl;
                tempFile << "Kilometers Travelled: " << kmTraveled << " km\n";
                tempFile << "Ratings: " << rating << " stars\n";
                goto CloseFile;
            }
            else
            {
                tempFile << line << endl;
            }
        }
    CloseFile:
        inFile.close();
        tempFile.close();
        remove("Cars.txt");
        rename("temp.txt", "Cars.txt");

        if (carFound)
        {
            cout << "Car details updated in Cars.txt\n";
        }
        else
        {
            cout << "Car not found in Cars.txt\n";
        }
    }
    else
    {
        cout << "Unable to open Cars.txt file for updating.\n";
    }

    // Open thanks.txt file and go back to the main menu
    ifstream thanksFile("thanks.txt");
    if (thanksFile)
    {
        // thanksFile << "Thank you for returning the car!\n";
        string line;
        while (getline(inFile, line))
        {
            getline(inFile, line);
        }
        thanksFile.close();
        cout << "Thank you for returning the car!\n";
    }
    else
    {
        cout << "Unable to open thanks.txt file.\n";
    }
    return;
}
