const int BAUD_RATE = 9600;

int inputVal = 0;

const int MOTOR_PIN_POSITIVE = 2;
const int MOTOR_PIN_NEGATIVE = 4;

void setup()
{
  Serial.begin(BAUD_RATE);     // opens serial port, sets data rate to 9600 bps

  // Set all pins to output
  pinMode(MOTOR_PIN_POSITIVE, OUTPUT);
  pinMode(MOTOR_PIN_NEGATIVE, OUTPUT);

  // Set all pins to LOW
  SetMotorPinStates(LOW, LOW);
}

void loop() 
{
  if (Serial.available() > 0)
  {
    inputVal = Serial.parseInt();

    // Check parsed value. Invalid parse will return 0
    if (inputVal == 0)
    {
      Serial.print("Unrecognised input: ");
      Serial.print(inputVal);
      Serial.print("\r\n");
    }
    else
    {
      updateMotor(inputVal);
    }
  }
}

void updateMotor(int inputVal)
{
  if (inputVal == 1)
  {
    SetMotorPinStates(LOW, LOW);
    Serial.println("Stopping");
  }
  else if (inputVal == 2)
  {
    SetMotorPinStates(HIGH, LOW);
    Serial.println("Forward");
  }
  else if (inputVal == 3)
  {
    SetMotorPinStates(LOW, HIGH);
    Serial.println("Reverse");
  }
}

void SetMotorPinStates(int pin_pos_state, int pin_neg_state)
{
  digitalWrite(MOTOR_PIN_POSITIVE, pin_pos_state);
  digitalWrite(MOTOR_PIN_NEGATIVE, pin_neg_state);
}

