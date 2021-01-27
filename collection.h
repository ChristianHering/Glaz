#ifndef COLLECTION_H_INCLUDED
#define COLLECTION_H_INCLUDED
    #include <stdbool.h> //bools

    #include "./utils/slice.h"

    bool isNumerical(const char *name);
    int getActivePIDs(struct Slice *pids);
    void* collectionMain(void *p);
#endif
