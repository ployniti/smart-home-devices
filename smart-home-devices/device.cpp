//This is the code to implement the device base class and the derived classes for smart devices

#include "device.h"
#include "cll.h"

/*DEVICE*/
//This is default constructor for the device class that allows the user to provide the name of the
//device at initialization and sets the other data member to their zero-equivalent values
device::device(const char * a_name /*=""*/):on_off(0), time_on("")
{
    device_name = new char [strlen(a_name)+1];
    strcpy(device_name, a_name);
}

//This is the copy constructor for the device obj
device::device(const device & to_copy)
{
    copy_data(to_copy);
}

//This is the assignment operator for the device class
//Argument: a device object
//Return: a device object by reference
device & device::operator=(const device & obj2)
{
    //Check for self-assignment
    if (this == &obj2)
        return *this;

    if (device_name)
        delete [] device_name;

    copy_data(obj2);

    return *this;
}

//This is a private copy function to be used in the copy constructor and assignment operator
//Argument: a device object
//Return: void
void device::copy_data(const device & to_copy)
{
    device_name = new char [strlen(to_copy.device_name)+1];
    strcpy(device_name, to_copy.device_name);

    time_on = to_copy.time_on;
    on_off = to_copy.on_off;
}

//This is the destructor of the device class. It deallocates memory and resets data member to
//their zero-equivalent values
device::~device()
{
    if (device_name)
    {
        delete [] device_name;
        device_name = nullptr;
    }

    on_off = 0;
    time_on = "";
}

//This is the display function to display the data members of the base device class
//Argument: none
//Return: void
void device::display_base() const
{
    cout << "Device's name: " << device_name << endl;

    if (on_off)
        cout << device_name << " is currently on." << endl;
    else
        cout << device_name << " is currently off." << endl;

    if (!time_on.empty())
        cout << "Set to be on at " << time_on << "." << endl;
}

//This is the function that set the on_off data member to 1 for on or 0 for off
//Argument: none
//Return: int, 1 for success, 0 for failure
int device::turn_on_off()
{
    char answer;

    cout << "Would you like to turn on " << device_name << " ? (y/n) ";
    cin >> answer;
    cin.ignore(100, '\n');
    cout << '\n';

    if (answer != 'y' && answer != 'Y')
        on_off = 0; //turn off
    else
        on_off = 1; //turn on

    return 1;
}

//This is the function that sets the time on the device to be on
//Argument: none
//Return: int, 1 for success, 0 for failure
int device::set_time()
{
    cout << "When would you like " << device_name << " to be on? ";
    getline(cin, time_on);
    
    return 1;
}

//This is the function to set/reset the name of the device
//Argument: none
//Return: int, 1 for success, 0 for failure
int device::set_name(/*char * a_name*/)
{
    char input_name[100]; //char array holder for user input
    
    cout << "What would you like to name your device? ";
    cin.get(input_name, 100, '\n');
    cin.ignore(100, '\n');
    cout << '\n';

    if (device_name)
        delete [] device_name;

    device_name = new char [strlen(input_name)+1];
    strcpy(device_name, input_name);

    return 1;
}

//This function returns true if the name of the argument matches the name of the device
//Argument: const char *
//Return: bool, true for a match, false for no match
bool device::match_device(const char * a_name) const
{
    if (strcmp(device_name, a_name) == 0)
        return true;
    
    return false;
}

/*SEC_CAM*/
//This is the default constructor for the sec_cam class, derived from the device base class
sec_cam::sec_cam(const char * a_name /*=""*/):device(a_name), is_recording(false), angle(0), zoom_mode(nullptr)
{
}

//This is the copy constructor for the sec_cam object
sec_cam::sec_cam(const sec_cam & to_copy):device(to_copy)
{
    //Copy the zoom_mode of to_copy
    if (to_copy.zoom_mode)
    {
        zoom_mode = new char [strlen(to_copy.zoom_mode)+1];
        strcpy(zoom_mode, to_copy.zoom_mode);
    }
    else
        zoom_mode = nullptr;

    is_recording = to_copy.is_recording;
    angle = to_copy.angle;
}

//This is the assignment operator for the sec_cam class
//Argument: a sec_cam object
//Return: a sec_cam object by reference
sec_cam & sec_cam::operator=(const sec_cam & obj2)
{
    //Check for self-assignment
    if (this == &obj2)
        return *this;

    if (zoom_mode)
    {
        delete [] zoom_mode;
        zoom_mode = new char [strlen(obj2.zoom_mode)+1];
        strcpy(zoom_mode, obj2.zoom_mode);
    }
    else
        zoom_mode = nullptr;

    //Call the device base class assignment operator
    device::operator=(obj2);

    is_recording = obj2.is_recording;
    angle = obj2.angle;
    
    return *this;
}

