#ifndef __INI_PARSER_H_
#define __INI_PARSER_H_

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <exception>
#include <iterator>

#pragma warning( disable : 4290 )

typedef std::map<std::string, std::string>      KeyValueMapType;
typedef std::map<std::string, KeyValueMapType > SectionMapType;
typedef std::vector<std::string> FileLineType;

class IniParseException {
public:
	IniParseException(	std::string message, 
						int line = 0) : m_message(message),
										m_line(line) {
		if ( m_line != 0 ) {
			std::ostringstream custom_message;
			custom_message << "Parsing Error occured at line number ";
			custom_message << m_line << " : " ;
			custom_message << m_message;		
			m_message = custom_message.str();
		}
	}
	const char* what() const throw(){
		return m_message.c_str();
	}
private:
	std::string m_message;
	int m_line;
};

class IniParser {
private:
	template <typename T>
	static T string_to_T(std::string const &val) {
		std::istringstream istr(val);
		T returnVal;
		istr >> returnVal;
		return returnVal;
	}
public:
	IniParser();		
	~IniParser();
	void Load( const std::string &filename) throw (IniParseException); 
	std::vector<std::string> getAllSections();
	template < typename ValueType>
	void QueryKeyValue(const std::string &section, 
							const std::string &key, 
							ValueType &defaultValue = ValueType()) 
							const throw (IniParseException) {
		SectionMapType::const_iterator itrS = m_sectionMap.find(section);
		if ( itrS == m_sectionMap.end()){
			throw IniParseException( section + " not found");
		}
		KeyValueMapType::const_iterator itrK = itrS->second.find(key);	
		if ( itrK == itrS->second.end()){
			throw IniParseException( key + " not found under section " + section );
		}
		defaultValue = string_to_T<ValueType>(itrK->second);
	}
private:
	bool validLine(const std::string &line) const;
	SectionMapType m_sectionMap;
};

#endif
