# smart-home-devices
This project explores inheritance and data abstraction in conjunction with an implementation of multiple data structures 
(an array of linear linked lists, circular linked list, STL vector) through the context of smart home devices.

# Specification
Design a program that allows the users to set the states of different smart home devices, such as a smart lamp and a smart thermostat, in multiple rooms and locations.

# Hierarchy Design
<p align="center">
  <img width="637" alt="uml" src="https://github.com/ployniti/smart-home-devices/assets/145937137/5bb7d6e0-1913-4472-bd7f-175517299c74">
</p>

First, I think that it makes sense for the user to pick their location first, then a room at that location before they can get to the devices in the room. 
I designed my hierarchies and built the relationships between the classes with these steps of user interaction in mind which I think helped me approach the program in an organized manner.

The classes in my program have the following relationships. 
There is a device class which serves as the base class for the three specific smart device types: security camera, thermostat, and light. 
This is because the different smart devices “is a” device. I think this was an effective breakdown since all the smart devices need to be able to change a common state 
such as turning on and off and setting their time to be on. 
They also all have a name so all these data members are included in the base device class which can flow through to the derived classes with a public derivation. 
The smart device classes have, in addition to the base data members and member functions, their own unique states such as brightness for the light class and temperature for the thermostat class.

In addition to the device hierarchy above, I have a location class and a room class which are separate from the devices. 
These classes have a containing or “has a” relationship with one another and with the different smart device classes. 
This was where some of the required data structures came in. A location object has a linear linked list of rooms and a room object has vectors of devices. 
Again, I thought this aligned well with the organization I mentioned earlier. 
Each class has specific jobs to perform: the location class manages the different addresses and gives access to the rooms at that location, 
the room class manages access to the devices within the room, and the smart device classes change their state according to user inputs. 

# Compile Instructions
Run `g++ -std=c++17 *.cpp` in terminal.

# Run Instructions
Run `./a.out` in terminal.
