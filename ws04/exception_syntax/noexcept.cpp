int minimum(int a, int b, int c) noexcept {
	return a<b?(a<c?a:c):(b<c?b:c);
}

int maximum(int a, int b, int c) throw() {
	return a>b?(a>c?a:c):(b>c?b:c);
}
