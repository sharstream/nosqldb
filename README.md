# Graphyte 

&copy; 2015 Apex Data Solutions LLC
by David Perez

## Overview

**Getting Node.js with Global and GraphyteDB Apps Development Ready**

> Stages:
> 
> 1. Development
> 
> 2. Test
> 
> 3. Stage
> 
> 4. Production
> 
> 5. Integration

**Writing Graphyte.js Addons** 

The first environment of development to GraphyteDB. This preparation before will then create the C/C++ libraries to create a wrapper dynamically for standard NoSQL Global object.

**Preparation**
 

Before we start writing, install:

    npm install -g node-gyp

On Windows you will need:

> Python (2.7.3, 3.x will not work)
> 
> Microsoft Visual Studio C++ 2010 (for Windows XP/Vista)
> 
> Microsoft Visual Studio C++ 2012 for Windows Desktop (Windows 7/8)

As for the dependencies, on Unix systems you will need:

**The `binding.gyp` File**

    {
	    "targets": [
			{
				"target_name": "graphyteAPI",
				"sources" : ["src/graphyte.cc"]
			}
		]
    }

`"sources"` contains all files that add-on use. In my case, I use two add-on one to call the Global Interface Class and another to stick if there is open or close connection.

**Building**

Running:

    node-gyp configure

This will create the appropriate build configuration and link to the `compilable  unit`.