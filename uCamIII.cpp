#include "UCAMIII.h"
#include "HardwareSerial.h"
#include <SD.h>

byte _SYNC_COMMAND[6] = {0xAA, 0x0D, 0x00, 0x00, 0x00, 0x00};
byte _SYNC_ACK_REPLY[6] = {0xAA, 0x0E, 0x0D, 0x00, 0x00, 0x00};
byte _SYNC_ACK_REPLY_EXT[6] = {0xAA, 0x0D, 0x00, 0x00, 0x00, 0x00};
byte _SYNC_FINAL_COMMAND[6] = {0xAA, 0x0E, 0x00, 0x00, 0xF5, 0x00};

byte INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x07, 0x03, 0x07};
byte _GENERIC_ACK_REPLY[6] = {0xAA, 0x0E, 0x00, 0x00, 0x00, 0x00};
byte _PACK_SIZE[6] = {0xAA, 0x06, 0x08, UCAMIII_BUF_SIZE + 6, 0x00, 0x00};
byte SNAPSHOT[6] = {0xAA, 0x05, 0x00, 0x00, 0x00, 0x00};
byte GET_PICTURE[6] = {0xAA, 0x04, 0x01, 0x00, 0x00, 0x00};

UCAMIII::UCAMIII(HardwareSerial *interface, HardwareSerial *output_interface)
{
  this->image_pos = 0;
  this->package_no = 0;
  this->camSerial = interface;
  this->output_interface = output_interface;
}

UCAMIII::UCAMIII(HardwareSerial *interface)
{
  this->image_pos = 0;
  this->package_no = 0;
  this->camSerial = interface;
}

void UCAMIII::set_picture_format(String format, String resolution)
{
  if (format == "GRAY")
  {
    if (resolution == "80x60")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x03, 0x01, 0x05};
      SNAPSHOT[2] = 0x01;
      GET_PICTURE[2] = 0x02;
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
    else if (resolution == "128x96")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x03, 0x0B, 0x05};
      SNAPSHOT[2] = 0x01;
      GET_PICTURE[2] = 0x02;
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
    else if (resolution == "128x128")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x03, 0x09, 0x05};
      SNAPSHOT[2] = 0x01;
      GET_PICTURE[2] = 0x02;
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
    else if (resolution == "160x120")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x03, 0x03, 0x05};
      SNAPSHOT[2] = 0x01;
      GET_PICTURE[2] = 0x02;
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
  }
  else if (format == "COLOUR")
  {
    if (resolution == "80x60")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x06, 0x01, 0x05};
      SNAPSHOT[2] = 0x01;
      GET_PICTURE[2] = 0x02;
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
    else if (resolution == "128x96")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x06, 0x0B, 0x05};
      SNAPSHOT[2] = 0x01;
      GET_PICTURE[2] = 0x02;
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
    else if (resolution == "128x128")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x06, 0x09, 0x05};
      SNAPSHOT[2] = 0x01;
      GET_PICTURE[2] = 0x02;
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
    else if (resolution == "160x120")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x06, 0x03, 0x05};
      SNAPSHOT[2] = 0x01;
      GET_PICTURE[2] = 0x02;
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
  }
  else if (format == "JPEG")
  {
    if (resolution == "160x128")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x07, 0x03, 0x03};
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
    else if (resolution == "320x240")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x07, 0x03, 0x05};
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
    else if (resolution == "640x480")
    {
      byte NEW_INITIAL_COMMAND[6] = {0xAA, 0x01, 0x00, 0x07, 0x03, 0x07};
      for (int i = 0; i < 6; i++)
      {
        INITIAL_COMMAND[i] = NEW_INITIAL_COMMAND[i];
      }
    }
  }
}

