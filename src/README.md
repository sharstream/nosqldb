    Copyright (c) 2015 by David Perez

    Apex Data Solutions, LLC

# V8: Object overview #

##Properties of properties##

    obj[1];//
    obj["1"];  // names for the same property
    obj[1.0];  //
    
    var o = { toString: function () { return "-1.5"; } };
    
    obj[-1.5];  // also equivalent
    obj[o]; // since o is converted to string

##Dictionary mode##

   	 0:  map (string type)
     4:  length (in characters)
     8:  hash code (lazily computed)
    12:  characters...
 
##In-object slack tracking##

V8 uses a process called in-object slack tracking to determine an appropriate size for instances of each constructor.

## Numbered properties: fast elements ##

> fast small integers
> 
> fast doubles
> 
> fast values
> 
> fast elements

**Some examples of undefined:**
	
	...
	HandleScope handle_scope;
	Local<Object> obj = Object::New("RegistedGlobal");
	Local<Value> arrays = object->Get(Undefined);
    if(!arrays->IsUndefined()){
    	/*do something*/
    }
	...

JavaScript doesn't provide any way to specify how many elements an object will contain. You can say, for example, `new Array(100)`, but this only works for array objects. V8 can handle arrays with "holes": elements that haven't been defined between those that have. Internally, a special sentinel value is stored in these locations, so you get the `undefined` value when you load such a property.



**Working with Garbage Collection in V8 lib**

Generational collection:

    mark-compact and scavenge
> mark-sweep and compact: major garbage collection cycle.
> 
> scavenge: minor garbage collection cycle.
> 
> Incremental marking and lazy sweeping

Object are located in new-space, which is fairly small and cheap. New-space is triggered, which quickly removes. 