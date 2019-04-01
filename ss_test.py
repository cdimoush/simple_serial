#!/usr/bin/env python
import serial
import time
from simple_serial import SimpleSerial

port = '/dev/ttyUSB0'
brate = '9600'

def realcallback(topic, msg):
	print topic 
	print msg

	s.publish("add", msg)

if __name__ == "__main__":
	cb  = realcallback
	s = SimpleSerial(port, brate, cb)

	s.publish("add", 1)

	while True:
		s.spin()
		time.sleep(0.01)

