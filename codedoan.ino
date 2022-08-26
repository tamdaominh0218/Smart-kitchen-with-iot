#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "html.h" // HTML webpage contents with javascripts
#include <dht11.h>
#define BLYNK_PRINT Serial  
#include <BlynkSimpleEsp8266.h>
#define Load1 2
#define Load2 0
#define dht_pin D0
BlynkTimer timer;
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

dht11 dhtObject;

const char* ssid = "OK e";
const char* password = "tam123123";
 // blink api
 char auth[] = "5fsYnDsdVj2Pqf4yrgBsozwqib1E0IDv"; 
ESP8266WebServer server(80); //Server on port 80


 
void handle_OnConnect() {
  String s= MAIN_page;
  server.send(200, "text/html", s); 
}
void handleADC() {
 int gas = analogRead(A0);
 gas= gas*1023/100;
 float temperature, humidity, pressure, atttitude;
 dhtObject.read(dht_pin);
 Serial.print(" Humidity in %= ");
 humidity = dhtObject.humidity;
 sensors_event_t event;
 bmp.getEvent(&event);
 
  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa */
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    bmp.getTemperature(&temperature);
    Serial.print("temperature: ");
    
    Serial.print(temperature);
    Serial.println("*C");
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:"); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure)); 
    Serial.println(" m");
    Serial.println("");
  }
  
  
 //Create JSON data
 String data = "{\"gas\":\""+String(gas)+"\", \"humidity\":\""+ String(humidity) +"\", \"pressure\":\""+ String(event.pressure) +"\", \"temperature\":\""+ String(temperature) +"\"}";

 server.send(200, "text/plane", data); 
  Blynk.virtualWrite(V5, temperature);  
  Blynk.virtualWrite(V6, humidity); 
  Blynk.virtualWrite(V7, event.pressure); 
  Blynk.virtualWrite(V8, gas);  
  
}
// turn led on and redirect to main page
void handleLEDOn() {
  Serial.println("LED on");
  digitalWrite(Load1,HIGH);
  server.sendHeader("Location", "/");       
  server.send(303);                         
}


void handleLEDOff() { 
   Serial.println("LED off");
  digitalWrite(Load1,LOW);    
  server.sendHeader("Location", "/");       
  server.send(303);                         
}
void handleRelayOn() {
  Serial.println("Fan on");
  digitalWrite(Load2,HIGH);
  server.sendHeader("Location", "/");       
  server.send(303);                         
}


void handleRelayOff() {  
   Serial.println("Fan off");
  digitalWrite(Load2,LOW);
  server.sendHeader("Location", "/");       
  server.send(303);                         
}


void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}



void setup()
{
  Serial.begin(9600);
  delay(10);
 
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  //Onboard LED port Direction output
  pinMode(Load1,OUTPUT); 
  pinMode(Load2,OUTPUT); 
 
  digitalWrite(Load1,LOW);
  digitalWrite(Load2,LOW);
  Blynk.begin(auth, ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 if(!bmp.begin())
  {
   
    Serial.print(" no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  server.on("/", handle_OnConnect);    //Hien thi trang html
  server.on("/readADC", handleADC); //gọi page bằng AJAX
  server.onNotFound(handle_NotFound);
  server.on("/LEDON", handleLEDOn);
  server.on("/LEDOFF", handleLEDOff);
  server.on("/FANON", handleRelayOn);
  server.on("/FANOFF", handleRelayOff);
  server.begin();                  //Start server
  Serial.println("HTTP server started");
  
  
  
}

//==============================================================
//                     LOOP
//==============================================================
void loop()
{
  server.handleClient();          //Handle client requests
  Blynk.run();
  timer.run();
}
