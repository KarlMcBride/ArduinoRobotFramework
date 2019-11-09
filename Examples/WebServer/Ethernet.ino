#include <Ethernet.h>

// assign a MAC address for the Ethernet controller.
// fill in your address here:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// assign an IP address for the controller:
IPAddress ip(192, 168, 1, 19);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

long lastReadingTime = 0;

const int temperature = 25;
const int pressure = 21;

void setup()
{
    // start the Ethernet connection
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

    // start listening for clients
    server.begin();

    // give the Ethernet shield time to set up:
    delay(1000);
}

void loop()
{
    // check for a reading no more than once a second.
    if (millis() - lastReadingTime > 1000)
    {
        // timestamp the last time you got a reading:
        lastReadingTime = millis();
    }

    // listen for incoming Ethernet connections:
    listenForEthernetClients();
}

void getData()
{
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" degrees C");
    Serial.print("Pressure: " + String(pressure));
    Serial.println(" Pa");
}

void listenForEthernetClients()
{
    // listen for incoming clients
    EthernetClient client = server.available();
    if (client)
    {
        Serial.println("Got a client");
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();
                // if you've gotten to the end of the line (received a newline
                // character) and the line is blank, the http request has ended,
                // so you can send a reply
                if (c == '\n' && currentLineIsBlank)
                {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println();
                    // print the current readings, in HTML format:
                    client.print("Temperature: ");
                    client.print(temperature);
                    client.print(" degrees C");
                    client.println("<br />");
                    client.print("Pressure: " + String(pressure));
                    client.print(" Pa");
                    client.println("<br />");
                    break;
                }
                if (c == '\n')
                {
                    // you're starting a new line
                    currentLineIsBlank = true;
                }
                else if (c != '\r')
                {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        client.stop();
    }
}
