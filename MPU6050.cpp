#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // Tunggu koneksi serial

  Serial.println("--- Mulai Uji Coba Sensor MPU6050 ---");

  // Inisialisasi MPU6050
  if (!mpu.begin()) {
    Serial.println("Gagal menemukan chip MPU6050. Cek kembali wiring I2C (SDA/SCL)!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Berhasil Ditemukan!");

  // Konfigurasi rentang pembacaan sesuai kebutuhan sensitivitas standar
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  delay(2000);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Kalkulasi nilai Pitch dan Roll dari data Akselerometer
  float roll = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / PI;
  float pitch = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180.0 / PI;

  // Gunakan nilai absolut agar pembacaan miring ke kiri/kanan/depan/belakang bernilai sama
  float absRoll = abs(roll);
  float absPitch = abs(pitch);
  
  // Mengambil nilai kemiringan paling ekstrem antara pitch atau roll
  float maxTilt = max(absRoll, absPitch);

  Serial.print("Roll: ");
  Serial.print(absRoll, 1);
  Serial.print("° | Pitch: ");
  Serial.print(absPitch, 1);
  Serial.print("° | STATUS KESTABILAN: ");

  // Logika Klasifikasi sesuai Proposal
  if (maxTilt >= 90.0) {
    Serial.println("TERBALIK");
  } else if (maxTilt >= 60.0 && maxTilt < 90.0) {
    Serial.println("WASPADA");
  } else {
    Serial.println("AMAN");
  }

  delay(1000); // Jeda 1 detik
}
