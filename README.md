# ESP8266-UART-to-UART-Wifi-Bridge

Transparent UART to UART Bridge using ESP8266.   

# Before   

|Microprocessor-1||Microprocessor-2|
|:-:|:-:|:-:|
||UART||
|TX||RX|
|RX||TX|
|GND||GND|

# After   

|Microprocessor-1||ESP8266-1||WifiAP||ESP8266-2||Microprocessor-2|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
||UART||Wifi||Wifi||UART||
|TX||RX||||TX||RX|
|RX||TX||||RX||TX|
|GND||GND||||GND||GND|

![image1](https://user-images.githubusercontent.com/6020549/51569293-45da8580-1edf-11e9-9606-17c2ff43674e.JPG)

# How to use   
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
||UART||Wifi||Wifi||UART||
|TX||RX||||TX||RX|
|RX||TX||||RX||TX|
|GND||GND||||GND||GND|

![image2](https://user-images.githubusercontent.com/6020549/51569295-483cdf80-1edf-11e9-912b-94245c3f4ba7.JPG)
