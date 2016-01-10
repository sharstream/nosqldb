/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| String Unit support                         |
| String and Object Transformation            |
| Apex Data Solutions, LLC                    | 
|____________________________________________*/

#include <boost/spirit/home/support/container.hpp>
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <iterator>
#include <iostream>
#include <cxxabi.h>
#include <cstdlib>

#ifdef __GNUG__ // GCC

// ____________________________________________________________________________//

static std::string readable_name(const char* mangled_name) {
	int status;
	char* temp = __cxxabiv1::__cxa_demangle(mangled_name, nullptr, nullptr,
		&status);
	if (temp) {
		std::string result(temp);
		std::free(temp);
		return result;
	}
	else
		return mangled_name;
}

#else // not GCC

inline std::string readable_name(const char* mangled_name) {
	return mangled_name;

}
// ____________________________________________________________________________//

#endif // __GNUG__

template<typename T>
std::string type_to_string() {
	return readable_name(typeid(T).name());
}

template<typename T>
std::string type_to_string(const T& obj) {
	return readable_name(typeid(obj).name());
}

// ____________________________________________________________________________//

template<typename T>
typename std::enable_if<boost::spirit::traits::is_container<T>::value,
	bool>::type is_it_a_container(T && v) {
	std::cout << "yes, this is a container holding values of type " <<
		type_to_string < decltype(*std::begin(v)) > () << '\n';
	return true;
}

template<typename T>
typename std::enable_if < !boost::spirit::traits::is_container<T>::value,
	bool > ::type is_it_a_container(T &&) {
	std::cout << "no, this is not a container\n";
	return false;
}

//____________________________________________________________________________//

