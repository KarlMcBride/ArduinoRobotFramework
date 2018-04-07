const int BAUD_RATE = 9600;

int inputVal = 0;

const int MOTOR_PIN_POSITIVE = 2;
const int MOTOR_PIN_NEGATIVE = 4;

int motorPositive = LOW;
int motorNegative = HIGH;

void setup()
{
  Serial.begin(BAUD_RATE);     // opens serial port, sets data rate to 9600 bps
  //pinMode (ledPin, OUTPUT);
  pinMode(MOTOR_PIN_POSITIVE, OUTPUT);
  pinMode(MOTOR_PIN_NEGATIVE, OUTPUT);
  
  motorPositive = LOW;
  motorNegative = LOW;
}

void loop() 
{
  if (Serial.available() > 0)
  {
    inputVal = Serial.parseInt();
    updateMotor(inputVal);
  }
}

void updateMotor(int inputVal)
{
  if (inputVal == 1)
  {
    motorPositive = LOW;
    motorNegative = LOW;
    Serial.println("Stopping motor");     
  }
  else if (inputVal == 2)
  {
    motorPositive = HIGH;
    motorNegative = LOW;     
    Serial.println("Forward"); 
  }
  else if (inputVal == 3)
  {
    motorPositive = LOW;
    motorNegative = HIGH;   
    Serial.println("Reverse");   
  }
  else
  {
    Serial.print("Unrecognised input: ");
    Serial.print(inputVal);    
    Serial.print("\r\n");    
  }
  
  // Set the motor output
  digitalWrite(MOTOR_PIN_POSITIVE, motorPositive);
  digitalWrite(MOTOR_PIN_NEGATIVE, motorNegative);
}

