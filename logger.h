#ifndef LOGGER_h
#define LOGGER_H

#include <string>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

class Logger{

    public:

        enum class LogLevel {INFO, WARN, ERROR};

        Logger(const std::string& shmName); //constructor
        ~Logger(); //destructor

        void info(const std::string& message);
        void warn(const std::string& message);
        void error(const std::string& message);

    private:

        void writeToSharedMemory(const std::string& message, LogLevel level);
        int shmFd;
        char* shmPtr;

};


#endif
