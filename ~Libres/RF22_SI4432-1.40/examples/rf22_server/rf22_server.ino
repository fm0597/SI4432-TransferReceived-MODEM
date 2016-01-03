/*1.2_Write_by_ImaSoft_27.11.15
 * Воскресенье - v1.0 от 22.11.15, Начало_проекта_написания_фунции_передачи_данных_с_клиенской_части_на_сервер_для_модема_SI4432
 * Понедельник - v1.1 от 23.11.15, Обновил_модуль_библиотеки_на_RF22_SI4432-1.40_изменил_формулу_вывода_данных_уровня_сигнала_RSSI
 * Пятница     - v1.2 от 27.11.15, Ввел_переменную_максимального_значения_мощьности_передатчика
 * -----------------------------------------------------------------------------------------------------------
 * rf22_server.ino
 * -*- mode: C++ -*-
 * Example sketch showing how to create a simple messageing client
 * with the RH_RF22 class. RH_RF22 class does not provide for addressing or
 * reliability, so you should only use RH_RF22 if you do not need the higher
 * level messaging abilities.
 * It is designed to work with the other example rf22_server
 * Tested on Duemilanove, Uno with Sparkfun RFM22 wireless shield
 * Tested on Flymaple with sparkfun RFM22 wireless shield
 * Tested on ChiKit Uno32 with sparkfun RFM22 wireless shield
*/

/* Таблица_переменных_выходной_мощьности_передатчика
 * RF22_TXPOW_1DBM
 * RF22_TXPOW_2DBM
 * RF22_TXPOW_5DBM
 * RF22_TXPOW_8DBM
 * RF22_TXPOW_11DBM
 * RF22_TXPOW_14DBM
 * RF22_TXPOW_17DBM
 * RF22_TXPOW_20DBM
 * RF22_TXPOW_MAXDBM
*/

/* Таблица_видов_додуляции_и_скорости_передачи_данных
 * FSK_Rb2Fd5                                                     //< FSK, No Manchester, Rb = 2kbs,    Fd = 5kHz
 * FSK_Rb2_4Fd36                                                  //< FSK, No Manchester, Rb = 2.4kbs,  Fd = 36kHz
 * FSK_Rb4_8Fd45                                                  //< FSK, No Manchester, Rb = 4.8kbs,  Fd = 45kHz
 * FSK_Rb9_6Fd45                                                  //< FSK, No Manchester, Rb = 9.6kbs,  Fd = 45kHz
 * FSK_Rb19_2Fd9_6                                                //< FSK, No Manchester, Rb = 19.2kbs, Fd = 9.6kHz
 * FSK_Rb38_4Fd19_6                                               //< FSK, No Manchester, Rb = 38.4kbs, Fd = 19.6kHz
 * FSK_Rb57_6Fd28_8                                               //< FSK, No Manchester, Rb = 57.6kbs, Fd = 28.8kHz
 * FSK_Rb125Fd125                                                 //< FSK, No Manchester, Rb = 125kbs,  Fd = 125kHz
 * FSK_Rb_512Fd2_5                                                //< FSK, No Manchester, Rb = 512bs,  Fd = 2.5kHz, for POCSAG compatibility
 * FSK_Rb_512Fd4_5                                                //< FSK, No Manchester, Rb = 512bs,  Fd = 4.5kHz, for POCSAG compatibility
 *
 * GFSK_Rb2Fd5                                                    //< GFSK, No Manchester, Rb = 2kbs,    Fd = 5kHz
 * GFSK_Rb2_4Fd36                                                 //< GFSK, No Manchester, Rb = 2.4kbs,  Fd = 36kHz
 * GFSK_Rb4_8Fd45                                                 //< GFSK, No Manchester, Rb = 4.8kbs,  Fd = 45kHz
 * GFSK_Rb9_6Fd45                                                 //< GFSK, No Manchester, Rb = 9.6kbs,  Fd = 45kHz
 * GFSK_Rb19_2Fd9_6                                               //< GFSK, No Manchester, Rb = 19.2kbs, Fd = 9.6kHz
 * GFSK_Rb38_4Fd19_6                                              //< GFSK, No Manchester, Rb = 38.4kbs, Fd = 19.6kHz
 * GFSK_Rb57_6Fd28_8                                              //< GFSK, No Manchester, Rb = 57.6kbs, Fd = 28.8kHz
 * GFSK_Rb125Fd125                                                //< GFSK, No Manchester, Rb = 125kbs,  Fd = 125kHz
 *
 * OOK_Rb2_4Bw335                                                 //< OOK, No Manchester, Rb = 2.4kbs,  Rx Bandwidth = 335kHz
 * OOK_Rb4_8Bw335                                                 //< OOK, No Manchester, Rb = 4.8kbs,  Rx Bandwidth = 335kHz
 * OOK_Rb9_6Bw335                                                 //< OOK, No Manchester, Rb = 9.6kbs,  Rx Bandwidth = 335kHz
 * OOK_Rb19_2Bw335                                                //< OOK, No Manchester, Rb = 19.2kbs, Rx Bandwidth = 335kHz
 * OOK_Rb38_4Bw335                                                //< OOK, No Manchester, Rb = 38.4kbs, Rx Bandwidth = 335kHz
 * OOK_Rb40Bw335                                                  //< OOK, No Manchester, Rb = 40kbs,   Rx Bandwidth = 335kHz
*/


