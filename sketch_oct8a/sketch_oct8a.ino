#include <WiFi.h>
#include <WebServer.h>



String _ssidAP = "PANKROK";
String _passwordAP = "";
String ssid = "Wi-Fi";  
String password = "password";
IPAddress gateway(192,168,1,1);
IPAddress ip(192,168,1,90);
IPAddress subnet (255,255,255,0);
IPAddress apIP(192,168,1,19);

const int freq = 5000;
const int ledChannel = 0;
const int ledChannel1 = 1;
const int ledChannel2 = 2;
const int resolution = 8;

const int output12 = 12;
const int output13 = 13;
const int output14 = 14;
const int input23 = 23;
const int output22 = 22;


int buttonState = 0;


bool trigger12 = false;
bool trigger13 = false;
bool trigger14 = false;


WebServer server(80);

void Wifi_init(){
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, gateway, IPAddress(255, 255, 255, 0));
  WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
}




void Wifi_connect(String ss, String pass){
  WiFi.disconnect();
  WiFi.begin(ss, pass);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
}


String SendHTML(){
  String Web="";
  Web+="<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Led</title></head><body style=\"display: flex; justify-content: center;\">";
  Web+="<div><div style=\"border: 1px solid violet; display: inline-block; padding:20px; text-align: center;\">";
  Web+="<form action='/setWifi'> <input type='text' name='ssid'><input type='password' name='password'><input type='submit' value='send'></form>";
  Web+="</div></div></body></html>";
 // Web+="<label>GRIO 12 Green</label><form action=\"/gpio12on\"><button type=\"submit\" style=\"width:90px; border-radius:10px; cursor: pointer\">Включить</button></form><br><form action=\"/gpio12off\"><button type=\"submit\" style\"width:90px; border-radius:10px; cursor: pointer\">Выключить</button></form>";
  //Web+="</div><div style=\"border: 1px solid violet; display: inline-block; padding:20px; text-align: center;\"><label>GRIO 13 Red</label><form action=\"/gpio13on\"><button type=\"submit\" style=\"width:90px; border-radius:10px; cursor: pointer\">Включить</button></form><form action=\"/gpio13off\"><button type=\"submit\" style=\"width:90px; border-radius:10px; cursor: pointer\">Выключить</button></form>";
  //Web+="</div><div style=\"border: 1px solid violet; display: inline-block; padding:20px; text-align: center;\"><label>GRIO 14 Blue</label><br><form action=\"/gpio14on\"><button type=\"submit\" style=\"width:90px; border-radius:10px; cursor: pointer\">Включить</button></form><br><form action=\"/gpio14off\"><button type=\"submit\" style=\"width:90px; border-radius:10px; cursor: pointer\">Выключить</button></form></div></div>";
  
 
  return Web;
}


void handle_OnConnect(){
  server.send(200, "text/html", SendHTML());
}


String trig12true()
{
  
  trigger12 = true;
  return "<html>Cool rep</html>";
}
String trig12false()
{
  trigger12 = false;
  return "<html>Cool rep</html>";
}


String trig13true()
{
  trigger13 = true;
  return "<html>Cool rep</html>";
}
String trig13false()
{
  trigger13 = false;
  return "<html>Cool rep</html>";
}


String trig14true()
{
  trigger14 = true;
  return "<html>Cool rep</html>";
}
String trig14false()
{
  trigger14 = false;
  return "<html>Cool rep</html>";
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wifi_init();
  server.on("/", handle_OnConnect);
  server.on("/gpio12on", trig12true);
  server.on("/gpio12off", trig12false);
  server.on("/gpio13on", trig13true);
  server.on("/gpio13off", trig13false);
  server.on("/gpio14on", trig14true);
  server.on("/gpio14off", trig14false);
   server.on("/setWiFi", [](){
    Wifi_connect(server.arg("ssid"),server.arg("password"));});
  
  server.begin();
  pinMode(input23, INPUT);
  pinMode(output22, OUTPUT);

  
  
 // pinMode(output12, OUTPUT);
//   pinMode(output13, OUTPUT);
//   pinMode(output14, OUTPUT);

// //  digitalWrite(output12, LOW);
//   digitalWrite(output13, LOW);
//   digitalWrite(output14, LOW);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(output12, ledChannel);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(output13, ledChannel1);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(output14, ledChannel2);

 


  
}





void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();


 
  


//  if (trigger13)
//  {
//    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
//    // changing the LED brightness with PWM
//    ledcWrite(ledChannel, dutyCycle);
//    delay(1);
//  }
//
//  // decrease the LED brightness
//  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
//    // changing the LED brightness with PWM
//    ledcWrite(ledChannel, dutyCycle);   
//    delay(1);
//  }
//  }
//
//  if (trigger12)
//  {
//    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
//    // changing the LED brightness with PWM
//    ledcWrite(ledChannel1, dutyCycle);
//    delay(1);
//  }
//
//  // decrease the LED brightness
//  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
//    // changing the LED brightness with PWM
//    ledcWrite(ledChannel1, dutyCycle);   
//    delay(1);
//  }
//  }
//
//  if (trigger14)
//  {
//    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
//    // changing the LED brightness with PWM
//    ledcWrite(ledChannel2, dutyCycle);
//    delay(1);
//  }
//
//  // decrease the LED brightness
//  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
//    // changing the LED brightness with PWM
//    ledcWrite(ledChannel2, dutyCycle);   
//    delay(1);
//  }
//  }



  buttonState = digitalRead(input23);
  if (buttonState== HIGH){
    Serial.println("HEIGy");
   ledcWrite(ledChannel, 0);
    ledcWrite(ledChannel1, 0);
    ledcWrite(ledChannel2, 0);
    digitalWrite(output22,HIGH);
    
  }
  else{
     ledcWrite(ledChannel, 255);
    ledcWrite(ledChannel2, 255);
    ledcWrite(ledChannel1, 255);
    Serial.println("LET ME DOEN SLOWLY");
    digitalWrite(output22,LOW);
  }




  

}
