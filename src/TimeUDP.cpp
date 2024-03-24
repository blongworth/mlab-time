#include "TimeUDP.h"

TimeUDP::TimeUDP(EthernetUDP& udp, IPAddress remoteIP, unsigned int remotePort)
    : _udp(udp), _remoteIP(remoteIP), _remotePort(remotePort) {}

void TimeUDP::sendTime() {
  time_t currentTime = now();
  byte timeBytes[8];
  memcpy(timeBytes, &currentTime, sizeof(time_t));

  uint8_t checksum = calculateChecksum(timeBytes, sizeof(time_t));

  _udp.beginPacket(_remoteIP, _remotePort);
  _udp.write(timeBytes, sizeof(time_t));
  _udp.write(checksum);
  _udp.endPacket();
}

time_t TimeUDP::receiveTime() {
  int packetSize = _udp.parsePacket();
  if (packetSize == sizeof(time_t) + 1) {
    byte timeBytes[8];
    _udp.read(timeBytes, sizeof(time_t));
    uint8_t receivedChecksum = _udp.read();

    uint8_t checksum = calculateChecksum(timeBytes, sizeof(time_t));

    if (checksum == receivedChecksum) {
      time_t receivedTime;
      memcpy(&receivedTime, timeBytes, sizeof(time_t));
      return receivedTime;
    }
  }

  return 0; // Return 0 if checksum doesn't match or packet size is incorrect
}

uint8_t TimeUDP::calculateChecksum(byte* data, size_t len) {
  uint8_t checksum = 0;
  for (size_t i = 0; i < len; i++) {
    checksum ^= data[i];
  }
  return checksum;
}
