#define UART_interface Serial
#include <uCamIII.h>

HardwareSerial camera_interface(USART3);
UCAMIII camera(&camera_interface, &UART_interface);

void setup() {
  camera.begin();
  Serial.begin(115200, SERIAL_8E1);
}

void loop() {
  camera.print_picture();
}