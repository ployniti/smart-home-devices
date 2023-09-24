//This is the .h file for the location class

#pragma once
#include "main.h"
#include "room.h"
#include "lll.h"

//Constant
//const size_t SIZE {5};

//Class 
//This is the location class that has a containing relationship with the room class
class location
{
    public:
        location(const string & an_address="", const string & a_name="");
        ~location();

        int set_address();
        int set_name(); //set name of the location
        int set_empty();
        string & get_name();
        int list_rooms() const; //list rooms at the same address
        int display_room() const;
        int access_room();
        int add_room();
        int remove_room();
        int remove_all();
        void display_info() const;
        bool is_empty() const; //check if there is no room at a location
        int menu();

    private:
        string address;
        string name; //"home" etc.
        LLL rooms;
};
