#ifndef SRC_MODULE_H_
#define SRC_MODULE_H_

#include <memory>
#include <string>
#include <istream>
#include <vector>

struct module{
	using spm=std::shared_ptr<module>;
	std::string name;
	std::vector<spm> pre_requisites;
	module(std::string const &s):name{s}{}
	void add(spm other){ pre_requisites.push_back(other);}
	void done_with(spm other) {
		pre_requisites.erase(
				remove(begin(pre_requisites),end(pre_requisites),other),end(pre_requisites));
	}
	bool is_ready() const { return pre_requisites.empty();}
	bool operator<(module const &other)const{return name < other.name;}
	bool operator==(module const &other) const { return name == other.name;}
};
inline std::istream & operator>>(std::istream &is, module &m){
	is >> m.name;
	return is;
}

using spm=module::spm;

inline spm make_module(std::string name){ return std::make_shared<module>(name);}


#endif /* SRC_MODULE_H_ */
