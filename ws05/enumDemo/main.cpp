enum day_of_week {
	Mon, Tue, Wed, Thu, Fri, Sat, Sun
};

day_of_week operator++(day_of_week &aday) {
	int day = (aday + 1) % (Sun + 1);
	aday = static_cast<day_of_week>(day);
	return aday;
}

void demo() {
	int i = Mon;
	day_of_week aday { Tue };
	while (++aday != Mon)
		;
	aday = static_cast<day_of_week>(42);
}

day_of_week operator++(day_of_week &aday, int) {
	day_of_week ret { aday };
	if (aday == Sun)
		aday = Mon;
	else
		aday = static_cast<day_of_week>(1 + aday);
	return ret;
}

namespace dummy {
enum Months {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
//void dec(){} // compile error, conflicts
}

enum class month {
	jan = 1,
	feb,
	mar,
	apr,
	may,
	jun,
	jul,
	aug,
	sep,
	oct,
	nov,
	dec,
	january = jan,
	feburary,
	march,
	april,
	june = jun,
	july,
	august,
	september,
	october,
	november,
	december
};
void dec() {
} // no conflict with months::dec
static_assert(month::mar==month::march,"enumeration should continue");

enum class launch_policy
	: unsigned char {
		sync = 1, async = 2, gpu = 4, process = 8, none = 0
};

#include <iostream>
int main() {
	using std::cout;
	day_of_week aday { Sat };
	if (++aday != Sun)
		cout << 1;
	if (aday++ != Sun)
		cout << 2;
	if (aday != Mon)
		cout << 3;
	month amonth { month::aug };
}

