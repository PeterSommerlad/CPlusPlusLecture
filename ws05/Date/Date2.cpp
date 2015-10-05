#include "Date.h"
#include <stdexcept>
#if 0

void Date::print(std::ostream& out) const {
	auto ch = out.fill('0');
	out << std::setw(2) << day << '.';
	out << std::setw(2) << month << '.';
	out << std::setw(4) << year;
	out.fill(ch);
}

bool Date::isValidYear(int year) {
	return year >= 1813 && year < 10000;
}

bool Date::isLeapYear(int year) {
	return !(year % 4) && ((year % 100) || !(year % 400));
}

bool Date::isValidDate(int year, int month, int day) {
	if (! isValidYear(year) || day <=0 ) return false;
	switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10:
		case 12: return day <= 31;
		case 4: case 6: case 9: case 11: return day <= 30;
		case 2: return day <=(isLeapYear(year)?29:28);
	}
	return false;
}
Date:: Date(int year, int month, int day)
:year {year},month {month},day {day} {
	if (! isValidDate(year,month,day))
	throw std::out_of_range {"invalid date"};
}

void Date::nextDay() {
	++day;
}
#endif
