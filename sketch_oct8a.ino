#include <WiFi.h>
#include <WebServer.h>


String _ssidAP = "PANKROK";
String _passwordAP = "";
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

void handle_OnConnect(){
  server.send(200, "text/html", SendHTML());
}
String SendHTML(){
  String Web="";
  Web+="<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Led</title></head><body style=\"display: flex; justify-content: center;\"><div><div style=\"border: 1px solid violet; display: inline-block; padding:20px; text-align: center;\">";
  Web+="<label>GRIO 12 Green</label><form action=\"/gpio12on\"><button type=\"submit\" style=\"width:90px; border-radius:10px; cursor: pointer\">Включить</button></form><br><form action=\"/gpio12off\"><button type=\"submit\" style\"width:90px; border-radius:10px; cursor: pointer\">Выключить</button></form>";
  Web+="</div><div style=\"border: 1px solid violet; display: inline-block; padding:20px; text-align: center;\"><label>GRIO 13 Red</label><form action=\"/gpio13on\"><button type=\"submit\" style=\"width:90px; border-radius:10px; cursor: pointer\">Включить</button></form><form action=\"/gpio13off\"><button type=\"submit\" style=\"width:90px; border-radius:10px; cursor: pointer\">Выключить</button></form>";
  Web+="</div><div style=\"border: 1px solid violet; display: inline-block; padding:20px; text-align: center;\"><label>GRIO 14 Blue</label><br><form action=\"/gpio14on\"><button type=\"submit\" style=\"width:90px; border-radius:10px; cursor: pointer\">Включить</button></form><br><form action=\"/gpio14off\"><button type=\"submit\" style=\"width:90px; border-radius:10px; cursor: pointer\">Выключить</button></form></div></div>";
 
  return Web;
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
  
  Wifi_init();
  server.on("/", handle_OnConnect);
  server.on("/gpio12on", trig12true);
  server.on("/gpio12off", trig12false);
  server.on("/gpio13on", trig13true);
  server.on("/gpio13off", trig13false);
  server.on("/gpio14on", trig14true);
  server.on("/gpio14off", trig14false);
  server.begin();
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


  if (trigger13)
  {
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(1);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);   
    delay(1);
  }
  }

  if (trigger12)
  {
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel1, dutyCycle);
    delay(1);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel1, dutyCycle);   
    delay(1);
  }
  }

  if (trigger14)
  {
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel2, dutyCycle);
    delay(1);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel2, dutyCycle);   
    delay(1);
  }
  }

}