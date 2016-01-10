/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| Main global using Generic Factory Pattern   |
| GraphyteDB API controller   	              |
| Apex Data Solutions, LLC 					  |
| The Graphyte Library is distributed in the  |
| hope that it will be useful, but WITHOUT ANY|
| WARRANTY; without even the implied warranty |
| of MERCHANTABILITY or FITNESS FOR A   	  |
| PARTICULAR PURPOSE.  See the Documentation  |
| General Public License for more details.    |  		      	  |
|____________________________________________*/

#ifndef TGlobalFactoryH
#define TGlobalFactoryH

extern C
#include <boost/shared_ptr.hpp>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"
#include "boost/tuple/tuple_io.hpp"
#include <stdexcept>
#include <exception>
#include <iostream>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
#include <list>
#include <tuple>
#include <typeinfo>
#include <functional>

#include "TGlobalContainer.hpp"
#include "SupportFunction.h"
#include "SmartUnit.h"

#include <termios.h>

#define REGISTER_CLASS(NAME, TYPE)
#define LENGTH = 9999

// ____________________________________________________________________________//

using namespace std;
using namespace boost::tuples;
using namespace boost::lambda;
using namespace global_container;

// ____________________________________________________________________________//
/* :::::::::::::Factory class::::::::::::: */
// ____________________________________________________________________________//

template<class TGlobalBase, typename Global, typename CreationPolicy,
	template<typename, class>class FactoryErrorPolicy>
class TGlobalFactory : public FactoryErrorPolicy<Global, TGlobalBase> {
public:

	TGlobalFactory() { // argument's constructor
		MyMyCollectionGlobalNodes = new std::vector<tupleGlobal, std::string>();
		AssocRedisTree = new std::map<tupleRedis, TGlobalRedis>(T, T);
		tupleRedis = new boost::tuple<std::vector<TSubscript>, std::vector<TValue> >(T, T);
		CollectionRedis = new std::vector<T>(T);
	}

	explicit TGlobalFactory(const TGlobalFactory&);

	void operator = (const TGlobalFactory&);

	virtual ~TGlobalFactory() {
		auto i = FactoryGlobalMap.begin();
		while (i != FactoryGlobalMap.end()) {
			delete(*i).second;
			++i;
		}
		MySubscripts.clear();
		MyValues.clear();
		MyMyCollectionGlobalNodes.clear();
		tupleRedis.clear();
		AssocRedisTree.clear();
		CollectionRedis.clear();
	}

	// function object overload-operators defined
	inline bool operator == (const nullptr &LeftValue, const nullptr &RightValue){
		return (LeftValue == RightValue);
	}

	inline bool operator < (const T &LeftValue, const T &RightValue) {
		return (LeftValue < RightValue);
	}

	// declare Lambda Functions by Searching
	inline std::vector<std::string>FindAllGlobalByName() {
		return findMatchGlobalName([&](const std::string & pCurrentGlobal) {	
			return pCurrentGlobal.find(MyMyCollectioGlobalNodes.second)!= std::string.npos;});
	}

	inline std::vector<TIndex*>FindIndexInDocument() {
		return ensureIndex([&](const std::string & pCurrentGlobal) {	
			return pCurrentGlobal.find(MyMyCollectioGlobalNodes.second)!= std::string.npos;});
	}

	// declare Lambda Functions by Order index to MyCollectionGlobalNodes
	inline std::vector<std::string>OrderByDecreasedList() {
		return DecreaseOrder([&](const std::string & pCurrentGlobal) {
			return sort(MyMyCollectioGlobalNodes.first.get<0>.begin(), MyMyCollectioGlobalNodes.first.get<0>.end());});
	}

	inline std::vector<std::string>OrderGlobalbySubscript(TGlobalBase pGlobal) {
		if(find(MyMyCollectionGlobalNodes.begin(), MyMyCollectionGlobalNodes.end(), pGlobal)){
			return sort(pGlobal.GetSubscripts().begin(), pGlobal.GetSubscripts().end());
		}
		return nullptr;
	}

	// callback lambda function
	inline void callbackFunctions(std::string error, std::result) {
		[&]	(const std::vector<Functor>CallbackPointers) {
			if (CallbackPointers) {
				callbackFunctions(error, result); // recursive call
			} else
				throw Global_Error("Wrong Functor");
		}
	}

	struct CompareObj {
		template<typename T>
		bool operator < ()(const T &lhs, const T &rhs) const {
   			return get<0>(lhs) < get<0>(rhs) || lhs < rhs;
	};

	struct Cstring_less{
		bool operator < ()(const std::string lhs, const std::string rhs) const {
   			return lhs.compare(rhs) < 0;
	};

	struct Equiv {
		template<typename T>
    	bool operator == ()(const T &ls, const T &rs) const {
    		return !(cmp(ls,rs)||cmp(rs,ls));
    	}
	};

