#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <iomanip>
#include <numeric>
#include <utility>
#include <array>
#include <type_traits>

template <size_t...I>
constexpr
auto make_compile_time_sequence(size_t const row,std::index_sequence<I...>){
	return std::array<size_t,sizeof...(I)>{{row*(1+I)...}};
}

constexpr auto check_compile_time=make_compile_time_sequence(1,std::make_index_sequence<20>{});

void testIndexSequenceArray(std::ostream &out){
	auto const a=make_compile_time_sequence(1,std::make_index_sequence<20>{});
	for (auto  i=a.cbegin(); i < a.cend(); ++i){
		out << '\n';
		std::for_each(std::cbegin(a),std::cend(a),[i,&out](auto j){
			out << std::setw(4)<< *i * j;
		});
	}
	out << '\n';
}
template <size_t...I>
constexpr
auto make_compile_time_square(std::index_sequence<I...> ){
	return std::array<std::array<size_t,sizeof...(I)>,sizeof...(I)>
	      {{make_compile_time_sequence(1+I,std::make_index_sequence<sizeof...(I)>{})...}};
}
constexpr auto multab_20 = make_compile_time_square(std::make_index_sequence<20>{});

void testCompileTimeArray(std::ostream &out){
	using namespace std;
	for_each(begin(multab_20),end(multab_20),[&out](auto row){
		out << '\n';
		for_each(begin(row),end(row),[&out](auto elt){
			out << setw(4) << elt;
		});
	});
	out << '\n';
}

template <size_t n>
using index_constant=std::integral_constant<size_t,n>;

// compile time string handling machinery:
template <char... s>
using char_sequence=std::integer_sequence<char,s...>;
template <char ...s>
constexpr char const make_char_string[]={s... , '\0'}; // plain array
template <char ...s>
constexpr auto make_char_string_from_sequence(char_sequence<s...>){
	return make_char_string<s...>;
}

template <char ...s>
constexpr auto newline(char_sequence<s...>){
	return char_sequence<s...,'\n'>{};
}
constexpr auto newline(){
	return char_sequence<'\n'>{};
}

constexpr char make_digit_char(size_t const digit,
		size_t const power_of_ten=1,char const zero=' '){
	return char(digit>=power_of_ten?digit/power_of_ten+'0':zero);
}

template <size_t num>
constexpr auto make_chars_from_num(){
	static_assert(num < 1000, "can not handle large numbers");
	return char_sequence< ' ',
		make_digit_char(num,100),
		make_digit_char(num%100,10,num>=100?'0':' '),
		char(num%10+'0')
	>{};
}

static_assert(std::is_same<
		char_sequence<' ','1','9','8'>,
		decltype(make_chars_from_num<198>())>{}
,"make_chars_from_num<198>() should return correct value/type");
static_assert(std::is_same<
		char_sequence<' ','2','0','0'>,
		decltype(make_chars_from_num<200>())>{}
,"make_chars_from_num<200>() should return correct value/type");
static_assert(std::is_same<
		char_sequence<' ',' ',' ','0'>,
		decltype(make_chars_from_num<0>())>{}
,"make_chars_from_num<0>() should return correct value/type");

template <typename INT, INT ...s, INT ...t>
constexpr auto concat_sequence(std::integer_sequence<INT,s...>,std::integer_sequence<INT,t...>){
	return std::integer_sequence<INT,s...,t...>{};
}

template<size_t N, size_t ...I>
constexpr auto add(std::index_sequence<I...>){
	return std::index_sequence<(N+I)...>{};
}
template<size_t factor, size_t ...cols>
constexpr auto multiply(std::index_sequence<cols...>){
	return std::index_sequence<(factor*cols)...>{};
}

constexpr auto convert_to_charseq(std::index_sequence<>){
	return char_sequence<>{};
}

// need level of indirection to do variadic template recursion head-tail cutting
template <size_t n, size_t ...rest>
constexpr auto convert_to_charseq(std::index_sequence<n,rest...>){
	return concat_sequence(
			make_chars_from_num<n>(),
			convert_to_charseq(std::index_sequence<rest...>{}));
}

template<size_t ...cols>
constexpr auto makerowcharseq(std::index_sequence<cols...> columns){
	return newline(convert_to_charseq(columns));
}

