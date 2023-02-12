#include "heltec.h"
#define BAND    915E6  
String packSize = "--";
String packet ;
/* Funciones */
void LoRaDataPrint();
void cbk(int packetSize);
/*Imprime Dtaos y Tamaño de Paquete*/
void LoRaDataPrint(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0 , 1 , "Recibiendo "+ packSize + " bytes");
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(1, 20, packet);
  Heltec.display->display();
}
/* Recibe los datoasa traves de LoRa y las almacena en la variable Packet.*/
void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) {
    packet += (char) LoRa.read(); 
  }
  LoRaDataPrint();
}

void setup()
{
  pinMode(LED,OUTPUT); //inicializa o LED
  
  Serial.begin(9600);
  Heltec.begin(true /*Habilita o Display*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Habilita debug Serial*/, true /*Habilita o PABOOST*/, BAND /*long BAND*/);
 
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
  Heltec.display->drawString(10, 5, "Iniciado con Exito!");
  Heltec.display->drawString(10, 30, "Esperando Datos...");
  Heltec.display->display();
  Serial.println("Iniciado con Exito!");
  Serial.println("Esperando Datos...");
  delay(1000);
  
  LoRa.receive(); //
}

void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) { 
    cbk(packetSize);
    digitalWrite(LED, HIGH);   
    delay(500);                
    digitalWrite(LED, LOW);    
    delay(500);                
    Serial.print(packet); 
  }
  delay(10);
}
