#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <fstream>

using analist=std::set<std::string>;
analist makeAnagrams(std::string s){
	sort(s.begin(),s.end());
	analist anagrams{};
	anagrams.insert(s);
	while(std::next_permutation(s.begin(),s.end())){
		anagrams.insert(s);
	}
	return anagrams;
}
using outiter=std::ostream_iterator<std::string>;
void outputRealWordsWithLambda(outiter out,analist const &list){
	using initer=std::istream_iterator<std::string>;
	std::ifstream allwords{"/usr/share/dict/words"};
	initer input{allwords};
	copy_if(input,initer{},out,[&list](std::string const& s){return list.count(s);});
}
int main(){
	std::string word{};
	std::cin >> word;
	auto list=makeAnagrams(word);
	std::ostream_iterator<std::string> out{std::cout,"\n"};
	copy(list.begin(),list.end(),out);
	std::cout << "--------------------------\n";
	outputRealWordsWithLambda(out,list);
}
