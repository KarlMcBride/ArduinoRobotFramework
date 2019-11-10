/*
    Based on the Ethernet UDPSendReceiveString example
    Modified to allow control of an LED via ethernet
 */

#include <Ethernet.h>
//#include <EthernetUdp.h>

const int LED_PIN_R = 3;
const int LED_PIN_G = 5;
const int LED_PIN_B = 6;
int currentLedBrightness = 0;
int fadeAmount = 2;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 20);

unsigned int localPort = 8888; // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];    // buffer to hold incoming packet,
const char REPLY_MESSAGE[] = "Arduino Ack: "; // a string to send back
const int ACK_MESSAGE_MAX_SIZE = 100;

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

bool fadeLedEnabled = false;

const int RGB_SETUP_DELAY_MS = 500;

void setup()
{
    // Start ethernet connection
    Ethernet.begin(mac, ip);

    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        while (true)
        {
            delay(1); // do nothing, no point running without Ethernet hardware
        }
    }
    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println("Ethernet cable is not connected.");
    }

    // start UDP
    Udp.begin(localPort);

    // Declare RGB pins
    pinMode(LED_PIN_R, OUTPUT);
    pinMode(LED_PIN_G, OUTPUT);
    pinMode(LED_PIN_B, OUTPUT);

    // Cycle RGB at startup
    analogWrite(LED_PIN_R, 255);
    delay(RGB_SETUP_DELAY_MS);
    analogWrite(LED_PIN_R, 0);
    analogWrite(LED_PIN_G, 255);
    delay(RGB_SETUP_DELAY_MS);
    analogWrite(LED_PIN_G, 0);
    analogWrite(LED_PIN_B, 255);
    delay(RGB_SETUP_DELAY_MS);
    analogWrite(LED_PIN_R, 255);
    analogWrite(LED_PIN_G, 255);
    analogWrite(LED_PIN_B, 255);
    delay(RGB_SETUP_DELAY_MS);
    analogWrite(LED_PIN_R, 0);
    analogWrite(LED_PIN_G, 0);
    analogWrite(LED_PIN_B, 0);
}

void loop()
{
    // if there's data available, read a packet
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remote = Udp.remoteIP();
        for (int i = 0; i < 4; i++)
        {
            Serial.print(remote[i], DEC);
            if (i < 3)
            {
                Serial.print(".");
            }
        }
        Serial.print(", port ");
        Serial.println(Udp.remotePort());

        // read the packet into packetBufffer
        memset(&packetBuffer[0], 0, UDP_TX_PACKET_MAX_SIZE);
        Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        Serial.println("Contents:");
        Serial.println(packetBuffer);
        Serial.println("-----");

        // send a reply to the IP address and port that sent us the packet we received
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

        char ackMessage[ACK_MESSAGE_MAX_SIZE] = {0};
        strcpy(ackMessage, REPLY_MESSAGE);
        strcat(ackMessage, packetBuffer);
        Udp.write(ackMessage);
        Udp.endPacket();

        if (0 == strcmp(packetBuffer, "RGB_FADE"))
        {
            currentLedBrightness = 0;
            fadeAmount = (fadeAmount < 0) ? -fadeAmount : fadeAmount;
            fadeLedEnabled = true;
        }
        else
        {
            fadeLedEnabled = false;
        }
    }

    fade_led(fadeLedEnabled);
    delay(10);
}

void fade_led(bool _keepRunning)
{
    if (_keepRunning)
    {
        analogWrite(LED_PIN_R, currentLedBrightness);
        analogWrite(LED_PIN_G, currentLedBrightness);
        analogWrite(LED_PIN_B, currentLedBrightness);

        // change the brightness for next time through the loop:
        currentLedBrightness = currentLedBrightness + fadeAmount;

        // Reverse the direction of the fading at the ends of the fade:
        if (currentLedBrightness <= 0 || currentLedBrightness >= 254)
        {
            fadeAmount = -fadeAmount;
        }
    }
    else
    {
        analogWrite(LED_PIN_R, 0);
        analogWrite(LED_PIN_G, 0);
        analogWrite(LED_PIN_B, 0);
    }
}
