/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| Wrapper Class and Namespace                 |
| Graphyte Addon JS and C++ language          |
| Bridge  Interface JS and C++ language       |
| Apex Data Solutions, LLC                    |
|____________________________________________*/

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(disable: 4032) /* formal parameter has different type when promoted */
#pragma warning(disable: 4115) /* named type definition in parenthesis */
#pragma warning(disable: 4996)
#include <windows.h>
#include <conio.h>
#include <io.h>
#elif defined _UNIX
#include <unistd.h>
#include <wchar.h>
int fwide(FILE *stream, int mode);
int wprintf(const wchar_t *format, ...);
#endif
#if !defined(_UNIX) && !defined(__GNUC__)
#include <sys\timeb.h>
#endif
#if defined(_MACOSX_IOS)
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif
#define STDSTRING_H
#define _DBG_MAP_ALLOC
#include <node.h>
#include <node_buffer.h>
#include <stdio.h> 
#include <strsafe.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <inttypes.h>
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
//#include "./lib/C++/TGlobalFactory.h"
#include <iostream>

//#include "TGlobalFactory.h"
#include <node.h>
#include <node_object_wrap.h>

//using namespace node;
/*
class Graphyte : public node::ObjectWrap {
public:

	 void init(v8::Handle<v8::Object> exports);
	 
private:

	explicit Graphyte(){}
	~Graphyte(){}

	void CreateGlobal(const v8::FunctionCallbackInfo<v8::Value> &args);
	void UpdateGlobal(const v8::FunctionCallbackInfo<v8::Value> &args);
	void InsertValue(const v8::FunctionCallbackInfo<v8::Value> &args);
	void InsertSubscript(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void AdvancedCreateGlobalNodes(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void AdvancedCreateTree(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void GetGlobalDirectory(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void OrderGlobalbySubscript(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void PreviousNodeGlobal(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void NextNodeGlobal(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void GetValue(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void ArrayOfSubscripts(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void Parse_JSON(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void WrapperCall(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void SwitchPrototype(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void GetGlobalType(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void WrapGlobal(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void NewInstance(const v8::FunctionCallbackInfo<v8::Value> &args);
	 void New(const v8::FunctionCallbackInfo<v8::Value> &args);

	void* InstanceFactory;
};*/