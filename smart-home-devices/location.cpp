//This is the code to implement the location and room classes' constructors/destructor and member functions

#include "location.h"
#include "room.h"

/*LOCATION*/
//This is the constructor for the location class
//The user can provide address and name at initialization, default values are ""
location::location(const string & an_address, const string & a_name):address(an_address), name(a_name) /*, rooms(nullptr)*/
{
}

//This is the destructor for the location class
location::~location()
{
    if (!address.empty())
        address.clear();

    if (!name.empty())
        name.clear();

    rooms.remove_all();
}

//This is the display function to display the data members of the location class
//Argument: none
//Return: void
void location::display_info() const
{
    if (!name.empty())
        cout << "Location name: " << name << endl;
    
    if (!address.empty())
        cout << "Address: " << address << endl;
}

//This is the function to set/reset the address of the location
//Argument: none
//Return: int, 1 for success, 0 for failure
int location::set_address()
{
    cout << "What is the address of your location? ";
    getline(cin, address);

    return 1;
}

//This is the function to set/reset the name of the location
//Argument: none
//Return: int, 1 for success, 0 for failure
int location::set_name()
{
    cout << "What would you like to name your location? ";
    getline(cin, name);

    return 1;
}

//This function sets the class object info to "" to mimic deleting the object in the array
//Argument: none
//Return: int, 1 for success, 0 for failure
int location::set_empty()
{
    name = "";
    address = "";

    return 1;
}

//This is the function to get the location's name for the array of locations
//Argument: none
//Return: string passed by reference
string & location::get_name()
{
    return name;
}

//This function checks if there is no room at a location
//Argument: none
//Return: bool, true for empty and false for not empty
bool location::is_empty() const
{
    if (rooms.is_empty())
    {
        cout << "No rooms in " << name << "." << endl << endl;
        return true;
    }

    return false;
}

//This is the function to all rooms' info in a location
//Argument: none
//Return: int, 1 for success, 0 for failure
int location::list_rooms() const
{
    if (!is_empty())
    {
        cout << "The rooms at " << name << " are..." << endl;
        rooms.display_all();
        cout << '\n';
    }
    else
        return 0;

    return 1;
}

//This is the function to display a matching room in the LLL
//Argument: none
//Return: int, 1 for success, 0 for failure
int location::display_room() const
{
    int success {0};

    if (!is_empty())
    {
        char input_name[100]; //char array holder for user input
        
        cout << "What room would you like to display?: ";
        cin.get(input_name, 100, '\n');
        cin.ignore(100, '\n');
        cout << '\n';

        success += rooms.display_room(input_name);
    }

    return success;
}

//This is the function to add a room to the LLL in location object
//Argument: none
//Return: int, 1 for success, 0 for failure
int location::add_room()
{
    bool agree {true};
    char answer;
    int success {0};
    
    while (agree)
    {
        room new_room;
        success += new_room.set_name();
        success += rooms.insert(new_room);
        
        cout << "Would you like to add another room in this location? (y/n): ";
        cin >> answer;
        cin.ignore(100, '\n');
        if (answer != 'y' && answer != 'Y')
            agree = false;
    }
    cout << '\n';
    
    return success;
}

//This is the function to remove a room from the LLL in location object
//Argument: none
//Return: int, 1 for success, 0 for failure
int location::remove_room(/*room & a_room*/)
{
    int success {0};

    if (!is_empty())
    {
        char input_name[100]; //char array holder for user input
        
        cout << "What room would you like to remove at " << name << "?: ";
        cin.get(input_name, 100, '\n');
        cin.ignore(100, '\n');
        cout << '\n';

        success += rooms.remove(input_name);

        if (success)
            cout << "Successfully removed " << input_name << "." << endl << endl;
        else
            cout << "No match found for " << input_name << " to remove, please try again." << endl << endl;
    }

    return success;
}

//This is the function to remove all rooms from the LLL in location object
//Argument: none
//Return: int, 1 for success, 0 for failure
int location::remove_all()
{
    if (!is_empty())
    {
        rooms.remove_all();
        cout << "All rooms in " << name << " removed." << endl << endl;
        return 1;
    }
    
    return 0;
}

//This function calls the retrieve function in LLL to find a match in the room and call that room's menu
//Argument: none
//Return: int, 1 for success, 0 for failure
int location::access_room()
{
    int success {0};

    if (!is_empty())
    {
        char input_name[100]; //char array holder for user input

        cout << "What room would you like to access at " << name << "?: ";
        cin.get(input_name, 100, '\n');
        cin.ignore(100, '\n');
        cout << '\n';

        success += rooms.retrieve(input_name);

        if (!success)
            cout << "No match found for " << input_name << ", please try again." << endl << endl;
    }
    
    return success;
}

