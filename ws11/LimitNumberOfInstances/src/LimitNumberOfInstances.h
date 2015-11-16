#ifndef LIMITNUMBEROFINSTANCES_H_
#define LIMITNUMBEROFINSTANCES_H_

#include <stdexcept>
#include <atomic>
template <typename TOBELIMITED, unsigned int maxNumberOfInstances>
class LimitNofInstances {
	static std::atomic<size_t> counter;
protected:
    void checkNofInstances() {
        if(counter == maxNumberOfInstances)
            throw std::logic_error("too many instances");
    }
    LimitNofInstances() {
        checkNofInstances();
        ++counter;
    }
    ~LimitNofInstances() {
        --counter;
    }
    LimitNofInstances(const LimitNofInstances &other){
        checkNofInstances();
        ++counter;
	}
};
template <typename TOBELIMITED, unsigned int maxNumberOfInstances>
std::atomic<size_t>
LimitNofInstances<TOBELIMITED,maxNumberOfInstances>::counter{0};
#endif /* LIMITNUMBEROFINSTANCES_H_ */
