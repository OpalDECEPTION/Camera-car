#include <RH_RF69.h>
#include <PWMServo.h>

#define RFM69_RST 2
#define RFM69_INT 3
#define RFM69_CS 4

#define MOTOR1 7
#define MOTOR2 6
#define MOTORPWM 5

#define RF69_FREQ 915.0

int speed = 0;
int pos = 0;

PWMServo myservo;

RH_RF69 rf69(RFM69_CS, RFM69_INT);

void setup() {
  Serial.begin(115200);
  delay(3000);
  pinMode(MOTORPWM, OUTPUT);

  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  digitalWrite(RFM69_RST, HIGH);  //manual reset
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  myservo.attach(10);

  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1)
      ;
  }

  Serial.println("RFM69 radio init OK!");

  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  rf69.setEncryptionKey(key);

  Serial.print("RFM69 radio @");
  Serial.print((int)RF69_FREQ);
  Serial.println(" MHz");
}

void loop() {
  if (rf69.available()) {

    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf69.recv(buf, &len)) {

      if (!len) return;
      buf[len] = 0;
      int x = buf[1];
      int y = buf[2];
      Serial.print("Initial speed = ");
      Serial.println(y);
      Serial.print("Initial pos = ");
      Serial.println(x);

      pos = map(x, 48, 57, 65, 140);
      myservo.write(pos);

      if (y < 52) {
        digitalWrite(MOTOR1, LOW);
        digitalWrite(MOTOR2, HIGH);
        Serial.println("Backward");
        speed = map(y, 48, 52, 250, 0);
      }
      if (y > 52) {
        digitalWrite(MOTOR1, HIGH);
        digitalWrite(MOTOR2, LOW);
        Serial.println("Foreward");
        speed = map(y, 52, 57, 0, 250);
      }


      if (y == 52) {
        speed = 10;
        Serial.println("STOP");
      }
      if (speed > 20) {
        analogWrite(MOTORPWM, speed);
      } else {
        digitalWrite(MOTORPWM, LOW);
      }


      Serial.print("speed = ");
      Serial.println(speed);
      Serial.print("pos = ");
      Serial.println(pos);
      Serial.println();
    }
  }
}
