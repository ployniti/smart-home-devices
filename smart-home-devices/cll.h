//This is the .h file for the CLL node and CLL classes

#pragma once
#include "main.h"

//This is the CLL node class that will be used to keep schedule of when the light object's energy saving mode is on and off
class C_node
{
    public:
        C_node();
        C_node(int option, const string & a_time);
        ~C_node();
        C_node(const C_node & src);
        C_node & operator=(const C_node & src);
        void display() const;
        void set_next(C_node * new_next);
        C_node * & get_next();
        string & get_time();

    private:
        C_node * next;
        int on_off; //whether energy saving mode is on/off
        string time; //time to be on/off

        void copy(const C_node & src);
};

//This is the CLL class
class CLL
{
    public:
        CLL();
        ~CLL();
        CLL(const CLL & src);
        CLL & operator=(const CLL & src);
        
        int insert(int option, const string & a_time); //add at rear
        void display_all() const;
        bool is_empty();
        int remove(const string & a_time);
        int retrieve(const string & a_time);
        void remove_all();

    private:
        C_node * rear;

        void display_all(C_node * rear) const;
        int remove(const string & a_time, C_node * & rear);
        int retrieve(const string & a_time, C_node * rear);
        void remove_all(C_node * & rear);
        void copy(C_node * & dest_rear, C_node * src, C_node * src_rear);
};
