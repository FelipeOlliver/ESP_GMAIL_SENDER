#include <ESP8266WiFi.h>
#include "Gsender.h"

#pragma region Globals
const char* ssid = "GVT-02AA";                           // Nome da Rede IWIF
const char* password = "S1EB501452";                       // Password da Rede WIFI
uint8_t connection_state = 0;                    // Conectar-se ou não ao WIFI
uint16_t reconnect_interval = 10000;             // Se não conectado, tempo de espera para conectar-se novamente
#pragma endregion Globals

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
    static uint16_t attempt = 0;
    Serial.print("Connecting to ");
    if(nSSID) {
        WiFi.begin(nSSID, nPassword);  
        Serial.println(nSSID);
    } else {
        WiFi.begin(ssid, password);
        Serial.println(ssid);
    }

    uint8_t i = 0;
    while(WiFi.status()!= WL_CONNECTED && i++ < 50)
    {
        delay(200);
        Serial.print(".");
    }
    ++attempt;
    Serial.println("");
    if(i == 51) {
        Serial.print("Connection: TIMEOUT on attempt: ");
        Serial.println(attempt);
        if(attempt % 2 == 0)
            Serial.println("Check if access point available or SSID and Password\r\n");
        return false;
    }
    Serial.println("Connection: ESTABLISHED");
    Serial.print("Got IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void Awaits()
{
    uint32_t ts = millis();
    while(!connection_state)
    {
        delay(50);
        if(millis() > (ts + reconnect_interval) && !connection_state){
            connection_state = WiFiConnect();
            ts = millis();
        }
    }
}

void setup()
{
    Serial.begin(115200);
    connection_state = WiFiConnect();
    if(!connection_state)  // Se não estiver conectado ao WIFI
        Awaits();          // Constatemente buscando conexão

    Gsender *gsender = Gsender::Instance();    
     
    String subject = "Assunto";
    if(gsender->Subject(subject)->Send("email@gmail.com", "Informação")) {
        Serial.println("Message send.");
    } else {
        Serial.print("Error sending message: ");
        Serial.println(gsender->getError());
    }
}

void loop(){}
