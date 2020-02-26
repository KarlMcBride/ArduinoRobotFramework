/*
    Based on the Ethernet UDPSendReceiveString example
    Modified to allow control of an LED via ethernet
*/

#include <Ethernet.h>
//#include <EthernetUdp.h>

#include <Keyboard.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(172, 16, 230, 118);

unsigned int localPort = 8888; // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];    // buffer to hold incoming packet,
const char REPLY_MESSAGE[] = "Arduino Ack: "; // a string to send back
const int ACK_MESSAGE_MAX_SIZE = 100;

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup()
{
    Serial.println("Leonardo setup starting");

    // Initialise keyboard
    Keyboard.begin();

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

    Serial.println("Leonardo setup complete");
}

void type_string(String _string)
{
    int string_length = _string.length();
        Serial.println("type_string: [" + _string + "]");
    for (int i = 0; i < string_length; i++)
    {
        Keyboard.write(_string[i]);
        delay(10);
        Keyboard.releaseAll();
    }
    Keyboard.write(176);
    delay(10);
    Keyboard.releaseAll();
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

        if (0 == strcmp(packetBuffer, "INSTALL_ISO"))
        {
            type_string("INSTALLING ISO");
        }
        else if (strstr (packetBuffer, "SEQ"))
        {
            String keypresses = packetBuffer;
            keypresses.remove(0, 4); // Remove 'SEQ,'
            type_string(keypresses);
        }
        else
        {
            Serial.println("Unknown instruction received:");
            Serial.println(packetBuffer);
        }
    }

    delay(10);
}
