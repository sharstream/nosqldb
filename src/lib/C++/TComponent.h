/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| Main global using Factory Pattern           |
| Subscripts and Data/Value Object            |
| Apex Data Solutions, LLC    				  |	
|____________________________________________*/

#ifndef TComponentH
#define TComponentH

#include <vector>
#include <stxxl>

#define LENGTH
typedef stxxl::VECTOR_GENERATOR<Persistent>::result vector;
vector my_vector;  // creates empty vector object

template<typename T>
struct Persitent {
  	stxxl::vector<TSubscript> subscripts;
  	stxxl::vector<TValue> data;
  	std::string global;
};

// ____________________________________________________________________________//

template<typename TValue>
class TSubscript {
public:
	TSubscript() {
		value = new TValue();
	};

	TSubscript(const TValue pValue) {
		value = pValue;
	}

	~TSubscript() {
	};

	TValue* HasValue() {
		return value;
	}

	void HasValue(const TValue* pValue) {
		value = pValue;
	}

private:
	TValue* value;

	std::vector<Persistent> retrieve_globals;

	void operator = (const TSubscript&);

	TSubscript(const TSubscript&);
};

// ____________________________________________________________________________//

template<typename T>
class TValue {
public:
	TValue() {
	};

	TValue(const T pMyValue, const std::vector<T>pMySource) {
		aValue = pMyValue;
		aSource = pMySource;

	}

	~TValue() {
	};

	std::vector<T>GetSource() {
		return storage.subscripts;
	}

	std::string GetValue() {
		return storage.data;
	}

	std::string GetGlobal(){
		return storage.global;
	}

	void SetSource(const std::vector<T>pMySource) {
		storage.subscripts = pMySource;
	}

	void SetValue(const std::string pMyValue) {
		storage.data = pMyValue;
	}

	void SetGlobal(std::string pGlobal){
		storage.global = pGlobal;
	}

private:

	Persistent storage;

	void operator = (const TValue&);

	TValue(const TValue&);
};
// ____________________________________________________________________________//

template<typename T>
class TIndex{
public:
	TIndex(){}

private:
	std::string selection;
	std::string option;
	std::vector<std::string> options;
};

#endif
