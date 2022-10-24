/*
 SPDX-License-Identifier: MIT
 
 XsLealCheck 1.0.0
 Copyright (c) 2012 - 2022 William Xiao
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/
#ifndef __XSLEAKCHECK_H__   //__XMLEAKCHECK_H__
#define __XSLEAKCHECK_H__   //__XMLEAKCHECK_H__

#include <stdlib.h>

//Macro Declare
#define XSFILE   __FILE__     //File Name
#define XSLINE   __LINE__     //Line
#define XSFUNC  __FUNCTION__  //Function

#undef malloc                 //Undefine Malloc
#undef calloc                 //Undefine Calloc
#undef realloc                //Undefine Realloc
#undef free                   //Undefine Free

//Prototype Declare
void* XsMalloc(size_t Size,char* FileName,const char* FuncName,size_t Line);
void* XsCalloc(size_t Count,size_t Size,char* FileName,const char* FuncName,size_t Line);
void* XsRealloc(void* Addr,size_t Size,char* FileName,const char* FuncName,size_t Line);
void XsFree(void *Addr);
int XsLeakMemoryInfo(void);

//Macro Function Declare
#define malloc(s)           XsMalloc(s,XSFILE,XSFUNC,XSLINE)
#define calloc(c,s)         XsCalloc(c,s,XSFILE,XSFUNC,XSLINE)
#define realloc(p,s)        XsRealloc(p,s,XSFILE,XSFUNC,XSLINE)
#define free(p)             XsFree(p)

#endif    //__XMLEAKCHECK_H__