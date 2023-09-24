//Ploy Nitipiyaroj
//CS302
//Program 1 - Final Submission
//02/06/2023

//This is the .h file for the table class

#pragma once
#include "main.h"
#include "location.h"

//This is the table class with an array of locations
class table
{
    public:
        table(int size = 5);
        ~table();
        table(const table & src);
        table & operator=(const table & src);
        
        int add_location();
        int display_all() const;
        int remove_location();
        int display_location() const;
        int access_location(); //retrieve a location object and access its menu
        int remove_all();

    private:
        int arr_size; //size of the array
        int count; //number of object filled in array
        location * location_array;
        
        void copy(const table & src);
        int remove(const string & location_name);
        int insert();
        bool is_empty() const;
};
