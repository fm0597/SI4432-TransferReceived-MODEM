/*
 * приёмник receiver server.
 * приёмник SI4432 Wireless Module receiver server Variable Resistor RGB // Скачать sketch.
 * Передатчик SI4432 Wireless Module transmitter client Variable Resistor RGB // Скачать sketch. https://yadi.sk/d/yF_fwOrUZFjLm
 * Самый дальнобойный Радио Передатчик SI4432 Wireless Module 433mhz Transmitter Receiver Arduino
 * https://www.youtube.com/watch?v=wPhbWEMBIsw&list=UU7aH7HVqDvwB1xNHfSl-fDw
*/

//--------------------------------------------------------------
//#include <SPI.h>
#include <RH_RF22.h>                                            // скачанная библиотека, RadioHead https://yadi.sk/d/Impr0nuNWY2Zq
RH_RF22 rf22;                                                   // Singleton instance of the radio driver.
//--------------------------------------------------------------

//---Дерективы_отладки--После_отдадки_все_за_комментировать-----
#define Debug_Serial                                            //Разрешить_использование_для_отладки_последавательный_порт
#define Debug_RF-DATA                                           //Вывод_в_сериал_данных_информации_зачении_потециометра
//--------------------------------------------------------------
#define ledPin          3                                       // Светодиод.
//--------------------------------------------------------------

//***START_Setup***********************************************
void setup() 
{ 
  //-----------------------------------------------------------
  #ifdef Debug_Serial
  Serial.begin(9600);
  #endif
  //-----------------------------------------------------------
  rf22.init();
  pinMode(ledPin, OUTPUT); 
}
//***END_Setup*************************************************

//***START_loop************************************************
void loop()
{
  //-----------------------------------------------------------
  if (rf22.available() > 0){                                    //Если обнаружены радио данные.
    uint8_t buf[RH_RF22_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf22.recv(buf, &len))analogWrite(ledPin, *buf);         // Меняем яркость светодиода.
    //--------------------------------------------------------
    #ifdef Debug_RF-DATA
    Serial.print("RF-DATA:");Serial.print(*buf);
    Serial.println("DATA_Size");Serial.println(len);
    #endif 
    //--------------------------------------------------------
  }
  //-----------------------------------------------------------
  
  //-----------------------------------------------------------
}
//***END_loop**************************************************

