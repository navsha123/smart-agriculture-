#define BLYNK_TEMPLATE_ID "TMPLm22-DcDd"
#define BLYNK_DEVICE_NAME "Smart Agriculture"
#define BLYNK_AUTH_TOKEN "ge5NtTf4UAlzSb77XIfo_s9NsbrWfPQU"
 
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
  
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>


char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "puneeth";
char pass[] = "01234567";

int buzzer=2;

#define DHT11_PIN 5
//DHT11 data pin to D4
DHT dht(DHT11_PIN,DHT11);

#define ledpin 15
#define pump 19 
 
BlynkTimer timer; 
#include <LiquidCrystal_I2C.h> 

#define soil 18
#define light 32

 
//String long_lat;
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
 
void setup()
{
  //Init serial
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  
  //Blynk.begin(auth, ssid, pass);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
    lcd.begin(16, 2);
    pinMode(buzzer,OUTPUT);
        pinMode(pump,OUTPUT);
            pinMode(ledpin,OUTPUT);
    pinMode(soil,INPUT);
    pinMode(light,INPUT); 
    dht.begin(); 
}


void loop()
{
 
Blynk.run();
timer.run();
 
   
    float h = dht.readHumidity();
    float t = dht.readTemperature();         
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
 
   lcd.setCursor(0,0);
   lcd.print("T:");
   lcd.print(t);

   lcd.setCursor(7,0);
   lcd.print("H:");
   lcd.print(h);

    Blynk.virtualWrite(V2,t);
    Blynk.virtualWrite(V3,h);

   int soilval=digitalRead(soil);
   if(soilval==1)
   {
   Blynk.virtualWrite(V0,"NO SOIL MOISTURE DETECTED");
   lcd.setCursor(0,1);
   lcd.print("DT");
   digitalWrite(pump,HIGH);
   }
   
   else
   {
       Blynk.virtualWrite(V0,"SOIL MOISTURE DETECTED");
   lcd.setCursor(0,1);
   lcd.print("S:ND");
      digitalWrite(pump,LOW);
 
    }

   int lightval=digitalRead(light);
   if(lightval==1)
   {
   Blynk.virtualWrite(V1,"NO LIGHT DETECTED");
    lcd.setCursor(7,1); 
   lcd.print("L:DT");
  digitalWrite(ledpin,HIGH); 

 }
 else
 {
   Blynk.virtualWrite(V1,"LIGHT DETECTED");
   lcd.setCursor(7,1);
   lcd.print("L:ND"); 
    digitalWrite(ledpin,LOW);
  }
 }
