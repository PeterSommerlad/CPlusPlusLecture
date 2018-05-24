#include "psst.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <vector>
#include <memory>

#include <functional>

#include <utility>

#include <sstream>
#include <any>

struct Width:Psst::strong<int,Width>,Psst::ops<Width,Psst::Out>{};
struct Height:Psst::strong<int,Height>,Psst::ops<Height,Psst::Out>{};
struct Radius:Psst::strong<int,Radius>,Psst::ops<Radius,Psst::Out>{};

// drawables hierarchy

namespace poly{

using screen=std::ostream;


struct drawable {
	virtual ~drawable()=0;
	virtual void draw(screen& on)=0;
protected:
	drawable& operator=(drawable&&)noexcept=delete; // prohibit move and copy
};
drawable::~drawable()=default;
using widget=std::unique_ptr<drawable>;
using widgets=std::vector<widget>;

struct rect:drawable{
	rect(Width w, Height h):
		width{w},height{h}{}
	void draw(screen& on){
		on << "rectangle:" << width << "," << height;
	}
	Width width;
	Height height;
};
struct circle:drawable{
	circle(Radius r):
		radius{r}{}
	void draw(screen& on){
		on << "circle:" << radius;
	}
	Radius radius;
};
struct composite:drawable{
	composite()=default;
	void add(widget w){
		content.push_back(std::move(w));
	}
	void draw(screen &on){
		on << "{ ";
		for(auto &w:content){
			w->draw(on);
		}
		on << " }";
	}
private:
	widgets content{};
};
struct refcomposite:drawable{
	using widget=std::reference_wrapper<drawable>;
	using widgets=std::vector<widget>;
	refcomposite()=default;
	void add(widget w){
		content.push_back(w);
	}
	void draw(screen &on){
		on << "{ ";
		for(drawable& w:content){
			w.draw(on);
		}
		on << " }";
	}
private:
	widgets content{};
};

void testRect(){
	std::ostringstream out{};
	rect r{Width{2},Height{4}};
	r.draw(out);
	ASSERT_EQUAL("rectangle:2,4",out.str());
}
void testCircle(){
	std::ostringstream out{};
	circle c{Radius{4}};
	c.draw(out);
	ASSERT_EQUAL("circle:4",out.str());
}
void testComposite(){
	std::ostringstream out{};
	composite c{};
	c.add(std::make_unique<circle>(Radius{42}));
	c.add(std::make_unique<rect>(Width{4},Height{2}));
	c.add(std::make_unique<circle>(Radius{4}));
	c.draw(out);
	ASSERT_EQUAL("{ circle:42rectangle:4,2circle:4 }",out.str());
}
void testRefComposite(){
	std::ostringstream out{};
	circle c1{Radius{42}};
	rect r1{Width{4},Height{2}};
	circle c2{Radius{4}};
	refcomposite c{};
	c.add(c1);c.add(r1);c.add(c2);
	c.draw(out);
	ASSERT_EQUAL("{ circle:42rectangle:4,2circle:4 }",out.str());
}

struct ScreenItems{
	void add(widget w){
		content.push_back(std::move(w));
	}
	void draw_all(screen &out){
		for(auto &drawable:content){
			drawable->draw(out);
		}
	}
private:
	ScreenItems&operator =(ScreenItems&&) noexcept = delete; // all others deleted
	widgets content{};
};
static_assert(!std::is_copy_constructible_v<ScreenItems>,"no copying");
static_assert(!std::is_move_constructible_v<ScreenItems>,"no moving");

ScreenItems makeScreenItems(){
	return ScreenItems {};
}

void testPolyScreenManager(){
	std::ostringstream out{};
	{
		ScreenItems sm{};
		sm.add(std::make_unique<circle>(Radius{42}));
		sm.add(std::make_unique<rect>(Width{4},Height{2}));
		sm.add(std::make_unique<circle>(Radius{4}));
		sm.draw_all(out);
	}
	ASSERT_EQUAL("circle:42rectangle:4,2circle:4",out.str());
}
void testPolyScreenManagerFactory(){
	std::ostringstream out{};
		 auto sm = makeScreenItems();
			sm.add(std::make_unique<circle>(Radius{42}));
			sm.add(std::make_unique<rect>(Width{4},Height{2}));
			sm.add(std::make_unique<circle>(Radius{4}));

		sm.draw_all(out);
	ASSERT_EQUAL("circle:42rectangle:4,2circle:4",out.str());
}



}

// Sean Parent Beispiel, generic polymorphism with Regular types
namespace sean{
using screen=std::ostream;

template<typename T>
void draw(T const & o, screen &out){
	out << o;
}
void draw(int i,screen &os){ // make ints a special case
	os << "an_int:"<<i;
}


struct widget {
	template<typename T>
	widget(T x) :
			self_(std::make_unique<model<T>>(std::move(x))) {
	}

