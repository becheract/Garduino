#define AOUT_PIN A0 // Arduino pin that connects to AOUT pin of moisture sensor
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 

//gnd yellow is connected to ground
//vdd orange  is connected to 5v
//rdd is red is connected to ground
//rs is red and blue connected to pin 13
//E is white pin 12
//d4 is blue connected to pin 11
//d5 is green connected to pin 10
//d6 is white connected to pin 9 
//d7 is red and is pin 8 
//v0 is red connected to potentomiter
//blk is green connected to ground 

// Water level Sensor pins
#define waterLevelSensorPower 5
#define waterLevelSensorPin A1
#define DHTPIN 1 // what digital pin we're connected to
#define DHTTYPE    DHT11     // DHT 11
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7) 
const int RELAY_PIN = 3;
const unsigned long pumpDuration = 900000; // Duration for water pump activation (15 minutes = 900000 milliseconds)
//water pump on led
//water pump off led
#define LED_PIN_PUMP_ON 6
//lowest soil moisture is 430
#define LED_PIN_PUMP_OFF 7

//water level low led
#define LED_PIN_WATER_LOW 2
// Value for storing water level
int val = 0;


 


void setup() {
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(waterLevelSensorPower, OUTPUT);
  pinMode(LED_PIN_WATER_LOW, OUTPUT);
  digitalWrite(waterLevelSensorPower, LOW);
  lcd.print("Arduino"); // Prints "Arduino" on the LCD 
  pinMode(LED_PIN_PUMP_OFF, OUTPUT);
  digitalWrite(LED_PIN_PUMP_OFF, HIGH);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(AOUT_PIN); // read the analog value from sensor
 digitalWrite(RELAY_PIN, HIGH);

  if(value <= 470){
    //activate water pump
  Serial.print("Activate the pump!: ");
  pinMode(LED_PIN_PUMP_ON, OUTPUT);
  digitalWrite(LED_PIN_PUMP_ON, HIGH);
  Serial.println(value);
  delay(pumpDuration);
  digitalWrite(RELAY_PIN, LOW);
 
  }
  else { 
    	//get the reading from the function below and print it
	int water_level = readSensor();
  int low_water_level = 60;
	Serial.print("Water level: ");
	Serial.println(low_water_level);
	
  if(water_level <= low_water_level){
    digitalWrite(LED_PIN_WATER_LOW, HIGH);
    delay(100);
    digitalWrite(LED_PIN_WATER_LOW, LOW);
  }

  Serial.print("Moisture: ");
  Serial.println(value);

	delay(1000);

  }
}
//This is a function used to get the reading
int readSensor() {
	digitalWrite(waterLevelSensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// wait 10 milliseconds
	val = analogRead(waterLevelSensorPin);		// Read the analog value form sensor
	digitalWrite(waterLevelSensorPower, LOW);		// Turn the sensor OFF
	return val;							// send current reading
}

