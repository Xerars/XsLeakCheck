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
#include <stdio.h>
#include <stdlib.h>

//Macro Declare
#define EXECUTE_NONE     0  //Execute None
#define EXECUTE_ONCE     1  //Execute Once

//Struct Declare
typedef struct _MEMNODE
{
  void* Addr;               //Memory Leaked Address
  size_t Block;             //Memory Leaked Block
  size_t Line;              //Memory Leaked Line
  char* FileName;           //Memory Leaked File Name
  const char* FuncName;     //Memory Leaked Function Name
  struct _MEMNODE *next;    //Pointer to Next Memory Node
} MEMNODE;

//Private Variable Declare
MEMNODE* Head=NULL;
static int XmExecuteOnce=EXECUTE_NONE;

//Prototype Declare
static void MEMNodeAdd(void* Addr,size_t Block,size_t Line,char* FileName,const char* FuncName);
static void MEMNodeRemove(void *Addr);

//Function:MEMNodeAdd
//Descript:Memory Node Add
static void MEMNodeAdd(void* Addr,size_t Block,size_t Line,char* FileName,const char* FuncName)
{
  //Create New Node
  MEMNODE *Node = (MEMNODE*)malloc(sizeof(MEMNODE));

  Node->Addr  = Addr;         //Set Address
  Node->Block = Block;        //Set Block
  Node->Line  = Line;         //Set Line
  Node->FileName = FileName;  //Set File Name
  Node->FuncName = FuncName;  //Set Function Name
  Node->next = NULL;

  //Add Node to Linked List
  if(Head)  //First Node
  {
    Node->next = Head;
    Head = Node;
  }
  else      //Other Node
    Head = Node;
}


//Function:MEMNodeRemove
//Descript:Memory Node Remove
static void MEMNodeRemove(void *Addr)
{
  //Check Head Node is Exist
  if(Head)
  {
    if(Head->Addr==Addr)    //Head Node
    {
      //Delete Head Node
      MEMNODE* pn = Head->next;
      free(Head);
      Head=pn;
    }
    else  //Check Linked Table is Null
    {
      MEMNODE* pn = Head->next;
      MEMNODE* pc = Head;

      //Traverse all Node
      while(pn)
      {
        MEMNODE* pnext=pn->next;
        if(pn->Addr==Addr)
        {
          pc->next = pnext;
          free(pn);
        }
        else
          pc=pc->next;
        pn=pnext;
      }
    }
  }
}


//Function:XsLeakMemoryInfo
//Descript:Show Leak Memory Information
int XsLeakMemoryInfo(void)
{
  size_t total=0;

  if(XmExecuteOnce==0)
  {
    if(Head)
    {
      MEMNODE* pn=Head;
      int Count=0;
      //Output Title
      puts("\n------------------------- Memory Leak Report -------------------------\n");
      //Traverse all Node
      while(pn)
      {
        Count++;
        //Output Leaked Memory Information
        printf("%02d.[%s\t]:(%s\t) <Line:%4d>:Addr:%p (%d byte)\n",
                Count,pn->FileName,pn->FuncName,pn->Line,pn->Addr,pn->Block);

        total+=pn->Block;
        if(pn!=NULL)  //Check Link List Node is Not NULL
          free(pn);   //Destroy Linked List Node
        pn=pn->next;
      }
      printf("\n@ Total Leak Memory:%d byte\n",total);
      //Output End of Line
      puts("\n--------------------- End of Memory Lake Report ----------------------\n");
      XmExecuteOnce=EXECUTE_ONCE;
    }
  }
  else
    printf("@ XsLeakMemoryInfo can Only be Execute Once!");
  return total;
}


//Function:XsMalloc
//Descript:The Malloc Function with Memory Laked Checking
void* XsMalloc(size_t Size,char* FileName,const char* FuncName,size_t Line)
{
  void* Addr = malloc(Size);
  MEMNodeAdd(Addr,Size,Line,FileName,FuncName);
  return Addr;
}


//Function:XsCalloc
//Descript:The Calloc Function with Memory Laked Checking
void* XsCalloc(size_t Count,size_t Size,char* FileName,const char* FuncName,size_t Line)
{
  void* Addr = calloc(Count,Size);
  MEMNodeAdd(Addr,Size*Count,Line,FileName,FuncName);
  return Addr;
}


//Function:XsRealloc
//Descript:The Realloc Function with Memory Laked Checking
void* XsRealloc(void* Addr,size_t Size,char* FileName,const char* FuncName,size_t Line)
{
  void* TempAddr=Addr;
  Addr = (void*)realloc(Addr,Size);

  MEMNODE* pn = Head->next;
  //Traverse all Node
  while(pn)
  {
    if(pn->Addr==TempAddr)
    {
      pn->Addr = Addr;          //Set Address
      pn->Block = Size;         //Set Size
      pn->FileName = FileName;  //Set File Name
      pn->FuncName = FuncName;  //Set Function Name
      pn->Line = Line;          //Set Line
      break;
    }
    pn = pn->next;
  }
  return Addr;
}


//Function:XsFree
//Descript:The Free Function with Memory Leaked Checking
void XsFree(void *Addr)
{
  free(Addr);
  MEMNodeRemove(Addr);
}