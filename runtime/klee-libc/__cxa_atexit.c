/*===-- __cxa_atexit.c ----------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===*/

//#include "klee/klee.h"
//#include <stdio.h>
#define MAX_ATEXIT 128

static struct {
  void (*fn)(void*);
  void *arg;
  void *dso_handle;
} AtExit[MAX_ATEXIT];
static unsigned NumAtExit = 0;

__attribute__((destructor))
static void RunAtExit(void)  {
  unsigned i;
  for (i = NumAtExit - 1; i < MAX_ATEXIT; --i)
    AtExit[i].fn(AtExit[i].arg);
}

 int __cxa_atexit(void (*fn)(void*),
                 void *arg,
                 void *dso_handle) {

  AtExit[NumAtExit].fn = fn;
  AtExit[NumAtExit].arg = arg;
  ++NumAtExit;
  
  return 0;
}

int __cxa_thread_atexit(void (*fn)(void*), void *arg, void *dso_handle) {
  return __cxa_atexit(fn, arg, dso_handle);
}