void UCAMIII::save_to_sd_and_print(File *output_interface)
{
  this->sd_interface = output_interface;
  this->image_pos = 0;
  this->package_no = 0;
  short x = 0;
  int bytes;
  if (this->init())
  {
    this->takePicture();
    while ((bytes = this->getData()))
    {
      for (x = 0; x < bytes; x++)
      {
        if (this->imgBuffer[x] < 16)
        {
          this->output_interface->print("0");
        }
        this->output_interface->print(this->imgBuffer[x], HEX);
        this->sd_interface->write(this->imgBuffer[x]);
      }
      this->output_interface->println("");
    }
  }
}

void UCAMIII::save_to_sd(File *output_interface)
{
  this->sd_interface = output_interface;
  this->image_pos = 0;
  this->package_no = 0;
  short x = 0;
  int bytes;
  if (this->init())
  {
    this->takePicture();
    while ((bytes = this->getData()))
    {
      for (x = 0; x < bytes; x++)
      {
        this->sd_interface->write(this->imgBuffer[x]);
      }
    }
  }
}

void UCAMIII::print_picture()
{
  this->image_pos = 0;
  this->package_no = 0;
  short x = 0;
  int bytes;
  if (this->init())
  {
    this->takePicture();
    while ((bytes = this->getData()))
    {
      for (x = 0; x < bytes; x++)
      {
        if (this->imgBuffer[x] < 16)
        {
          this->output_interface->print("0");
        }
        this->output_interface->print(this->imgBuffer[x], HEX);
      }
      this->output_interface->println("");
    }
  }
}

void UCAMIII::begin()
{
  this->camSerial->begin(57600);
}

bool UCAMIII::init()
{
  if (this->attempt_sync())
  {
    return true;
  }
  return false;
}

bool UCAMIII::attempt_sync()
{
  int attempts = 0;
  int ack_success = 0;

  while (attempts < 60 && ack_success == 0)
  {
    this->camSerial->flush();
    delay(200);
    for (int i = 0; i < 6; i++)
    {
      this->camSerial->write(_SYNC_COMMAND[i]);
    }

    if (this->wait_for_bytes(_SYNC_ACK_REPLY))
    {
      if (this->wait_for_bytes(_SYNC_ACK_REPLY_EXT))
      {
        delay(50);
        for (int i = 0; i < 6; i++)
        {
          this->camSerial->write(_SYNC_FINAL_COMMAND[i]);
        }
        return true;
      }
    }
  }

  return false;
}

int UCAMIII::numberOfPackages()
{
  return this->imageSize / UCAMIII_BUF_SIZE;
}

bool UCAMIII::send_initial()
{
  this->camSerial->flush();
  delay(100);

  for (int i = 0; i < 6; i++)
  {
    this->camSerial->write(INITIAL_COMMAND[i]);
  }

  delay(500);
  if (this->wait_for_bytes(_GENERIC_ACK_REPLY))
  {
    return true;
  }

  return false;
}

bool UCAMIII::wait_for_bytes(byte command[6])
{
  byte cam_reply;
  int i = 0;
  int received;
  short found_bytes;
  found_bytes = 0;

  while (this->camSerial->available())
  {
    cam_reply = this->camSerial->read();
    if (i < 6)
    {
      if ((cam_reply == command[i]) || command[i] == 0x00)
      {
        found_bytes++;
        i++;
      }
    }

    received++;
    if (found_bytes == 6)
    {
      return true;
    }
  }
  return false;
}

