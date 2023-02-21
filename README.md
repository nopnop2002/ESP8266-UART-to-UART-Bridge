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

|Microprocessor-1||ESP8266-1||ROUTER||ESP8266-2||Microprocessor-2|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
||UART||WiFi||WiFi||UART||
|TX||RX||||TX||RX|
|RX||TX||||RX||TX|
|GND||GND||||GND||GND|

![slide1](https://user-images.githubusercontent.com/6020549/220303303-9f0e7907-5a2e-4ab1-809d-78cd3b64897e.JPG)



# Using ESPNOW   

|Microprocessor-1||ESP8266-1||ESP8266-2||Microprocessor-2|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
||UART||ESPNOW||UART||
|TX||RX||X||RX|
|RX||TX||X||TX|
|GND||GND||GND||GND|

![slide3](https://user-images.githubusercontent.com/6020549/220303392-85d6e234-8dc1-48c5-b0ba-ab3978840c12.JPG)


# How to use WiFi  
Edit Your SSID & Password.   
Edit UART boudrate.   
Flash sketch to ESP8266-1.   
Flash same sketch to ESP8266-2.   
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
Flash same sketch to ESP8266-2.   
Connect Microprocessor-1 to ESP8266-1 via UART.   
Connect Microprocessor-2 to ESP8266-2 via UART.   
Send data from Microprocessor-1 to ESP8266-1.   
Receive data from ESP8266-2 to Microprocessor-2.   
