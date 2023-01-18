#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Ultrasonic.h>
#include <ArduinoJson.h>

//Inserir as credenciais de conexão wifi 
const char* ssid = "deassis";
const char* password = "100senha";

//Inicializa o BOT do telegram
#define BOTtoken "1610042084:AAGfozxSBAeWCGQdKi8H1_6FIdnnPIWlnMA"
#define CHAT_ID "1025346506"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


bool presencaDetectado = false;
Ultrasonic ultrassom (13, 12); //define onde está ligado o trig(13) e o echo(12)

long distancia;


void setup() {

  Serial.begin(9600);
  
  Serial.print("Conectando ao Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); //adiciona certificado root para api.telegram.org

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("Wifi Conectado");
  Serial.print("Endereço IP");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot inicializado", "");
}

void loop() {

  distancia = ultrassom.Ranging(CM); //Retorna a distancia em centimetros
  /////Este trecho é somente para verificação da distancia/////////////
    //Serial.print(distancia);
    //Serial.println("cm");
    //delay(100);
  ///////////////////
  detectaMovimento(distancia);
  if(presencaDetectado){
    bot.sendMessage(CHAT_ID, "Movimento detectado!!!", "");
    Serial.println("Movimento detectado");
    presencaDetectado = false;
   }
}

void detectaMovimento(const long dist){
  if(dist <= 20){
    presencaDetectado = true;
  }
}
