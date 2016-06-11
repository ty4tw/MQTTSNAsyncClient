# MQTTSNAsyncClient
MQTT-SN AsyncClient over XBee and UDP for linux and Arduino ( Single thread AsyncClient)    
The client can send and receive PUBLISH messages concurrently.   
##How to build a MQTT SN Linux Client over UDP
## What you need: 
* Linux machine and the C ++ development environment
* Arduino Ethernet Rev3 and the Arduino IDE (1.6.4)    

## Things to create:    
* Clients over UDP, one for Linux and the other is for Aruduino.
* MQTT-SN Gateway over UDP    
    
## Test content:    
* Arduino client SUBSCRIBE to topic xxxx/onoff/arduino for turning on/off the LED light. When PUBLISH takes place with the boolean value, the LED light turns on/off. And topic xxxx/onoff/linux with False/True PUBLISH alternately.
* Linux client SUBSCRIBE to topic xxxx/onoff/linux for turning on/off LED light. Whenever PUBLISH with the boolean value, result in standard output “ON” or “OFF”.  With topic xxxx/onoff/arduino, PUBLISH alternately with True/False.
* Gateway takes these topics, converts between MQTT and MQTT-SN , realy between client and broker.     
  
>1. From the set-up, LED light on Arduino will flash, and Linux client will be ON/OFF and print out accordingly.    
2. Gateway will output a communication log into RAM simultaneously, display the log and you should be able to understand MQTT-SN protocol more easily.    

## How to build Linux Client    
### step1. in Home Directory, download library from Github   
 
    $ git clone https://github.com/ty4tw/MQTTSNAsyncClient.git  
    
in MQTTSNAsyncClient/src, you can find the source code Application.cpp and the library you need for MQTTSNAsyncClient/src/lib    
     
### step2. compile Application.cpp   
 
    $ cd MQTTSNAsyncClient
    
if there is no error, copy the Client program.   
   
    $ make install   
    
execution module TomyAsyncClient is then copied to Home Directory.    
    
### step3. execute on Client   
  
    $ cd
    $ ./TomyAsyncClient        

At this point, Gateway is not ready so nothing actually happened. However if use wireshark to monitor, you can see that SEARCHGW messages have been sent over UDP.    
You can also uncomment line 63 and 64 of MqttsnClientApp.h and compile again. This will get you standard output of the message which was sent over UDP.   
     
![](https://qiita-image-store.s3.amazonaws.com/0/41752/c4b262bb-36f4-aa96-0b2e-59bcd62272e5.png)
