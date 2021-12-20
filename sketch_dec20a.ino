
#include <ESP8266wifi.h>           
#define BLYNK_PRINT Serial       
#include <BlynkSimpleEsp8266.h>   
BlynkTimer timer;

char auth[] = "IPE5pn7ACBwKsKeYK1Aos41RZhqEOMs3"
char ssid[] = "Extinguisher"
char pass[] = "123456"
const int Flame_Sensor = 11;         
int Buzzer = 9; 
int flame = HIGH;
int green_light = 5; 
int red_light = 6;
const int motor = 8;
 
int Y = 0;
bool x; 
void Activate_on_fire()              
{                                           
  int sensor = digitalRead(D0);     
  if(sensor == 1 && Y== 0)
  {
    Serial.println("ALARM!!! FIRE!!! ALARM!!! FIRE!!!");    
    Blynk.notify("Fire in premises");
    Y=1;
  }
  else if(sensor == 0)
  {
    Y = 0;
  }
}
 
void setup() {                          
  Blynk.begin(auth, ssid, pass);              
  pinMode(D0, INPUT_PULLUP);                    
  timer.setInterval(1000L,Activate_on_fire);    
  pinMode(Buzzer, OUTPUT);                      
  pinMode(green_light, OUTPUT);
  pinMode(blue_light, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(Flame_Sensor, INPUT);
}
void loop() {                                   
  flame = digitalRead(Flame_Sensor);            
  if (flame == LOW)
  {
    digitalWrite(green_led, LOW);                 
    digitalWrite(blue_led, HIGH);                 
    delay(100);                                   
    digitalWrite(blue_led, LOW);                
    delay(100);                                   
    digitalWrite(blue_led,HIGH);
    digitalWrite(motor, HIGH);
    tone(Buzzer, 4000);
    delay(100);
    noTone(Buzzer);
  }
  else
  {
    noTone(Buzzer);
    digitalWrite(green_led, HIGH);
    digitalWrite(motor, LOW);
    digitalWrite(red_led, LOW);
  }
  Blynk.run();                           
  timer.run();                           
}

}
