#include <Arduino.h>
#include <SPI.h>
#include <w25q64.hpp>

#define CS_PIN 5
#define SCK_PIN 8
#define MISO_PIN 19
#define MOSI_PIN 23

// request
#define GET_CHIP_ID 0x9F

// panjang ID
#define LEN_ID 4

byte chip_id[4];
unsigned char write_Page[256] = "";
unsigned char read_Page[256] = "";

w25q64 spiChip;

void setup()
{
  Serial.begin(9600);
  spiChip.begin();

  spiChip.getId(chip_id);
  for (int i = 0; i < LEN_ID; i++)
  {
    Serial.print(chip_id[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Menulis data ke chip W25Q64
  memcpy(write_Page, "Teknik Komputer UPI", sizeof("Teknik Komputer UPI"));
  spiChip.erasePageSector(0xFFFF);
  spiChip.pageWrite(write_Page, 0xFFFF);
  Serial.println("Done writing");
  delay(1000);

  // Baca hasil penulisan data di W25Q64
  Serial.println("Start Reading...");
  spiChip.readPages(read_Page, 0xFFFF, 1);
  for (int i = 0; i < 256; i++)
  {
    if (read_Page[i] > 8 && read_Page[i] < 127)
      Serial.print((char)read_Page[i]);
  }
  Serial.println();
}

void loop()
{
}
