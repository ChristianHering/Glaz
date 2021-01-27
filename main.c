#include <pthread.h>

#include "collection.h"
#include "networking.h"
#include "processing.h"

#include "./utils/slice.h"

int main() {
    pthread_t collectionThread;
    pthread_t processingThread;

    pthread_create(&collectionThread, NULL, collectionMain, NULL);
    pthread_create(&processingThread, NULL, processingMain, NULL);

    return networkingMain();
}

/*
    int index;

    getActivePIDs(&my_pids);

    for (index = 0; index < my_pids.used; index++) {
       //printf("%i\n", *(int*)((char*)(my_pids.values) + (sizeof(int) * index)));
    }

    int dd = my_pids.used;

    for (index = 0; index < (dd - 1); index++) {
       delete(&my_pids, my_pids.values, sizeof(int));
       //printf("Deleted %i\n", *(int*)(my_pids.values));
    }

    pop(&my_pids, 1, sizeof(int));
*/

//readlink and /proc/pid/exe for getting executables
