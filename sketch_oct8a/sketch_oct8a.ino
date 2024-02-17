#include <WiFi.h>
#include <WebServer.h>
#include <ezButton.h>

String _ssidAP = "PANKROK";
String _passwordAP = "";
String ssid = "LameLemurrrr";
String password = "SinBandit";
IPAddress gateway(192, 168, 0, 1);
IPAddress ip(192, 168, 0, 90);
IPAddress subnet(255, 255, 255, 0);
IPAddress apIP(192, 168, 0, 19);

const int freq = 5000;
const int ledChannel_red = 0;
const int ledChannel_green = 1;
const int ledChannel_blue = 2;
const int resolution = 8;

const int output_green_12 = 12;
const int output_red_13 = 13;
const int output_blue_14 = 14;
const int input23 = 23;
const int output22 = 22;

int r = 255;
int g = 255;
int b = 255;



ezButton mySwitch(17);

const int input_analog_red_34 = 34;
const int input_analog_green_39 = 39;
const int input_analog_blue_36 = 36;


//инфа с инпута в компорт

int buttonState = 0;


bool trigger12 = false;
bool trigger13 = false;
bool trigger14 = false;

int readinput34 = 0;
int readinput39 = 0;
int readinput36 = 0;

bool lastButton = LOW;
bool currentButton = LOW;
bool ledOn = false;

bool flagConnect = false;


WebServer server(80);

void Wifi_init() {
  Serial.println("ap mode in function");
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, gateway, IPAddress(255, 255, 255, 0));
  WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
}




void Wifi_connect(String ss, String pass) {
  int connect = 8;
  WiFi.disconnect();
  WiFi.begin(ss, pass);
  while ((WiFi.status() != WL_CONNECTED) &&(connect>=0)){
    delay(1000);
    Serial.print(".");
    connect--;
  }
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("AP MODE START");
  }
  else{
    Serial.println("");
    Serial.println("WiFi connected..!");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());
  }
  
}


String SendHTML() {
  String dop = "<!DOCTYPE html>\
<html>\
<head>\
	<meta charset=\"UTF-8\" />\
	<title>jscolor Sandbox</title>\
</head>\
<body>\
	 <script src=\"https://moonlightmoth.ru/static/jss.js\"></script>\
	Color: <input value=\"#3399FF80\" data-jscolor=\"{}\">\
</body>\
</html>";

  return dop;
}




String SendHTMLForConnect(){
  
  String html = "<!DOCTYPE html>\
<html>\
<head>\
  <meta charset=\"UTF-8\" />\
  <title>Connect WiFi</title>\
</head>\
  <style>\
  body >div{\
        display: flex;\
        align-items: center;\
        width: 100vw;\
        height: 100vh;\
        margin: 0;\
        padding: 0;}\
    form{\
        background-color: #b79dff;\
        width: fit-content;\
        padding: 20px;\
        border-radius: 20px;\
        margin: 0 auto;\
        display: flex;\
        flex-direction: column;\
        gap: 20px;}\
    form input{\
        padding:10px;\
        border-radius: 20px;}\
    form input.submit{\
        color: blueviolet;\
        border: 2px solid blueviolet;\
        background-color: white;}\
</style>\
<body>\
    <div>\
    <form action='setWiFi/setup'>\
        <input placeholder='login' name='login'/>\
        <input placeholder='password' name='password'/>\
        <input class='submit' type='submit' value='Connect'/>\
    </form>\
</div>\
</body>\
</html>";
return html;
  }


void handle_OnConnect() {
  server.send(200, "text/html", SendHTML());
}
void handleONNotConnect(){
  server.send(200, "text/html", SendHTMLForConnect());
  
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Wifi_init();
  Wifi_connect(ssid, password);
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Ap mode in else");
     Wifi_init();
     
  }
  server.on("/setWiFi", handleONNotConnect);
  server.on("/", handle_OnConnect);
  server.on("/setWiFi/setup", []() {
    Serial.println(server.arg("login"));
    Serial.println(server.arg("password"));
    Wifi_connect(server.arg("login"), server.arg("password"));
  });
  server.on("/rgb", []() {
    // String r = server.arg("r");
    // String g = server.arg("g");
    // String b = server.arg("b");
    // Serial.println("***");
    // Serial.println(r);
    // Serial.println(g);
    // Serial.println(b);
    String args = server.arg(0);
    
    int i1 = args.indexOf(',');
    int i2 = args.indexOf(',', i1+1);

    r = 254 - args.substring(1, i1).toInt();
    g = 254 - args.substring(i1+1, i2).toInt();
    b = 254 - args.substring(i2 + 1).toInt();

    Serial.println(r);
    Serial.println(g);
    Serial.println(b);

  });

  server.begin();
  // pinMode(input23, INPUT);
  mySwitch.setDebounceTime(50);


  pinMode(input_analog_red_34, INPUT);
  pinMode(input_analog_green_39, INPUT);
  pinMode(input_analog_blue_36, INPUT);

  pinMode(output_green_12, OUTPUT);
  pinMode(output_red_13, OUTPUT);
  pinMode(output_blue_14, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel_green, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(output_green_12, ledChannel_green);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel_red, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(output_red_13, ledChannel_red);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel_blue, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(output_blue_14, ledChannel_blue);
}


void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

  readinput34 = analogRead(input_analog_red_34) * 255 / 4096 + 1;
  readinput39 = analogRead(input_analog_green_39) * 255 / 4096 + 1;
  readinput36 = analogRead(input_analog_blue_36) * 255 / 4096 + 1;

  // Serial.print("input red: ");
  // Serial.println(readinput34);

  // Serial.print("input green: ");
  // Serial.println(readinput39);

  // Serial.print("input blue: ");
  // Serial.println(readinput36);


  //  buttonState = digitalRead(input23);
  mySwitch.loop();

  // currentButton = debounse(lastButton);
  // if (lastButton == LOW && currentButton == HIGH) {
  //   ledOn = !ledOn;
  // }
  // lastButton = currentButton;
  // digitalWrite(ledPin, ledOn);
  int state = mySwitch.getState();
  if (state == HIGH) {
    // Serial.println("ManualMode");
    ledcWrite(ledChannel_red, readinput34);
    ledcWrite(ledChannel_green, readinput39);
    ledcWrite(ledChannel_blue, readinput36);
  } else {
    ledcWrite(ledChannel_red, r);
    ledcWrite(ledChannel_green, g);
    ledcWrite(ledChannel_blue, b);
    // Serial.println("NetworkMode");
  }

  //  if (buttonState== HIGH){
  //    Serial.println("ManualMode");
  //   ledcWrite(ledChannel_red, readinput34);
  //   ledcWrite(ledChannel_green, readinput39);
  //   ledcWrite(ledChannel_blue, readinput36);

  //  }
  //  else
  //  {
  //   ledcWrite(ledChannel_red, 128);
  //   ledcWrite(ledChannel_green, 128);
  //   ledcWrite(ledChannel_blue, 128);
  //    Serial.println("NetworkMode");
  //  }

  //считывание информации с 25-27 и вывод в ком
}
