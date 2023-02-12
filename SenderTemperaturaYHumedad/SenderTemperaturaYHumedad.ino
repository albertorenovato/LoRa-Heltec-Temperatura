#include "heltec.h"
#include "DHTesp.h"
#define BAND    915E6  
DHTesp dht;
String packet ;
float currentTemp;
float currentHumidity;
/* Funciones */
void getTemp();
void getHum();
void sendPacket();

/*Leer Temperatura*/
void getTemp()
{
  float temperatura = dht.getTemperature();
 
  if (temperatura != currentTemp) { //Verifica se cambia la temperatura
    currentTemp = temperatura;
    digitalWrite(LED, HIGH);   
    delay(500);                
    digitalWrite(LED, LOW);    
    delay(500);                
  }
  delay(500);
}

/*Leer Humedad*/
void getHum()
{
  float humedad = dht.getHumidity();
 
  if (humedad != currentHumidity) { //Verifica si cambia la humedad
    currentHumidity = humedad;
    digitalWrite(LED, HIGH);   
    delay(500);               
    digitalWrite(LED, LOW);    
    delay(500);                
  }
  delay(500);
}
/*Enviar La Temperatura y Humedad*/
void sendPacket()
{
  LoRa.beginPacket();
  LoRa.print("Temp: ");
  LoRa.print(currentTemp);

  LoRa.print("Hum: ");
  LoRa.print(currentHumidity);
  LoRa.endPacket();
}

void setup()
{
  pinMode(LED,OUTPUT); 
  
  Heltec.begin(true /*Habilita o Display*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Habilita debug Serial*/, true /*Habilita o PABOOST*/, BAND /*long BAND*/);
 
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->clear();
  Heltec.display->drawString(33, 5, "Iniciado");
  Heltec.display->display();
  delay(500);
  
  dht.setup(13, DHTesp::DHT11); 
   
  currentTemp = dht.getTemperature();
  currentHumidity = dht.getHumidity();
  
}
void loop()
{
  getTemp(); //Leer temperatura
  getHum();  //Leer humedad
  
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_16);
  
  Heltec.display->drawString(30, 5, "Enviando");
  Heltec.display->drawString(10, 30, (String)currentTemp);
  Heltec.display->drawString(50, 30, "°C");
  Heltec.display->drawString(78, 30, (String)currentHumidity);
  Heltec.display->display();
  sendPacket(); 
}
