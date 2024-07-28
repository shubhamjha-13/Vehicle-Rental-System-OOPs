#include <bits/stdc++.h>
using namespace std;
class Vehicle
{
private:
    int ID_num;
    string type;
    string brand;
    string model;
    int price;
    bool rented;
    int quantity;
    int availableQuantity;

public:
    // CONSRUCTOR
    Vehicle() = default;
    Vehicle(int id, string type, string brand, string model, int cost, bool isrented, int quantity, int availableQuantity)
    {
        this->ID_num = id;
        this->type = type;
        this->brand = brand;
        this->model = model;
        this->price = cost;
        this->rented = isrented;
        this->quantity = quantity;
        this->availableQuantity = availableQuantity;
    }
    // GETTER-----------
    int getId()
    {
        return this->ID_num;
    }
    string gettype()
    {
        return this->type;
    }
    string getbrand()
    {
        return this->brand;
    }
    string getmodel()
    {
        return this->model;
    }
    int getprice()
    {
        return this->price;
    }
    bool isrented()
    {
        return this->rented;
    }
    int getquantity()
    {
        return this->quantity;
    }
    int getavailableQuantity()
    {
        return this->availableQuantity;
    }
    // member func
    void rent()
    {
        rented = true;
        availableQuantity--;
    }
    void returnVehicle()
    {
        rented = false;
        availableQuantity++;
    }
    void displayDetails() const
    {
        cout << "ID: " << ID_num << "\tType: " << type << "\tBrand: " << brand << "\tModel: " << model << "\tPrice: " << price << "\tStatus: " << (availableQuantity > 0 ? "Available" : "Not Available") << "\tAvailable Quantity: " << availableQuantity << endl;
    }
};
void updateFile(vector<Vehicle> veh)
{
    fstream myFile;
    myFile.open("VehicleDetails.txt", ios::out);
    myFile.close();
    myFile.open("VehicleDetails.txt", ios::app);
    for (size_t i = 0; i < veh.size(); i++)
    {
        myFile << veh[i].getId() << ',' << veh[i].gettype() << ',' << veh[i].getbrand() << ',' << veh[i].getmodel() << ',' << veh[i].getprice() << ',' << veh[i].isrented() << ',' << veh[i].getquantity() << ',' << veh[i].getavailableQuantity() << '\n';
    }
}
class RentalSystem
{
private:
    vector<Vehicle> veh;

public:
    RentalSystem()
    {
        fstream myFile;
        myFile.open("VehicleDetails.txt", ios::in);
        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                vector<string> d;
                stringstream ss(line);
                string detail;
                while (getline(ss, detail, ','))
                {
                    d.push_back(detail);
                }
                int ID_num = stoi(d[0]);
                string type = d[1];
                string brand = d[2];
                string model = d[3];
                int price = stoi(d[4]);
                bool rented = (d[5] == "true") ? true : false;
                int quantity = stoi(d[6]);
                int availableQuantity = stoi(d[7]);
                veh.push_back(Vehicle(ID_num, type, brand, model, price, rented, quantity, availableQuantity));
            }
        }
        myFile.close();
    }
    void addVehicle(Vehicle &vehicle)
    {
        veh.push_back(vehicle);
    }

    void displayAllVehicles()
    {
        cout << "All Vehicles :" << endl;
        for (auto &vehicle : veh)
        {
            vehicle.displayDetails();
        }
    }

    void displayAvailableVehicles()
    {
        cout << "Available Vehicles :" << endl;
        for (auto &vehicle : veh)
        {
            if (vehicle.getavailableQuantity() > 0)
            {
                vehicle.displayDetails();
            }
        }
    }

    void rentVehicle(int id)
    {
        for (auto &vehicle : veh)
        {
            if (vehicle.getId() == id && vehicle.getavailableQuantity() > 0)
            {
                vehicle.rent();
                cout << "Vehicle with ID - " << id << " has been rented." << endl;
                updateFile(veh);
                return;
            }
        }
        cout << "Vehicle with ID - " << id << " is not available" << endl;
    }

    void returnVehicle(int id)
    {
        for (auto &vehicle : veh)
        {
            if (vehicle.getId() == id && vehicle.getavailableQuantity() < vehicle.getquantity())
            {
                vehicle.returnVehicle();
                cout << "Vehicle with ID " << id << " has been returned." << endl;
                updateFile(veh);
                return;
            }
        }
        cout << "Invalid vehicle ID or vehicle is not rented." << endl;
    }
};

int main()
{
    cout << "\t\t\t\t\t\t\t\t\tWELCOME" << endl;
    RentalSystem rentalSystem;
    // MENU
    int choice;
    do
    {
        cout << "\nMenu:" << endl;
        cout << "1. Display all vehicles" << endl;
        cout << "2. Display available vehicles" << endl;
        cout << "3. Rent a vehicle" << endl;
        cout << "4. Return a vehicle" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            rentalSystem.displayAllVehicles();
            break;
        case 2:
            rentalSystem.displayAvailableVehicles();
            break;
        case 3:
            int rentId;
            cout << "Enter the ID of the vehicle you want to rent: ";
            cin >> rentId;
            rentalSystem.rentVehicle(rentId);
            break;
        case 4:
            int returnId;
            cout << "Enter the ID of the vehicle you want to return: ";
            cin >> returnId;
            rentalSystem.returnVehicle(returnId);
            break;
        case 5:
            cout << "\t\t\t\t\t\t\t\t\tExiting program.\n\t\t\t\t\t\t\t\t\tTHANK YOU" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}