g++ ../Emulator/intel8080.cpp -o myi8080.o -c
gcc ../TestEmulator/i8080.c -o testi8080.o -c
g++ myi8080.o testi8080.o EmulatorComparison.cpp -o EmulatorComparison.exe
EmulatorComparison.exe