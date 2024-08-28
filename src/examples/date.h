#ifndef DATE_H
#define DATE_H

#include <cassert>
#include <stdexcept>
#include <string>

struct Date {
    unsigned short year;
    unsigned short month;
    unsigned short day;
};

struct DateTime {
    enum zone_offsets_t { OFF_NOT_SET, OFFSET_Z, OFFSET_UTC_PLUS, OFFSET_UTC_MINUS };

private:
    unsigned short year_;
    unsigned short month_;
    unsigned short day_;
    unsigned short hours_;
    unsigned short minutes_;
    unsigned short seconds_;

    zone_offsets_t zone_offset_type_;
    unsigned int zone_offset_in_min_;

    static void dt_assert(bool res, const char *msg)
    {
        if (!res) {
            throw std::logic_error("Assertion failed in datetime: " + std::string(msg));
        }
    }

public:
    DateTime() :
        year_(0), month_(0), day_(0), hours_(0), minutes_(0), seconds_(0),
        zone_offset_type_(OFF_NOT_SET), zone_offset_in_min_(0)
    {
    }

    // getters
    unsigned short year() const { return year_; }
    unsigned short month() const { return month_; }
    unsigned short day() const { return day_; }
    unsigned short hours() const { return hours_; }
    unsigned short minutes() const { return minutes_; }
    unsigned short seconds() const { return seconds_; }
    zone_offsets_t zone_offset_type() const { return zone_offset_type_; }
    unsigned int zone_offset_in_min() const { return zone_offset_in_min_; }

    // setters
    void setYear(unsigned short value) { this->year_ = value; }
    void setMonth(unsigned short value) { this->month_ = value; }
    void setDay(unsigned short value) { this->day_ = value; }
    void setHours(unsigned short value) { this->hours_ = value; }
    void setMinutes(unsigned short value) { this->minutes_ = value; }
    void setSeconds(unsigned short value) { this->seconds_ = value; }
    void setZoneOffsetType(zone_offsets_t zone_offset_type)
    {
        this->zone_offset_type_ = zone_offset_type;
    }
    void setZoneOffsetInMin(unsigned int zone_offset_in_min)
    {
        this->zone_offset_in_min_ = zone_offset_in_min;
    }
};

void set_zone_offset(DateTime &dt, char sign, unsigned short hours, unsigned short minutes);

DateTime parse_datetime(const std::string &s);

Date parse_date_time1(const std::string &s);

Date parse_date_time2(const std::string &s);

#endif // DATE_H
