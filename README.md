# Linux_and_Cpp_Shared_Library
Shared library example.

logger.h: Contains function descriptors.
logger.cpp: Writes logs to shared memory.
log_to_file.cpp: Reads from the shared memory and writes to file.
main.cpp: main.


How to Compile?

Terminal codes are below here:

g++ -fPIC -c logger.cpp -o logger.o

g++ -shared -o liblogger.so logger.o -lrt

g++ -o main main.cpp -L. -llogger -lrt

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

./logger

./main






If you dont want to export library path everytime:

g++ -fPIC -c logger.cpp -o logger.o

g++ -shared -o liblogger.so logger.o -lrt

g++ -o main main.cpp -L. -llogger -lrt

sudo sh -c 'echo "/path/to/your/library" > /etc/ld.so.conf.d/my_library.conf'

sudo ldconfig

./logger

./main

