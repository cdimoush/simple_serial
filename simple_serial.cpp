#include <Arduino.h>
#include "simple_serial.h"

void SimpleSerial::publish(String topic_out, String msg_out)
{
	Serial.println("<" + topic_out + ":" + msg_out + ">");
}

//Create Subscriber
void SimpleSerial::subscribe(String topic, String msg_type, void (*callback)())
{
	//Fill subscriber_object struct with topic, msg_type, and callback pointer

	_callback_map[_cb_index].topic = topic;
	_callback_map[_cb_index].msg_type = msg_type;
	_callback_map[_cb_index].callback = *callback;
	_cb_index ++;
}

//Call callback function... send the MSG recieved 
void SimpleSerial::executeCallback(String msg, String msg_type, void(*callback)())
{
	//Data and callback pointer must be modified for correct data type....
	//Use ifs with msg_type
	//If a custom msg is needed it should be added here
	Serial.println("Running executeCallback");
	if (msg_type == "int")
	{
		struct callback_pointer<int> cb;
		cb.cbPointer = *callback;
		int msg_out = msg.toInt();	
		cb.cbPointer(msg_out);
	}
	else
	{
		struct callback_pointer<String> cb;	
		cb.cbPointer = *callback;
		cb.cbPointer(msg);
	}
}

//Spin... Look Topics and Messages serial port then match topics to subscribers
void SimpleSerial::spin()
{

	//Loop Function

	//Check Buffer for input data
	if(Serial.available() > 0) 
	{
		//Read oldest char in Buffer
		char x = Serial.read();

		// NOTE: the order of these IF clauses is significant

		//If input char marks the end of the data input message
		if (x == _read_mark_end) 
		{
			_read_in_progress = false;
			//Reset the input buffer string and send data message to be parsed
			_input_buffer[_bytes_read] = 0;
			parseDataIn();
		}

		//If the spin is currently receiving an input message
		if(_read_in_progress) 
		{	
			//Add the char to the end of the buffer and increase the buffer index
			_input_buffer[_bytes_read] = x;
			_bytes_read ++;
			if (_bytes_read == _buff_size) 
			{
				_bytes_read = _buff_size - 1;
			}
		}

		//If input char marks the beginging of an input message
		if (x == _read_mark_start)
		{ 
			_bytes_read = 0; 
			_read_in_progress = true;
		}
	}

}

void SimpleSerial::parseDataIn()
{
	char * strtok_index;
	strtok_index = strtok(_input_buffer, ":");
	char topic[_buff_size] = {0};
	char msg[_buff_size] = {0};
	strcpy(topic, strtok_index);
	strtok_index = strtok(NULL, ":");
	strcpy(msg, strtok_index);

	Serial.print("Topic: ");
	Serial.println(topic);
	Serial.print("Msg: ");
	Serial.println(msg);
	for (int i=0; i<_cb_index + 1; i++)
	{
		Serial.print("Trying Topic: ");
		Serial.println( _callback_map[i].topic);
		if (strcmp(topic, _callback_map[i].topic.c_str()) == 0)
		{
			Serial.println("Pointing to Callback");
			SimpleSerial::executeCallback(msg, _callback_map[i].msg_type, _callback_map[i].callback);
			return ;
		}
	}
}