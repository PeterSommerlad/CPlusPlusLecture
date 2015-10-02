#include "Date.h"
#include <stdexcept>
#include <ostream>
#include <iomanip>
#include <vector>
#include <string>
namespace date {


std::ostream& operator <<(std::ostream& out, Month m) {
    static std::vector<std::string> const month_map { "Jan",
        "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
        "Sep", "Oct", "Nov", "Dec" };
    out << month_map[m-1];
    return out;
}



Month operator++(Month& m) {
    m = Month((m % 12) + 1);
    return m;
}
Month operator++(Month& m, int) {
    Month old = m;
    ++m;
    return old;
}

void Date::print(std::ostream& out) const {
    auto ch = out.fill('0');
    out << std::setw(2) << day << '.';
    out.fill(' ');
    out << std::setw(4) << month << ' ';
    out << year;
    out.fill(ch);
}

bool Date::isValidYear(int year) {
    return year >= 1813 && year < 10000;
}

bool Date::isLeapYear(int year) {
    return !(year % 4) && ((year % 100) || !(year % 400));
}

bool Date::isValidDate(int year, Month month, int day) {
    return isValidYear(year) && day > 0
    && day <= endOfMonth(year, month);
}

Date::Date(int year, Month month, int day) :
year { year }, month { month }, day { day } {
    if (!isValidDate(year, month, day))
        throw std::out_of_range { "invalid date" };
}

int Date::endOfMonth(int year, Month month) {
    switch (month) {
    case jan: case mar: case may: case jul:
    case aug: case oct: case dec:
        return 31;
    case apr: case jun: case sep: case nov:
        return 30;
    case feb:
        return (isLeapYear(year) ? 29 : 28);
    }
    return 0; // never reached
}

void Date::nextDay() {
    if (day == endOfMonth(year, month)) {
        day = 1;
        ++month;
        if (month == jan) {
            ++year;
            if (!isValidYear(year))
                throw std::out_of_range("last year");
        }
    } else {
        ++day;
    }
}

bool Date::operator <(Date const& rhs) const {
    return year < rhs.year || (year == rhs.year
            && (month < rhs.month
               || (month == rhs.month && day < rhs.day)));
}

void Date::read(std::istream& in) {
    int in_day { }, in_month { }, in_year { };
    char sep1 { }, sep2 { };
    in >> in_day >> sep1 >> in_month >> sep2 >> in_year;
    if (isValidYear(in_day))
        std::swap(in_day, in_year);
    if (in_year >= 0 && in_year < 100)
        in_year += 2000;
    if (!in.fail() && sep1 == sep2
        && (sep1 == '.' || sep1 == '/' || sep1 == '-')
        && isValidDate(in_year, in_month, in_day)) {
        year = in_year;
        month = Month(in_month);
        day = in_day;
    } else {
        in.setstate(std::ios::failbit | in.rdstate());
    }
}

Date::Date(std::istream& in) :
Date{} {
    read(in);
    if (in.fail())
        throw std::out_of_range { "invalid date" };
}

Date make_date(std::istream& in)
try {
    return Date{in};
}
catch (std::out_of_range const &) {
    return Date{ 9999, dec, 31 }; // default value
    return Date{};
}


} // namespace date
