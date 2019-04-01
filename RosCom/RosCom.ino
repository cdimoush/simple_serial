#include <simple_serial.h>

SimpleSerial ser;

void adder(int msg)
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
  delay(100);                       // wait for half a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off 
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
  delay(100);                       // wait for half a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off 
  delay(100);
  
  int c = msg + msg;
  String msg_out = String(c);
  ser.publish("result", msg_out);
}

void setup() 
{
  Serial.begin(9600);
  ser.subscribe("add", "int", adder);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  ser.spin(); 
  delay(10);
}





