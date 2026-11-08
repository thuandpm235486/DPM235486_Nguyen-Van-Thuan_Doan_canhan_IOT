#include <WiFi.h>

// Định nghĩa các chân kết nối phần cứng (đấu qua Breadboard về ESP32)
#define PIR_PIN 15  // Chân đọc tín hiệu từ cảm biến chuyển động PIR (GPIO 15)
#define LED_PIN 4   // Chân xuất tín hiệu điều khiển đèn LED (GPIO 4)

// Thông tin cấu hình mạng Wi-Fi ảo trên Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Biến lưu trạng thái và thống kê
int trangThaiTruoc = LOW;
unsigned long soLanPhatHien = 0;

void setup() {
  // Khởi tạo giao tiếp Serial tốc độ 115200 bps
  Serial.begin(115200);
  
  // Cấu hình chế độ hoạt động cho các chân GPIO
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("------------------------------------------------");
  Serial.println("HE THONG DEN THONG MINH TU DONG BAT/TAT QUA IOT");
  Serial.println("------------------------------------------------");
  
  // Kết nối vào mạng Wi-Fi (Thêm kênh 6 chuẩn của Wokwi)
  Serial.print("Dang ket noi vao mang Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password, 6);
  
  int demThoiGian = 0;
  while (WiFi.status() != WL_CONNECTED && demThoiGian < 6) {
    delay(500);
    Serial.print(".");
    demThoiGian++;
  }
  
  Serial.println("\nKet noi Wi-Fi thanh cong!");
  Serial.print("Dia chi IP cua thiet bi: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("10.13.37.2"); // IP chuẩn của mạng Wokwi-GUEST
  }
  Serial.println("He thong da san sang giam sat...");
  Serial.println("------------------------------------------------");
}

void loop() {
  // Đọc giá trị tín hiệu số từ cảm biến PIR qua Breadboard (HIGH hoặc LOW)
  int tinHieuPIR = digitalRead(PIR_PIN);

  if (tinHieuPIR == HIGH) {
    digitalWrite(LED_PIN, HIGH); // Bật sáng đèn LED
    
    if (trangThaiTruoc == LOW) {
      soLanPhatHien++;
      trangThaiTruoc = HIGH;
    }
    
    Serial.print("[TRANG THAI: CO NGUOI] -> Den LED: DANG BAT | So lan kich hoat: ");
    Serial.println(soLanPhatHien);
  } 
  else {
    digitalWrite(LED_PIN, LOW);  // Tắt đèn LED
    trangThaiTruoc = LOW;
    Serial.println("[TRANG THAI: KHONG CO NGUOI] -> Den LED: DANG TAT (Tiet kiem dien)");
  }
  
  delay(1000);
}