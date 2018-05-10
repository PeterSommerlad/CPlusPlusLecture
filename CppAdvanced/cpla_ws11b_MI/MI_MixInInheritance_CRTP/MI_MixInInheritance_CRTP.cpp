template<typename T>
struct addable {
	friend T operator+(T lhs, T const & rhs) {
		return lhs += rhs;
	}
};

struct Number
//		: addable<Number>
{
	Number(long long value) :
			value { value } {
	}

//	Number & operator +=(Number const & rhs) {
//		value += rhs.value;
//		return *this;
//	}

private:
	long long value;
};


int main(int argc, char **argv) {
	Number n { 15 };
//	n += n;
//	n + n;
}
