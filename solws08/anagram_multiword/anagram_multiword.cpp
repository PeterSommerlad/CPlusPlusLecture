#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <chrono>

using anaset=std::multiset<char>;
using anaword=std::pair<anaset,std::string>;
using anawords=std::vector<anaword>;
using anaiter=anawords::const_iterator;
using anacand=std::vector<anaword>;
using allanas=std::vector<anacand>;
using outiter=std::ostream_iterator<std::string>;
void printCandidate(std::ostream & out,anacand const & cand){
	// should create all permutations of cand's words
	std::vector<std::string> sentence{};

	transform(begin(cand),end(cand),back_inserter(sentence),[](anaword w){
		std::string word{};
		transform(begin(w.second),end(w.second),back_inserter(word),tolower);
		return word;
	});
	copy(begin(sentence),end(sentence),outiter{out," "});
	out << '\n';
}
void printAllCandidates(std::ostream & out, allanas const &all){
	for (auto c:all){
		printCandidate(out,c);
	}
}

anaword makeAnaword(std::string const & words){
	std::string s{words};
	s.erase(remove_if(begin(s),end(s),[](char c){return !isalpha(c);}),end(s));
	transform(begin(s),end(s),begin(s),tolower);
	return make_pair(anaset{begin(s),end(s)},words);
}

void print(std::ostream &out, anaword w){
	std::ostream_iterator<char> os{out};
	copy(begin(w.first),end(w.first),os);
	out << ": " << w.second << std::endl;
}

bool subsetOfWord(anaword const& w, anaword const& aw) {
	return aw.second.size()
		&& includes(begin(w.first),end(w.first),begin(aw.first),end(aw.first));
}

bool caselessEqual(anaword const &w,anaword const&v){
	return equal(begin(w.second),end(w.second),begin(v.second),end(v.second),
			[](char l, char r){ return tolower(l)==tolower(r);});
}

bool notalreadyinSetInDifferentSpelling(anaword const& w, anawords const & wl) {
	auto b=begin(wl);
	auto e=end(wl);
	bool res= e == find_if(b,e,[w](auto v){ return caselessEqual(w,v);});
	if (!res)std::cout << "already there "<<w.second<<std::endl;
	return res;
}

anawords collectFromFile(anaword w,std::string filename="/usr/share/dict/words"){
	anawords wl;
	std::ifstream allwords(filename);
	std::string s;
	while(getline(allwords,s)){
		if (s.size()>1 || s=="I" || s=="A"){
		auto aw=makeAnaword(s);
		if (subsetOfWord(w,aw) && notalreadyinSetInDifferentSpelling(aw,wl)){
			wl.push_back(aw);

		}
		}
	}
	return wl;
}

anaword subtract(anaword const &origin, anaword const &candidate){
	if (subsetOfWord(origin,candidate)){
		std::string res{};
		std::set_difference(begin(origin.first),end(origin.first),
				           begin(candidate.first),end(candidate.first),
						   back_inserter(res));
		return makeAnaword(res);
	}
	return origin;
}

void lookForFittingRest(anawords const &wl,anaiter b, anaiter e,anaword rest,allanas &res,anacand &cand){
	while (b != e){
		if (subsetOfWord(rest,*b)){
			cand.push_back(*b);
			auto newrest=subtract(rest,*b);
			if (newrest.first.size()){
				lookForFittingRest(wl,begin(wl),e,newrest,res,cand);
			} else {
				res.push_back(cand);
			}
			cand.pop_back();
		}
		++b;
	}
}

void addCandidatesFor(anawords const &wl,anaiter b, anaiter e, anaword origin,allanas &res){
	while (b != e){
		if (subsetOfWord(origin,*b)){ // should be true anyway
			anacand cand{1,*b};
			auto rest=subtract(origin,*b);
			if (rest.first.size()){
				lookForFittingRest(wl,begin(wl),e,rest,res,cand);
			} else {
				res.push_back(cand);
			}
		}
		++b;
	}
}

allanas findCandidates(anawords const &wl, anaword const &origin){
	allanas res{};
	addCandidatesFor(wl,wl.begin(),wl.end(),origin,res);
	return res;
}

void doAnagram(std::istream &in, std::ostream &out){
	std::string word{};
	getline(in, word);
	auto w=makeAnaword(word);
	print(out, w);
	auto start=std::chrono::system_clock::now();
	auto wl=collectFromFile(w,"linuxwords.txt");
	out << wl.size() << "matching words in set" << std::endl;
	auto res=findCandidates(wl,w);
	std::chrono::duration<double> delta=std::chrono::system_clock::now()-start;
	out << res.size() << " anagrams found\n";
	out << delta.count() << "s time\n";
	getline(in,word);
	printAllCandidates(out,res);
}
int main(){
	doAnagram(std::cin,std::cout);
}
