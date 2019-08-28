#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "80f287b3d7e54e5eb09d9f57942dc4e8";              //Your Project authentication key
char ssid[] = "Free ka nhi h..";                                //"JioFi2_CAE25A";                                       // Name of your network (HotSpot or Router name)
char pass[] =  "18120109";                                 //"irjvejbcq2";                                      // Corresponding Password


int relay= D0; // Wet Indicator at Digital PIN D0

const int trigPin = D1;  //D1
const int echoPin = D2;  //D3

// defines variables
long duration;
int distance;
int sense_Pin= 0; // Soil Sensor input at Analog PIN A0
int value= 0;
long motoron=0;
long motoroff=0;

void setup() {
   Serial.begin(9600);
   pinMode(relay,OUTPUT);
   pinMode(trigPin,OUTPUT);
   pinMode(echoPin,INPUT);
   
   
   delay(2000);
   Blynk.begin(auth,ssid,pass);
}

void loop() {
  Blynk.run();
//   Serial.print("MOISTURE LEVEL : ");
//   value= analogRead(sense_Pin);
//   value= value/10;
//   Serial.println(value);
//   if(value>75)
//   {
//      digitalWrite(relay, LOW);
//      delay(1000);
//   }
//   else
//   {
//      digitalWrite(relay,HIGH);
//   }
   //delay(1000);
   

   // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

Blynk.virtualWrite(V0, distance); 

if(distance<=4){
    digitalWrite(relay,HIGH);
    //Blynk.notify("Your Tank is Filled Motor Turned OFF");
    
    motoroff++;
    motoron=0;
    
  
  }
  
  else if(distance>=18 ){
    digitalWrite(relay,LOW);
    //Blynk.notify("Your Tank Is Empty Motor Turning ON");

    
    motoron++;
    motoroff=0;
    
    }

    if(motoroff==1){
    Blynk.notify("Motor Turned OFF");
    }

    
    if(motoron==1){
    Blynk.notify("Motor Turned ON");
    }

    
   //
   //delay(1000);


delay(500);
}