//This is the menu for the location object so user can control the rooms at the location
//Argument: none
//Return: int, 1 for success, 0 for failure
int location::menu()
{
    bool agree {true};
    char answer;
    int selected_option;
    int success;
    
    cout << "What action would you like to take in " << name << "?" << endl;
    cout << "Please select from the options below: " << endl
         << "1) Add a room" << endl
         << "2) Display a room" << endl
         << "3) List all rooms" << endl
         << "4) Remove a room" << endl
         << "5) Remove all rooms" << endl
         << "6) Retrieve and access a room and its devices" << endl
         << "7) Set location's name" << endl
         << "8) Set location's address" << endl
         << "9) Display location's info" << endl << endl;

    while (agree) 
    {
        do
        {
            cout << "Please select from the options by entering a number from 1 to 9: ";
            cin >> selected_option;
            cin.ignore(100, '\n');
            cout << '\n';

            if (selected_option < 1 || selected_option > 9)
                cout << "Please only enter a number between 1 and 9, inclusive" << endl << endl;
        } while (selected_option < 1 || selected_option > 9);

        if (1 == selected_option)
            success = add_room();
        else if (2 == selected_option)
            success = display_room();
        else if (3 == selected_option)
            success = list_rooms();
        else if (4 == selected_option)
            success = remove_room();
        else if (5 == selected_option)
            success = remove_all();
        else if (6 == selected_option)
            success = access_room();
        else if (7 == selected_option)
            success = set_name();
        else if (8 == selected_option)
            success = set_address();
        else if (9 == selected_option)
            display_info();

        cout << "Would you like to take another action in this location? (y/n): ";
        cin >> answer;
        cin.ignore(100, '\n');
        if (answer != 'y' && answer != 'Y')
            agree = false;
    }
    cout << '\n';

    return success;
}

/*ROOM*/
//This is the constructor for the room class
//The user can provide name at initialization, default value is ""
room::room(const string & a_name):name(a_name)
{
}

//This is the destructor for the room class
room::~room()
{
    if (!name.empty())
        name.clear();
}

//This is the display function to display the name of the room class
//Argument: none
//Return: void
void room::display_info() const
{
    if (!name.empty())
        cout << "Room name: " << name << endl;
}

//This is the function to set/reset the name of the room
//Argument: none
//Return: int, 1 for success, 0 for failure
int room::set_name()
{
    cout << "What would you like to name your room? ";
    getline(cin, name);

    return 1;
}

//This function checks if there is no device in the room, all vectors are empty
//Argument: none
//Return: bool, true for empty, false for not empty
bool room::is_empty() const
{
    if (cams.empty() && lights.empty() && thermostats.empty())
    {
        cout << "No devices in " << name << "." << endl << endl;
        return true;
    }

    return false;
}

//This is the function to add a new device to the device vector in the room object
//Arguments: char for the type of device to add ('s', 'l', and 't') and char * for the name of the device
//Return: int, 1 for success, and 0 for failure
int room::add_device()
{
    bool agree {true};
    char answer;
    int selected_option;

    cout << "Which device would you like to add to " << name << "?" << endl;
    cout << "Please select from the options below: " << endl
         << "1) Security camera" << endl
         << "2) Light" << endl
         << "3) Thermostat" << endl << endl;

    while (agree) 
    {
        do
        {
            cout << "Please select from the options by entering a number from 1 to 3: ";
            cin >> selected_option;
            cin.ignore(100, '\n');
            cout << '\n';

            if (selected_option < 1 || selected_option > 3)
                cout << "Please only enter a number between 1 and 3, inclusive" << endl << endl;
        } while (selected_option < 1 || selected_option > 3);

        if (1 == selected_option)
        {
            cout << "Adding a security camera to " << name << "." << endl;
            sec_cam cam;
            cam.set_name();
            cams.push_back(cam);
        }
        else if (2 == selected_option)
        {
            cout << "Adding a light to " << name << "." << endl;
            light a_light;
            a_light.set_name();
            lights.push_back(a_light);
        }
        else if (3 == selected_option)
        {
            cout << "Adding a thermostat to " << name << "." << endl;
            thermostat a_thermostat;
            a_thermostat.set_name();
            thermostats.push_back(a_thermostat);
        }

        cout << "Would you like to add another device? (y/n): ";
        cin >> answer;
        cin.ignore(100, '\n');
        if (answer != 'y' && answer != 'Y')
            agree = false;
    }

    cout << '\n';

    return 1;
}

