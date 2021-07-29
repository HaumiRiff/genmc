clang -c -emit-llvm -I ../../../../include global_var.cpp

cd ../../../../runtime
cmake CMakeLists.txt
make

cd klee-libc

llvm-link atexit64_Release.bc calloc64_Release.bc __cxa_atexit64_Release.bc dso_handle64_Release.bc ../../tests/wrong/infr/cthread_thread_local/global_var.bc -o global_var_f.bc

../../src/genmc --input-from-bitcode-file global_var_f.bc