	std::vector<Functor> CallbackPointers();
	
	// declare Lambda Functions to RegisterGlobal another version
	inline static nullptr REGISTER_CLASS(NAME, [](nullptr)->TGlobalBase*{ return new TYPE();});
	// manipulate data!
	void InsertValue(const T& pMyValue, std::vector<T> &MySubscripts);
	void InsertSubscript(const T Subscript);
	void ArrayOfSubscripts(TGlobalBase* GlobalId);
	auto GetGlobalType(const Global & GlobalId);
	bool RegisterGlobal(Global & GlobalId, std::vector<std::shared_ptr<CreationPolicy> >FactoryGlobalMap);
	bool UnregisterGlobal(const Global & GlobalId);
	auto CreateGlobal(const Global & GlobalId);
	void AdvancedCreateGlobalNodes(const std::string pMyGlobalName);
	void AdvancedCreateTree(const std::string MyType);
	auto Instance(); // singleton pattern
	bool EqualsByValue(const TGlobalBase value1, const TGlobalBase value2);
	void CallGlobal(const std::string<TValue*>cmd, const std::string &args);
	std::vector<TGlobalBase*> GetGlobalDirectory(const std::vector<TGlobalBase>range);
	void MergeGlobals(const TGlobalBase DestGlobal, TGlobalBase SrcGlobal, Functor callbackFunctions);
	int IncrementGlobal(const TGlobalBase CurrentGlobal, Functor callbackFunctions);
	bool PreviousNodeGlobal(const TGlobalBase CurrentGlobal);
	bool PreviousLevSubscript(const TGlobalBase CurLevGlobal,	Functor callbackFunctions);
	bool NextNodeGlobal(const GlobalBase CurrentGlobal, Functor callbackFunctions);
	bool NextLevSubscript(const GlobalBase CurLevGlobal, Functor callbackFunctions);
	void UpdateGlobal(const std::string Name, const std::vector<TSubscripts> subscripts, const TValue Value)
	void DeleteGlobal(const TGlobalBase* DeletedGlobal);
	int WriteMemoryBlock(std::string Global, const std::vector<TValue*>& MyVector);
	void ReadMemoryBlock(const std::string path);
	void CreateIndex(const TIndex* index, const std::string option, callbackFunctions);
	void EnsureIndex(const std::string queryIndex, const std::string Index, const std::vector<TIndex> Indexes);
	void OrderByCompund(const Index IndexId, const std::vector<TIndex> collections, std::string criteria);
	void CreateMultipleIndex(const Index IndexId, std::vector<Index> fields);
	bool ExplainJSON(const Index IndexId, std::vector<TGlobalBase> globals, std::string verbosa);

private:

	typedef CreationPolicy<CreatorPolicy<T> >MyCreator;
	static typedef std::map<Global,	std::vector<std::shared_ptr<CreationPolicy> > >factoryGlobalMap;

	enum class Global { // Global identifier
		REDIS, TABULAR, DOCUMENT, GRAPHDB
	};
	
