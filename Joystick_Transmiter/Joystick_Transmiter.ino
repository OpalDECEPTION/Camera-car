
#include <RH_RF69.h>

#define RF69_FREQ 915.0

#define RFM69_RST 2
#define RFM69_INT 3
#define RFM69_CS 4

#define yInput A3
#define xInput A4


int hello = 0;

RH_RF69 rf69(RFM69_CS, RFM69_INT);

int16_t packetnum = 0;

void setup() {
  Serial.begin(115200);
  pinMode(RFM69_RST, OUTPUT);

  digitalWrite(RFM69_RST, LOW);

  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1)
      ;
  }
  Serial.println("RFM69 radio init OK!");
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  rf69.setTxPower(20, true);

  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  rf69.setEncryptionKey(key);

  Serial.print("RFM69 radio @");
  Serial.print((int)RF69_FREQ);
  Serial.println(" MHz");
}

void loop() {

  int x = analogRead(A3);
  int y = analogRead(A4);

  Serial.println();
  Serial.print("x = ");
  Serial.println(x);
  Serial.print("y = ");
  Serial.println(y);

  int pos = map(x, 1, 1023, 0, 9);
  Serial.print("Position = ");
  Serial.println(pos);

  int speed = map(y, 1, 1023, 0, 9);
  Serial.print("Speed = ");
  Serial.println(speed);

  int z;
  char radiopacket[20] = " ";

  if (pos == 0) {
    radiopacket[1] = '0';
  }
  if (pos == 1) {
    radiopacket[1] = '1';
  }
  if (pos == 2) {
    radiopacket[1] = '2';
  }
  if (pos == 3) {
    radiopacket[1] = '3';
  }
  if (pos == 4) {
    radiopacket[1] = '4';
  }
  if (pos == 5) {
    radiopacket[1] = '5';
  }
  if (pos == 6) {
    radiopacket[1] = '6';
  }
  if (pos == 7) {
    radiopacket[1] = '7';
  }
  if (pos == 8) {
    radiopacket[1] = '8';
  }
  if (pos == 9) {
    radiopacket[1] = '9';
  }
  if (speed == 0) {
    radiopacket[2] = '0';
  }
  if (speed == 1) {
    radiopacket[2] = '1';
  }
  if (speed == 2) {
    radiopacket[2] = '2';
  }
  if (speed == 3) {
    radiopacket[2] = '3';
  }
  if (speed == 4) {
    radiopacket[2] = '4';
  }
  if (speed == 5) {
    radiopacket[2] = '5';
  }
  if (speed == 6) {
    radiopacket[2] = '6';
  }
  if (speed == 7) {
    radiopacket[2] = '7';
  }
  if (speed == 8) {
    radiopacket[2] = '8';
  }
  if (speed == 9) {
    radiopacket[2] = '9';
  }


  Serial.print("Sending -");
  Serial.println(radiopacket);

  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf69.waitPacketSent();
delay(20);
}
