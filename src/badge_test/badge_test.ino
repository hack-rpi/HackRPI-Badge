#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

uint8_t bytes[8] = {0b00000000,
                    0b00000000,
                    0b00000000,
                    0b10010000,
                    0b10010000,
                    0b11110000,
                    0b10010000,
                    0b10010000};

#include <SPI.h>

#define CLOCK 14
#define DATA 13
//#define INPUT 12

uint8_t LAT      = 5;
uint8_t LED_OE   = 4;
uint8_t FLASH_CS = 0;
uint8_t INPUT_CS = 2;

void shiftOutFast(byte data)
{
  byte i = 8;
    do{
      GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1 << CLOCK);
      if(data & 0x80)
        GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1 << DATA);
      else
        GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1 << DATA);
      GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1 << CLOCK);
      data <<= 1;
    }while(--i);
    return;
}

void setup() {
  pinMode(LED_OE, OUTPUT);
  pinMode(LAT, OUTPUT);
  pinMode(FLASH_CS, OUTPUT);
  pinMode(INPUT_CS, OUTPUT);
  //pinMode(DATA, OUTPUT);
  //pinMode(CLOCK, OUTPUT);
  pinMode(SCK, OUTPUT);
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, OUTPUT);

  digitalWrite(LED_OE, LOW);
  digitalWrite(LAT, LOW);
  digitalWrite(FLASH_CS, HIGH);
  digitalWrite(INPUT_CS, HIGH);
  SPI.setFrequency(500000);
  SPI.begin();
  WiFi.forceSleepBegin();
}

void loop() {
  uint8_t a[3];
  uint8_t i;

  for (i = 0; i < 8; i++)
  {
    a[1] = (1 << i);
    a[2] = bytes[i];
    a[0] = bytes[i];
    SPI.beginTransaction(SPISettings(1000000, LSBFIRST, SPI_MODE0));
    SPI.writeBytes(a, 3);
    SPI.endTransaction();
    digitalWrite(LAT, LOW);
    digitalWrite(LAT, HIGH);
    delayMicroseconds(100);
  }

  //shiftOutFast(0xFF);
  //shiftOutFast(0xFF);
  //shiftOutFast(0xFF);
  
  //digitalWrite(2, HIGH);
  //delay(1);
}
