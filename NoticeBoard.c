/*--------------------------------------------------------------
  Program:      Internet Equipped Notice Board

  Description:  Arduino web server that serves up a web page
                allowing the user to control an LED Moving Display

  Hardware:     - Arduino Uno and official Arduino Ethernet
                  shield. Should work with other Arduinos and
                  compatible Ethernet shields.
                - LED and resistor in series connected between
                  Arduino pin 2 and GND

  Software:     Developed using Arduino 1.0.3 software 
                Should be compatible with Arduino 1.0 +

  References:   - WebServer example by David A. Mellis and
                  modified by Faiz
                - Ethernet library documentation:
                  http://arduino.cc/en/Reference/Ethernet

  Date:         28  April 2015

  Author:      Mohammed Faizuddin
--------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>

#define DELAY 1000

void processHtmlString(String HTTP_str);



SoftwareSerial mySerial(6, 7); // RX, TX

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };

EthernetServer server(80);  // create a server at port 80

String HTTP_req;          // stores the HTTP request
boolean LED_status = 0;   // state of LED, off by default

String line1 = "Default Message";


void setup()
{
    Ethernet.begin(mac);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    Serial.begin(9600);       // for diagnostics

    mySerial.begin(9600);

}

void loop()
{
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                HTTP_req += c;  // save the HTTP request 1 char at a time
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    // send web page
                    client.println("<!DOCTYPE html>");
                    client.println("<html>");
                    client.println("<head>");
                    client.println("<title>INTERNET EQUIPPED NOTICE BOARD (An R&D Initiative)</title>");
                    client.println("</head>");
                    client.println("<body bgcolor=\"#E6E6FA\">");
                    client.println("<h1>INTERNET EQUIPPED NOTICE BOARD (An R&D Initiative)</h1>");
                    client.println("<p>Please enter the notice to be scrolled on display board</p>");
                    //client.println("<form method=\"get\">");
                    client.println("<form action=\"\" method=get>");
                    client.println("<b>Line 1: </b><input type=\"text\" name=\"L1\" maxlength=\"100\" size=\"50\" /><br />");
                    client.println("<input type=\"submit\" value=\"Submit\" /></form>");
                    //ProcessCheckbox(client);
                    client.println("</form>");
                    client.println("</body>");
                    client.println("</html>");
                    Serial.print(HTTP_req);

                    Serial.println();

                   int index;

                   index = HTTP_req.indexOf("L1=");

                   Serial.print("Index = ");
                   Serial.print(index);
                   Serial.println();

                   if(index != -1)
                   {
                     processHtmlString();
                   }

                    HTTP_req = "";    // finished with request, empty string
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                }
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}

// switch LED and send back HTML for LED checkbox
void processHtmlString(void)
{

  int indexOfMsgStart = 0;
  int indexOfMsgEnd = 0;

  //Serial.print(HTTP_req);


     HTTP_req.replace("+"," ");


    indexOfMsgStart = HTTP_req.indexOf("L1=") + 3;       // find the index of that delimiter
    indexOfMsgEnd = HTTP_req.indexOf("HTTP/1.1")-1;


      Serial.print("Message Starting Index : ");
      Serial.println(indexOfMsgStart);
       Serial.print("Message Ending Index : ");
       Serial.println(indexOfMsgEnd);

    line1 = HTTP_req.substring(indexOfMsgStart,indexOfMsgEnd); // set line1 and line 2 using that knowlege
    line1 += NULL;

    line1.setCharAt(line1.lastIndexOf('0'), '\0');

    Serial.print("Received Message is : ");
    Serial.println(line1);

    int str_len = line1.length() + 1;

    char msg[str_len];

    line1.toCharArray(msg,str_len);

     Serial.println("Entering Cmd Mode");
    mySerial.println("#");
    delay(DELAY);

    Serial.println("Formating...");
    mySerial.println("4");
    delay(DELAY);
    Serial.println("Done Formating.");


    Serial.println("Editing New Message");
    mySerial.println("1");
    delay(DELAY);

    mySerial.print("<M ");
    mySerial.print(msg);
    mySerial.println("><D L1>");

    delay(DELAY);

    mySerial.println("6");

    Serial.println("Done");

}
