#ifndef ARDUINO_H
#define ARDUINO_H
#define INPUT 1
#define OUTPUT 0
void pinMode(IOPin pin, int mode);
void delayMicroseconds(int us);
void error(char *str);
#endif
