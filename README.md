# simple_serial

Attempt to make a more dependable bare bone version of rosserial.

This package contains a serial comunication library for both arduino and ros. Data is sent between the two in the formate of < topic : msg >. The arduino code allows for the creation of custom subscribers and unique callbacks. More work needs to be done to allow for a larger range of message variable types and mutiple variable messages. The ros code is in python and uses pyserial. All data in is returned to a general subscriber.

In order to use this package the simple_serial.cpp and simple_serial.h must be placed inside the arduino library folder.

roscom and ss_test are example scripts