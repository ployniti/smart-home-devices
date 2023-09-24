//This is the code to implement the CLL node and CLL classes

#include "cll.h"

/*C_NODE*/
//This is the default constructor for the C_node class
C_node::C_node():next(nullptr), on_off(0)
{
}

//This is the overloaded constructor for the C_node class
C_node::C_node(int option, const string & a_time):next(nullptr), on_off(option), time(a_time)
{
}

//This is the destructor for the C_node class
C_node::~C_node()
{
    if (!time.empty())
        time.clear();
    
    on_off = 0;

    if (next)
    {
        delete next;
        next = nullptr;
    }
}

//This is the copy constructor for the C_node class
C_node::C_node(const C_node & src):next(nullptr)
{
    copy(src);
}

//This is the assignment operator for the C_node class
C_node & C_node:: operator=(const C_node & src)
{
    if (this == &src)
        return *this;

    if (next)
    {
        delete next;
        next = nullptr;
    }
    
    if (!time.empty())
        time.clear();

    copy(src);

    return *this;
}

//This is the private copy function to be used in the copy constructor and assignment operator
//Argument: C_node object passed by reference
//Return: void
void C_node::copy(const C_node & src)
{
    time = src.time;
    on_off = src.on_off;
    next = src.next;
}

//This is the function to set the C_node's next pointer to a new C_node
//Argument: C_node pointer to point next to
//Return: void
void C_node::set_next(C_node * new_next)
{
    next = new_next;
}

//This is the function to get the C_node's next pointer
//Argument: C_node pointer to point next to
//Return: C_node pointer passed by reference
C_node * & C_node::get_next()
{
    return next;
}

//This is the function to display the C_node's data members
//Argument: none
//Return: void
void C_node::display() const
{
    if (on_off)
        cout << "The energy saving mode will be on at " << time << endl;
    else
        cout << "The energy saving mode will be off at " << time << endl;

    return;
}

//This is the function to get the time data member
//Argument: none
//Return: string by reference
string & C_node::get_time()
{
    return time;
}

/*CLL*/
//This is the default constructor for the CLL class
CLL::CLL():rear(nullptr)
{
}

//This is the destructor for the CLL class
CLL::~CLL()
{
    remove_all();
}

//This is the wrapper function for the remove all function
//Argument: none
//Return: void
void CLL::remove_all()
{
    if (!rear) return;

    C_node * temp = rear->get_next();
    rear->set_next(nullptr);
    remove_all(temp);
    rear = nullptr;
}

//This is the function that removes all nodes in a CLL recursively
//Argument: C_node rear pointer passed by reference
//Return: void
void CLL::remove_all(C_node * & rear)
{
    if (!rear) return;
    
    remove_all(rear->get_next());

    delete rear;
    rear = nullptr;
}

//This is the copy constructor for the CLL class
CLL::CLL(const CLL & src):rear(nullptr)
{
    if (!src.rear)
        return;

    copy(rear, src.rear->get_next(), src.rear);
}

//This is the assignment operator for the CLL class
CLL & CLL::operator=(const CLL & src)
{
    if (this == &src)
        return *this;

    remove_all(rear);

    copy(rear, src.rear->get_next(), src.rear);

    return *this;
}

//This is the copy function to copy all nodes in a CLL recursively
//Argument: C_node pointer to copy to, C_node pointer to copy from, and the C_node pointer of the real rear of source
//Return: void
void CLL::copy(C_node * & dest, C_node * src, C_node * src_rear)
{
    if (src == src_rear)
    {
        dest = new C_node(*src);
        dest->set_next(this->rear);
        this->rear = dest;
        return;
    }

    dest = new C_node(*src);

    return copy(dest->get_next(), src->get_next(), src_rear);
}

//This is the wrapper function for the display function recursively
//Argument: none
//Return: void
void CLL::display_all() const
{
    if (!rear) return;
    display_all(rear->get_next());
}

//This is the function to display the C_node data recursively
//Argument: none
//Return: void
void CLL::display_all(C_node * rear) const
{
    rear->display();

    if (rear==this->rear) return;

    return display_all(rear->get_next());
}

//This is the function to insert a new node into the CLL at the rear
//Argument: string of when the mode should be set and an int for what the setting should be
//Return: int, 1 for success, 0 for failure
int CLL::insert(int option, const string & a_time)
{
    if (!rear)
    {
        rear = new C_node(option, a_time);
        rear->set_next(rear);
        return 1;
    }

    C_node * temp = new C_node(option, a_time);
    temp->set_next(rear->get_next());
    rear->set_next(temp);
    rear = temp;

    return 1;
}

//This function checks if the CLL is empty
//Argument: none
//Return: bool, true for empty, false for not empty
bool CLL::is_empty()
{
    if (!rear) return true;

    return false;
}

//This is the wrapper function finds the time and delete the node in the schedule
//Arguments: string of the time
//Return: int, 1 for success, 0 for failure
int CLL::remove(const string & a_time)
{
    if (!rear) return 0;
    
    if (rear->get_next() == rear)
    {
        if (a_time == rear->get_time())
        {
            rear->set_next(nullptr);
            delete rear;
            rear = nullptr;
            return 1;
        }
        return 0;
    }
    
    return remove(a_time, rear->get_next());
}

//This function finds the time and delete the node in the schedule recursively
//Arguments: string of the time and C_node pointer to rear
//Return: int, 1 for success, 0 for failure
int CLL::remove(const string & a_time, C_node * & rear)
{
    if (a_time == rear->get_next()->get_time())
    {
        C_node * temp = rear->get_next()->get_next();
        rear->get_next()->set_next(nullptr);

        if (rear->get_next() == this->rear)
            this->rear = rear;

        delete rear->get_next();
        rear->set_next(temp);

        return 1;
    }

    if (rear == this->rear)
        return 0;

    return remove(a_time, rear->get_next());
}

//This is the wrapper function to find the time and display the information in the node
//Arguments: string of the time
//Return: int, 1 for success, 0 for failure
int CLL::retrieve(const string & a_time)
{
    if (!rear) return 0;

    return retrieve(a_time, rear->get_next());
}

//This function finds the time and display the information in the node
//Arguments: string of the time and C_node pointer to rear
//Return: int, 1 for success, 0 for failure
int CLL::retrieve(const string & a_time, C_node * rear)
{
    if (a_time == rear->get_time())
    {
        rear->display();
        return 1;
    }

    if (rear == this->rear)
        return 0;

    return retrieve(a_time, rear->get_next());
}