//This is the destructor of the sec_cam object
sec_cam::~sec_cam()
{
    if (zoom_mode)
    {
        delete [] zoom_mode;
        zoom_mode = nullptr;
    }

    angle = 0;
    is_recording = false;
}

//This is the display function to display the data members of the sec_cam class and the base device class
//Argument: none
//Return: void
void sec_cam::display_info() const
{
    //Call the display function of the device class
    display_base();
    
    if (is_recording)
        cout << device_name << " is recording." << endl;
    cout << "Angle: " << angle << " degrees." << endl;

    if (zoom_mode)
        cout << "Zoom mode: " << zoom_mode << endl << endl;
}

//This function sets the is_recording data member to true or false and returns the current recording state
//Argument: none
//Return: bool, true for recording, false for not recording
bool sec_cam::set_record()
{
    char answer;

    cout << "Would you like to set " << device_name << " to record? (y/n): ";
    cin >> answer;
    cin.ignore(100, '\n');
    cout << '\n';

    if (answer != 'y' && answer != 'Y')
        is_recording = false; //turn off
    else
        is_recording = true; //turn on

    return is_recording;
}

//This function sets the angle of the sec_cam object
//Argument: none
//Return: int, the current angle
int sec_cam::set_angle()
{
    cout << "What angle would you like to set " << device_name << " to?: ";
    cin >> angle;
    cin.ignore(100, '\n');
    cout << '\n';
    
    return angle;
}

//This function sets the zoom mode of the sec_cam object
//Argument: none
//Return: int, 1 for success, 0 for failure
int sec_cam::set_mode()
{
    char input_mode[100]; //char array holder for user input
    
    cout << "What would you like to set " << device_name << " zoom mode to?: ";
    cin.get(input_mode, 100, '\n');
    cin.ignore(100, '\n');
    cout << '\n';

    if (zoom_mode)
        delete [] zoom_mode;

    zoom_mode = new char [strlen(input_mode)+1];
    strcpy(zoom_mode, input_mode);

    return 1;
}

//This is the menu for the sec_cam object so user change its settings
//Argument: none
//Return: int, 1 for success, 0 for failure
int sec_cam::menu()
{
    bool agree {true};
    char answer;
    int selected_option;
    int success;
    
    cout << "What action would you like to take with " << device_name << "?" << endl;
    cout << "Please select from the options below: " << endl
         << "1) Turn device on/off" << endl
         << "2) Set time for device to be on" << endl
         << "3) Set camera to record" << endl
         << "4) Set camera's angle" << endl
         << "5) Set camera's mode" << endl
         << "6) Set device's name" << endl
         << "7) Display device's info" << endl << endl;

    while (agree) 
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
            success = turn_on_off();
        else if (2 == selected_option)
            success = set_time();
        else if (3 == selected_option)
            success = set_record();
        else if (4 == selected_option)
            success = set_angle();
        else if (5 == selected_option)
            success = set_mode();
        else if (6 == selected_option)
            success = set_name();
        else if (7 == selected_option)
            display_info();

        cout << "Would you like to take another action with this device? (y/n): ";
        cin >> answer;
        cin.ignore(100, '\n');
        if (answer != 'y' && answer != 'Y')
            agree = false;
    }
    cout << '\n';

    return success;
}

/*LIGHT*/
//This is the constructor for the light class
light::light(const char * a_name /*=""*/):device(a_name), brightness_setting(0), color_setting(0), energy_saving(0)
{
    //0 for unset
}

//This is the destructor for the light class
light::~light()
{
    brightness_setting = color_setting = energy_saving = 0;
}

//This is the display function to display the data members of the light class and the base device class
//Argument: none
//Return: void
void light::display_info() const
{
    //Call the display function of the device class
    display_base();

    cout << "Brightness: " << brightness_setting << endl;
    cout << "Color: " << color_setting << endl;

    if (energy_saving)
        cout << "Energy saving mode on." << endl;
}

//This is the function to set the brightness data member of the light class
//Argument: none
//Return: int, the current brightness setting
int light::set_brightness()
{
    int selected_option;

    do
    {
        cout << "Please select the brightness setting for " << device_name << " from 1 to 5: ";
        cin >> selected_option;
        cin.ignore(100, '\n');
        cout << '\n';

        if (selected_option < 1 || selected_option > 5)
            cout << "Please only enter a number between 1 and 5, inclusive" << endl << endl;
    } while (selected_option < 1 || selected_option > 5);

    brightness_setting = selected_option;

    return brightness_setting;
}