//--------------------------------------------------------------
//#include <SPI.h>
#include <RF22.h>                                            // скачанная библиотека, RadioHead https://yadi.sk/d/Impr0nuNWY2Zq
RF22 RF22_Si4432;        
//--------------------------------------------------------------

//---Дерективы_отладки--После_отдадки_все_за_комментировать-----
#define Debug_Serial                                            //Разрешить_использование_для_отладки_последавательный_порт
#define Debug_RF-DATA                                           //Вывод_в_сериал_данных_информации_зачении_потециометра
//--------------------------------------------------------------
#define LedPin            9                                    //Светодиод_который_на_плате
#define RF22_TXPOW_MAXDBM 15                                    //Значение_максимальной_мощьности_прердатчика_для_SI4432

#define RF_TIME_OUT       500                                   //Время_ожидания_приема_данных_в_милисекундах
byte PACAGE_LOOP_TX     = 0x03;                                 //Количество_повторений_пакета_TX_в_случае_неудачной_передачи_данных
float OperatingFreq     = 434.17;                               //Рабочая_частота_передатчика_в_мГц
boolean FLERRInitRHRF22 = false;                                //Флаг_ошибки_инициализации_драйвера_RH_RF22_модуля_SI4432
//--------------------------------------------------------------






//***START_DataTransferRF22*************************************
int  RF22LastRssi     = 0;                                     //Уровень_принемаемого_сигнала
//--------------------------------------------------------------
boolean DataTransferRF22(uint8_t* buf, uint8_t Sizebuf, float OperatiFreq, uint8_t PowerTransmitter, byte PACAGELOOPTX, word RFTIMEOUT) {
  //------------------------------------------------------------
  RF22_Si4432.setFrequency(OperatiFreq, 0.1);
  RF22_Si4432.setTxPower(PowerTransmitter);
  //------------------------------------------------------------
  for(byte i =0; i<PACAGELOOPTX; i++) {
    //----------------------------------------------------------
    if (!RF22_Si4432.send(buf, Sizebuf)) return false;
    RF22_Si4432.waitPacketSent();
    if (RF22_Si4432.waitAvailableTimeout(RFTIMEOUT)) {        // Now wait for a reply
      uint8_t Data[RF22_MAX_MESSAGE_LEN];
      uint8_t len = sizeof(Data);
      // Should be a reply message for us now   
      if (RF22_Si4432.recv(Data, &len))
        {
         for(byte ii =1; ii<Data[0]; ii++) {
          if (buf[ii] != Data[ii]) {return false;}
          //Serial.print("Length_Data_Buf:");Serial.println(len,DEC );
          //Serial.print("buf[");Serial.print(ii);Serial.print("]:");Serial.println(buf[ii],DEC );
          //Serial.print("Data[");Serial.print(ii);Serial.print("]:");Serial.println(Data[ii],DEC );
          //Serial.println("");           
         }
         RF22LastRssi = (int8_t)(-120 + ((RF22_Si4432.lastRssi()/2)));
	       RF22_Si4432.setModeTx();                                 //Уменьшаем_потребление(в_режиме_приема~20мА)_модуля_переводом_его_в_режим_передатчика_для_уменьшения_потребления_до~1,2мА
         return true;
        }
      else return false;
    }
    else {
      //Serial.print("waitAvailableTimeout: ERROR, RFTIMEOUT:");Serial.println(RFTIMEOUT,DEC);
    }
  }
  return false;
}
//***END_DataTransferRF22***************************************

//***START_DataSendSI4432***************************************
byte DataSendSI4432(uint8_t* buf, uint8_t Sizebuf, float OperatiFreq, uint8_t PowerTransmitter, byte PACAGELOOPTX, word RFTIMEOUT) {
  if (!FLERRInitRHRF22) { 
    if (!DataTransferRF22(buf, Sizebuf, OperatingFreq, PowerTransmitter, PACAGE_LOOP_TX, RFTIMEOUT)) {
      #ifdef Debug_RF-DATA
      Serial.println("No reply, is rf22_server: Data Send FAILED!");
      Serial.println("");
      #endif
      return 2;
    }
   else {
      #ifdef Debug_RF-DATA
      Serial.println("Sending to rf22_server");               // Send a message to rf22_server
      Serial.print("Data_Send_to_Server: ");Serial.print((char*)buf);Serial.print(" Length_Data_Buf:");Serial.println(buf[0],DEC );
      Serial.print("RSSIRead:");Serial.println(RF22LastRssi,DEC);
      Serial.println("");
      #endif
      return 0;
   }
  }
  else {
    #ifdef Debug_RF-DATA
    Serial.print("RH_RF22:");Serial.println("Init-Failed");
    Serial.print("");
    #endif    
    return 1;
  }
}
//---END_DataSendSI4432-----------------------------------------

