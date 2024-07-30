#include "logger.h"

int main(){
    Logger log("/my_shm"); //Logger nesnesi
    log.info("program başlatıldı");
    log.warn("Uyarı!");
    log.error("Hata oluştu");

    return 0;
}
