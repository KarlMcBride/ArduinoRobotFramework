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
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Pin connected to LCD pin 3. Allows control of LCD contrast
const int lcd_contrast_pwm_pin = 9;
 // 0-100. 100 give max for 1602A, 0 gives max for 1602C
const int lcd_contrast = 50;

// Pin connected to LCD pin 15. Allows control of backlight brightness
const int lcd_backlight_pwm_pin = 10;
const int lcd_backlight = 100;

// Stores value of previous millis() call
long previousMillis = 0;
// Interval to update time on display, prevents excessive writes
long timeUpdateInterval = 1000;

void setup()
{
  Serial.begin(BAUD_RATE);     // opens serial port, sets data rate to 9600 bps

  // Set all pins to output
  pinMode(MOTOR_PIN_POSITIVE, OUTPUT);
  pinMode(MOTOR_PIN_NEGATIVE, OUTPUT);

  pinMode(lcd_contrast_pwm_pin, OUTPUT);
  analogWrite(lcd_contrast_pwm_pin, lcd_contrast);

  pinMode(lcd_backlight_pwm_pin, OUTPUT);
  analogWrite(lcd_backlight_pwm_pin, lcd_backlight);

  // Set all pins to LOW
  SetMotorPinStates(LOW, LOW);

  // Set up the LCD pins for a 16*2 display
  lcd.begin(16, 2);
  
  DisplayLcdMessage("ArduinoRF Bot", "Setup Complete");
  delay(2000);
}

void loop() 
{
  DisplayUpTime();

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

void DisplayUpTime()
{
  // Get uptime
  long currentMillis = millis();

  if(currentMillis - previousMillis > timeUpdateInterval)
  {
    previousMillis = currentMillis;

    int up_hours = currentMillis / 3600000;
    currentMillis = (currentMillis >= 3600000) ? (currentMillis % 3600000) : currentMillis;
    int up_mins = currentMillis / 60000;
    currentMillis = (currentMillis >= 60000) ? (currentMillis % 60000) : currentMillis;
    int up_secs = currentMillis / 1000;

    lcd.clear();
    char timeMessage[50];
    sprintf(timeMessage, "%ih %im %is", up_hours, up_mins, up_secs);
    lcd.print("Uptime:");
    lcd.setCursor(0,1);
    lcd.print(timeMessage);
  }
}

void SetMotorPinStates(int pin_pos_state, int pin_neg_state)
{
  digitalWrite(MOTOR_PIN_POSITIVE, pin_pos_state);
  digitalWrite(MOTOR_PIN_NEGATIVE, pin_neg_state);
}

void DisplayLcdMessage(unsigned int numeric)
{
  lcd.clear();
  lcd.print(numeric);
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
