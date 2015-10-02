#include "Date.h"
#include <stdexcept>
#include <ostream>
#include <iomanip>


namespace date{


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
	return !(year % 4) && ((year % 100)	|| !(year % 400));
}







bool Date::isValidDate(int year, int month, int day) {
	return isValidYear(year) && day > 0 &&
			day <= endOfMonth(year,month);
}






Date::	Date(int year, int month, int day)
:year{year},month{month},day{day}{
	if (! isValidDate(year,month,day))
		throw std::out_of_range{"invalid date"};
}





int  Date::endOfMonth(int year, int month){
	switch (month){
	case 1: case 3: case 5: case 7: case 8: case 10:
	case 12: return 31;
	case 4: case 6: case 9: case 11: return  30;
	case 2: return (isLeapYear(year)?29:28);
	}
	return 0;
}

void Date::nextDay() {
	if (day == endOfMonth(year,month)){
		day = 1;
		if (month == 12){
			month=1;
			++year;
			if (!isValidYear(year))
				throw std::out_of_range("last year");
		} else {
			++month;
		}
	} else {
		++day;
	}
}





bool Date::operator <(Date const& rhs) const {
	return year < rhs.year ||
		(year == rhs.year && (month < rhs.month ||
			(month==rhs.month && day < rhs.day)));
}





void Date::read(std::istream& in) {
	int in_day{}, in_month{}, in_year{ };
	char sep1{}, sep2{};
	in >> in_day >> sep1 >> in_month >> sep2 >> in_year;
	if (isValidYear(in_day)) std::swap(in_day,in_year);
	if (in_year >= 0 && in_year < 100)
		in_year += 2000;
	if (!in.fail() && sep1==sep2
		&& (sep1=='.' || sep1=='/' || sep1=='-')
		&& isValidDate(in_year, in_month, in_day) ) {
		year=in_year; month=in_month; day=in_day;
	} else {
		in.setstate(std::ios::failbit | in.rdstate());
	}
}





Date::Date(std::istream& in)
:Date{} {
	read(in);
	if(in.fail())
		throw std::out_of_range{"invalid date"};
}




Date make_date(std::istream& in)
try {
	return Date { in };
} catch (std::out_of_range const &) {
	return Date { 9999, 12, 31 }; // default value
	return Date{};
}



//bool Date::operator!=(Date const& rhs) const {
//	return !(*this == rhs);
//}

} // namespace date
