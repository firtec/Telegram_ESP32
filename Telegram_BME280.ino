/*********************************************************************** 
 *  ESP32 mediante el puerto I2C recibe informacion de 
 *  un sensor bme280, mide temperatura, humedad y presión. 
 *  Los datos del sensor se envían mediante Telegram cuando
 *  se recibe el mensaje /sensor.
 *  Cuando se recibe el mensaje /led, contesta con el estado
 *  de un led conctado al Pin5 de la placa ESP32.
 *  El mensaje /encender o /apagar controlan el estado del LED
 *  
 *  Pines usados en ESP32 GPIO_21 (SDA) y GPIO_22 (SCL), pin 5 LED
 *  www.firtec.com.ar  
***********************************************************************/

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "SparkFunBME280.h"
BME280 mySensorA; // Default I2C address 0x77
BME280 mySensorB; // I2C address 0x76 (en mi caso este)


// Datos de conexión con la red WiFi
const char* ssid     = "RED_Lab_1";
const char* password = "mICroLab_2020";

float p;   
float t;  
float h;
char msg[30];

// Inicia el bot de telegram
#define BOTtoken "442837211:ABFlea9Ya-JI_SOzxiP4AGSw8FFKwhyaAAM" // El bot token generado por Botfather
#define ledPin 5

String texto;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 200; // Espera entre mensajes
long Bot_lasttime;   
bool Start = false, bandera = false;


int ledStatus = 0;
void Leer_Sensor(void);
String chat_id;
String text;
String from_name;


void handleNewMessages(int numNewMessages) {
  
  for (int i=0; i<numNewMessages; i++) {
     chat_id = String(bot.messages[i].chat_id);
     text = bot.messages[i].text;

    from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/encender") {
      digitalWrite(ledPin, HIGH);   // LED encendido
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led encendido!!", "");
      bandera = true;
    }

    if (text == "/apagar") {
      ledStatus = 0;
      digitalWrite(ledPin, LOW);    // LED apagado
      bot.sendMessage(chat_id, "Led apagado!!", "");
      bandera = true;
    }

    if (text == "/led") {
      if(ledStatus){
        bot.sendMessage(chat_id, "Led encendido", "");
        bandera = true;
      } else {
        bot.sendMessage(chat_id, "Led apagado", "");
        bandera = true;
      }
    }
    if (text == "/sensor") {	// Interroga por datos del sensor
       Leer_Sensor();		// Rutina del sensor BME280
       bandera = true;
    }
    
    if (text == "/start") {	// Mensaje al inicar el chat con el bot
      String welcome = "Benvenido al Bot Telegram con ESP32, " + from_name + ".\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
      bandera = true;
    }

    else // Si el comando no es correcto envía mensaje de error con emoticon
         // Emoticones https://apps.timwhitlock.info/emoji/tables/unicode
      {
        if(bandera == false){
        String welcome = "Comando invalido \xF0\x9F\x98\x9E";
        bot.sendSimpleMessage(chat_id, welcome, "");
        }
      }
      bandera = false;
  }
}

void setup() {
pinMode(ledPin, OUTPUT); // ledPin es salida
  delay(10);
  digitalWrite(ledPin, LOW); // inicia apagado
  
  Serial.begin(115200);
  
  // Conectando con la red Wifi:
  Serial.print("Conectando con Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    mySensorB.setI2CAddress(0x76); // Conectando con el sensor BME280
  if(mySensorB.beginI2C() == false) Serial.println("ERROR! Sensor no encontrado");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("LLegó un mensaje!!");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
      Bot_lasttime = millis();
  }
}

void Leer_Sensor(void){
  t = mySensorB.readTempC();
  snprintf (msg, 28, "Temperatura: %2.1f  \xF0\x9F\x86\x97 \n", t); 
  bot.sendMessage(chat_id, msg, "Markdown");
  
  p = mySensorB.readFloatPressure()/100;
  snprintf (msg, 25, "Presión: %3.1f  \xF0\x9F\x86\x97 \n", p);
  bot.sendMessage(chat_id, msg, "Markdown"); 
 
  h = mySensorB.readFloatHumidity();
  snprintf (msg, 28, "Humedad: %2.1f %%  \xF0\x9F\x86\x97 \n", h);  
  bot.sendMessage(chat_id, msg, "Markdown");
 
}
