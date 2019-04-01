#!/usr/bin/env python
import serial
import time

class SimpleSerial:
	_read_in_progress = False
	_read_mark_start = "<"
	_read_mark_end = ">"
	_input_buffer = ""

	def __init__(self, port, rate, cb):
		self.subscriber_cb = cb
		self._ser = serial.Serial(port=port, baudrate=rate, timeout=1)
		empty = self._ser.readline()
		self._ser.flushOutput()
		self._ser.flushInput()
		time.sleep(1.5)
		
	def publish(self, topic, msg):
		msg = "<" + topic + ":" + str(msg) + ">"
		self._ser.write(msg)

	def parseDataIn(self, s):
		split = s.index(":")
		topic = s[0:split]
		msg = s[split + 1:]

		self.subscriber_cb(topic, msg)

	def spin(self):
		if self._ser.inWaiting() != 0:
			x = self._ser.read().decode("utf-8")
			if (x == self._read_mark_end):
				
				self.parseDataIn(self._input_buffer)

				self._input_buffer = ""
				self._read_in_progress = False
				
			elif(self._read_in_progress):
				self._input_buffer += x
			
			elif(x == self._read_mark_start):
				self._read_in_progress = True

				

