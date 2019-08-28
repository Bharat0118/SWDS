#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>





char auth[] = "80f287b3d7e54e5eb09d9f57942dc4e8";              //Your Project authentication key
char ssid[] = "Free ka nhi h..";                          //"JioFi2_CAE25A";                                       // Name of your network (HotSpot or Router name)
char pass[] = "18120109";                          //"irjvejbcq2";                                      // Corresponding Password


int relay= D0; // Wet Indicator at Digital PIN D0


// defines variables

int sense_Pin= 0; // Soil Sensor input at Analog PIN A0
int value= 0;
long motoron=0;
long motoroff=0;

void setup() {
   Serial.begin(9600);
   pinMode(relay,OUTPUT);
   
   
   
   delay(2000);
   Blynk.begin(auth,ssid,pass);
}

void loop() {
  Blynk.run();
   Serial.print("MOISTURE LEVEL : ");
   value= analogRead(sense_Pin);
   value= value/10;
   Serial.println(value);
   Blynk.virtualWrite(V1, value); 
   if(value>75)
   {
      digitalWrite(relay, LOW);
      delay(1000);

      motoron++;
      motoroff=0;
   }
   else
   {
      digitalWrite(relay,HIGH);

      

    motoroff++;
    motoron=0;
   }

   if(motoroff==1){
    Blynk.notify("Your Plants Have Full of Water Motor Turned OFF");
    }

    
    if(motoron==1){
    Blynk.notify("Your Plants Need Water Motor Turning ON");
    }
   
   

   





delay(500);
}