template <size_t row, size_t num>
constexpr auto makerow(){
	constexpr auto indices=
			multiply<row>(
				add<1>(std::make_index_sequence<num>{}));
	return makerowcharseq(indices);
}

template <size_t n>
constexpr auto make_rows_as_charseq(index_constant<n>,std::index_sequence<>){
	return char_sequence<>{};
}
template <size_t n, size_t row, size_t ...rest>
constexpr auto make_rows_as_charseq(index_constant<n> dim,std::index_sequence<row,rest...>){
	return concat_sequence(
			makerow<row,n>(),
			make_rows_as_charseq(dim,std::index_sequence<rest...>{}));
}

namespace fourteen_direct_constexpr {

template <typename ELT, size_t n>
struct myarray{
	constexpr myarray():a{{}}{}
	constexpr ELT& operator[](size_t i){ return a[i];}
	constexpr ELT const & operator[](size_t i) const { return a[i];}
private:
	ELT a[n];
};
template <size_t n>
using square=myarray<myarray<size_t,n>,n>;

template <size_t n>
constexpr square<n> make_table_direct(){
	square<n> result{};
	for (size_t i=0; i < n; ++i)
		for(size_t j=0; j < n; ++j)
			result[i][j]=(i+1)*(j+1);
	return result;
}
template <size_t n>
constexpr square<n> multab_direct=make_table_direct<n>();





template <size_t n,size_t ...rows>
constexpr auto makerows(std::index_sequence<rows...> rest){
	 return make_rows_as_charseq(index_constant<n>{},rest);
}
template <size_t dim>
constexpr auto multiplication_table=
		make_char_string_from_sequence(
			concat_sequence(newline(),
				makerows<dim>(
					add<1>(
						std::make_index_sequence<dim>{}))));

constexpr auto const & tt=make_char_string<'a','b'>;
static_assert(sizeof(tt)==3,"tt should have length 3");


void testToString(std::ostream &out){
	out << static_cast<char const *const>(
			make_char_string_from_sequence(
			concat_sequence(newline(),
					makerows<20>(
							add<1>(std::make_index_sequence<20>{})))));
}
}
using namespace fourteen_direct_constexpr;
void testKleinesEinmaleins(){
	using namespace std::string_literals;
	std::string val{multiplication_table<10>};
	ASSERT_EQUAL(R"(
   1   2   3   4   5   6   7   8   9  10
   2   4   6   8  10  12  14  16  18  20
   3   6   9  12  15  18  21  24  27  30
   4   8  12  16  20  24  28  32  36  40
   5  10  15  20  25  30  35  40  45  50
   6  12  18  24  30  36  42  48  54  60
   7  14  21  28  35  42  49  56  63  70
   8  16  24  32  40  48  56  64  72  80
   9  18  27  36  45  54  63  72  81  90
  10  20  30  40  50  60  70  80  90 100
)",val);
}
void testGrossesEinmaleins(){
	using namespace std::string_literals;
	std::string val{multiplication_table<20>};
	std::string const expected=R"(
   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
   2   4   6   8  10  12  14  16  18  20  22  24  26  28  30  32  34  36  38  40
   3   6   9  12  15  18  21  24  27  30  33  36  39  42  45  48  51  54  57  60
   4   8  12  16  20  24  28  32  36  40  44  48  52  56  60  64  68  72  76  80
   5  10  15  20  25  30  35  40  45  50  55  60  65  70  75  80  85  90  95 100
   6  12  18  24  30  36  42  48  54  60  66  72  78  84  90  96 102 108 114 120
   7  14  21  28  35  42  49  56  63  70  77  84  91  98 105 112 119 126 133 140
   8  16  24  32  40  48  56  64  72  80  88  96 104 112 120 128 136 144 152 160
   9  18  27  36  45  54  63  72  81  90  99 108 117 126 135 144 153 162 171 180
  10  20  30  40  50  60  70  80  90 100 110 120 130 140 150 160 170 180 190 200
  11  22  33  44  55  66  77  88  99 110 121 132 143 154 165 176 187 198 209 220
  12  24  36  48  60  72  84  96 108 120 132 144 156 168 180 192 204 216 228 240
  13  26  39  52  65  78  91 104 117 130 143 156 169 182 195 208 221 234 247 260
  14  28  42  56  70  84  98 112 126 140 154 168 182 196 210 224 238 252 266 280
  15  30  45  60  75  90 105 120 135 150 165 180 195 210 225 240 255 270 285 300
  16  32  48  64  80  96 112 128 144 160 176 192 208 224 240 256 272 288 304 320
  17  34  51  68  85 102 119 136 153 170 187 204 221 238 255 272 289 306 323 340
  18  36  54  72  90 108 126 144 162 180 198 216 234 252 270 288 306 324 342 360
  19  38  57  76  95 114 133 152 171 190 209 228 247 266 285 304 323 342 361 380
  20  40  60  80 100 120 140 160 180 200 220 240 260 280 300 320 340 360 380 400
)";
	ASSERT_EQUAL(expected,multiplication_table<20>);
}



