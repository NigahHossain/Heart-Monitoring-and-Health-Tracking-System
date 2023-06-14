
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.
#define USE_ARDUINO_INTERRUPTS true     // Set-up low-level interrupts for most acurate BPM math.
#define kpa2mmhg 7.50062

   

//  Variables
const int PulseWire = A4;    //A0;      
int pressurePin = 0;
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
int val;
float pkPa; // pressure in kPa
float pmmhg; // pressure in Atm

unsigned long time;                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   

  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("Patient Health Monitor");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }

}



void loop() {

 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
 val = analogRead(pressurePin);
 pkPa = ((float)val/(float)1023+0.095)/0.09;
 pmmhg = kpa2mmhg*pkPa;                                            // "myBPM" hold this BPM value now. 
 

 if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
 Serial.println("Blood Pressure: ");
 Serial.print(pmmhg);
 Serial.println("mmHg");
}

  delay(50);                    // considered best practice in a simple sketch.

}
