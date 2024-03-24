#include <Ethernet.h>
#include <TimeUDP.h>

// Replace with your Teensy's MAC address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Replace with the IP address of the receiving Teensy
IPAddress remoteIP(192, 168, 1, 100);
unsigned int remotePort = 8888;

EthernetUDP udp;

void setup() {
  Ethernet.begin(mac);
  udp.begin(remotePort);

  TimeUDP timeUDP(udp, remoteIP, remotePort);

  // Set the initial time
  setTime(12, 0, 0, 22, 3, 2024);
}

void loop() {
  timeUDP.sendTime();
  delay(1000); // Send the time every second
}
