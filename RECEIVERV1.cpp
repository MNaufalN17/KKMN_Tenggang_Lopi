#include <SPI.h>
#include <LoRa.h>

#define ss 5
#define rst 14
#define dio0 26

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("--- INISIALISASI GATEWAY TENGGANG LOPI ---");

  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("❌ LoRa Gateway Gagal!");
    while (1) delay(10);
  }
  
  Serial.println("✅ LoRa Gateway Siap! Menunggu telemetri dari laut...");
  Serial.println("==================================================");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    String dataMasuk = "";
    while (LoRa.available()) {
      dataMasuk += (char)LoRa.read();
    }

    Serial.print("[DATA MASUK] ");
    Serial.print(dataMasuk);
    Serial.print(" | Kekuatan Sinyal (RSSI): ");
    Serial.print(LoRa.packetRssi());
    Serial.println(" dBm");
  }
}
