//This is the code to implement an array of LLL which will be an array of location objects
//that each contains a LLL of room whose nodes are derived from the room class

#include "table.h"
#include "lll.h"

/*TABLE*/
//This is the constructor for the table class
table::table(int size /*= 5*/):arr_size(size), count(0), location_array(nullptr)
{
    location_array = new location [size];
}

//This is the copy constructor for the table class
table::table(const table & src):arr_size(src.arr_size), count(src.count), location_array(nullptr)
{
    copy(src);
}

//This is the assignment operator for the table class
table & table::operator=(const table & src)
{
    if (this == &src)
        return *this;

    if (src.location_array)
        delete [] location_array;

    copy(src);

    return *this;
}

//This is the copy function to copy data members in the table class from one to another
//Argument: table object to copy from passed by reference
//Return: void
void table::copy(const table & src)
{
    location_array = new location [src.arr_size]; //constructor for location obj called
    for (int i = 0; i < arr_size; ++i)
        location_array[i] = src.location_array[i]; //assign location obj in new array

    arr_size = src.arr_size;

    count = src.count;
}

//This is the destructor for the table class
table::~table()
{
    if (location_array)
    {
        delete [] location_array;
        location_array = nullptr;
    }

    arr_size = 0;
    count = 0;
}

//This is the function to set a location's name and address in an empty location object in the array
//Argument: none
//Return: int, 1 for success, 0 for failure
int table::insert()
{
    int success {0};
    
    if (count == arr_size)
        return 0; //array is full

    for (int i = 0; i < arr_size; ++i)
    {
        location * a_location = &location_array[i];
        
        if (a_location->get_name() == "") //empty location object
        {
            success += a_location->set_name();
            success += a_location->set_address();
            ++count;
            return success;
        }
    }

    return 0;
}

//This is the function to prompt the user to add more location using the insert function
//Argument: none
//Return: int, 1 for success, 0 for failure
int table::add_location()
{
    bool agree {true};
    char answer;
    int success {0};

    do
    {
        success = insert();
        if (!success)
            cout << "Error adding a new location, please try again." << endl << endl;
        else
        {
            cout << "New location added!" << endl << endl;

            cout << "Would you like to add another location? (y/n): ";
            cin >> answer;
            cin.ignore(100, '\n');
            if (answer != 'y' && answer != 'Y')
                agree = false;
        }

    } while (agree && success);

    return success;
}

//This is the function to remove/empty a matching location object
//Argument: string of location name passed by reference
//Return: int, 1 for success, 0 for failure
int table::remove(const string & location_name)
{
    for (int i = 0; i < arr_size; ++i)
    {
        location * a_location = &location_array[i];
        
        if (a_location->get_name() == location_name)
            return a_location->set_empty();
    }

    return 0;
}

//This is a wrapper function to prompt user for location name to remove
//Argument: none
//Return: int, 1 for success, 0 for failure
int table::remove_location()
{
    int success {0};

    if (!is_empty())
    {
        char input_name[100]; //char array holder for user input
        
        cout << "What location would you like to remove?: ";
        cin.get(input_name, 100, '\n');
        cin.ignore(100, '\n');
        cout << '\n';

        success += remove(input_name);

        if (success)
        {
            --count;
            cout << "Successfully removed " << input_name << "." << endl << endl;
        }
    }

    return success;
}

//This is the function to remove/empty all location objects in the array
//Argument: none
//Return: int, 1 for success, 0 for failure
int table::remove_all()
{
    int success {0};

    if (!is_empty())
    {

        for (int i = 0; i < arr_size; ++i)
        {
            location * a_location = &location_array[i];
            success += a_location->set_empty();
        }

        count = 0; //resets count to 0

        cout << "Successfully removed all locations." << endl << endl;
    }

    return success;
}

//This is the function to display a matching location object information and the rooms within it
//Argument: none
//Return: int, 1 for success, 0 for failure
int table::display_location() const
{   
    if (!is_empty())
    {
        char input_name[100]; //char array holder for user input
        
        cout << "What location would you like to display?: ";
        cin.get(input_name, 100, '\n');
        cin.ignore(100, '\n');
        cout << '\n';

        for (int i = 0; i < arr_size; ++i)
        {
            location * a_location = &location_array[i];
            
            if (a_location->get_name() == input_name)
            {
                a_location->display_info(); //display location info
                a_location->list_rooms(); //display rooms in the location's LLL
                return 1;
            }
        }
    }

    return 0;
}

//This is the function to display all location's name and address in the array
//Argument: none
//Return: int, 1 for success, 0 for failure
int table::display_all() const
{
    if (is_empty()) return 0;

    for (int i = 0; i < arr_size; ++i)
        location_array[i].display_info();

    return 1;
}

//This is the function that prompt the user for a location name to retrieve and call its menu function for actions
//Argument: none
//Return: int, 1 for success, 0 for failure
int table::access_location()
{
    int success {0};

    if (!is_empty())
    {
        char input_name[100]; //char array holder for user input
        
        cout << "What location would you like to access?: ";
        cin.get(input_name, 100, '\n');
        cin.ignore(100, '\n');
        cout << '\n';

        for (int i = 0; i < arr_size; ++i)
        {
            location * a_location = &location_array[i];
            
            if (a_location->get_name() == input_name)
            {
                success += a_location->menu(); //CANT FIND ROOM IN LOCATION AFTER ADDED
                return success;
            }
        }
    }

    return success;
}

//This function checks if the location array is empty
//Argument: none
//Return: bool, true for empty, false for not empty
bool table::is_empty() const
{
    if (!count) return true;
    return false;
}

