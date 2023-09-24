//Ploy Nitipiyaroj
//CS302
//Program 1 - Final Submission
//02/06/2023

//This is the .h file for the room class

#pragma once
#include "main.h"
#include "device.h"

//Classes
//This is the room class that has a vector of devices
class room
{
    public:
        room(const string & a_name="");
        ~room();

        int set_name(); //set name of room
        void list_devices() const; //list devices in the room
        int access_device();
        int add_device(); //provide the type of device to add and its name
        int remove_device();
        bool is_empty() const; //check if there is no device in the room
        void display_info() const;
        int menu();
    
    protected:
        string name;

    private:
        vector <sec_cam> cams; //a vector of security cameras in a room obj
        vector <light> lights; //a vector of lights in a room obj
        vector <thermostat> thermostats; //a vector of thermostats in a room obj
};
