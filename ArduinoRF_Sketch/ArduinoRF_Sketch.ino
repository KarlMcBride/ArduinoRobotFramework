const int BAUD_RATE = 9600;

int inputVal = 0;

const int MOTOR_STATE_STOP = 1;
const int MOTOR_STATE_INSERT = 2;
const int MOTOR_STATE_REMOVE = 3;

const int MOTOR_PIN_POSITIVE = 8;
const int MOTOR_PIN_NEGATIVE = 13;

const String MSG_IDLE = "Idle";
const String MSG_INSERTED = "Card Inserted";

const String MSG_STOPPED = "Stopped";
const String MSG_REMOVED = "Card Removed";

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(BAUD_RATE);     // opens serial port, sets data rate to 9600 bps

  // Set all pins to output
  pinMode(MOTOR_PIN_POSITIVE, OUTPUT);
  pinMode(MOTOR_PIN_NEGATIVE, OUTPUT);

  // Set all pins to LOW
  SetMotorPinStates(LOW, LOW);

  // Set up the LCD pins for a 16*2 display
  lcd.begin(16, 2);
  
  DisplayLcdMessage("ArduinoRF Bot", "ready for orders");
}

void loop() 
{
  if (Serial.available() > 0)
  {
    inputVal = Serial.parseInt();

    // Check parsed value. Invalid parse will return 0
    if (inputVal >= MOTOR_STATE_STOP && MOTOR_STATE_REMOVE <= 3)
    {
      updateMotor(inputVal);
    }
  }
}

void updateMotor(int inputVal)
{
  if (inputVal == MOTOR_STATE_STOP)
  {
    SetMotorPinStates(LOW, LOW);
    Serial.println(MSG_STOPPED);
  }
  else if (inputVal == MOTOR_STATE_INSERT)
  {
    SetMotorPinStates(HIGH, LOW);
    DisplayLcdMessage(MSG_INSERTED);
    Serial.println(MSG_INSERTED);
  }
  else if (inputVal == MOTOR_STATE_REMOVE)
  {
    SetMotorPinStates(LOW, HIGH);
    DisplayLcdMessage(MSG_IDLE);
    Serial.println(MSG_REMOVED);
  }
}

void SetMotorPinStates(int pin_pos_state, int pin_neg_state)
{
  digitalWrite(MOTOR_PIN_POSITIVE, pin_pos_state);
  digitalWrite(MOTOR_PIN_NEGATIVE, pin_neg_state);
}

void DisplayLcdMessage(String line1)
{
  lcd.clear();
  lcd.print(line1);
}

void DisplayLcdMessage(String line1, String line2)
{
  lcd.clear();
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}

