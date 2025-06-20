 // C++ code
//make the km/h equal the max speed if it starts to go over the neccesary rpm
//highest known attainable speed is 397.36 1.6856v power supply needed for max speed
//Takes values off the track and speed and tries to take hp value of tyres
//to let user know in simulation when the tyres need to be changed, also lets user know when the capacity of the tyres speed has been reached and exceeded
//By emmitting a warning light
#include <Adafruit_LiquidCrystal.h>// import i2c LCD library
#include <Adafruit_NeoPixel.h> // import NEOPIXEL library
#define PIN 2	 // input pin Neopixel is attached to
int NUMPIXELS = 12;
//#define NUMPIXELS      6 // number of neopixels in strip
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int output1=0;
int output2=0;
int seconds = 0;
int delayVal=0;
int lastLapCounter = 0; // Tracks the last lap when tire degradation was applied
int redColour=0;// values for LEDs
int greenColour=0;
int blueColour=0;
int black_colour=0;// value to be used for blinking effect in for loop
int dummyVal;
int warning=2;// pin initialisation for warning led
unsigned long lapStartTime = 0;// initialising a byte reader for time elapsed within the actual simulation of tinkercad
int lapTimeSeconds;
int degradationRate=0;// rate at which the tyres will degrade wuth every passing lap
float track = 5;// length of the track in km/h per lap
int laps=10;// total regulated laps for f1 of silverstone
float total_Distance=5*10;//5km between stops
int maxSpeed;// maximum speed the tyre can achieve
int tyreHealth; // Represents the health of the tires
int lapCounter = 0; // Keeps track of laps completed
int lastSecond = 0;      // Tracks last time update
  int currentMillis = millis(); // Get the current time
  int lastUpdateTime = 0;
  bool lapStarted = false; // Track if lap has started
String tyres="regular";// user will input via a terminal what type of tyres will be assigned to the simulator
Adafruit_LiquidCrystal lcd_1(0);


void setup()
{
  lcd_1.begin(16, 2);
  pinMode(4,OUTPUT);// setting all pins and what role they play in the system
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  
  pixels.begin();// begins the imported program for the neopixel
  lapStartTime = millis();// assigns the time in milliseconds since the simulation on tinkercad began
  Serial.begin(9600);
}

void loop()
{
  lcd_1.setCursor(10,0);
  lcd_1.print(lapCounter);// prints the current laps attained by the driver
  lcd_1.print("/10");// total laps, will never change
  
  
  if (tyres=="regular"){//
   digitalWrite(3,HIGH); // writes which LED will be displayed to correspond with tyre chosen at the moment
   tyreHealth= 23; // health assigned to each type of tyre
   lcd_1.setCursor(4,0);// sets where the cursor will begin outputting information on the LCD
   lcd_1.print("km/h ");
    softTyres();
  }
    
  setColor(); // sets colour of the neopixels

  
  
 for (int i = 0; i < 12; i++) {// for loop begins for NEOPIXEL. 12 is the number of LEDs in the neopixel
  pixels.setPixelColor(i,pixels.Color(0,0,0)); // initialisation has them turned off to begin with
  pixels.show();// shows the resulting value on the neopixel
  }
  for (int i = 0; i < NUMPIXELS; i++) {// creates the radial effect in line with the potentiometer's mapped values
  pixels.setPixelColor(i,pixels.Color(redColour, greenColour, blueColour));// the following code from line 95-122 is a 
    //long form of flashing the last LED on and off for an aesthetic effect.
  pixels.show();// unfortunately tinkercad cant handle much of this following code so iut has been simplified to a longer blinking programme rather than another if else statement or for loop
  }
  delay(500);
  pixels.setPixelColor(NUMPIXELS,pixels.Color(0,0,0));
  pixels.show();
  delay(500);
    pixels.setPixelColor(NUMPIXELS,pixels.Color(redColour, greenColour, blueColour));
  pixels.show();
  delay(500);
    pixels.setPixelColor(NUMPIXELS,pixels.Color(0,0,0));
  pixels.show();
  delay(500);
    pixels.setPixelColor(NUMPIXELS,pixels.Color(redColour, greenColour, blueColour));
  pixels.show();
  delay(500);
   pixels.setPixelColor(NUMPIXELS,pixels.Color(0,0,0));
  pixels.show();
  delay(500);
  // Loop the "black" hopping effect with the green color
 // for (int i = 0; i < NUMPIXELS; i++) {
    // Set current pixel to black (off) and the previous one back to green
  //  pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Turn current pixel off (black)
  //  if (i > 0) {
  //    pixels.setPixelColor(i - 1, pixels.Color(redColour, greenColour, blueColour)); // Set previous pixel to green
  //  }
  //  pixels.show();
  //  delay(100); // Delay before the next "hop"
 // }
  lapTimeCalculator();
//  healthEvaluationoftyres();
    
  

  
}
void setColor(){// function that sets the led colour on the neopixels based on the health remaining within each chosen tyre
  redColour = 0;
  greenColour = 255;
  blueColour=  0;
  black_colour = 0;
  if(tyreHealth> tyreHealth/2){// if tyre is more than half health it should be good
    greenColour=255;
    redColour=0;
  }  
if (tyreHealth <= tyreHealth/2){// if less than it should switch to orange to let driver know of any imminent dangers
    redColour = 255;// both colour values make an orange effect
    greenColour=165;
  }
  if (tyreHealth <5){ // turns neopixel fred as health is nearly depleted
    redColour = 255;// both colour values make an orange effect
    greenColour=0 ;
  }
  
}