void test10by10VariableTemplateVersion(){
	using namespace std::string_literals;
	std::ostringstream out { };
	out << multiplication_table<0b10>;
	auto const expected=R"(
   1   2
   2   4
)"s;
	ASSERT_EQUAL(expected,out.str());
	ASSERT_EQUAL(expected,multiplication_table<2>);
	ASSERT_EQUAL(make_char_string_from_sequence(concat_sequence(newline(),makerows<2>(add<1>(std::make_index_sequence<2>{})))),std::string{multiplication_table<2>});
}


template<typename MULTABFUNC>
void testMultab(MULTABFUNC multab) {
	using namespace std::string_literals;
	static auto const expected=R"(
   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
   2   4   6   8  10  12  14  16  18  20  22  24  26  28  30  32  34  36  38  40
   3   6   9  12  15  18  21  24  27  30  33  36  39  42  45  48  51  54  57  60
   4   8  12  16  20  24  28  32  36  40  44  48  52  56  60  64  68  72  76  80
   5  10  15  20  25  30  35  40  45  50  55  60  65  70  75  80  85  90  95 100
   6  12  18  24  30  36  42  48  54  60  66  72  78  84  90  96 102 108 114 120
   7  14  21  28  35  42  49  56  63  70  77  84  91  98 105 112 119 126 133 140
   8  16  24  32  40  48  56  64  72  80  88  96 104 112 120 128 136 144 152 160
   9  18  27  36  45  54  63  72  81  90  99 108 117 126 135 144 153 162 171 180
  10  20  30  40  50  60  70  80  90 100 110 120 130 140 150 160 170 180 190 200
  11  22  33  44  55  66  77  88  99 110 121 132 143 154 165 176 187 198 209 220
  12  24  36  48  60  72  84  96 108 120 132 144 156 168 180 192 204 216 228 240
  13  26  39  52  65  78  91 104 117 130 143 156 169 182 195 208 221 234 247 260
  14  28  42  56  70  84  98 112 126 140 154 168 182 196 210 224 238 252 266 280
  15  30  45  60  75  90 105 120 135 150 165 180 195 210 225 240 255 270 285 300
  16  32  48  64  80  96 112 128 144 160 176 192 208 224 240 256 272 288 304 320
  17  34  51  68  85 102 119 136 153 170 187 204 221 238 255 272 289 306 323 340
  18  36  54  72  90 108 126 144 162 180 198 216 234 252 270 288 306 324 342 360
  19  38  57  76  95 114 133 152 171 190 209 228 247 266 285 304 323 342 361 380
  20  40  60  80 100 120 140 160 180 200 220 240 260 280 300 320 340 360 380 400
)"s;
	std::ostringstream out { };
	multab(out);
	ASSERT_EQUAL(expected,out.str());
}
void testMultabCompileTimeArray(){
	testMultab(testCompileTimeArray);
}
void testIndexSequence(){
	testMultab(testIndexSequenceArray);
}
void testIndexSequenceCompileTime(){
	testMultab(testToString);
}
void runAllTests(int argc, char const *argv[]){
	cute::suite s { };
	s.push_back(CUTE(testIndexSequenceCompileTime));
	s.push_back(CUTE(testIndexSequence));
	s.push_back(CUTE(testMultabCompileTimeArray));
	s.push_back(CUTE(test10by10VariableTemplateVersion));
	s.push_back(CUTE(testKleinesEinmaleins));
	s.push_back(CUTE(testGrossesEinmaleins));
	s.push_back(CUTE(testKleinesEinmaleins));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}


