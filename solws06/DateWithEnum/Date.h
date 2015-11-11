#ifndef DATE_H_
#define DATE_H_
#include <iosfwd>
#include <boost/operators.hpp>

namespace date {
enum Month{
    jan = 1, feb, mar, apr, may, jun,
    jul, aug, sep, oct, nov, dec,
    january = jan, feburary, march, april,
    june = jun, july, august, september, october,
    november, december
};
std::ostream& operator<<(std::ostream& out, Month m);
Month operator++(Month& m);
Month operator++(Month& m, int);

struct Date
: private boost::less_than_comparable<Date>
, boost::equality_comparable<Date> {

	constexpr Date()=default;
	explicit Date(std::istream& in);
	Date(int year, Month month, int day);
	Date(Month month, int day, int year);
	// can not do Date(int day, Month, int year), only with range-specifc input

	enum weekday{Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
	weekday day_of_week() const ;
	void print(std::ostream& out) const;
	static bool isValidYear(int year);
	static bool isLeapYear(int year);
	static bool isValidDate(int year, Month month, int day);
	static bool isValidDate(int year, int month, int day){ return isValidDate(year,Month(month),day);}
	static int  endOfMonth(int year, Month month);
	void nextDay();
	bool operator <(Date const& rhs) const;
	void read(std::istream& in);
	static bool isValidSep(char ch);
	bool operator==(Date const& rhs) const {
		return year==rhs.year && month==rhs.month && day==rhs.day;
	}
private:
	int year{9999};
	Month month{Month::dec};
	int day{31};
};

std::ostream& operator<<(std::ostream & out, Date::weekday dow);

inline std::ostream&
operator<<(std::ostream& out,Date const& d){
	d.print(out);
	return out;
}

inline std::istream&
operator>>(std::istream& in,Date& d){
	d.read(in);
	return in;
}

Date make_date(std::istream& in);
//...
} // namespace date
#endif /* DATE_H_ */
