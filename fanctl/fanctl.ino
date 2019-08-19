#include <PID_v1.h>

byte PWMA = 3; // PWM control (speed) for motor A
byte PWMB = 11; // PWM control (brightness) for LED B
byte DIRA = 12; // Polarity control for motor A
byte DIRB = 13; // Polarity control for LED B
byte doorPin = 2; //door switch pin

int sensorPin = A0;
int sensorVal = 0;
int tempF = 0;
unsigned long timeStep = 5; //Time interval for LED brightness ramping
int ledBright = 0; //LED brightness PWM value

//PID variables
double Setpoint, Input, Output;
double Kp=3, Ki=0.2, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  setupArdumoto(); // Set all pins as outputs
  Serial.begin(9600); // serial output for debugging
  Setpoint = 80; //Setpoint temp in degrees Fahrenheit
  pinMode(doorPin, INPUT_PULLUP);
  myPID.SetMode(AUTOMATIC);
  myPID.SetControllerDirection(REVERSE);
}

void loop()
{
  if (digitalRead(doorPin) == HIGH){
    Input = checkTemp();
    myPID.Compute();
    analogWrite(PWMA, Output);
    Serial.print(Output); Serial.print(" PWM output "); Serial.print(tempF); Serial.println(" degrees F");
    ledOff();
  }
  else {
    analogWrite(PWMA, 0);
    ledOn();
  }
}

// setupArdumoto initialize all pins
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

double checkTemp()
{
	int sensorVal = analogRead(sensorPin);
	float voltage = sensorVal * 5.0;
 	voltage /= 1024.0; 
 	tempF = (((voltage - 0.5) * 100)* 9.0 / 5.0) + 32.0;
 	return tempF;
}

void ledOn()
{
  unsigned long currentTime = millis();
  while (ledBright < 255)
    {
      if(millis() > currentTime + timeStep){
	currentTime = millis();
	ledBright = ledBright + 1;
	analogWrite(PWMB, ledBright);
      }
    }
}

void ledOff()
{
  unsigned long currentTime = millis();
  while (ledBright > 0)
    {
      if(millis() > currentTime + timeStep){
	currentTime = millis();
	ledBright = ledBright - 1;
	analogWrite(PWMB, ledBright);
      }
    }
}