bool UCAMIII::takePicture()
{
  if (send_initial())
  {
    if (this->set_package_size())
    {
      if (this->do_snapshot())
      {
        if (get_picture())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

/*bool UCAMIII::takePicture()
{
  byte ack[6] = {0xAA, 0x0E, 0x04, 0x03, 0x00, 0x00};
  byte my_ack[6] = {0xAA, 0x0E, 0x00, 0x00, 0x00, 0x00};

  this->send_initial();
  this->do_snapshot();

  for (int i = 0; i < 6; i++)
  {
    this->camSerial->write(GET_PICTURE[i]);
  }

  while (!this->camSerial->available())
    ;

  for (int i = 0; i < 5; i++)
  {
    for (int i = 0; i < 6; i++)
    {
      this->camSerial->write(my_ack[i]);
    }
    my_ack[4] += 1;
    for (int i = 0; i < 12; i++)
    {
      while (!this->camSerial->available())
        ;
      byte data = this->camSerial->read();
      if (data < 16)
      {
        Serial.print("0");
      }
      Serial.println(data, HEX);
    }
  }

  /*
  if (this->wait_for_bytes(ack))
  {
    while (!this->camSerial->available())
      ;

    while (this->camSerial->available())
    {
      while (!this->camSerial->available())
        ;
      Serial.print(this->camSerial->read(), HEX);
    }
  }*/

/* this->camSerial->flush();
  for (int i = 0; i < 6; i++)
  {
    this->camSerial->write(final_ack[i]);
  }*/
//}

bool UCAMIII::set_package_size()
{
  byte ack[6] = {0xAA, 0x0E, 0x06, 0x00, 0x00, 0x00};
  delay(100);

  for (int i = 0; i < 6; i++)
  {
    this->camSerial->write(_PACK_SIZE[i]);
  }

  delay(500);
  if (this->wait_for_bytes(ack))
  {
    return true;
  }

  return false;
}

bool UCAMIII::do_snapshot()
{
  byte ack[6] = {0xAA, 0x0E, 0x05, 0x00, 0x00, 0x00};
  delay(100);

  for (int i = 0; i < 6; i++)
  {
    this->camSerial->write(SNAPSHOT[i]);
  }
  delay(500);
  if (this->wait_for_bytes(ack))
  {
    return true;
  }

  return false;
}

int UCAMIII::get_picture()
{

  byte ack[6] = {0xAA, 0x0E, 0x04, 0x00, 0x00, 0x00};
  unsigned long imageSize;
  short i;

  delay(100);

  for (int i = 0; i < 6; i++)
  {
    this->camSerial->write(GET_PICTURE[i]);
  }
  delay(500);
  if (this->wait_for_bytes(ack))
  {

    for (i = 0; i <= 5; i++)
    {
      ack[i] = 0;
      while (!this->camSerial->available())
        ;

      ack[i] = this->camSerial->read();
    }

    imageSize = 0;
    imageSize = (imageSize << 8) | ack[5];
    imageSize = (imageSize << 8) | ack[4];
    imageSize = (imageSize << 8) | ack[3];

    this->imageSize = imageSize;
    this->image_pos = this->imageSize;
    if (imageSize > 0)
    {
      return 1;
    }
  }

  return 0;
}

int UCAMIII::getData()
{
  unsigned char high = (unsigned char)(this->package_no >> 8);
  unsigned char low = this->package_no & 0xff;
  byte my_ack[6] = {0xAA, 0x0E, 0x00, 0x00, low, high};
  int i = 0;
  byte s;
  int bytes;
  if (this->image_pos == 0)
  {
    return 0;
  }

  // request bytes
  for (int i = 0; i < 6; i++)
  {
    this->camSerial->write(my_ack[i]);
  }

  // Set number of bytes we should wait for
  if (this->image_pos < UCAMIII_BUF_SIZE)
  {
    bytes = this->image_pos + 6;
  }
  else
  {
    bytes = UCAMIII_BUF_SIZE + 6;
  }

  for (i = 0; i < bytes; i++)
  {
    while (!this->camSerial->available())
      ; // wait for bytes
    s = this->camSerial->read();
    // Skip first 4 and last 2, Page 10 of the datasheet
    if (i >= 4 && i < bytes - 2)
    {
      this->imgBuffer[i - 4] = s;
      this->image_pos--;
    }
  }

  this->package_no++;
  if (this->image_pos <= 0)
  {
    // send the final thank you goodbye package
    my_ack[4] = 0xF0;
    my_ack[5] = 0xF0;
    for (int i = 0; i < 6; i++)
    {
      this->camSerial->write(my_ack[i]);
    }
  }
  return bytes - 6;
}
