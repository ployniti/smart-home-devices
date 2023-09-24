//This is the .h file for the LLL node and LLL classes

#pragma once
#include "main.h"
#include "room.h"

//This is the LLL node class derived from the room class that will be used to keep a LLL of rooms as part of an array of LLL
class L_node : public room
{
    public:
        L_node();
        ~L_node();
        L_node(const L_node & src);
        L_node(const room & new_room);
        L_node & operator=(const L_node & src);
        
        void set_next(L_node * new_next);
        L_node * & get_next();
        string & get_name();

    private:
        L_node * next;
};

//This is the LLL class
class LLL
{
    public:
        LLL();
        ~LLL();
        LLL(const LLL & src);
        LLL & operator=(const LLL & src);
        
        int insert(const room & new_room);
        void display_all() const;
        int display_room(const string & room_name) const;
        bool is_empty() const;
        int remove(const string & room_name);
        int retrieve(const string & room_name);
        void remove_all();

    private:
        L_node * head;

        void display_all(L_node * head) const;
        int display_room(L_node * head, const string & room_name) const;
        int remove(const string & room_name, L_node * & head);
        int retrieve(const string & room_name, L_node * head);
        void remove_all(L_node * & head);
        void copy(L_node * & dest, L_node * src);
};