	typedef Functor max;
	typedef Functor lo;
	typedef Functor hi; // underlying global structure	
	typedef std::vector<TSubscript*>MySubscripts;
	typedef std::vector<TValue*>MyValues;
	typedef boost::tuple<std::pair<std::vector<std::string>, std::vector<TValue*> > >tupleGlobal(T, T);
	typedef std::vector<std::string>MyCollectionGlobalNodes;
	typedef boost::tuple<std::vector<TSubscript*>, std::vector<TValue*> >tupleRedis(T, T);
	typedef std::list<std::string>CollectionRedis;
	typedef std::map<std::vector<TSubscripts>, Global> >AssocRedisTree;
};
//Declarations 
// ____________________________________________________________________________//

auto TGlobalFactory<class>::GetGlobalType(Global EvalGlobal){
    
    if (EvalGlobal::REDIS)
	return REDIS;
    if (EvalGlobal::TABULAR)
	return TABULAR;
    if (EvalGlobal::DOCUMENT)
	return DOCUMENT;
    if (EvalGlobal::GRAPHDB)
	return GRAPHDB;
}

//____________________________________________________________________________//

template <template <class> class CreationPolicy>
bool TGlobalFactory<CreationPolicy>::RegisterGlobal(const Global GlobalId, std::vector<std::shared_ptr<CreationPolicy> > FactoryGlobalMap){
    
    return factoryGlobalMap.insert(factoryGlobalMap::value_type(GlobalId, pFactoryGlobalMap)).second;
}

//____________________________________________________________________________//

template <template<class> class CreationPolicy>
bool TGlobalFactory<CreationPolicy>::UnregisterGlobal(const Global GlobalId){
    
    return factoryGlobalMap.erase(GlobalId) == 1;
}

//____________________________________________________________________________//

template <template <class> class CreationPolicy>
auto TGlobalFactory<class>::CreateGlobal(const Global GlobalId){
    
    TGlobalBase* instance = nullptr;
    auto it = factoryGlobalMap.find(GlobalId);
    
    if (it != factoryGlobalMap.end())
		instance = it->second();
    if (instance != nullptr)
		return std::shared_ptr<CreationPolicy>(instance);
    else
    	return OnUnknownType(GlobalId);
}

//____________________________________________________________________________//

template<typename TGlobalBase>
void TGlobalFactory<TGlobalBase*>::SwitchPrototype(const TGlobalBase* pNewPrototype) {
	
	CreationPolicy<TGlobalBase>&myPolicy = *this;
	delete myPolicy.GetPrototype();
	myPolicy.SetPrototype(pNewPrototype);
}

//____________________________________________________________________________//

auto TGlobalFactory::ArrayOfSubscripts(const std::string GlobalId){
	
	auto retrieve_value;					
	auto first = MyCollectionGlobalNodes.begin();
	auto last = MyCollectionGlobalNodes.end();
	auto subscripts = std::find(first.second, last.second, GlobalId).first.first;
	if (subscripts)	{
		retrieve_value = subscripts.HasValue();
		if(retrieve_value != nullptr){
			return subscripts;
		}		
	}
	else if(subscripts.HasValue()){ 		
		bool isExpression = false;
		
		if(subscript.size() <= 1){
			isExpression = true;	
			subscripts = GlobalId;
		}

		if(isExpression){
			return subscripts;
		}
	}
	return nullptr;
}

//____________________________________________________________________________//
//singleton instance
template<>
auto TGlobalFactory<TGlobalFactory*>::Instance(){
    
    static TGlobalFactory factory;
    return &factory;
}

//____________________________________________________________________________//

template<typename TGlobalBase>
void TGlobalFactory<TGlobalBase*>::DeleteGlobal(const TGlobalBase* DeletedGlobal){
	std::vector<TGlobalBase*>::Iterator del;
	del = std::find(MyCollectionGlobalNodes.begin(), MyCollectionGlobalNodes.end(), DeletedGlobal);
	if(del){
		MyCollectionGlobalNodes.pop_back(del);
	}
}

//____________________________________________________________________________//

template<typename T>
void TGlobalFactory<T>::InsertSubscript(const T Subscript){
    
    bool isExpresion = false;

    MySubscripts = new std::vector<TSubscript>(Subscript);
    
    if(Subscript.HasValue()){

    	if(Subscript.size() <= 1){
    		isExpresion = true;
    	}

    	if(isExpresion){
    		Subscript = Subscript.HasValue();
    		std::string global = Subscript;
    		MyCollectionGlobalNodes.push_back(MyCollectionGlobalNodes.second(global));
    	}
    	else{//is a subscript array
    		MySubscripts.push_back(Subscript);
    		unique(MySubscripts.begin(), MySubscripts.end(), Equiv());
    		sort(MySubscripts.begin(), MySubscripts.end());
    	}
    }
}

//____________________________________________________________________________//

template<typename T>
bool TGlobalFactory<TSubscript>::UpdateSubscript(const std::string GlobalId, TValue& changeSub){
	
	if(changeSub != ""){
		std::vector<std::string>::Iterator first;
		std::vector<std::string>:;Iterator last;
		std::vector<TSubscripts>::Iterator found = std::find(first, last, GlobalId);
		
		if(found){
			bool isExpression = false;

			std::vector<TSubscript> v;
			std::vector<TSubscript>::Iterator iter = v.insert(found, )

		}
	}
}

template<typename T>
void TGlobalFactory<T>::InsertValue(const std::string& Global, const TValue& pMyValue) {
    
    if(Global){
    	MyValues.push_back(pMyValue);
    }
}

//____________________________________________________________________________//

template<typename T>
std::vector<TValue*> TGlobalFactory<TValue*>::GetValues(const std::string Global){
	
	std::vector<TValue*> myvector;
	std::vector<TGlobalBase>::Iterator found = find(MyCollectionGlobalNodes.begin(), MyCollectionGlobalNodes.end(), Global);
	
	if(found){
		myvector = found.GetValues();	
	}
	return myvector;
}

//____________________________________________________________________________//

template<typename T>
void TGlobalFactory<TValue>::WriteMemoryBlock(const std::string Global, const std::vector<TValue*>& MyVector) {
	
	std::vector<TValue*> newVector;
    std::string path ("./data");
    
    if (Global == MyVector.data()->GetGlobal()) {
   		
    	std::ofstream outfile(path, std::ios::out | std::ios::binary);
    	size_t size = MyVector.size();
    	if(size > 0){
    		std::ostreambuf_iterator out_iter(outfile);
	    	std::vector<TValue*>::Iterator first = MyVector.begin();
	    	std::vector<TValue*>::Iterator last = MyVector.end();
	    	std::copy(first, last, out_iter);    	
    	}	
    }
} 

//____________________________________________________________________________//

template<typename T>
std::vector<TValue*> TGlobalFactory<TValue*>::ReadMemoryBlock(const std::string path) {
	
	bool result = false;
	std::vector<TValue*> newVector;
	std::ifstream infile(path, std::ios::in | std::ifstream::binary);
	std::istreambuf_iterator in_iter(infile);
	std::istreambuf_iterator infirst = in_iter.begin();
	std::vector<TValue*>::Iterator inlast = in_iter.end();
	std::copy(infirst, inlast, std::back_inserter(newVector));
	size_t size = newVector.size();
	
	if(size > 0){
		return newVector;
	}	
    return newVector;
} 

//____________________________________________________________________________//
//fix and check C++ paradigm
template <typename CreatorPolicy, typename Key>
void TGlobalFactory<CreatorPolicy, Key>::SetGlobalNode(const TGlobalBase GlobalId, const TGlobalBase NewGlobal) {
    
    std::shared_ptr<CreatorPolicy> temp = MyCollectionGlobalNodes.find(GlobalId);
    
    if (temp) {
		SwitchPrototype(static_cast<CreatorPolicy*>NewGlobal);
        MyCollectionGlobalNodes.push_back(NewGlobal);
        unique(CollectionRedis.begin(), CollectionRedis.end(), Equiv());
        sort(CollectionRedis.begin(),CollectionRedis.end(),CompareObj());
    }
}

//____________________________________________________________________________//

template<typename T, typename TSubscripts, typename TValue>
void TGlobalFactory<T,Subscripts,TValue>::SetGlobal(const std::string OldGlobal, const std::string NewGlobal, const std::vector<TSubscripts> subscripts, const TValue Value){
	
	std::vector<T>::iterator found = std::find(MyCollectionGlobalNodes.begin(), MyCollectionGlobalNodes.end(), OldGlobal).second;
	std::string newGlobal;
	std::vector<TSubscript> subscripts;
	std::vector<TValue> data;

	if(found){
		newGlobal = NewGlobal;
		MyCollectionGlobalNodes.at(OldGlobal).push_back(newGlobal);
		if(subscripts.size() <= 1){
			bool updateSub = UpdateSubscript(newGlobal, subscripts);
			if(updateSub ){
				subscripts.SetValue(Value);
			}
		}
	}
}

//____________________________________________________________________________//

template<typename T>
void TGlobalFactory<T>::CreateGlobalNodeCollection(const std::string pMyGlobalName, const Global GlobalId){
	
	MyCollectioGlobalNodes.push_back(CollectionRedis.find(pMyGlobalName));
    sort(MyCollectioGlobalNodes.begin(), MyCollectioGlobalNodes.end(), Cstring_less());
    bool expression = false;
    std::string global = GetGlobalType(GlobalId);

    if(global){

    	switch(global){
    		case: REDIS{
    			auto data;
    			CreateRedis(Global::REDIS);
    			std::vector<TGlobalRedis*>::Iterator r;
    			std::for_each(r: CollectionRedis){
    				std::vector<TSubscript> SubRedis =	r.GetSubscripts();
    				tupleGlobal.first.push_back(SubRedis);
    				data = SubRedis.HasValue().data();
    				if(data){
    					tupleGlobal.second.push_back(data);
    				}
    			}
    		}	break;
    		case: DOCUMENT{

    		}	break;
    		case: TABULAR{

    		}	break;
    		case: GRAPHDB{

    		}	break;
    		default:
    			break;
    	}
    }
}

//____________________________________________________________________________//

template<typename T>
void TGlobalFactory<T>::CreateRedis(const Type EvalRedis) {
    
    std::string NameGlobal;
    std::vector<TSubscripts> Subscripts;
    std::vector<TValue> Values;
    
    std::for_each(auto it: MyCollectionGlobalNodes){
    	auto iter = it.get<1>();
        std::for_each(iter.begin(); iter.end(), iter) {
            NameGlobal = it->get<0>();
            Subscripts = it->get<1>();
            Values = it->get<2>();
            TGlobalRedis* MyGlobal = CreateObject(Global::REDIS);
            if (MyGlobal) {
                std::string redis = static_cast<TGlobalRedis*>(MyGlobal).GetRedisType(EvalRedis);  
            	if(redis){
            		CollectionRedis.push_back(boost::make_tuple(redis, Subscripts, Values));		
            	}    
            	if()
            }
        }
    }
}

//____________________________________________________________________________//

