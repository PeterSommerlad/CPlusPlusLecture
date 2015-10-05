#ifndef DATE_H_
#define DATE_H_

class Date {
public:
	int year, month, day;
//...
	Date(int year, int month, int day) :
			year { year }, month { month }, day { day } {
		// should check here.
	}
};

Date myBirthday { 1964, 12, 24 };
#endif /* DATE_H_ */
