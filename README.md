# ESP8266-UART-to-UART-Wifi-Bridge

Transparent UART to UART Bridge using ESP8266.   

# Before   

|Microprocessor-1||Microprocessor-2|
|:-:|:-:|:-:|
||UART||

# After   

|Microprocessor-1||ESP8266-1||WifiAP||ESP8266-2||Microprocessor-2|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
||UART||Wifi||Wifi||UART||
|TX||RX||RX||TX||

# How to use   
Edit Your SSID & Password.   
Edit UART boudrate.   
Flash sketch to ESP8266-1.   
Flash same sketch to ESP8266-2.   
Connect Microprocessor-1 to ESP8266-1 via UART.   
Connect Microprocessor-2 to ESP8266-2 via UART.   
Send data from Microprocessor-1 to Microprocessor-2.   
Responce data from Microprocessor-2 to Microprocessor-1.   
