#ifndef LONG_FUNCTION_H_
#define LONG_FUNCTION_H_
#include <string>
#include <iosfwd>





void writeNTimesToStream( std::ostream& file
                        , std::string content
                        , size_t n);

bool writeNTimesToStreamIfOk( std::ostream& file
		              	    , std::string content
		              	    , size_t n);


bool writeNTimesToFile3(std::string filename
		               , std::string content
		               , size_t n);



#endif /* LONG_FUNCTION_SYNTAX_H_ */
