// ���������� transmitter client
// ���������� SI4432 Wireless Module transmitter client Variable Resistor RGB // ������� sketch.
// ������� SI4432 Wireless Module receiver server Variable Resistor RGB // ������� sketch.
// ����� ������������ ����� ���������� SI4432 Wireless Module 433mhz Transmitter Receiver Arduino.
// https://www.youtube.com/watch?v=wPhbWEMBIsw&list=UU7aH7HVqDvwB1xNHfSl-fDw
#include <SPI.h>
#include <RH_RF22.h> // ��������� ����������, RadioHead https://yadi.sk/d/Impr0nuNWY2Zq
RH_RF22 rf22; // Singleton instance of the radio driver.
void setup() 
{ 
  rf22.init(); 
}
void loop()
{
  delay(30); // ������ �� ������� ���������� ����.
  int q = analogRead(A0); // ���� �� �������� ����� ����, �������� ������ ������, ���� ��������� ��������� �� PIN (A0).
  delay(10); // ����� ��� ����������� ��������� ��  PIN (A0).
  int VariableResistor = analogRead(A0); // ����� ��������� �������� � ����������� ���������, ��� ���������.
  if (VariableResistor >= (q+2) || VariableResistor <= (q-2)) // ������ ���� ���������, ��� ��������� ����� ����������� ���������.    
  {
    VariableResistor = map(VariableResistor, 0, 1023, 0, 254); // ������������ �������� � 1023 � 254, ��� ����������.
    rf22.send((uint8_t*)&VariableResistor, sizeof(VariableResistor)); // ���������� �������� �� �������/receiver/server SI4432.
  }
}







//  Serial.begin(9600);
//  Serial.println(VariableResistor);  
// if (VariableResistor != q)

