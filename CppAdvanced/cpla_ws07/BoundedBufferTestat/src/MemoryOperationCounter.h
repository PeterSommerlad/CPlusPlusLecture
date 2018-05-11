
#ifndef MEMORYOPERATIONCOUNTER_H_
#define MEMORYOPERATIONCOUNTER_H_

struct MemoryOperationCounter {
	MemoryOperationCounter() = default;
	MemoryOperationCounter(unsigned moves, unsigned copies, bool known_state) :
			moves { moves }, copies { copies }, known_state { known_state } {
	}

	MemoryOperationCounter(MemoryOperationCounter && source) :
			moves { std::move(source.moves) }, copies { std::move(source.copies) }, known_state { std::move(source.known_state) } {
		moves++;
		source.known_state = false;
	}

	MemoryOperationCounter & operator=(MemoryOperationCounter && source) & noexcept {
		copyFrom(source);
		moves++;
		source.known_state = false;
		return *this;
	}

	MemoryOperationCounter(MemoryOperationCounter const & source) :
			moves { std::move(source.moves) }, copies { std::move(source.copies) }, known_state { std::move(source.known_state) } {
		copies++;
	}

	MemoryOperationCounter & operator=(MemoryOperationCounter const & source) & noexcept {
		copyFrom(source);
		copies++;
		return *this;
	}

	bool operator==(MemoryOperationCounter const & other) const {
		return (moves == other.moves) && (copies == other.copies) == (known_state == other.known_state);
	}

	void print(std::ostream & os) const {
		os << "MemoryOperationsCounter{moves: " << moves << ", copies: " << copies << ", known_state: " << known_state << "}\n";
	}

private:
	unsigned moves { 0 };
	unsigned copies { 0 };
	bool known_state { true };

	void copyFrom(MemoryOperationCounter const & source) {
		moves = source.moves;
		copies = source.copies;
		known_state = source.known_state;
	}
};

inline std::ostream & operator <<(std::ostream & os, MemoryOperationCounter const & counter) {
	counter.print(os);
	return os;
}


#endif /* MEMORYOPERATIONCOUNTER_H_ */
