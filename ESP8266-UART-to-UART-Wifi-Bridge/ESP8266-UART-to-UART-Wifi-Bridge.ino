/*
 * ESP8266 UART <-> WiFi(UDP) <-> UART Bridge
 * ESP8266 TX of Serial1 is GPIO2 
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>

const char* ssid = "**********";
const char* password = "**********";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets

#define bufferSize 8192
uint8_t buf[bufferSize];
uint8_t iofs=0;
IPAddress remoteIp;
unsigned int remotePort;
char myDomainName[16] = {0};
char remoteDomainName[16] = {0};

void setup()
{
  delay(1000);
  Serial1.begin(115200); // for Debug print
  Serial.begin(115200); // You can change
 
  Serial1.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial1.print(".");
  }
  Serial1.println(" connected");

  Udp.begin(localUdpPort);
  Serial1.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  sprintf(myDomainName, "ESP_%06X", ESP.getChipId());
  Serial1.print("Hostname: ");
  Serial1.println(myDomainName);
  // Set up mDNS responder:
  // - first argument is the domain name, in this example
  //   the fully-qualified domain name is "esp8266.local"
  // - second argument is the IP address to advertise
  //   we send our IP address on the WiFi network
  if (!MDNS.begin(myDomainName)) {
    Serial1.println("Error setting up MDNS responder!");
  }
  Serial1.println("mDNS responder started");

  // Announce esp8266_wifi udp service on port 4210
  MDNS.addService("esp8266_wifi", "udp", localUdpPort);
}


void loop()
{
  static int validRemoteIp = 0;

  MDNS.update();
 
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial1.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial1.printf("UDP packet contents: %s\n", incomingPacket);
    Serial.print(incomingPacket);
  }

  if(Serial.available()) {
   
    while(Serial.available()) {
      buf[iofs] = (char)Serial.read(); // read char from UART
      if(iofs<bufferSize-1) {
        iofs++;
      }
    }

    if (validRemoteIp == 0) {
      // Send out query for esp8266_wifi udp services
      Serial1.println("Sending mDNS query");
      int n = MDNS.queryService("esp8266_wifi", "udp");
      Serial1.println("mDNS query done");
      if (n == 0) {
        Serial1.println("no services found");
      } else {
        Serial1.print(n);
        Serial1.println(" service(s) found");
        for (int i = 0; i < n; ++i) {
          // Print details for each service found
          Serial1.print(i + 1);
          Serial1.print(": ");
          Serial1.print(MDNS.hostname(i));
          Serial1.print(" (");
          Serial1.print(MDNS.IP(i));
          Serial1.print(":");
          Serial1.print(MDNS.port(i));
          Serial1.println(")");
    
          MDNS.hostname(i).toCharArray(remoteDomainName, sizeof(remoteDomainName)); 
          if (strcmp(remoteDomainName, myDomainName) != 0) {
            remoteIp = MDNS.IP(i);
            remotePort = MDNS.port(i);
            validRemoteIp = 1;
          }
        }
      }
      Serial1.println();
      Serial1.print("remoteIp=");
      Serial1.println(remoteIp);
      Serial1.print("remotePort=");
      Serial1.println(remotePort);
    }
    
    Serial1.print("validRemoteIp=");
    Serial1.println(validRemoteIp);
    if (validRemoteIp) {
      Udp.beginPacket(remoteIp, remotePort); // remote IP and port
      Udp.write(buf, iofs);
      Udp.endPacket();
    }
    iofs = 0;
  }
}
