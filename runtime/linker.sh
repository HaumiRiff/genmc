#cmake CMakeLists.txt
#make
cd ../tests/correct/infr/thread_local
clang -c -emit-llvm  -I ../../../include destructor_order.cpp



cd ../../../../runtime/klee-libc
 llvm-link atexit64_Release.bc calloc64_Release.bc __cxa_atexit64_Release.bc dso_handle64_Release.bc ../../tests/correct/infr/thread_local/destructor_order.bc -o a.bc
../../src/genmc --input-from-bitcode-file a.bc
