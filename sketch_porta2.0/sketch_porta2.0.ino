#include <ArduinoJson.h>

#include <SPI.h>
#include <MFRC522.h>
#include <HTTPClient.h> 
#define SS_PIN 21
#define RST_PIN 22
#define RELE_PIN 32
#define BUTTON_PIN 27
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

String id[30]; //VETOR DE ID
int numeroDeCadastrados = 0; 
char st[20];

#if defined(ESP8266)
#include <ESP8266WiFi.h>  //ESP8266 Core WiFi Library         
#else
#include <WiFi.h>      //ESP32 Core WiFi Library    
#endif
 
#if defined(ESP8266)
#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal
#else
#include <WebServer.h> //Local WebServer used to serve the configuration portal ( https://github.com/zhouhan0126/WebServer-esp32 )
#endif
 
#include <DNSServer.h> //Local DNS Server used for redirecting all requests to the configuration portal ( https://github.com/zhouhan0126/DNSServer---esp32 )
#include <WiFiManager.h>   // WiFi Configuration Magic ( https://github.com/zhouhan0126/WIFIMANAGER-ESP32 ) >> https://github.com/tzapu/WiFiManager (ORIGINAL)
#include <PubSubClient.h>
 
const char* mqttServer = "m16.cloudmqtt.com";
const int mqttPort = 17990;
const char* mqttUser = "zzzzrxve";
const char* mqttPassword = "eUo0gAhjtyPe";

const int PIN_AP = 2;
WiFiClient espClient;
PubSubClient client(espClient);

class Pessoa{
  String Nome;
  String key;
  bool dias[7];
  };
  
void setup() {
  Serial.begin(9600);
  Serial.print("Inicializando...");
  pinMode(PIN_AP, INPUT);
  //declaração do objeto wifiManager
  WiFiManager wifiManager;
 
  //utilizando esse comando, as configurações são apagadas da memória
  //caso tiver salvo alguma rede para conectar automaticamente, ela é apagada.
//  wifiManager.resetSettings();
 
//callback para quando entra em modo de configuração AP
  wifiManager.setAPCallback(configModeCallback); 
//callback para quando se conecta em uma rede, ou seja, quando passa a trabalhar em modo estação
  wifiManager.setSaveConfigCallback(saveConfigCallback); 

  Serial.print("Configure o Wi-Fi...");
//cria uma rede de nome ESP_AP com senha 12345678
  wifiManager.autoConnect("ESP_AP", "12345678"); 

  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
  // caso queira subscrever algo no servidor mqtt
  //client.subscribe("LED", 1);
  client.setCallback(retorno);
 
}

void loop() 
{
   if ( digitalRead(PIN_AP) == HIGH ) 
   {
      WiFiManager wifiManager;
      if(!wifiManager.startConfigPortal("ESP_AP", "12345678") )
      {
        Serial.println("Falha ao conectar");
        delay(2000);
        ESP.restart();
      }
   }
   
   if(digitalRead(BUTTON_PIN)){
      Serial.println("LIBERADO!");
      liberar();
    }
    else{
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) 
        {
          return;
        }
        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial()) 
        {
          return;
        }
        //Mostra UID na serial
        Serial.println();
        Serial.print("UID da tag :");
        String conteudo= "";
        byte letra;
        for (byte i = 0; i < mfrc522.uid.size; i++) 
        {
           Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
           Serial.print(mfrc522.uid.uidByte[i], HEX);
           conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
           conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        Serial.println();
        Serial.print("Mensagem : ");
        conteudo.toUpperCase();
        
        if (conteudo.substring(1) == "26 50 F6 E8") //UID 1 - Chaveiro
        {
          //Serial.println("Ola Inaldo !");
          //Serial.println("Acesso Liberado");
          //Serial.println();
          //liberar();
          Serial.print("Modo Cadastramento");
          delay(2000);
          cadastrar();
          delay(3000);
        }
       
        else if (conteudo.substring(1) == "4A 1E 00 29") //UID 2 - Cartao
        {
          Serial.println("Ola Alexandre !");
          Serial.println("Acesso Liberado");
          Serial.println();
          liberar();
          delay(3000);
        }
      
        
        else if (conteudo.substring(1) == "36 C5 A0 59") //UID 2 - Cartao
        {
          Serial.println("Ola Cícero !");
          Serial.println("Acesso Liberado");
          Serial.println();
          liberar();
          delay(3000);
        }
      
       else{
        for(int i=0; i<numeroDeCadastrados; i++){
      
            if (conteudo.substring(1) == id[i])
        {
          Serial.println("Ola Usuário !");
          Serial.println("Acesso Liberado");
          Serial.println();
          liberar();
          delay(3000);
          break;
        }
        
        }
       }
}
   client.loop();
}

//callback que indica que o ESP entrou no modo AP
void configModeCallback (WiFiManager *myWiFiManager) {  
//  Serial.println("Entered config mode");
  Serial.println("Entrou no modo de configuração");
  Serial.println(WiFi.softAPIP()); //imprime o IP do AP
  Serial.println(myWiFiManager->getConfigPortalSSID()); //imprime o SSID criado da rede
}

//callback que indica que salvamos uma nova rede para se conectar (modo estação)
void saveConfigCallback () {
  Serial.println("Configuração salva");
}



//Função que será chamada ao receber mensagem do servidor MQTT
void retorno(char* topico, byte* mensagem, unsigned int tamanho) {
  //Convertendo a mensagem recebida para string
  mensagem[tamanho] = '\0';
  String strMensagem = String((char*)mensagem);
  strMensagem.toLowerCase();
  //float f = s.toFloat();
  
 Serial.println(strMensagem);

 if( strMensagem == "abrir"){
  liberar();
  }
}

void cadastrar()
{
  delay(1000);
  while( ! mfrc522.PICC_IsNewCardPresent()) 
  {
      delay(100);
  }
  while( ! mfrc522.PICC_ReadCardSerial()) 
  {

    delay(100);
  }
  delay(500);
  String conteudo= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.println();
  conteudo.toUpperCase();

  if(buscarId(conteudo.substring(1))){
  Serial.println("TAG CADASTRADA: ");
  Serial.println(conteudo.substring(1));
  id[numeroDeCadastrados] = conteudo.substring(1);
  numeroDeCadastrados++;
  }
  
  else{
    Serial.println("TAG JÁ CADASTRADA!");
  }
  
  delay(2000);
} 


void liberar()
{
  digitalWrite(RELE_PIN, HIGH);
  delay(2500);
  atualizar();
  digitalWrite(RELE_PIN, LOW);
}

bool buscarId(String conteudo){
      for(int i=0; i<numeroDeCadastrados; i++){
          if(id[i] == conteudo){
            return false;
            }
        }
    return true;
}

void atualizar(){
      
    HTTPClient http;
    http.begin("http://jsonplaceholder.typicode.com/comments?id=10"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(payload);

  Serial.println(payload.length());
        
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
  }