void softTyres() { // soft tyre function that revolves around a what a soft tre might act like
  int rpmperpotval;
  int maxspeed = 60;// maximum speed attainable in and f1 car
  int sensorVal = analogRead(A0);
  //dummyVal=sensorVal;
  
  output2 = map(sensorVal, 0, 1023, 0, 255);// maps the bits of the potentiometer to be in line with the DC motor
  analogWrite(10,output2);
  NUMPIXELS = map(output2 , 0, 255, 0, 12);// maps again to be in line with NEOPIXEL display
  output2 = map(output2 , 0, 255, 0, maxspeed);// further maps output 2 to be displayed on the LCD 
  
  analogWrite(9,0);
	int rps=((3196/dummyVal)/60);//calculation for rps/ rpm required fir maximum attainable speed divided by vakye taken from the output/ further divided by 60 to get rps
	delayVal=(1/12)/rps;//delayval for the actual neopixel to rotate at the speed of

  // Display the output on the LCD with if statements
  lcd_1.setCursor(0, 0);  // Set LCD cursor position

  // Check if the number is less than 10
  if (output2 < 100) {
    lcd_1.print("0");      // Print a leading zero for numbers less than 10
  }
  if(output2<10){
    lcd_1.print("0");      // Print a leading zero for numbers less than 10
  }
 


  // Print the actual number
  lcd_1.print(output2);     // This will print the number, whether it's one or two digits
//onto the delay bit
//
//using outputValue and radius per metre of the revolution
//3197 the average maximum value when maximum acceleration is applied
}









void lapTimeCalculator() {
  static unsigned long lastSerialUpdate = 0; // Track last time data was sent
  static unsigned long lastLCDUpdate = 0;    // Track last LCD update time
  int currentMillis = millis(); // Get current time

  if (output2 > 0) { 
    lapTimeSeconds = (track * 3600) / output2; 
    lapStarted = true; // Lap starts when speed > 0
  }

  if (lapStarted) { 
    int elapsedSeconds = (millis() - lapStartTime) / 1000;
    int remainingTime = lapTimeSeconds - elapsedSeconds;

    // If speed is 0, add 1 second every second
    if (output2 == 0 && currentMillis - lastUpdateTime >= 1000) {
      remainingTime += 1;
      lastUpdateTime = currentMillis;
    }

    // If time reaches zero, move to the next lap
    if (remainingTime <= 0) {
      lapCounter++;
      tyreHealth--;
      lapStartTime = millis();
      lapStarted = false;

      if (lapCounter >= laps) {
        lcd_1.setCursor(0, 1);
        lcd_1.print("Race Complete!   ");
        return;
      }
      remainingTime = lapTimeSeconds; 
    }

    // **Update LCD every second**
    if (currentMillis - lastLCDUpdate >= 1000) {
      lastLCDUpdate = currentMillis; // Reset LCD timer

      // Convert to minutes & seconds for LCD display
      int minutes = remainingTime / 60;
      int seconds = remainingTime % 60;

      // Display on LCD
      lcd_1.setCursor(0, 1);
      lcd_1.print("Time: ");
      if (minutes < 10) lcd_1.print("0");
      lcd_1.print(minutes);
      lcd_1.print(":");
      if (seconds < 10) lcd_1.print("0");
      lcd_1.print(seconds);
    }

    // **Send data every 5 seconds to Raspberry Pi**
    if (millis() - lastSerialUpdate >= 5000) {
      lastSerialUpdate = millis(); // Reset timer

      Serial.print("Next Stop: ");
      Serial.print(lapCounter+1);
      Serial.print(", Time Left: ");
      Serial.print(remainingTime);
      Serial.print(", Speed: ");
      Serial.print(output2);

      // **Send vehicle status**
      if (output2 == 0) {
        Serial.println(", Status: STOPPED");
      } else {
        Serial.println(", Status: MOVING");
      }
    }
  }
}

