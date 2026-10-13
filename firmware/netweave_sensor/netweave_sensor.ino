#include "config.h"

struct Counters {
  unsigned long total, syn, icmp, arp;
};
Counters c = {};
unsigned long windowStart = 0;

// TODO: dipanggil tiap ada paket dari port mirror (hanya baca header)
void onPacket() {
  c.total++;
  // TODO: klasifikasi dari header: TCP SYN, ICMP, ARP, dll.
}

void checkWindow() {
  if (c.syn > SYN_FLOOD_THRESHOLD)   Serial.println("ALERT: SYN flood");
  if (c.icmp > ICMP_FLOOD_THRESHOLD) Serial.println("ALERT: ICMP flood");
  if (c.arp > ARP_THRESHOLD)         Serial.println("ALERT: ARP spoofing");
  Serial.printf("total=%lu syn=%lu icmp=%lu arp=%lu\n",
                c.total, c.syn, c.icmp, c.arp);
  c = {};
}

void setup() {
  Serial.begin(115200);
  windowStart = millis();
}

void loop() {
  if (millis() - windowStart >= WINDOW_MS) {
    checkWindow();
    windowStart = millis();
  }
}