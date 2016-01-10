/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| Wrapper Class and Namespace                 |
| Graphyte Addon JS and C++ language          |
| Bridge  Interface JS and C++ language       |
| Apex Data Solutions, LLC                    |
|____________________________________________*/
/****************************************************************************/
/*Global Type			                                                */
/****************************************************************************/
#define REDIS_NOSQL "redis"
#define TABLE_NOSQL "table"
#define DOCUMENT_NOSQL "document"
#define GRAPH_NOSQL "graph"

/****************************************************************************/
/*Element Type				                                                */
/****************************************************************************/
#define TYPE_STRING
#define TYPE_INTEGER
#define TYPE_LONG
#define TYPE_DOUBLE
#define TYPE_INTEGER_ARRAY
#define TYPE_LONG_WRAPPER
#define TYPE_DOUBLE_WRAPPER
#define TYPE_STRING_ARRAY
#define TYPE_LONG_ARRAY
#define TYPE_DOUBLE_ARRAY

#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "GraphyteWrap.h"
#include <sstream>
#include <node.h>
#include <v8.h>
using namespace std;
using namespace v8;
//using namespace rapidjson;
/****************************************************************************/
/*METHOD: parse json docs                                                   */
/****************************************************************************/
struct redis {
	int ID;
	std::string global;
	std::string subscripts;
	std::string value;
};

struct json {
	int ID;
	std::string global;
	char subscripts;
	void * value;
};

struct table {
	int ID;
	std::string global;
	char subscripts;
	void * value;
};

struct graph {
	int ID;
	std::string global;
	std::string subscripts;
	void * value;
};

void increment(int i){
	i++;
};

/****************************************************************************/
/*METHOD: working with Globals                                              */
/****************************************************************************/
void Add(const FunctionCallbackInfo<Value> &args){
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	printf("testing...");
	if (args.Length() < 2)
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong length")));
	return;

	if (!args[0]->IsNumber() || !args[1]->IsNumber())
		isolate->ThrowException(v8::Exception::TypeError(String::NewFromUtf8(isolate, "it is not a number")));
	return;
	std::stringstream temp;
	int result_integer = args.Length();

	std::string test;
	temp.str();
	double value = args[0]->NumberValue() + args[1]->NumberValue();
	temp << 0;
	test = temp.str();
	printf(test.c_str());
	Local<Number> num = Number::New(isolate, value);
	args.GetReturnValue().Set(num);
}

void RunCallBack(const FunctionCallbackInfo<Value> &args){
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Local<Function> cb = Local<Function>::Cast(args[0]);
	const unsigned argc = 1;
	Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello") };
	cb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}

void Functions(const v8::FunctionCallbackInfo<v8::Value> &args) {
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);
	v8::Persistent<v8::Function> callback;
	callback.Reset(isolate, args[0].As<v8::Function>());
	const unsigned argc = 2;
	v8::Local<v8::Value> argv[argc] = { Null(isolate), v8::String::NewFromUtf8(isolate, "success") };
	v8::Local<v8::Function>::New(isolate, callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);
	callback.Reset();
}
/****************************************************************************/
/*METHOD: parse json docs                                                   */
/****************************************************************************/
//Parameter: Document document, String separator, boolean topLeve
/*
std::string toJSON(Document document, std::string separator, bool topLeve){

	if (separator == "") {
		separator = "";
	}
	std::string json = separator + "{" + separator;
	bool first = true;
	for (std::string key : document.()) {
		if (!first) {
			json = json + "," + separator;
		}
		first = false;

		v8::Local<v8::Object> doc = document.GetSubscript(key);
		if (doc instanceof Document[]) {
			Document[] docs = (Document[]) doc;
			String temp = "";
			for (int i = 0; i<docs.length; i++) {
				temp = temp + toJSON(docs[i], separator + " ", false);
			}
			json = json + key + ":" + separator + "[" + temp + separator + "]";
		}
		else if (doc instanceof Document) {
			json = json + key + " : " + toJSON((Document)doc, separator + " ", false);
		}
		else {
			Object value = document.get(key);
			if (value == null) {
				json = json + key + " : null";
			}
			else if (value instanceof Object[]) {
				json = json + key + jsonStringArray(toStringArray((Object[])value));
			}
			else if (value instanceof byte[]) {
				json = json + key + " : " + new String((byte[])value);
			}
			else {
				json = json + key + " : " + value;
			}
		}
	}
	return json + separator + "}";
}

//End of Global_Response2JSON
void parseJSON(const v8::FunctionCallbackInfo<Value> &args){
	v8::String::Utf8Value cmd(args[0]);
	std::string value = std::string(*cmd);
	//to do
	char result[255] = "";
	static char *retValue;
	retValue = result;
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);
	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, retValue));
}//End of parse_json
*/
/*void InsertSubscript(const v8::FunctionCallbackInfo<Value> &args) {
	v8::String::Utf8Value cmd(args[0]);
	std::string subscript = std::string(*cmd);
	
	uint32_t userId = args[0]->ToUint32()->Value();
	v8::Isolate* isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);
	if (subscript.length ==0) {
		args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "wrong subscript array"));
	}
	else {
		//CreateGlobal(args);
	}
	
	char result[255] = "";
	
	redisGlobal redis;
	memcpy(result, subscript.c_str(), sizeof(subscript));
	static char *retValue;
	retValue = result;

	args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, retValue));
}*/
/****************************************************************************/
/*METHOD: export				                                            */
/****************************************************************************/

void init(v8::Handle<v8::Object> exports) {
	//NODE_SET_METHOD(exports, "parseJSON", parseJSON);
	NODE_SET_METHOD(exports, "add", Add);
	NODE_SET_METHOD(exports, "callback", RunCallBack);
	//NODE_SET_METHOD(exports, "CreateGlobal", CreateGlobal);
	//NODE_SET_METHOD(exports, "WrapGlobal", WrapGlobal);
	//NODE_SET_METHOD(exports, "SwitchPrototype", SwitchPrototype);
	//NODE_SET_METHOD(exports, "InsertValue", InsertValue);
	//NODE_SET_METHOD(exports, "InsertSubscript", InsertSubscript);
	//NODE_SET_METHOD(exports, "AdvancedCreateGlobalNodes", AdvancedCreateGlobalNodes);
	//NODE_SET_METHOD(exports, "AdvancedCreateTree", AdvancedCreateTree);
	//NODE_SET_METHOD(exports, "FindGlobalByName", FindGlobalByName);
	//NODE_SET_METHOD(exports, "GetGlobalDirectory", GetGlobalDirectory);
	//NODE_SET_METHOD(exports, "GetValue", GetValue);
	//NODE_SET_METHOD(exports, "ArrayOfSubscripts", ArrayOfSubscripts);
	//NODE_SET_METHOD(exports, "PreviousNodeGlobal", PreviousNodeGlobal);
	//NODE_SET_METHOD(exports, "NextNodeGlobal", NextNodeGlobal);
	//NODE_SET_METHOD(exports, "OrderGlobalbySubscript", OrderGlobalbySubscript);
	//NODE_SET_METHOD(exports, "OrderByDecreasedList", OrderByDecreasedList);
	//NODE_SET_METHOD(exports, "RegisterGlobal", RegisterGlobal);
}

//Init the module
NODE_MODULE(graphyteAPI, init)