	widget(widget const & x) :
			self_(x.self_->copy_()) {
	}
	widget(widget&&) noexcept = default;

	widget& operator=(widget const & x) {
		return *this = widget(x);
	}
	widget& operator=(widget&&) noexcept = default;

	friend void draw(widget const & x, screen& out) {
		x.self_->draw_(out);
	}

private:
	struct concept_t { // polymorphic base
		virtual ~concept_t() = default;
		virtual std::unique_ptr<concept_t> copy_() const = 0;
		virtual void draw_(screen&) const = 0;
	};
	template<typename T>
	struct model: concept_t {
		model(T x) :
				data_(std::move(x)) {
		}
		std::unique_ptr<concept_t> copy_() const {
			return std::make_unique<model>(*this); // cloning
		}
		void draw_(screen& out) const {
			draw(data_, out); // dispatch to global function
		}

		T data_;
	};
	std::unique_ptr<concept_t> self_;
};
using widgets=std::vector<widget>;

struct rect{
	rect(Width w, Height h):
		width{w},height{h}{}
	Width width;
	Height height;
};
void draw(rect const &r, screen& on){
	on << "rectangle:" << r.width << "," << r.height;
}

struct circle{
	circle(Radius r):
		radius{r}{}
	Radius radius;
};
void draw(circle const &c, screen& on){
	on << "circle:" << c.radius;
}

struct composite{
	void add(widget w){
		content.emplace_back(std::move(w));
	}
	friend void draw(composite const &c, screen &on){
		on << "{ ";
		for(widget const &drawable:c.content){
			draw(drawable, on); on << ',';
		}
		on << " }";
	}
private:
	widgets content{};
};

void testRect(){
	std::ostringstream out{};
	widget r{rect{Width{2},Height{4}}};
	draw(r,out);
	ASSERT_EQUAL("rectangle:2,4",out.str());
}

void testCircle(){
	std::ostringstream out{};
	widget c{circle{Radius{4}}};
	draw(c,out);
	ASSERT_EQUAL("circle:4",out.str());
}
void testComposite(){
	std::ostringstream out{};
	composite c{};
	c.add(circle(Radius{42}));
	c.add(rect(Width{4},Height{2}));
	c.add(circle(Radius{4}));
	c.add(42);
	c.add("a c string");
	widget w{c};
	draw(w,out);
	ASSERT_EQUAL("{ circle:42,rectangle:4,2,circle:4,an_int:42,a c string, }",out.str());
}
struct ScreenItems{
	void add(widget w){
		content.emplace_back(std::move(w));
	}
	void draw_all(screen &out) const {
		for(widget const &drawable:content){
			draw(drawable,out);
		}
	}
private:
	widgets content{};
};
static_assert(std::is_copy_constructible_v<ScreenItems>," copying");
static_assert(std::is_move_constructible_v<ScreenItems>," moving");

void draw(ScreenItems const &si, screen & out){
	si.draw_all(out);
}

void testPolyScreenManager(){
	std::ostringstream out{};
	{
		ScreenItems sm{};
		sm.add(circle(Radius{42}));
		sm.add(rect(Width{4},Height{2}));
		sm.add(circle(Radius{4}));
		sm.draw_all(out);
		widget w=sm;
		draw(w,out);
	}
	ASSERT_EQUAL("circle:42rectangle:4,2circle:4"
			     "circle:42rectangle:4,2circle:4",out.str());
}


}


namespace any_ns{
void demoAny(){
	std::any some;
	ASSERT(!some.has_value());
	some = 42;
	ASSERT(some.has_value());
	ASSERT_EQUAL(42,std::any_cast<int>(some));
	some = 3.14;
	ASSERT_THROWS(std::any_cast<int>(some),std::bad_any_cast);
	some = "anything";
	ASSERT_EQUAL("anything",std::any_cast<char const*>(some));
}

}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(poly::testRect));
	s.push_back(CUTE(poly::testCircle));
	s.push_back(CUTE(poly::testPolyScreenManager));
	s.push_back(CUTE(poly::testComposite));
	s.push_back(CUTE(poly::testRefComposite));
	s.push_back(CUTE(sean::testRect));
	s.push_back(CUTE(sean::testCircle));
	s.push_back(CUTE(sean::testComposite));
	s.push_back(CUTE(sean::testPolyScreenManager));
	s.push_back(CUTE(any_ns::demoAny));
	s.push_back(CUTE(poly::testPolyScreenManagerFactory));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}

inline void poly::drawable::draw(screen& on) {
}
