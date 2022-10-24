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