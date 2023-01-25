//
// m_qsort.cpp
//

#include <base.h>
#include <streams.h>
#include <stdlib.h>
#include "talgorithm.h"
#include "m_qsort.h"

namespace {

bool initialized = false;
CRITICAL_SECTION criticalSection;

}; // namespace {}

void __cdecl m_qsort(void *base, size_t nelem, size_t width, 
   int (_USERENTRY *fcmp)(const void *, const void *))
{
	AssertFatal( base || nelem == 0,"m_qsort: Sorting null vector");
   if (!initialized) {
      InitializeCriticalSection(&criticalSection);
      initialized = true;      
   }
	if (nelem) {
	   EnterCriticalSection(&criticalSection);
	   qsort(base, nelem, width, fcmp);      
	   LeaveCriticalSection(&criticalSection);
	}
}


