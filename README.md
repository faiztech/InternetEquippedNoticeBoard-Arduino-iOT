# InternetEquippedNoticeBoard-Arduino-iOT

Load this project into an Arduino UNO with an Ethernet Shield and it should be capable of turning a normal moving message display into a wireless display after some more configuring.


This project mainly focuses on transmission of textual data through internet interface by the use of Wi-Fi connection through asynchronous serial communication .
The data will be processed by the Arduino on the receivers’ end. The data will be displayed on the scrolling LED board. 
The messages can be changed only by the person who is connected to the network. 
And to connect to a network the user needs to get authorized by typing in a unique pass key. 
In addition to that address matching is done by the router and a unique IP is given to the receiver, so in case of number of receiver boards the message can be sent dedicatedly by using a unique IP. 
Actually what happens is, sending message through PC or a laptop can be used effectively.
If we can use this message through pc or laptop in displaying data. 
It is possible to receive or decode the message collectively by more than one receiver which is connected to the internet using Wi-Fi connection ie. 
We will be able to control the displays (which are connected to the internet using Arduino) from any part of campus in range of the WiFi router.  
In this project we do not send the data anonymously but send the data after proper authorization. 
Which enables us to prevent the unauthorized use of Led display board and only the person who has the pass code can have access to Led board. 

Important feature of thesis is we are using Wi-Fi network by which we can control Led display board by Computer present in any part of campus or block, condition is that we must have the respected pass code. 
And if the pass code is ok then the correct data is to be displayed on LED. 
