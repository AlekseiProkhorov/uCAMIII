#include <SPI.h>
#include <SD.h>
#include <uCamIII.h>

File picture_file;
int picture_number = 0;
String picture_file_name;

HardwareSerial camera_interface(USART3);
UCAMIII camera(&camera_interface);

const int spi_CS_pin = PA4;

void setup() {
  camera.begin();
  Serial.begin(115200, SERIAL_8E1);

  if (!SD.begin(spi_CS_pin)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialization done.");
}

void loop() {
  picture_file_name = "picture" + String(picture_number) + ".jpg";
  picture_file = SD.open(picture_file_name, FILE_WRITE);
  
  if (picture_file) {
    camera.save_to_sd(&picture_file);
    picture_file.close();
    
    Serial.println("Picture: " + picture_file_name + " saved.");
    picture_number += 1;
  }
}