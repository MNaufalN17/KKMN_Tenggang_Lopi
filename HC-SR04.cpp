// Definisi Pin HC-SR04
const int TRIG_PIN = 5;
const int ECHO_PIN = 18;

// Kecepatan suara di udara (0.0343 cm/mikrodetik)
const float SOUND_SPEED = 0.0343;

void setup() {
  Serial.begin(115200); 
  
  // Konfigurasi Pin
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.println("--- Mulai Uji Coba Sensor HC-SR04 (Deteksi Kebocoran) ---");
  delay(2000);
}

void loop() {
  // 1. Memastikan pin Trigger bersih
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // 2. Mengirimkan gelombang ultrasonik selama 10 mikrodetik
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // 3. Membaca durasi gelombang pantulan (Echo)
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // 4. Menghitung Jarak (cm)
  // Rumus: (Durasi * Kecepatan Suara) / 2 (karena bolak-balik)
  float distance = (duration * SOUND_SPEED) / 2;

  // 5. Menampilkan Output ke Serial Monitor
  Serial.print("Jarak Air: ");
  Serial.print(distance, 1);
  Serial.print(" cm | STATUS LAMBUNG: ");

  // 6. Logika Deteksi Kebocoran
  if (distance < 15.0) {
    Serial.println("TENGGELAM (Kirim SOS!)");
  } else if (distance >= 15.0 && distance < 50.0) {
    Serial.println("BOCOR (Waspada)");
  } else {
    Serial.println("AMAN");
  }

  delay(1000); // Jeda pembacaan 1 detik
}
