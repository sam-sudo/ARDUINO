
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>



IPAddress ip(192,168,1,135);
IPAddress gateway(192,168,1,1);
IPAddress subnet (255,255,255,0);

const char* ssid = "*****";
const char* password = "***";


WiFiServer server(80);

#define D0 2 //nombrar los pines
#define D4 16


//---------------------------------------------------------------------------------------------



void setup() {
  // put your setup code here, to run once:

  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);

  
Serial.begin(9600);
pinMode(D4, OUTPUT);
digitalWrite(D4, HIGH);

Serial.println("Conecting to ");
Serial.println(ssid);

WiFi.begin(ssid,password); //La conexion con la red
Serial.printf("MACAddress = %s\n", WiFi.softAPmacAddress ().c_str());
while(WiFi.status() != WL_CONNECTED) {

  delay(500);
  
  Serial.print(".");
  }
  Serial.println("\nWiFi connected");

server.begin();
Serial.println("Server Started");

Serial.print("Use this URL to connect: ");
Serial.print("https://");
Serial.println(WiFi.localIP());
Serial.println("/\n");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  WiFiClient client = server.available();
  if(!client){
    return;
    
    }
  
  while(!client.available()){
    delay(1);  
    }
  
  String request = client.readStringUntil('\r');
  if(request.indexOf("/favicon")== -1){
    Serial.println("New clietn");
    Serial.println(request);
  
  }
  client.flush();

  int value = LOW;
  String value2 = "";
  
  if(request.indexOf("/LED=ON")!= -1){

    digitalWrite(D4,HIGH);
    value = HIGH;
    
    }

  if(request.indexOf("/LED=OFF")!= -1){
    digitalWrite(D4,LOW);
    value = LOW;
   }

  if(request.indexOf("/LED=DELAY")!= -1){
    value2 = "Ramdom";
    for(int i = 0;i<4;i++){
      digitalWrite(D4,HIGH);
      delay(2000);
      digitalWrite(D4,LOW);
      delay(2000);
      
      //if(request.indexOf("/LED=OFF")!= -1){break;}
       
      }
      
    }

 // client.println("HTTP/1.1 200 OK");
//  client.println("Content-Type: text/html");
 // client.println("");
 // client.println("<!DOCTYPE HTML>");
 // client.println("<html>");

  client.print("Led pin is now: ");

  if(value == HIGH){
      client.println("On");
    }if(value2.equals("Ramdom")){
      client.println("Ramdom");
    }else{
        client.print("Off");
      }
  
   
 // client.println("<br><br>");
 // client.println("<a href=\"/LED=ON\"\"><BUTTON>Turn On </button><a/a>");
  //client.println("<a href=\"/LED=OFF\"\"><BUTTON>Turn Off </button><a/a>");
  //client.println("<a href=\"/LED=DELAY\"\"><BUTTON>Turn Ramdom </button><a/a>");
 // client.println("</html>");

delay(1);

if(request.indexOf("/favicon") == -1){
    Serial.println("Client disconnected\n");
  }





  
}
