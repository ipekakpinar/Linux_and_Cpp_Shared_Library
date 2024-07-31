#include "logger.h"
#include <cstring>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <mutex>

Logger::Logger(const std::string &shmName)
{

    // 1: SHARED MEMORY OLUŞTUR
    shmFd = shm_open(shmName.c_str(), O_CREAT | O_RDWR, 0666);
    if (shmFd == -1)
    {
        std::cerr << "shm_open hata" << std::endl;
        exit(1);
    }

    // 2. SHARED MEMORY BOYUTUNU AYARLA
    if (ftruncate(shmFd, 1024) == -1)
    {
        std::cerr << "ftruncate hata" << std::endl;
        exit(1);
    }

    // 3. SHARED MEMORYİ BELLEKLE EŞLEŞTİRME
    shmPtr = (char*) mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
    if(shmPtr == MAP_FAILED){
        std::cerr << "shared memory belleğe eşleştirilemedi" << std::endl;
        close(shmFd);
        exit(1);
    }

    std::memset(shmPtr, 0, 1024); //boş bellekle başlamak için

}

Logger::~Logger() {
    munmap(shmPtr, 1024);
    close(shmFd);
}


std::mutex logmutex;

void Logger::writeToSharedMemory(const std::string& message, LogLevel level) {

    std::lockguard<std::mutex> lock(logmutex);
    
    std::string levelStr;
    switch (level) {
        case LogLevel::INFO: levelStr = "INFO"; break;
        case LogLevel::WARN: levelStr = "WARN"; break;
        case LogLevel::ERROR: levelStr = "ERROR"; break;
    }
    std::string logEntry = levelStr + ": " + message + "\n";
    std::string oldContent(shmPtr);
    if (oldContent.length() + logEntry.length() < 1024) {
        strcat(shmPtr, logEntry.c_str());
    } else {
        std::cerr << "Mesaj çok uzun!" << std::endl;
    }
}


void Logger::info(const std::string& message) {
    writeToSharedMemory(message, LogLevel::INFO);
}

void Logger::warn(const std::string& message) {
    writeToSharedMemory(message, LogLevel::WARN);
}

void Logger::error(const std::string& message) {
    writeToSharedMemory(message, LogLevel::ERROR);
}

