#ifndef UCAMIII_h
#define UCAMIII_h
#define UCAMIII_BUF_SIZE 24
#include <Arduino.h>
#include <HardwareSerial.h>
#include <SD.h>

class UCAMIII
{

public:
    UCAMIII(HardwareSerial *interface, HardwareSerial *output_interface);
    UCAMIII(HardwareSerial *interface);

    void set_picture_format(String format, String resolution);
    void begin();
    void print_picture();
    void save_to_sd(File *output_interface);
    void save_to_sd_and_print(File *output_interface);
    bool init();
    bool takePicture();
    int numberOfPackages();
    HardwareSerial *camSerial;
    HardwareSerial *output_interface;
    File *sd_interface;
    unsigned long imageSize;

    int getData();
    byte imgBuffer[UCAMIII_BUF_SIZE];

private:
    unsigned long image_pos;
    int package_no;
    bool send_initial();
    bool set_package_size();
    bool do_snapshot();
    int get_picture();
    bool attempt_sync();
    bool wait_for_bytes(byte command[6]);
};

#endif
