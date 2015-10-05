#ifndef DATE_H_
#define DATE_H_

#include <iosfwd>

/*
 struct Date{
 */
class Date {
private:
public:
	int year, month, day;

//...

public:
	void print(std::ostream& out) const;
	static bool isValidYear(int year);
	static bool isLeapYear(int year);
	static bool isValidDate(int year, int month, int day);
	Date(int year, int month, int day);
	static int endOfMonth(int year, int month);
	void nextDay();
	bool operator <(Date const& rhs) const;

	/*
	 private:
	 int year, month, day;
	 */

};

inline bool operator>(Date const& lhs, Date const& rhs) {
	return rhs < lhs;
}
inline bool operator>=(Date const& lhs, Date const& rhs) {
	return !(lhs < rhs);
}
inline bool operator<=(Date const& lhs, Date const& rhs) {
	return !(rhs < lhs);
}

inline bool operator==(Date const& lhs, Date const& rhs) {
	return !(lhs < rhs) && !(rhs < lhs);
}
inline bool operator!=(Date const& lhs, Date const& rhs) {
	return !(lhs == rhs);
}

#endif /* DATE_H_ */