/*L_NODE*/
//This is the default constructor for the L_node class
L_node::L_node():next(nullptr)
{
}

//This is the copy constructor for the L_node class, taking in a L_node object
L_node::L_node(const L_node & src):room(src), next(nullptr)
{
    //Explicitly call the automatic room copy constructor
}

//This is the copy constructor for the L_node class, taking in a room object
L_node::L_node(const room & new_room):room(new_room), next(nullptr)
{
}

//This is the assignment operator for the L_node class
L_node & L_node::operator=(const L_node & src)
{
    if (this == &src)
        return *this;

    if (next)
    {
        delete next;
        next = nullptr;
    }
    
    //Call the room base class automatic assignment operator
    room::operator=(src);
    
    next = src.next;

    return *this;
}

//This is the destructor for the L_node class
L_node::~L_node()
{
    if (next)
    {
        delete next;
        next = nullptr;
    }
}

//This is the function to set the L_node's next pointer
//Argument: L_node pointer to a new address
//Return: void
void L_node::set_next(L_node * new_next)
{
    next = new_next;
}

//This is the function to get the L_node's next pointer
//Argument: none
//Return: L_node pointer passed by reference
L_node * & L_node::get_next()
{
    return next;
}

//This is the function to get the L_node/room's name
//Argument: none
//Return: string passed by reference
string & L_node::get_name()
{
    return name;
}

/*LLL*/
//This is the constructor for the LLL class
LLL::LLL():head(nullptr)
{
}

//This is the copy constructor for the LLL class
LLL::LLL(const LLL & src)
{
    copy(head, src.head);
}

//This is the assignment operator for the LLL
LLL & LLL::operator=(const LLL & src)
{
    if (this == &src)
        return *this;

    remove_all(head);

    copy(head, src.head);

    return *this;
}

//This is the copy function for the LLL class
//Arguments: L_node pointer to dest to copy on and L_node pointer to src to copy from
void LLL::copy(L_node * & dest, L_node * src)
{
    if (!src) return;

    dest = new L_node(*src);

    copy(dest->get_next(), src->get_next());
}

//This is the destructor for the LLL class
LLL::~LLL()
{
    remove_all();
}

//This is the wrapper function to remove all nodes in the LLL
//Argument: none
//Return: void
void LLL::remove_all()
{
    if (!head) return;

    remove_all(head);
}

//This is the function to remove all nodes in the LLL recursively
//Argument: none
//Return: void
void LLL::remove_all(L_node * & head)
{
    if (!head) return;

    remove_all(head->get_next());

    delete head;
    head = nullptr;
}

//This is the wrapper function to display the room's name in the node
//Argument: L_node pointer
//Return: void
void LLL::display_all() const
{
    if (!head) return;

    display_all(head);
}

//This is the function to display the room's name in the node
//Argument: L_node pointer
//Return: void
void LLL::display_all(L_node * head) const
{
    if (!head) return;

    head->display_info();

    display_all(head->get_next());
}

//This is the wrapper function to display a room with matching name
//Arguments: L_node pointer and string for room's name passed by reference
//Return: int, 1 for success, 0 for failure
int LLL::display_room(const string & room_name) const
{
    if (!head) return 0;
    
    return display_room(head, room_name);
}

//This is the function to display a room with matching name recursively
//Arguments: L_node pointer and string for room's name passed by reference
//Return: int, 1 for success, 0 for failure
int LLL::display_room(L_node * head, const string & room_name) const
{
    if (!head) return 0;

    if (head->get_name() == room_name)
    {
        head->display_info();
        return 1;
    }

    return display_room(head->get_next(), room_name);
}

//This is the function to insert a new room into the LLL
//Argument: room object passed by reference
//Return: int, 1 for succes, 0 for failure
int LLL::insert(const room & new_room)
{
    if (!head)
    {
        head = new L_node(new_room);
        return 1;
    }

    L_node * hold = head;
    head = new L_node(new_room);
    head->set_next(hold);

    return 1;
}

//This is the function that checks if the LLL is empty
//Argument: none
//Return: bool, true for empty, false for not empty
bool LLL::is_empty() const
{
    if (!head) return true;
    return false;
}

//This is the wrapper function to remove a node with matching name in a LLL
//Argument: string passed by reference
//Return: int, 1 for success, 0 for failure
int LLL::remove(const string & room_name)
{
    if (!head) return 0;

    return remove(room_name, head);
}

//This is the function to remove a node with matching name in a LLL recursively
//Argument: string passed by reference
//Return: int, 1 for success, 0 for failure
int LLL::remove(const string & room_name, L_node * & head)
{
    if (!head) return 0;

    if (head->get_name() == room_name)
    {
        L_node * hold = head->get_next();
        head->set_next(nullptr);
        delete head;
        head = hold;
        return 1;
    }

    return remove(room_name, head->get_next());
}

//This is the wrapper function to retrieve a node with matching name in a LLL
//Argument: string passed by reference
//Return: int, 1 for success, 0 for failure
int LLL::retrieve(const string & room_name)
{
    if (!head) return 0;
    
    return retrieve(room_name, head);
}

//This is the wrapper function to retrieve a node with matching name in a LLL recursively
//Argument: string passed by reference
//Return: int, 1 for success, 0 for failure
int LLL::retrieve(const string & room_name, L_node * head)
{
    if (!head) return 0;

    if (head->get_name() == room_name)
        return head->menu();

    return retrieve(room_name, head->get_next());
}
