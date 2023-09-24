//This is the client program to interact with the user

#include "device.h"
#include "location.h"
#include "room.h"
#include "table.h"
#include "cll.h"
#include "lll.h"
#include "main.h"

int main()
{  
    //Variables
    table locations;
    int selected_option {0};
    bool agree {true};
    char answer;
    
    cout << "Welcome to the smart home application!" << endl;
    cout << "Please select from the options below: " << endl
         << "1) Add a new smart home location" << endl
         << "2) Display a smart home location info" << endl
         << "3) Display all locations" << endl
         << "4) Remove a smart home location" << endl
         << "5) Remove all smart home locations" << endl
         << "6) Retrieve and access a smart home location" << endl
         << "7) Exit program" << endl << endl;

    while (agree && 7 != selected_option)
    {
        do
        {
            cout << "Please select from the options by entering a number from 1 to 7: ";
            cin >> selected_option;
            cin.ignore(100, '\n');
            cout << '\n';

            if (selected_option < 1 || selected_option > 7)
                cout << "Please only enter a number between 1 and 7, inclusive" << endl << endl;
        } while (selected_option < 1 || selected_option > 7);

        if (1 == selected_option)
        {
            if (!locations.add_location())
                cout << "We're at capacity and can't add more location at this time." << endl << endl;
        }
        else if (2 == selected_option)
        {
            if (!locations.display_location())
                cout << "No match found to remove or no locations in program, please try again." << endl << endl;
        }
        else if (3 == selected_option)
        {
            if (!locations.display_all())
                cout << "No locations in program yet, please add a location" << endl << endl;
        }
        else if (4 == selected_option)
        {
            if (!locations.remove_location())
                cout << "No match found to remove or no locations in program, please try again." << endl << endl;
        }
        else if (5 == selected_option)
        {
            if (!locations.remove_all())
                cout << "No locations in program yet, please add a location." << endl << endl;
        }
        else if (6 == selected_option)
        {
            if (!locations.access_location())
                cout << "No match found to remove or no locations in program, please try again." << endl << endl;
        }
        if (7 != selected_option)
        {
            cout << "Would you like to take another action? (y/n): ";
            cin >> answer;
            cin.ignore(100, '\n');
            if (answer != 'y' && answer != 'Y')
                agree = false;
        }
    }

    cout << '\n';
    cout << "Thank you for using the program!" << endl << endl;
    
    return 0;
}
