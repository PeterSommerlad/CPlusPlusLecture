#include "BoundedBuffer.h"
#include "bounded_buffer_student_suite.h"
#include "cute.h"

struct nasty{};

struct ThrowsOnCopy {
	ThrowsOnCopy()=default;
	ThrowsOnCopy(ThrowsOnCopy const &){
		throw nasty{};
	}
	ThrowsOnCopy(ThrowsOnCopy &&other) noexcept =default;
	ThrowsOnCopy& operator=(ThrowsOnCopy const&){
		throw nasty{};
	}
	ThrowsOnCopy& operator=(ThrowsOnCopy&& other)noexcept=default;
};

void BufferWithThrowsOnCopy(){
	BoundedBuffer<ThrowsOnCopy,2> buf{};
	buf.push(ThrowsOnCopy{});
	ASSERT_THROWS(buf.push(buf.front()),nasty);
	ASSERT_EQUAL(1,buf.size());
	ASSERT_THROWS((BoundedBuffer<ThrowsOnCopy,2>{buf}),nasty);
}

struct ThrowsOnCopyNonDefault {
	ThrowsOnCopyNonDefault(int){}
	ThrowsOnCopyNonDefault(ThrowsOnCopyNonDefault const &){
		throw nasty{};
	}
	ThrowsOnCopyNonDefault(ThrowsOnCopyNonDefault &&other) noexcept =default;
	ThrowsOnCopyNonDefault& operator=(ThrowsOnCopyNonDefault const&){
		throw nasty{};
	}
	ThrowsOnCopyNonDefault& operator=(ThrowsOnCopyNonDefault&& other)noexcept=default;
};

void BufferWithThrowsOnCopyNonDefault(){
	BoundedBuffer<ThrowsOnCopyNonDefault,2> buf{};
	ThrowsOnCopyNonDefault t{1};
	buf.push(ThrowsOnCopyNonDefault{1}); // move OK
	ASSERT_EQUAL(1,buf.size());
	ASSERT_THROWS(buf.push(t),nasty);
	ASSERT_EQUAL(1,buf.size());
}


cute::suite make_suite_bounded_buffer_student_suite(){
	cute::suite s;
	s.push_back(CUTE(BufferWithThrowsOnCopy));
	s.push_back(CUTE(BufferWithThrowsOnCopyNonDefault));
	return s;
}



