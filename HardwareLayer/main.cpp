/* 
 * File:   main.cpp
 * Author: Aivaras
 *
 * Created on Pirmadienis, 2014, Balandžio 21, 17.53
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "I2Cdev.h"

uint32_t getUserData(uint8_t address)
{
    uint8_t buffer[4] = {0x00, 0x00, 0x00, 0x00};
    
    I2Cdev::readBytes(address, 0x10, 4, buffer);

    return (buffer[0] << 24) |
           (buffer[1] << 16) |
           (buffer[2] << 8) |
           buffer[3];    
}

void userInterrupt(uint8_t id)
{       
    uint32_t user = getUserData(100 + id);
    printf("\nGot User: %d %u\n", id, user);
}

void userInterrupt0()
{
    return userInterrupt(0);
}

void userInterrupt1()
{
    return userInterrupt(1);
}

void userInterrupt2()
{
    return userInterrupt(2);
}

void userInterrupt3()
{
    return userInterrupt(3);
}

int setupInterrupts()
{
    int status = wiringPiSetup();
    if (status < 0) {
        printf ("Unable to setup wiringPi: %d\n", status);
        return 0;
    }
    
    wiringPiISR (7, INT_EDGE_RISING, &userInterrupt0);
    wiringPiISR (0, INT_EDGE_RISING, &userInterrupt1);
    wiringPiISR (2, INT_EDGE_RISING, &userInterrupt2);
    wiringPiISR (3, INT_EDGE_RISING, &userInterrupt3);

    return 1;
}

/*
 * 
 */
int main() {

    if (!setupInterrupts()) {
        return 0;
    }
    
    while(1){}
 
    return 0;
}