//This is the function to set the color_setting of the light class
//Argument: none
//Return: int, the current color_setting
int light::set_color()
{
    int selected_option;

    do
    {
        cout << "Please select the color setting for " << device_name << " from 1 to 5: ";
        cin >> selected_option;
        cin.ignore(100, '\n');
        cout << '\n';

        if (selected_option < 1 || selected_option > 5)
            cout << "Please only enter a number between 1 and 5, inclusive" << endl << endl;
    } while (selected_option < 1 || selected_option > 5);

    color_setting = selected_option;

    return color_setting;
}

//This is the function to set the energy saving mode of the light class
//Argument: none
//Return: int, the current energy saving setting
int light::set_energy_mode()
{
    char answer;

    cout << "Would you like to turn on energy saving mode for " << device_name << "? (y/n) ";
    cin >> answer;
    cin.ignore(100, '\n');
    cout << '\n';

    if (answer != 'y' && answer != 'Y')
        energy_saving = 0; //turn off
    else
        energy_saving = 1; //turn on

    return energy_saving;
}

//This function display a menu to manage the CLL energy mode schedule
//Argument: none
//Return: int, 1 for success, 0 for failure
int light::schedule_mode()
{
    bool agree {true};
    char answer;
    int selected_option;
    int success;
    int setting;
    string a_time;

    cout << "Welcome to the energy mode scheduler for " << device_name << endl;
    cout << "Please select from the options below: " << endl
         << "1) Add a schedule" << endl
         << "2) Display the current schedule" << endl
         << "3) Retrieve a schedule" << endl
         << "4) Remove a schedule" << endl
         << "5) Remove all schedule" << endl << endl;

    while (agree) 
    {
        do
        {
            cout << "Please select from the options by entering a number from 1 to 5: ";
            cin >> selected_option;
            cin.ignore(100, '\n');
            cout << '\n';

            if (selected_option < 1 || selected_option > 5)
                cout << "Please only enter a number between 1 and 5, inclusive" << endl << endl;
        } while (selected_option < 1 || selected_option > 5);

        if (1 == selected_option)
        {
            cout << "When would you like to set the energy mode?: ";
            getline(cin, a_time);
            setting = set_energy_mode();

            success = energy_mode_schedule.insert(setting, a_time);
        }
        else if (2 == selected_option)
        {
            if (!energy_mode_schedule.is_empty())
                energy_mode_schedule.display_all();
            else
                cout << "Schedule is empty, please add a schedule first." << endl << endl;
        }
        else if (3 == selected_option)
        {
            if (!energy_mode_schedule.is_empty())
            {
                cout << "Please enter the time of schedule to be retrieved: ";
                getline(cin, a_time);
                success = energy_mode_schedule.retrieve(a_time);
                
                if (!success)
                    cout << "No match found to retrieve, please try again." << endl << endl;
            }
            else
                cout << "Schedule is empty, please add a schedule first." << endl << endl;
        }
        else if (4 == selected_option)
        {
            if (!energy_mode_schedule.is_empty())
            {
                cout << "Please enter the time of schedule to be removed: ";
                getline(cin, a_time);
                success = energy_mode_schedule.remove(a_time);

                if (!success)
                    cout << "No match found to remove, please try again." << endl << endl;
            }
            else
                cout << "Schedule is empty, please add a schedule first." << endl << endl;
        }
        else if (5 == selected_option)
        {
            if (!energy_mode_schedule.is_empty())
            {
                energy_mode_schedule.remove_all(); //int return type? not used here?
                cout << "Successfully removed all schedules" << endl << endl;
            }
            else
                cout << "Schedule is empty, please add a schedule first." << endl << endl;
        }

        cout << "Would you like to take another action with the schedule? (y/n): ";
        cin >> answer;
        cin.ignore(100, '\n');
        if (answer != 'y' && answer != 'Y')
            agree = false;
    }
    cout << '\n';

    return success;
}

