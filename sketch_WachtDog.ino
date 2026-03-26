#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "DePaula";
const char* senha = "12345678";

const char* server = "https://jsonplaceholder.typicode.com/todos/1";

int led_off = 19;
int led_on = 18;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(led_off, OUTPUT);
  pinMode(led_on, OUTPUT);

  WiFi.begin(ssid, senha);
  if(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }else{
    Serial.print("\n conectou");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()==WL_CONNECTED){
    WiFiClientSecure *client = new WiFiClientSecure;
    digitalWrite(led_on, HIGH);
    digitalWrite(led_off, LOW);
    if(client){
      client-> setInsecure();
      HTTPClient https;
      Serial.print("inicio da requisição... \n");
      if(https.begin(*client, server)){
        int httpCode = https.GET();
        if(httpCode > 0){
          Serial.printf("Codigo resposta: %d\n", httpCode);
          if(httpCode == HTTP_CODE_OK){

            String payload = https.getString();
            Serial.println("Conteudo recebido:");
            Serial.print(payload);
          }
        }else{
 
          Serial.printf("falha de requisição, erro %s \n", https.errorToString(httpCode).c_str());
        }
      }else{
        delete client;
      }
    }
    }else{
      WiFi.reconnect();
      digitalWrite(led_off, HIGH);
      digitalWrite(led_on, LOW);

    }
    delay(10000);
  }
