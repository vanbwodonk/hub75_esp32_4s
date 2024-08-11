#include <Arduino.h>

#define R1_PIN 27
#define G1_PIN 26
#define B1_PIN 25

#define R2_PIN 13
#define G2_PIN 12
#define B2_PIN 14

#define A_PIN 23
#define B_PIN 19
#define C_PIN 5
#define D_PIN 17
#define E_PIN 22

#define CLK_PIN 16
#define OE_PIN 15
#define LAT_PIN 4

void blinker(void *arg)
{
  pinMode(LED_BUILTIN, OUTPUT);
  while (1)
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
}

void setAddress(uint8_t addr);

void setup()
{
  ledcAttach(OE_PIN, 5000, 8);
  pinMode(LED_BUILTIN, OUTPUT);
  // set pin mode
  pinMode(R1_PIN, OUTPUT);
  pinMode(G1_PIN, OUTPUT);
  pinMode(B1_PIN, OUTPUT);

  pinMode(R2_PIN, OUTPUT);
  pinMode(B2_PIN, OUTPUT);
  pinMode(G2_PIN, OUTPUT);

  pinMode(A_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(C_PIN, OUTPUT);
  pinMode(D_PIN, OUTPUT);
  pinMode(E_PIN, OUTPUT);

  pinMode(CLK_PIN, OUTPUT);
  pinMode(LAT_PIN, OUTPUT);

  // init pin value
  digitalWrite(R1_PIN, LOW);
  digitalWrite(G1_PIN, LOW);
  digitalWrite(B1_PIN, LOW);

  digitalWrite(R2_PIN, LOW);
  digitalWrite(G2_PIN, LOW);
  digitalWrite(B2_PIN, LOW);

  digitalWrite(A_PIN, HIGH);
  digitalWrite(B_PIN, HIGH);
  digitalWrite(C_PIN, HIGH);
  digitalWrite(D_PIN, HIGH);
  digitalWrite(E_PIN, HIGH);

  digitalWrite(CLK_PIN, LOW);
  digitalWrite(LAT_PIN, LOW);

  ledcAttach(OE_PIN, 5000, 8);
  ledcWrite(OE_PIN, 253);

  xTaskCreatePinnedToCore(blinker, "blinker", 8000, NULL, 2, NULL, 0);
}

uint8_t idx = 0, idx_cnt = 0, addrs = 0;
void loop()
{
  for (int i = 0; i < 64; i++)
  {
    if (i == 0 && addrs == 1)
    {
      digitalWrite(R1_PIN, HIGH);
      digitalWrite(R2_PIN, HIGH);
    }
    else
    {
      digitalWrite(R1_PIN, LOW);
      digitalWrite(G1_PIN, LOW);
      digitalWrite(B1_PIN, LOW);
      digitalWrite(R2_PIN, LOW);
      digitalWrite(G2_PIN, LOW);
      digitalWrite(B2_PIN, LOW);
    }
    digitalWrite(CLK_PIN, HIGH);
    digitalWrite(CLK_PIN, LOW);
  }
  digitalWrite(LAT_PIN, HIGH);
  digitalWrite(LAT_PIN, LOW);

  addrs++;
  if (addrs == 4)
    addrs = 0;
  setAddress(addrs);

  // delay to see pattern scan
  delay(5);
  idx_cnt++;
  if (idx_cnt == 8)
  {
    idx_cnt = 0;
    idx++;
    if (idx == 64)
      idx = 0;
  }
}

/*
  HUB75 1/4 scan has 2 addr A & B
  HUB75 1/8 scan has 3 addr A, B, C
  HUB75 1/16 scan has 4 addr A, B, C, D
  HUB75 1/32 scan has 5 addr A, B, C, D, E
*/
void setAddress(uint8_t addr)
{
  switch (addr)
  {
  case 0:
    digitalWrite(A_PIN, LOW);
    digitalWrite(B_PIN, LOW);
    digitalWrite(C_PIN, LOW);
    break;
  case 1:
    digitalWrite(A_PIN, HIGH);
    digitalWrite(B_PIN, LOW);
    digitalWrite(C_PIN, LOW);
    break;
  case 2:
    digitalWrite(A_PIN, LOW);
    digitalWrite(B_PIN, HIGH);
    digitalWrite(C_PIN, LOW);
    break;
  case 3:
    digitalWrite(A_PIN, HIGH);
    digitalWrite(B_PIN, HIGH);
    digitalWrite(C_PIN, LOW);
    break;
  case 4:
    digitalWrite(A_PIN, LOW);
    digitalWrite(B_PIN, LOW);
    digitalWrite(C_PIN, HIGH);
    break;
  case 5:
    digitalWrite(A_PIN, HIGH);
    digitalWrite(B_PIN, LOW);
    digitalWrite(C_PIN, HIGH);
    break;
  case 6:
    digitalWrite(A_PIN, LOW);
    digitalWrite(B_PIN, HIGH);
    digitalWrite(C_PIN, HIGH);
    break;
  case 7:
    digitalWrite(A_PIN, HIGH);
    digitalWrite(B_PIN, HIGH);
    digitalWrite(C_PIN, HIGH);
    break;
  default:
    digitalWrite(A_PIN, LOW);
    digitalWrite(B_PIN, LOW);
    digitalWrite(C_PIN, LOW);
    break;
  }
}