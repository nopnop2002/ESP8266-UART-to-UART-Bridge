# ESP8266-UART-to-UART-Bridge

Transparent UART to UART Bridge using ESP8266.   

# Before   

|Microprocessor-1||Microprocessor-2|
|:-:|:-:|:-:|
||UART||
|TX||RX|
|RX||TX|
|GND||GND|

# Using WiFi   
Many similar apps have been released, but they often use AP mode servers and STA mode clients.   
In this case, it is necessary to start the AP mode server first.   
If the STA mode client is started first, it will fail to connect to the AP.   
This project runs both nodes in STA mode.   
The IP address of the other side can be found using mDNS.   
__Therefore, we don't need to worry about the boot order of ESP8266.__   
|Microprocessor-1||ESP8266-1||ROUTER||ESP8266-2||Microprocessor-2|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
||UART||WiFi||WiFi||UART||
|TX||RX||||TX||RX|
|RX||TX||||RX||TX|
|GND||GND||||GND||GND|

![slide1](https://user-images.githubusercontent.com/6020549/220303303-9f0e7907-5a2e-4ab1-809d-78cd3b64897e.JPG)



# Using ESPNOW   
This project uses ESPNOW broadcast to find the MAC address of the other side.   
There is no need to register the MAC address of the other side.   
__We don't need to worry about the boot order of ESP8266.__   

|Microprocessor-1||ESP8266-1||ESP8266-2||Microprocessor-2|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
||UART||ESPNOW||UART||
|TX||RX||TX||RX|
|RX||TX||RX||TX|
|GND||GND||GND||GND|

![slide3](https://user-images.githubusercontent.com/6020549/220303392-85d6e234-8dc1-48c5-b0ba-ab3978840c12.JPG)


# How to use WiFi  
Edit Your SSID & Password.   
Edit UART boudrate.   
Flash sketch to ESP8266-1.   
Flash __same sketch__ to ESP8266-2.   
Connect Microprocessor-1 to ESP8266-1 via UART.   
Connect Microprocessor-2 to ESP8266-2 via UART.   
Send data from Microprocessor-1 to ESP8266-1.   
Receive data from ESP8266-2 to Microprocessor-2.   


You can use ESP8266 as a __dedicated__ WiFi router.   
esp_wifi_repeater   
https://github.com/martin-ger/esp_wifi_repeater   

|Microprocessor-1||ESP8266-1||ESP8266-3(esp_wifi_repeater)||ESP8266-2||Microprocessor-2|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
||UART||WiFi||WiFi||UART||
|TX||RX||||TX||RX|
|RX||TX||||RX||TX|
|GND||GND||||GND||GND|

![slide2](https://user-images.githubusercontent.com/6020549/220303636-3bda6f4c-0e68-450e-b434-d53a35f08c46.JPG)

# How to use ESPNOW  
Edit UART boudrate.   
Flash sketch to ESP8266-1.   
Flash __same sketch__ to ESP8266-2.   
Connect Microprocessor-1 to ESP8266-1 via UART.   
Connect Microprocessor-2 to ESP8266-2 via UART.   
Send data from Microprocessor-1 to ESP8266-1.   
Receive data from ESP8266-2 to Microprocessor-2.   


# How to disable ESP8266 boot messages
ESP8266 boot rom writes a log to the UART when booting like this:   
This message can cause unexpected trouble.   

```
ets Jan  8 2014,rst cause 1, boot mode:(3,7)

load 0x40100000, len 24236, room 16
tail 12
chksum 0xb7
ho 0 tail 12 room 4
load 0x3ffe8000, len 3008, room 12
tail 4
chksum 0x2c
load 0x3ffe8bc0, len 4816, room 4
tail 12
chksum 0x46
csum 0x46
```

### Swap UART
UART can be swapped by adding the following one line:
```
Serial.swap();   
```
TX / RX changes to the following when UART is swapped.
```
GPIO15(TXD)   --- RX
GPIO13(RXD)   --- TX
```
The boot message does not reach RX port of other side.   
However, since GPIO15 is a pin that determines the boot mode, ESP8266 does not start.   
__This method cannot be used.__   

### Add a circuit
If the following circuit is added, All messages does not reach RX port of the other side.   
I used 1N5819 Schottky Barrier Plastic Rectifier.   

![UART_BOOT_MESSAGE](https://user-images.githubusercontent.com/6020549/74654209-28084e80-51cd-11ea-8af5-d0c03551a484.jpg)

To start transmission, set the GPIO polarity to OUTPUT and the level to LOW.   

```
void setup() {
	pinMode(GPIO, OUTPUT);
	digitalWrite(GPIO, LOW);
	Serial.begin(115200);
```

NOTE:GPIO15 is pulled down and cannot be used for this.   

