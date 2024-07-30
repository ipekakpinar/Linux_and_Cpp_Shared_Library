#include <iostream>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){

    //1- shared memorye bağlan 
    const char* shmName = "/my_shm";
    int shmFd = shm_open(shmName, O_RDWR, 0666);
    if(shmFd == -1){
        std::cerr<<"shm_open hatasi"<<std::endl;
        exit(1);
    }

    //2- shared memoryi bellekle eşle
    char* shmPtr = (char*) mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
    if (shmPtr == MAP_FAILED) {
        std::cerr<<"mmap hatasi"<<std::endl;
        exit(1);
    }

    std::ofstream logFile("logfile.txt", std::ios::app);
    if(!logFile.is_open()){
        std::cerr << "dosya acilamadi" << std::endl;
        exit(1);
    }

    //std::memset(shmPtr, 0, 1024);

    while (true) {
    if (strlen(shmPtr) > 0) {
        logFile << shmPtr;
        logFile.flush();
        std::memset(shmPtr, 0, 1024); // Shared memory'yi temizle
    }
    sleep(1);
}


    munmap(shmPtr, 1024);
    close(shmFd);
    shm_unlink(shmName);

    return 0;

}
