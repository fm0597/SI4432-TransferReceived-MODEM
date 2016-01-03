// Передатчик transmitter client
// Передатчик SI4432 Wireless Module transmitter client Variable Resistor RGB // Скачать sketch.
// приёмник SI4432 Wireless Module receiver server Variable Resistor RGB // Скачать sketch.
// Самый дальнобойный Радио Передатчик SI4432 Wireless Module 433mhz Transmitter Receiver Arduino.
// https://www.youtube.com/watch?v=wPhbWEMBIsw&list=UU7aH7HVqDvwB1xNHfSl-fDw
#include <SPI.h>
#include <RH_RF22.h> // Скачанная библиотека, RadioHead https://yadi.sk/d/Impr0nuNWY2Zq
RH_RF22 rf22; // Singleton instance of the radio driver.
void setup() 
{ 
  rf22.init(); 
}
void loop()
{
  delay(30); // Защита от скачков напряжения тока.
  int q = analogRead(A0); // Чтоб не засорять радио эфир, отправим данные только, если обнаружим изменения на PIN (A0).
  delay(10); // Пауза для обнаружения изменения на  PIN (A0).
  int VariableResistor = analogRead(A0); // Снова фиксируем значение с переменного резистора, для сравнения.
  if (VariableResistor >= (q+2) || VariableResistor <= (q-2)) // Только если обнаружим, что повернули ручку переменного резистора.    
  {
    VariableResistor = map(VariableResistor, 0, 1023, 0, 254); // Конвертируем значения с 1023 в 254, для светодиода.
    rf22.send((uint8_t*)&VariableResistor, sizeof(VariableResistor)); // Отправляем значения на приёмник/receiver/server SI4432.
  }
}







//  Serial.begin(9600);
//  Serial.println(VariableResistor);  
// if (VariableResistor != q)

