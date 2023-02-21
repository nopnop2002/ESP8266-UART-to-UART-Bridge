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
This project runs both nodes in STA mode.   
The IP address of the other side can be found using mDNS.   
Therefore, we don't need to worry about the boot order of ESP8266.   
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
we don't need to worry about the boot order of ESP8266.   

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

You can use ESP8266 as WiFi router.   
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
