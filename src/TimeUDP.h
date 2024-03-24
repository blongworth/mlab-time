#ifndef TimeUDP_h
#define TimeUDP_h

#include <Ethernet.h>
#include <TimeLib.h>

class TimeUDP {
public:
  TimeUDP(EthernetUDP& udp, IPAddress remoteIP, unsigned int remotePort);
  void sendTime();
  time_t receiveTime();

private:
  EthernetUDP& _udp;
  IPAddress _remoteIP;
  unsigned int _remotePort;
  uint8_t calculateChecksum(byte* data, size_t len);
};

#endif
