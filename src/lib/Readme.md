#RapidJSON LIB

&copy; 2015 Apex Data Solutions LLC 

## Overview

RapidJSON  can be parsed into DOM, and then the DOM can be queried and modified easily, and finally be converted back to JSON. 

## Project Links







[JIRA Project](https://pm.apexdatasolutions.net/browse/IFF/)

[Documentation](https://pd.apexdatasolutions.net/display/IF/InkFlow+Foundation)

[Stash Repository](https://pc.apexdatasolutions.net/projects/IFF/repos/ink2text/browse)

[Project Drive](https://drive.google.com/a/apexdatasolutions.net/folderview?id=0B9YDoBiPGbcGfjdrWnRRclcxd2Y0cGpCTzV1WUFZSFlndldUTjFkR0VZWnFSQm95Wm5jbzA&usp=sharing)

**Compatibility**

RapidJSON is cross-platform. Some platform/compiler combinations which have been tested are shown as follows.


-  Visual C++ 2008/2010/2013 on Windows (32/64-bit)
- GNU C++ 3.8.x on Cygwin
- Clang 3.4 on Mac OS X (32/64-bit) and iOS
- Clang 3.4 on Android NDK

**Installation**

RapidJSON is a header-only C++ library. Just copy the include/rapidjson folder to system or project's include path.

**Value & Document**

Each JSON value is stored in a type called Value. A Document, representing the DOM, contains the root Value of the DOM tree. All public types and functions of RapidJSON are defined in the rapidjson namespace.

**Query Value**

Assumes we have a JSON stored in a C string (const char* json):

    {
    "hello": "world",
    "t": true ,
    "f": false,
    "n": null,
    "i": 123,
    "pi": 3.1416,
    "a": [1, 2, 3, 4]
    }

**Parse it into a Document:**

    #include "rapidjson/document.h"
    using namespace rapidjson;
    // ...
    Document document;
    document.Parse(json);


**JSON array contains a number of elements.**

    // Using a reference for consecutive access is handy and faster.
    const Value& a = document["a"];
    assert(a.IsArray());
    for (SizeType i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
    printf("a[%d] = %d\n", i, a[i].GetInt());
    a[0] = 1
    a[1] = 2
    a[2] = 3
    a[3] = 4

**Query Array**
	
	...
    if (doc.HasMember("gridparm")){
		if (doc["gridparm"].IsArray()){
			Value& grid = doc["gridparm"];
			for (SizeType i = 0; i < grid.Size(); i++){
				if (grid[i].HasMember("grid")){
					param.gridparm[i].grid = grid[i]["grid"].GetInt();
					printf("a[%d] = %d\n", i, param.gridparm[i].grid);
				}
			}
		}
	}
	...