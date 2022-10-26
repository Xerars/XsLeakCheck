# XsLeakCheck

## About

XsLeakCheck is a Lightweight Memory Leak Detection Library Written in C Language.

Xs Represents a `Simple` Library Made by William `XIAO`.

## Feature

* LightWeight(Only 2 Files)

* Simple API

* C99 Compatible

* The Code about 200 Line

## Install

* make all
  
  * Execute all of the Following Function.

* make Sample
  
  * Compiler Sample Code.

* make Slib
  
  * Generate Static Library

* make Dlib
  
  * Generate Dynamic Library

* make run-coverage
  
  * Run Code Coverage

* make clean
  
  * Clear all Generate File

## Usage

The XsLeakCheck Library has Only Five Functions and Macro Function.

### Malloc

Malloc is Based on the xsMalloc Function to Manage Memory.

```c
malloc(10);      //Configuration Memory Block
```

### Calloc

Calloc is Based on the xsCalloc Function to Manage Memory.

```c
calloc(10,10);    //Configuration Memory are Initialzed is 0
```

### Realloc

Realloc is Based on the xsRealloc Function to Manage Memory.

```c
realloc(ptr,20);  //Reconfigure Memory Blocks
```

### Free

Free is Based on the xsFree Function to Free Memory Block.

```c
free(ptr);        //Free Memory Block
```

### XsLeakMemoryInfo

The Original Design was `NO` Return Value,But I Modify  Return the Number of Memory Leaks to Easy do Unit Test.

```c
//Output Memory Leak Information
int Leak = XsLeakMemoryInfo();
```

## Example

This Sample Fully Illustrates the Complete Usage of the XsLeakCheck Library.

```c
#ifdef LEAKCHECK
  #include "XsLeakCheck.h"
#endif

#include <string.h>

void ShowLeakMemoryInfo(void);

int main(void)
{
#ifdef LEAKCHECK
  atexit(ShowLeakMemoryInfo);
#endif    //LEAKCHECK

  int* ptr1=malloc(1000*sizeof(int));
  int* ptr2=calloc(1000,sizeof(int));

  memset(ptr1,0,1000*sizeof(int));
  memset(ptr2,0,1000*sizeof(int));

  ptr1=realloc(ptr1,2000*sizeof(int));
  memset(ptr1,0,2000*sizeof(int));

  return 0;
}

//Function:ShowLeakMemoryInfo
//Descript:Show Leak Memory Information
void ShowLeakMemoryInfo(void)
{
  XsLeakMemoryInfo();
}
```

## License



[The MIT License (MIT)](http://opensource.org/licenses/mit-license.php)
