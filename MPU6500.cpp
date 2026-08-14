#include <Wire.h>

const int MPU_ADDR = 0x68; // Alamat I2C MPU6500


//PIN NCS ke 3.3V
//PIN AD0 ke GND
void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Membangunkan MPU6500 dari mode sleep (Register 0x6B)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // Set ke 0 untuk membangunkan sensor
  Wire.endTransmission(true);

  Serial.println("--- Mulai Uji Coba Sensor MPU6500 (Raw I2C) ---");
  delay(2000);
}

void loop() {
  // Meminta 6 byte data mulai dari register 0x3B (ACCEL_XOUT_H)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  // Membaca data akselerometer (X, Y, Z)
  int16_t accX = (Wire.read() << 8 | Wire.read());
  int16_t accY = (Wire.read() << 8 | Wire.read());
  int16_t accZ = (Wire.read() << 8 | Wire.read());

  // Kalkulasi nilai Pitch dan Roll 
  float roll = atan2(accY, accZ) * 180.0 / PI;
  float pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;

  // Gunakan nilai absolut untuk mendeteksi kemiringan dari segala arah
  float absRoll = abs(roll);
  float absPitch = abs(pitch);
  
  // Mengambil nilai kemiringan paling ekstrem
  float maxTilt = max(absRoll, absPitch);

  Serial.print("Roll: ");
  Serial.print(absRoll, 1);
  Serial.print("° | Pitch: ");
  Serial.print(absPitch, 1);
  Serial.print("° | STATUS: ");

  // Logika Klasifikasi Kestabilan Perahu
  if (maxTilt >= 90.0) {
    Serial.println("TERBALIK");
  } else if (maxTilt >= 60.0 && maxTilt < 90.0) {
    Serial.println("WASPADA");
  } else {
    Serial.println("AMAN");
  }

  delay(1000); // Jeda 1 detik
}
