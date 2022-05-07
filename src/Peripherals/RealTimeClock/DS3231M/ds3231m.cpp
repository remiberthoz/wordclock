#include "ds3231m.h"
#include <time.h>
#include "../../../Protocols/I2C/i2cnx.h"
#include "../../../Verbose/verbose.h"

#define if_nack_return(x) if (!ack) { printf_warn("I2CNX: NACK\n"); return x; }


constexpr uint8_t DS3231M_ADDR = 0xD0;
static I2CNX I2C1X_RTC{1, &PORTA, 3, &PORTA, 2, 3};


void RealTimeClock::DS3231M::init() {
    I2C1X_RTC.init();

    // tm timeinfo{};
    // timeinfo.tm_year = 2022-1900;
    // timeinfo.tm_mon = 4-1;
    // timeinfo.tm_mday = 18;
    // timeinfo.tm_hour = 15;
    // timeinfo.tm_min = 48;
    // timeinfo.tm_sec = 0;

    // set_time(&timeinfo);
}


tm RealTimeClock::DS3231M::fetch_time() {

    printf_info("Fetching time on RTC\n");

    bool ack;
    tm timeinfo{};

    // Manipulate device address
    constexpr uint8_t starting_adr = 0x00;
    ack = I2C1X_RTC.start_transmit(DS3231M_ADDR, starting_adr, false);
    if_nack_return(timeinfo);

    // Receive data
    ack = I2C1X_RTC.start_receive(DS3231M_ADDR, true);
    if_nack_return(timeinfo);

    uint8_t reg_seconds, reg_minutes, reg_hours, reg_dayofmonth, reg_month, reg_year;
    uint8_t reg_dayofweek;

    I2C1X_RTC.receive(&reg_seconds, true);
    I2C1X_RTC.receive(&reg_minutes, true);
    I2C1X_RTC.receive(&reg_hours, true);
    I2C1X_RTC.receive(&reg_dayofweek, true);
    I2C1X_RTC.receive(&reg_dayofmonth, true);
    I2C1X_RTC.receive(&reg_month, true);
    I2C1X_RTC.receive(&reg_year, false);

    // Decode BCD data
    timeinfo.tm_sec = static_cast<int8_t> ( ((reg_seconds & 0b01110000) >> 4)*10 + (reg_seconds & 0b00001111) );
    timeinfo.tm_min = static_cast<int8_t> ( ((reg_minutes & 0b01110000) >> 4)*10 + (reg_minutes & 0b00001111) );
    timeinfo.tm_hour = static_cast<int8_t> ( ((reg_hours & 0b00110000) >> 4)*10 + (reg_hours & 0b00001111) );
    timeinfo.tm_mday = static_cast<int8_t> ( ((reg_dayofmonth & 0b00110000) >> 4)*10 + (reg_dayofmonth & 0b00001111) );
    // timeinfo.tm_wday = ... ignored when creating a time_t from a tm
    timeinfo.tm_mon = static_cast<int8_t> ( - 1 + ((reg_month & 0b00010000) >> 4)*10 + (reg_month & 0b00001111) );
    // timeinfo.tm_yday = ... ignored when creating a time_t from a tm
    timeinfo.tm_year = static_cast<int8_t> ( 100 + ((reg_year & 0b11110000) >> 4)*10 + (reg_year & 0b00001111) );

    printf_info("Received time from RTC: ");
    printf_info_c("%04d-%02d-%02d %02d:%02d:%02d\n",
        1900+timeinfo.tm_year,
        1+timeinfo.tm_mon,
        timeinfo.tm_mday,
        timeinfo.tm_hour,
        timeinfo.tm_min,
        timeinfo.tm_sec);

    return timeinfo;
}


bool RealTimeClock::DS3231M::set_time(tm* timeinfo) {

    printf_info("Setting time on RTC: ");
    printf_info_c("%04d-%02d-%02d %02d:%02d:%02d\n",
        1900+timeinfo->tm_year,
        1+timeinfo->tm_mon,
        timeinfo->tm_mday,
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec);

    // Encode BCD data
    uint8_t reg_seconds = static_cast<uint8_t> ( ((timeinfo->tm_sec/10) << 4) | (timeinfo->tm_sec % 10) );
    uint8_t reg_minutes = static_cast<uint8_t> ( ((timeinfo->tm_min/10) << 4) | (timeinfo->tm_min % 10) );
    uint8_t reg_hours = static_cast<uint8_t> ( ((timeinfo->tm_hour/10) << 4) | (timeinfo->tm_hour % 10) );
    uint8_t reg_dayofweek = static_cast<uint8_t> ( timeinfo->tm_wday % 10 );
    uint8_t reg_dayofmonth = static_cast<uint8_t> ( ((timeinfo->tm_mday/10) << 4) | (timeinfo->tm_mday % 10) );
    uint8_t reg_month = static_cast<uint8_t> ( (((timeinfo->tm_mon + 1)/10) << 4) | ((timeinfo->tm_mon + 1) % 10) );
    uint8_t reg_year = static_cast<uint8_t> ( (((timeinfo->tm_year - 100)/10) << 4) | ((timeinfo->tm_year - 100) % 10) );

    bool ack;

    // Send data
    constexpr uint8_t starting_adr = 0x00;
    ack = I2C1X_RTC.start_transmit(DS3231M_ADDR, starting_adr, true);
    if_nack_return(false);

    ack = I2C1X_RTC.transmit(&reg_seconds, true);
    if_nack_return(false);
    ack = I2C1X_RTC.transmit(&reg_minutes, true);
    if_nack_return(false);
    ack = I2C1X_RTC.transmit(&reg_hours, true);
    if_nack_return(false);
    ack = I2C1X_RTC.transmit(&reg_dayofweek, true);
    if_nack_return(false);
    ack = I2C1X_RTC.transmit(&reg_dayofmonth, true);
    if_nack_return(false);
    ack = I2C1X_RTC.transmit(&reg_month, true);
    if_nack_return(false);
    ack = I2C1X_RTC.transmit(&reg_year, false);
    if_nack_return(false);

    return true;
}
