#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a customer
struct Customer {
    int roomNumber;
    string name;
    string address;
    double totalBill;
};

// Function prototypes
void displayMenu();
void bookRoom(vector<Customer>& customers);
void searchCustomer(const vector<Customer>& customers);
void viewAllottedRooms(const vector<Customer>& customers);
void modifyRecord(vector<Customer>& customers);
void deleteRecord(vector<Customer>& customers);
void displayTotalBill(const vector<Customer>& customers);

// Function to save customer data to a file
void saveDataToFile(const vector<Customer>& customers, const string& filename);

// Function to load customer data from a file
void loadDataFromFile(vector<Customer>& customers, const string& filename);

int main() {
    vector<Customer> customers;
    const string filename = "customer_data.txt";

    // Load data from the file at the beginning
    loadDataFromFile(customers, filename);

    char choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                bookRoom(customers);
                break;
            case '2':
                searchCustomer(customers);
                break;
            case '3':
                viewAllottedRooms(customers);
                break;
            case '4':
                modifyRecord(customers);
                break;
            case '5':
                deleteRecord(customers);
                break;
            case '6':
                displayTotalBill(customers);
                break;
            case '7':
                // Save data to the file before exiting
                saveDataToFile(customers, filename);
                cout << "Exiting the program. Data saved to " << filename << ".\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '7');

    return 0;
}

void displayMenu() {
    cout << "\nHotel Management System Menu\n";
    cout << "1. Book a room\n";
    cout << "2. Search for customer details\n";
    cout << "3. View total number of allotted rooms\n";
    cout << "4. Modify a record\n";
    cout << "5. Delete a record\n";
    cout << "6. Display total bill of a customer\n";
    cout << "7. Exit\n";
}

void bookRoom(vector<Customer>& customers) {
    Customer newCustomer;
    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, newCustomer.name);
    cout << "Enter customer address: ";
    getline(cin, newCustomer.address);
    cout << "Enter room number: ";
    cin >> newCustomer.roomNumber;
    cout << "Enter total bill: ";
    cin >> newCustomer.totalBill;

    customers.push_back(newCustomer);
    cout << "Room booked successfully!\n";
}

void searchCustomer(const vector<Customer>& customers) {
    int roomNumber;
    cout << "Enter room number to search: ";
    cin >> roomNumber;

    bool found = false;
    for (const auto& customer : customers) {
        if (customer.roomNumber == roomNumber) {
            cout << "Customer Details:\n";
            cout << "Name: " << customer.name << "\n";
            cout << "Address: " << customer.address << "\n";
            cout << "Room Number: " << customer.roomNumber << "\n";
            cout << "Total Bill: " << customer.totalBill << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Customer not found for room number " << roomNumber << ".\n";
    }
}

void viewAllottedRooms(const vector<Customer>& customers) {
    cout << "Total number of allotted rooms: " << customers.size() << "\n";
}

void modifyRecord(vector<Customer>& customers) {
    int roomNumber;
    cout << "Enter room number to modify: ";
    cin >> roomNumber;

    for (auto& customer : customers) {
        if (customer.roomNumber == roomNumber) {
            cout << "Enter new customer name: ";
            cin.ignore();
            getline(cin, customer.name);
            cout << "Enter new customer address: ";
            getline(cin, customer.address);
            cout << "Enter new total bill: ";
            cin >> customer.totalBill;
            cout << "Record modified successfully!\n";
            return;
        }
    }

    cout << "Customer not found for room number " << roomNumber << ".\n";
}

void deleteRecord(vector<Customer>& customers) {
    int roomNumber;
    cout << "Enter room number to delete: ";
    cin >> roomNumber;

    auto it = remove_if(customers.begin(), customers.end(),
                        [roomNumber](const Customer& customer) {
                            return customer.roomNumber == roomNumber;
                        });

    if (it != customers.end()) {
        customers.erase(it, customers.end());
        cout << "Record deleted successfully!\n";
    } else {
        cout << "Customer not found for room number " << roomNumber << ".\n";
    }
}

void displayTotalBill(const vector<Customer>& customers) {
    int roomNumber;
    cout << "Enter room number to display total bill: ";
    cin >> roomNumber;

    for (const auto& customer : customers) {
        if (customer.roomNumber == roomNumber) {
            cout << "Total bill for room number " << roomNumber << ": " << customer.totalBill << "\n";
            return;
        }
    }

    cout << "Customer not found for room number " << roomNumber << ".\n";
}

void saveDataToFile(const vector<Customer>& customers, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& customer : customers) {
            file << customer.roomNumber << " " << customer.name << " " << customer.address << " " << customer.totalBill << "\n";
        }
        file.close();
    } else {
        cerr << "Unable to open file " << filename << " for writing.\n";
    }
}

void loadDataFromFile(vector<Customer>& customers, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        Customer customer;
        while (file >> customer.roomNumber >> customer.name >> customer.address >> customer.totalBill) {
            customers.push_back(customer);
        }
        file.close();
    } else {
        cerr << "Unable to open file " << filename << " for reading.\n";
    }
}