//This is the menu for the light object so user change its settings
//Argument: none
//Return: int, 1 for success, 0 for failure
int light::menu()
{
    bool agree {true};
    char answer;
    int selected_option;
    int success;
    
    cout << "What action would you like to take with " << device_name << "?" << endl;
    cout << "Please select from the options below: " << endl
         << "1) Turn device on/off" << endl
         << "2) Set time for device to be on" << endl
         << "3) Set light's color" << endl
         << "4) Set light's brightness" << endl
         << "5) Set light's energy mode" << endl
         << "6) Schedule light's energy mode" << endl
         << "7) Set device's name" << endl
         << "8) Display device's info" << endl << endl;

    while (agree) 
    {
        do
        {
            cout << "Please select from the options by entering a number from 1 to 8: ";
            cin >> selected_option;
            cin.ignore(100, '\n');
            cout << '\n';

            if (selected_option < 1 || selected_option > 8)
                cout << "Please only enter a number between 1 and 8, inclusive" << endl << endl;
        } while (selected_option < 1 || selected_option > 8);

        if (1 == selected_option)
            success = turn_on_off();
        else if (2 == selected_option)
            success = set_time();
        else if (3 == selected_option)
            success = set_color();
        else if (4 == selected_option)
            success = set_brightness();
        else if (5 == selected_option)
            success = set_energy_mode();
        else if (6 == selected_option)
            success = schedule_mode();
        else if (7 == selected_option)
            success = set_name();
        else if (8 == selected_option)
            display_info();

        cout << "Would you like to take another action with this device? (y/n): ";
        cin >> answer;
        cin.ignore(100, '\n');
        if (answer != 'y' && answer != 'Y')
            agree = false;
    }
    cout << '\n';

    return success;
}

/*THERMOSTAT*/
//This is the constructor for the thermostat class
thermostat::thermostat(const char * a_name/*=""*/):device(a_name), temperature(0), fan_speed(0), ac_mode(0)
{
    //0 for unset
}

//This is the destructor for the thermostat class
thermostat::~thermostat()
{
    temperature = fan_speed = ac_mode = 0;
}

//This is the display function to display the data members of the thermostat class and the base device class
//Argument: none
//Return: void
void thermostat::display_info() const
{
    //Call the display function of the device class
    display_base();

    cout << "Temperature (F): " << temperature << endl;
    cout << "Fan speed: " << fan_speed << endl;

    if (ac_mode)
        cout << "AC mode: cooling" << endl;
    else
        cout << "AC mode: heating" << endl;
}

//This function sets the temperature data member of the thermostat object
//Argument: none
//Return: int, the current temperature in F
int thermostat::set_temperature()
{
    cout << "What temperature would you like to set " << device_name << " to?: ";
    cin >> temperature;
    cin.ignore(100, '\n');
    cout << '\n';
    
    return temperature;
}

//This function sets the fan_speed data member of the thermostat object
//Argument: none
//Return: int, the current fan_speed
int thermostat::set_fan()
{
    int selected_option;

    do
    {
        cout << "Please select the fan speed for " << device_name << " from 1 to 5: ";
        cin >> selected_option;
        cin.ignore(100, '\n');
        cout << '\n';

        if (selected_option < 1 || selected_option > 5)
            cout << "Please only enter a number between 1 and 5, inclusive" << endl << endl;
    } while (selected_option < 1 || selected_option > 5);

    fan_speed = selected_option;

    return fan_speed;
}

//This function sets the ac_mode data member of the thermostat object
//Argument: none
//Return: int, the current ac_mode (0 for heating, 1 for cooling)
int thermostat::set_ac()
{
    char answer;

    cout << "Would you like to set " << device_name << " to cooling or heating? (c/h): ";
    cin >> answer;
    cin.ignore(100, '\n');
    cout << '\n';

    if (answer != 'c' && answer != 'C')
        ac_mode = 0; //turn off
    else
        ac_mode = 1; //turn on

    return ac_mode;
}

//This is the menu for the thermostat object so user change its settings
//Argument: none
//Return: int, 1 for success, 0 for failure
int thermostat::menu()
{
    bool agree {true};
    char answer;
    int selected_option;
    int success;
    
    cout << "What action would you like to take with " << device_name << "?" << endl;
    cout << "Please select from the options below: " << endl
         << "1) Turn device on/off" << endl
         << "2) Set time for device to be on" << endl
         << "3) Set thermostat's temperature" << endl
         << "4) Set thermostat's fan speed" << endl
         << "5) Set thermostat's AC mode" << endl
         << "6) Set device's name" << endl
         << "7) Display device's info" << endl << endl;

    while (agree) 
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
            success = turn_on_off();
        else if (2 == selected_option)
            success = set_time();
        else if (3 == selected_option)
            success = set_temperature();
        else if (4 == selected_option)
            success = set_fan();
        else if (5 == selected_option)
            success = set_ac();
        else if (6 == selected_option)
            success = set_name();
        else if (7 == selected_option)
            display_info();

        cout << "Would you like to take another action with this device? (y/n): ";
        cin >> answer;
        cin.ignore(100, '\n');
        if (answer != 'y' && answer != 'Y')
            agree = false;
    }
    cout << '\n';

    return success;
}
