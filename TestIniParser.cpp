#include "IniParser.h"
#include <stdlib.h>
int main( int argc, char ** argv){
	IniParser myparser;
	int intValue;
	try {
		myparser.Load(argv[1]);
		myparser.QueryKeyValue<int>("Section4","KeyIt",intValue);
	} catch ( IniParseException &e) {
		std::cout << e.what();
		exit (1);
	}
	return 0;
}
