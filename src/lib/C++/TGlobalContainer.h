/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| Main global using Factory Pattern header    |
| NoSQL Global Object   					  |
| Apex Data Solutions, LLC    				  |	
|____________________________________________*/

#ifndef TGlobalContainerH
#define TGlobalContainerH

#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vcl.h>

#include <node.h>

#include "TComponent.h"

// ____________________________________________________________________________//

using namespace global_container {

	template<class CreatorPolicy, class TSubscript, class TValue>
	class TGlobalBase {
	public:
	    TGlobalBase(std::string& pGlobalName, std::vector<TSubscript>& pSubscripts,
		TValue& pValues) :  aGlobalName_(pGlobalName), aSubscripts_(pSubscripts),
	        aValues_(pValues) {
	    }

	    TGlobalBase() {
	    }; // default constructor

	    virtual ~TGlobalBase() {
	    } /* without this, you do not call allGlobal destructors in this example! */

	    virtual std::string GetGlobalName() {
			return aGlobalName_;
	    }

	    virtual void SetGlobalName(const std::string pGlobalName) {
			aGlobalName_ = pGlobalName;
	    }

	    virtual std::vector<TSubscript> GetSubscripts() {
			return aSubscripts_;
	    }

	    virtual void SetSubscripts(const std::vector<TSubscript>pSubscripts) {
			aSubscripts_ = pSubscripts;
	    }

	    virtual std::vector<TValue*> GetValues() {
			return aValues_;
	    }

	    virtual void SetValues(const std::vector<TValue>& pValues) {
			aValues_ = pValues;
	    }

	    virtual string toString() const = 0;

	    virtual void draw(std::string pGlobalName,
			std::vector<TSubscript>pSubscripts, TValue pValues) const = 0;

	    virtual TGlobalBase* Clone() const = 0{
	    }

	protected:
	    CreatorPolicy aCreator_;
	    std::vector<TSubscript*> aSubscripts_;
	    std::vector<TValue*> aValues_;

	    std::string aGlobalName_;

	    TGlobalBase(const TGlobalBase&);
	    void operator = (const TGlobalBase&);
	};

	// ____________________________________________________________________________//

	template<>
	class TGlobalRedis : public TGlobalBase<class TGlobalRedis, class TSubscript, class TValue> {
	public:

	    TGlobalRedis() {
			aMySet = new std::vector<TGlobalBase>();
	    }

	    TGlobalRedis(const TGlobalBase& pGlobal, const std::vector<TGlobalBase>& pMySet, const GetRedisType& pTypeRedis)
			: pGlobal_(pGlobal), aMySet_(pMySet), pType_(pTypeRedis) {
	    }

	    ~TGlobalRedis() {
	    }

	    // Access methods
	    std::vector<TGlobalRedis>GetRedisList() {
			return aMySet;
	    }

	    void SetRedisList(std::vector<T>pMySet) {
			aMySet = pMySet;
	    }

	    virtual std::string toString() {
			stringstream stm;
			stm << aGlobalName;
			for (int i = 0; i < aSubscripts.size(); ++i) {
			    stm << ": " << aSubscripts[i];
			}
			for (int j = 0; j < aValues.size(); ++j) {
			    stm << ": " << aValues[i];
			}
			for (int i = 0; i < aMySet.size(); ++i) {

			    stm << ": " << aMySet[i];
			}
			stm << ": " << end1;
			return stm.str();
	    }

	    virtual void draw(std::string pGlobalName, std::vector<T>pSubscripts,
		std::vector<T>pValues) {
			cout << "GlobalRedis : " << pGlobalName << "(" << std::for_each
		    (pSubscripts.begin(), pSubscripts.end()) << ")=(" << std::for_each
		    (pValues.begin(), pValues.end()) << ")" << end1;
	    }

	    virtual TGlobalRedis* Clone() const {
			return new TGlobalRedis(this*);
	    }

	    inline auto GetRedisType(Type EvalRedis){
	        if (EvalRedis::None)
	            return None;
	        if (EvalRedis::String)
	            return String;
	        if (EvalRedis::List)
	            return List;
	        if (EvalRedis::Set)
	            return Set;
	        if (EvalRedis::ZSet)
	            return ZSet;
	        if (EvalRedis::Hash)
	            return Hash;
	    }

	private:
	    TGlobalBase pGlobal_;

	    enum class Type {
			None, String, List, Set, ZSet, Hash
	    };

	    Type pType_;

	    std::vector<TGlobalRedis>aMySet_;

	    TGlobalRedis(const TGlobalRedis&);

	    void operator = (const TGlobalRedis&);
	};

	// ____________________________________________________________________________//

	template<>
	class TGlobalTabular : public TGlobalBase<class TGlobalTabular, class TSubscript, class TValue>{
	public:
		TGlobalTabular() {
		};

		TGlobalTabular(std::string pGlobalName, std::vector<T>pSubscripts,
			std::vector<T> pValues, int pCol, int pRow) : TGlobalGeneric<T>(pGlobalName,pSubscripts,pValue){}

		virtual ~TGlobalTabular() {
		};

		virtual string toString() override {
			stringstream stm;
			stm << aGlobalName;
			for (int i = 0; i < aSubscripts.size(); ++i) {
				stm << ": " << aSubscripts[i];
			}
			for (int j = 0; j < aValues.size(); ++j) {
				stm << ": " << aValues[i];
			}
			stm << ": " << aCol << ": " << aRow << end1;
			return stm.str();
		}

	        virtual void draw(std::string pGlobalName, std::vector<T>pSubscripts,
	            std::vector<T> pValues) override {
	            cout << "TGenericGlobal::Draw(" << pGlobalName << "," <<
	                    std::for_each(pSubscripts.begin(), pSubscripts.end()) << "," <<
	                    std::for_each(pSubscripts.begin(), pSubscripts.end()) << ")" << end1;
	        }

		virtual TGlobalTabular* Clone() override {
			return new TGlobalTabular(*this);
		}

		int GetCol(){return aCol;}
		void SetCol(int pCol){aCol = pCol;}

		int GetRow(){return aRow;}
		void SetRow(int pRow){aRow = pRow;}

	private:
		int aCol;
		
		int aRow;

		TGlobalTabular(const TGlobalTabular&);

		void operator=(const TGlobalTabular&);
	};

	//____________________________________________________________________________//

	template<>
	class TGlobalDocument : public TGlobalBase<class TGlobalDocument, class TSubscript, class TValue>{ // more complexity!!!!!!
	public:
		TGlobalDocument() {
		};

		TGlobalDocument(std::string pGlobalName, std::vector<T>pSubscripts,
			std::vector<T> pValues, std::set<TGlobalDocument> pDocuments)
			: TGlobalGeneric<T>(pGlobalName,pSubscripts,pValues){}

		virtual ~TGlobalDocument() {
		};

		virtual string toString() override {
			stringstream stm;
			stm << aGlobalName;
			for (int i = 0; i < aSubscripts.size(); ++i) {
				stm << ": " << aSubscripts[i];
			}
			for (int j = 0; j < aValues.size(); ++j) {
				stm << ": " << aValues[i];
			}
			stm << end1;
			return stm.str();
		}

	    void GetQueryByDocument();

		virtual void draw(std::string pGlobalName, std::vector<T>pSubscripts,
				std::vector<T> pValues) override {
				cout << "TGenericGlobal::Draw(" << pGlobalName << "," <<
						std::for_each(pSubscripts.begin(), pSubscripts.end()) << "," <<
						std::for_each(pSubscripts.begin(), pSubscripts.end()) << ")" << end1;
		}

		virtual TGlobalDocument* Clone() override {
			return new TGlobalDocument(*this);
		}

	private:
		enum class TypeDocumentMap {
	        	LIST, ARRAY, OBJECT
	    	};
		bool aType; // type of JSON & Array

		std::set<TGlobalDocument>SharedDocuments(T);

		TGlobalDocument(const TGlobalDocument&);

		void operator=(const TGlobalDocument&);
	};

	//____________________________________________________________________________//

	template<>
	class TGlobalGraph : public TGlobalBase<class TGlobalGraph, class TSubscript, class TValue>{ // more complexity!!!!!!
	public:
		// attached two nodes/relationships

		TGlobalGraph() {
		};

		TGlobalGraph(std::string pGlobalName, std::vector<T>pSubscripts,
			std::vector<T> pValues, T pEdgeGraph)
			: TGlobalGeneric<T>(pGlobalName,pSubscripts,pValue){}

		virtual ~TGlobalGraph() {
		};

		virtual string toString() override {
			stringstream stm;
			stm << aGlobalName;
			for (int i = 0; i < aSubscripts.size(); ++i) {
				stm << ": " << aSubscripts[i];
			}
			for (int j = 0; j < aValues.size(); ++j) {
				stm << ": " << aValues[i];
			}
			stm << end1;
			return stm.str();
		}

	        virtual void draw(std::string pGlobalName, std::vector<T>pSubscripts,
	            std::vector<T> pValues) override {
	            cout << "TGenericGlobal::Draw(" << pGlobalName << "," <<
	                    std::for_each(pSubscripts.begin(), pSubscripts.end()) << "," <<
	                    std::for_each(pSubscripts.begin(), pSubscripts.end()) << ")" << end1;
	        }

		virtual TGlobalGraph* Clone() override {
			return new TGlobalGraph(*this);
		}

	private:
		std::list<T> EdgeGraphCollection;

		TGlobalGraph(const TGlobalGraph&);

		void operator=(const TGlobalGraph&);
	};

}

// ____________________________________________________________________________//



#endif
