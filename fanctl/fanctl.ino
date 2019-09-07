#include <PID_v1.h>

byte PWMA = 3; // PWM control (speed) for fan motor on Ardumoto shield
byte PWMB = 11; // PWM control (brightness) for LED strip on Ardumoto shield
byte DIRA = 12; // Polarity control for fan motor on Ardumoto shield
byte DIRB = 13; // Polarity control for LED strip on Ardumoto shield
byte doorPin = 2; // digital input pin for door switch
int sensorPin = A0; // Analog input pin for TMP36 sensor
int sensorVal = 0;
float tempF = 0;
int ledBright = 0; // LED brightness PWM value


// Loop timing variables
unsigned long timeStep = 5; // Time interval for LED brightness ramping (longer == more gradual ramp)
unsigned long logInterval = 1000; // Time interval for sending logging data over serial connection
unsigned long currentTime = millis();
unsigned long lastTime1 = currentTime; 
unsigned long lastTime2 = currentTime;
unsigned long lastTime3 = currentTime;

// PID variables
double Input, Output;
double Kp=3, Ki=0.2, Kd=1; // Change these values to tune PID loop
double Setpoint = 80; // PID setpoint temp in degrees Fahrenheit
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  setupArdumoto(); // Set all pins as outputs
  Serial.begin(9600); // serial output for debugging
  pinMode(doorPin, INPUT_PULLUP); //As switch is directly attached to pins, we use INPUT_PULLUP to activate the Arduino's internal pullup resistor
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(65, 255); // Set minimum/maximum PWM values for controlling fan speed. Min value should be high enough than the fan will not stall
  myPID.SetControllerDirection(REVERSE);
}

void loop()
{
  if (digitalRead(doorPin) == HIGH) //Fan control will only turn on if door is closed
  	{
  		if (checkTemp() > 79) {
  			Input = checkTemp();
    		myPID.Compute();
    		analogWrite(PWMA, Output);
  		}
  		else {
  		   analogWrite(PWMA, 0);
  		}	
    ledOff();
 	 }
  else 
  {
    analogWrite(PWMA, 0);
    ledOn();	
  }
  serialLog();
}

// setupArdumoto shield by initializing all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

// return temperature in Fahrenheit from TMP36 sensor
float checkTemp()
{
	int sensorVal = analogRead(sensorPin);
	float voltage = sensorVal * 5.0;
 	voltage /= 1024.0; 
 	tempF = (((voltage - 0.5) * 100)* 9.0 / 5.0) + 32.0;
 	return tempF;
}

// turn LED strip on with a smooth fade by raising the PWM value
void ledOn()
{
  while (ledBright < 255)
    {
      if(millis() > lastTime1 + timeStep)
      {
		lastTime1 = millis();
		ledBright = ledBright + 1;
		analogWrite(PWMB, ledBright);
      }
    }
}

// turn LED strip off with a smooth fade by lowering the PWM value
void ledOff()
{
  unsigned long currentTime = millis();
  while (ledBright > 0)
    {
      if(millis() > lastTime2 + timeStep)
      {
		lastTime2 = millis();
		ledBright = ledBright - 1;
		analogWrite(PWMB, ledBright);
      }
    }
}

// Send log data over serial connection
void serialLog()
{
  String doorStatus = "";
  	if(millis() > lastTime3 + logInterval)
	  {
	    lastTime3 = millis();

	    // Set doorStatus varible based on whether door switch is open or closed
	    if(digitalRead(doorPin) == HIGH)
	    {
	      doorStatus = "CLOSED";
	    }
	    else
	    {
	      doorStatus = "OPEN";
	    }
	    //Print log data over serial, comma-separated
	    Serial.print(Output); //PID fan control speed
	    Serial.print(", ");
	    Serial.print(tempF); // Temperature
	    Serial.print(", ");
	    Serial.print(doorStatus); // Door open or closed
	    Serial.print(", ");
	    Serial.print(ledBright); // LED brightness
	    Serial.print(", ");
	    Serial.print(lastTime3 / 1000); //print time since program start in seconds
	    Serial.println(", ");
	  }
}
