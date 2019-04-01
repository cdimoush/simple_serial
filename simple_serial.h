#ifndef simple_serial_h
#define simple_serial_h

#include <Arduino.h>

class SimpleSerial
{
public:
	SimpleSerial(){}

	void publish(String topic_out, String msg_out);
	void subscribe(String topic, String msg_type, void (*callback)());
	void spin();

private:
	template <class N>
	struct callback_pointer
	{
	    void(*cbPointer)(N);
	};

	struct subscriber_object
	{
		String topic;
		String msg_type;
		void *callback;
	};

	void executeCallback(String msg, String msg_type, void (*callback)());
	void parseDataIn();

	struct subscriber_object _callback_map[5];
	int _cb_index = 0;

	const byte _buff_size = 40;
	char _input_buffer[40];
	const char _read_mark_start = '<';
	const char _read_mark_end = '>';
	byte _bytes_read = 0;
	boolean _read_in_progress = false;
};
#endif

