#include <Ethernet.h>
#include <TimeUDP.h>

// Replace with your Teensy's MAC address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

unsigned int localPort = 8888;

EthernetUDP udp;

void setup() {
  Ethernet.begin(mac);
  udp.begin(localPort);

  TimeUDP timeUDP(udp, IPAddress(0, 0, 0, 0), localPort);
  Serial.begin(115200);
}

void loop() {
  time_t receivedTime = timeUDP.receiveTime();
  if (receivedTime != 0) {
    setTime(receivedTime);
    Serial.print("Received time: ");
    Serial.println(receivedTime);
  } else {
    Serial.println("Bad time checksum");
  }
}
