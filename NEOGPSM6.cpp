#include <TinyGPS++.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;
HardwareSerial gpsSerial(1); // Menggunakan UART 1 pada ESP32

// Definisi pin sesuai tabel wiring
const int RXPin = 16;
const int TXPin = 17;
const uint32_t GPSBaud = 9600; // Baud rate standar pabrik untuk NEO-6M

void setup() {
  Serial.begin(115200);
  
  // Memulai komunikasi serial dengan modul GPS
  gpsSerial.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);
  
  Serial.println("--- Mulai Uji Coba Modul GPS NEO-6M ---");
  Serial.println("Mencari sinyal satelit...");
  Serial.println("PENTING: Bawa alat ke luar ruangan (atap terbuka) agar mendapat sinyal!");
  Serial.println("---------------------------------------");
}

void loop() {
  // Membaca data yang masuk dari GPS
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // Jika lokasi baru berhasil didapatkan (terkunci)
  if (gps.location.isUpdated()) {
    Serial.print("Latitude  : ");
    Serial.println(gps.location.lat(), 6); // Dicetak dengan 6 angka di belakang koma untuk akurasi
    
    Serial.print("Longitude : ");
    Serial.println(gps.location.lng(), 6);
    
    // Mencetak format link langsung ke Google Maps
    Serial.print("Cek di Google Maps: https://www.google.com/maps/place/");
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.println(gps.location.lng(), 6);
    
    Serial.println("---------------------------------------");
  }
}
