//This is the .h file for the base device class and the derived smart device classes
//(sec_cam, light, and thermostat).

#pragma once
#include "main.h"
#include "cll.h"

//Classes
//This is the device base class that the smart device classes will derive from
class device
{
    public:
        device(const char * a_name="");
        ~device();
        device(const device & to_copy);
        device & operator=(const device & obj2);

        int turn_on_off();
        int set_time(); //set time on the device to be on
        int set_name(); //set name on the device
        bool match_device(const char * a_name) const; //give the name of the device to match
        void display_base() const;

    protected:
        char * device_name;
        int on_off;
        string time_on; //"5AM" etc.

    private:
        void copy_data(const device & to_copy); //a copy function to be used in the copy constructor and assignment operator
};

//This is the security camera class derived from the base device class
class sec_cam: public device
{
    public:
        sec_cam(const char * a_name="");
        ~sec_cam();
        sec_cam(const sec_cam & to_copy);
        sec_cam & operator=(const sec_cam & obj2);

        bool set_record(); //true for recording in progress, false for not
        int set_angle(); //move camera angle, side to side
        int set_mode(); //set the zoom mode
        void display_info() const;
        int menu();

    private:
        bool is_recording;
        int angle;
        char * zoom_mode; //"narrow", "wide" etc.
};

//This is the light class derived from the base device class
class light: public device
{
    public:
        light(const char * a_name="");
        ~light();

        int set_brightness();
        int set_color();
        int set_energy_mode();
        int schedule_mode();
        void display_info() const;
        int menu();

    private:
        int brightness_setting; //from 1 to 5, 0 initialized
        int color_setting; //from 1 to 5, 0 initialized
        int energy_saving; //0 for off, 1 for on
        CLL energy_mode_schedule;
};

//This is the thermostat class derived from the base device class
class thermostat: public device
{
    public:
        thermostat(const char * a_name="");
        ~thermostat();

        int set_temperature(/*int fahrenheit*/);
        int set_fan(/*int speed*/);
        int set_ac(/*int mode*/);
        void display_info() const;
        //menu_interface for thermostat functions
        int menu();

    private:
        int temperature;
        int fan_speed; //from 1 to 5
        int ac_mode; //0 for cooling, 1 for heating
};
