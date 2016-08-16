template <typename LTC>
concept bool LessThanComparable() {
	return requires(LTC a, LTC b) {
		{ a < b } -> bool;
	};
}