//***START_DataReadSI4432***************************************
boolean FLDATAREADBUF         = false;                        //Флаг_чтения_данных_с_фифо_буффера 
//--------------------------------------------------------------
byte DataReadSI4432(uint8_t* buf, uint8_t len, byte RFTIMEOUT) {
  if (!FLERRInitRHRF22) { 
    if (RF22_Si4432.waitAvailableTimeout(RF_TIME_OUT)) {
      delay(100);
      if (RF22_Si4432.recv(buf, &len)) {
        //------------------------------------------------------
        #ifdef Debug_RF-DATA
        Serial.print("got request: ");
        Serial.println((char*)buf);
        Serial.print("RSSI: ");
        Serial.println((int8_t)(-120 + ((RF22_Si4432.lastRssi()/2))), DEC);
        #endif
        //------------------------------------------------------
        // Send a reply
        RF22_Si4432.send(buf, (buf[0]+1));
        RF22_Si4432.waitPacketSent();
        //------------------------------------------------------
        #ifdef Debug_RF-DATA
        Serial.println("Sent a reply");
        Serial.println("");
        #endif
        //------------------------------------------------------
        FLDATAREADBUF = true;
        digitalWrite(LedPin,LOW);
        return 0;
      }
     else {
      #ifdef Debug_RF-DATA
      Serial.println("recv failed");
      #endif
      return 2;
     }
   }
  }
  else {
    #ifdef Debug_RF-DATA
    Serial.print("RH_RF22:");Serial.println("Init-Failed");
    Serial.print("");
    #endif    
    return 1;
  }
}
//---END_DataReadSI4432-----------------------------------------







//***START_Setup************************************************
void setup() {
  //------------------------------------------------------------  
  #ifdef Debug_Serial
  Serial.begin(9600);
  #endif
  //------------------------------------------------------------    
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
  if (RF22_Si4432.init() == false) FLERRInitRHRF22 = true;   //Флаг_ошибки_инициализации_модуля_SI4432
  else {
    RF22_Si4432.setFrequency(OperatingFreq, 0.1);
    //RF22_Si4432.setModemConfig(RF22_Si4432.GFSK_Rb19_2Fd9_6);
    RF22_Si4432.setModemConfig(RF22_Si4432.OOK_Rb2_4Bw335);
    RF22_Si4432.setTxPower(RF22_TXPOW_MAXDBM);
  }
 //-------------------------------------------------------------
 pinMode(LedPin,OUTPUT);
 pinMode(LedPin-1,INPUT);
 digitalWrite(LedPin-1,HIGH);
 digitalWrite(LedPin,HIGH);
 //-------------------------------------------------------------
}
//***END_Setup**************************************************


//***START_loop*************************************************
uint8_t buf[RF22_MAX_MESSAGE_LEN];
uint8_t len                   = sizeof(buf);
//--------------------------------------------------------------
void loop() {
  //------------------------------------------------------------
  DataReadSI4432(buf, len, RF_TIME_OUT);
 //-------------------------------------------------------------
 if (FLDATAREADBUF) {
  FLDATAREADBUF = false;
  delay(300);
  digitalWrite(LedPin,HIGH);
 }
 //-------------------------------------------------------------
}
//***END_loop***************************************************

/*
//***START_loop*************************************************
void loop() {
  //------------------------------------------------------------
  char Str[] = "(Hello_World)";
  byte SizeStr = sizeof(Str);
  uint8_t buf[SizeStr+1];
  buf[0] = SizeStr;
  for(byte i =1; i<=SizeStr; i++) buf[i] = Str[i-1];
  //Serial.print("Data_Send_to_Server:");Serial.print((char*)buf);Serial.print(" length:");Serial.print(sizeof(buf));Serial.print(" length_buf[0]:");Serial.println(buf[0],DEC);
  //------------------------------------------------------------ 
  DataSendSI4432(buf, sizeof(buf), OperatingFreq, RF22_TXPOW_MAXDBM, PACAGE_LOOP_TX, RF_TIME_OUT);
  //------------------------------------------------------------ 
  
  delay(1500);  
  //------------------------------------------------------------
}
//***END_loop***************************************************
*/
