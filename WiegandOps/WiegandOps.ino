// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

/*
The intent of this program is to allow the means to detect sequences of Wiegand data from 
two GPIO pins using interrupt handlers. Each pin/line is pulsed high to signal a zero or one
for usually 200 microseconds, then both set low for the same interval.
*/

const int wiegand_data_pin_0 = 2;
const int wiegand_data_pin_1 = 3;

String inflight_data_string = "";
String complete_data_string = "";

unsigned long time_since_last_data_addition_ms = 0;
const unsigned long DURATION_BEFORE_RESET_MS = 1000;

// Pins to simulate board under test sending data.
const int data_sender_pin_d0 = 12; // Connect to wiegand_data_pin_0.
const int data_sender_pin_d1 = 13; // Connect to wiegand_data_pin_1.

void setup() 
{
    // Use an unused pin to seed the random number generator for data generation.
    randomSeed(analogRead(0));
  
    pinMode(wiegand_data_pin_0, INPUT_PULLUP);
    pinMode(wiegand_data_pin_1, INPUT_PULLUP);

    pinMode(data_sender_pin_d0, OUTPUT);
    pinMode(data_sender_pin_d1, OUTPUT);

    // Attach pin interrupts to the rising edge of the two 
    attachInterrupt(digitalPinToInterrupt(wiegand_data_pin_0), wiegand_d0_ISR, RISING);
    attachInterrupt(digitalPinToInterrupt(wiegand_data_pin_1), wiegand_d1_ISR, RISING);
    
    // Initialize serial communication for debug output
    Serial.begin(9600);
}

void loop() 
{
    delay(500);

    // If no new data has been received lately, set the complete data and clear inflight data
    // as no more wiegand data is being transmitted.
    if (millis() > time_since_last_data_addition_ms + DURATION_BEFORE_RESET_MS && inflight_data_string != "")
    {
        complete_data_string = inflight_data_string;
        inflight_data_string = "";
        Serial.println("Data: " + complete_data_string);
    }

    send_data("");

    delay(DURATION_BEFORE_RESET_MS);
}

// Function to simulate data being sent by board under test
void send_data(const String _data)
{
    if (_data == "")
    {
        for (int index = 0; index < 8; index++)
        {
            int data_value = random(2);
            if (data_value == 0)
            {
                _data += "0";
            }
            else
            {
                _data += "1";
            }
        }
    }

    Serial.println("send_data: " + _data);
  
    for (auto bit : _data)
    {
        if ('0' == bit)
        {
            digitalWrite(data_sender_pin_d0, HIGH);
            delay(1);
            digitalWrite(data_sender_pin_d0, LOW);
            delay(1);
        }
        else if ('1' == bit)
        {
            digitalWrite(data_sender_pin_d1, HIGH);
            delay(1);
            digitalWrite(data_sender_pin_d1, LOW);
            delay(1);
        }
    }
}

void add_new_data(const char &_new_char)
{
    inflight_data_string += _new_char;
    time_since_last_data_addition_ms = millis();
}

void wiegand_d0_ISR()
{
    add_new_data('0');
}

void wiegand_d1_ISR()
{
    add_new_data('1');
}