//This function iterates over the devices vector and display the device's info
//Argument: none
//Return: void
void room::list_devices() const
{
    if (!is_empty())
    {
        cout << "The devices in " << name << " are..." << endl;
        if (!cams.empty())
        {
            cout << "Security cameras: " << endl;
            for (auto cam : cams)
                cam.display_base();
        }
        if (!lights.empty())
        {
            cout << "Lights: " << endl;
            for (auto light : lights)
                light.display_base();
        }
        if (!thermostats.empty())
        {
            cout << "Thermostats: " << endl;
            for (auto thermostat : thermostats)
                thermostat.display_base();
        }
        cout << '\n';
    }
}

//This function iterates over the devices vector to find the device and remove it
//Argument: none
//Return: int, 1 for success, 0 for failure
int room::remove_device(/*char * device_name*/)
{
    if (!is_empty())
    {
        char input_name[100]; //char array holder for user input
        
        cout << "What device would you like to remove?: ";
        cin.get(input_name, 100, '\n');
        cin.ignore(100, '\n');
        cout << '\n';
        
        if (!cams.empty())
        {
            for (auto i = cams.begin(); i < cams.end(); ++i)
            {
                if (i->match_device(input_name))
                {
                    cams.erase(i);
                    cout << "Successfully removed " << input_name << "." << endl << endl;
                    return 1;
                }
            }
        }

        if (!lights.empty())
        {
            for (auto i = lights.begin(); i < lights.end(); ++i)
            {
                if (i->match_device(input_name))
                {
                    lights.erase(i);
                    cout << "Successfully removed " << input_name << "." << endl << endl;
                    return 1;
                }
            }
        }

        if (!thermostats.empty())
        {
            for (auto i = thermostats.begin(); i < thermostats.end(); ++i)
            {
                if (i->match_device(input_name))
                {
                    thermostats.erase(i);
                    cout << "Successfully removed " << input_name << "." << endl << endl;
                    return 1;
                }
            }
        }
        cout << "No devices matching " << input_name << "." << endl << endl;
    }

    return 0; //no match
}

//This function allows the user to access the menu of the devices in the room and make changes to their settings
//Argument: none
//Return: int, 1 for success, 0 for failure
int room::access_device()
{
    if (!is_empty())
    {
        char input_name[100]; //char array holder for user input

        cout << "What device would you like to access?: ";
        cin.get(input_name, 100, '\n');
        cin.ignore(100, '\n');
        cout << '\n';
        
        if (!cams.empty())
        {
            for (auto & cam : cams) //passed by reference
            {
                if (cam.match_device(input_name))
                    return cam.menu();
            }
        }
        if (!lights.empty())
        {
            for (auto & light : lights)
            {
                if (light.match_device(input_name))
                    return light.menu();
            }
        }
        if (!thermostats.empty())
        {
            for (auto & thermostat : thermostats)
            {
                if (thermostat.match_device(input_name))
                    return thermostat.menu();
            }
        }

        cout << "No devices matching " << input_name << "." << endl << endl;
    }

    return 0; //no match
}

//This is the menu for the room object so user can control the devices in the room
//Argument: none
//Return: int, 1 for success, 0 for failure
int room::menu()
{
    bool agree {true};
    char answer;
    int selected_option;
    int success;
    
    cout << "What action would you like to take in " << name << "?" << endl;
    cout << "Please select from the options below: " << endl
         << "1) Add a device" << endl
         << "2) Remove a device" << endl
         << "3) List devices" << endl
         << "4) Make changes to a device" << endl
         << "5) Set room's name" << endl
         << "6) Display room's info" << endl << endl;

    while (agree) 
    {
        do
        {
            cout << "Please select from the options by entering a number from 1 to 6: ";
            cin >> selected_option;
            cin.ignore(100, '\n');
            cout << '\n';

            if (selected_option < 1 || selected_option > 6)
                cout << "Please only enter a number between 1 and 6, inclusive" << endl << endl;
        } while (selected_option < 1 || selected_option > 6);

        if (1 == selected_option)
            success = add_device();
        else if (2 == selected_option)
            success = remove_device();
        else if (3 == selected_option)
            list_devices();
        else if (4 == selected_option)
            success = access_device();
        else if (5 == selected_option)
            success = set_name();
        else if (6 == selected_option)
            display_info();

        cout << "Would you like to take another action in this room? (y/n): ";
        cin >> answer;
        cin.ignore(100, '\n');
        if (answer != 'y' && answer != 'Y')
            agree = false;
    }
    cout << '\n';

    return success;
}
