#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slice.h"

//resize resizes slices that need to grow, or that should be shrunk
//
//Slices that are at max capacity are expanded.
//Slices that are less than half full are shrunk.
int resize(struct Slice *slice, unsigned int valueSize) {
    if(slice->used == slice->allocated) {
        if(!slice->allocated) { //Initial allocation
            slice->values = malloc(valueSize);
            if(slice->values == NULL) {
                perror("Unable to get a memory allocation for our slice");

                return 101;
            }

            slice->allocated = 1;
        } else { //Subsequent allocations
            slice->values = realloc(slice->values, slice->allocated * valueSize * 2);
            if(slice->values == NULL) {
                perror("Unable to get a memory reallocation for our slice");

                return 102;
            }
            
            slice->allocated = slice->allocated * 2;
        }
    } else if(slice->used < (slice->allocated / 2)) {
        slice->values = realloc(slice->values, (slice->allocated / 2) * valueSize);
        if(slice->values == NULL) {
            perror("Unable to get a memory reallocation for our slice");

            return 103;
        }
    }

    return 0;
}

//append adds "value" to "slice". Array memory
//reallocations are handled automatically, if needed
int append(struct Slice *slice, void* value, unsigned int valueSize) {
    resize(slice, valueSize); //Call "resize" to prevent segfaults

    (void)memcpy((void*)((char*)(slice->values) + (valueSize * slice->used)), value, valueSize);

    slice->used++;

    return 0;
}

//delete removes the first instance of "value" from "slice"
int delete(struct Slice *slice, void* value, unsigned int valueSize) {
    for(int index = 0; index < slice->used; index++) {
        int err = memcmp((void*)((char*)(slice->values) + (valueSize * index)), value, valueSize);
        if(err == 0) {
            if(valueSize * (slice->used - (index + 1)) != 0) { //There are no elements to copy if we're deleting the last element
                (void)memcpy((void*)((char*)(slice->values) + (valueSize * index)),
                    (void*)((char*)(slice->values) + (valueSize * (index + 1))),
                    valueSize * (slice->used - (index + 1))); //Copy all elements after "index" to "slice"
            }

            slice->used--;

            return resize(slice, valueSize);
        }
    }

    perror("Couldn't find value in slice");

    return 104;
}

//pop "pops" the last x values off the end of "slice"
int pop(struct Slice *slice, unsigned int valueCount, unsigned int valueSize) {
    slice->used = slice->used - valueCount;

    return resize(slice, valueSize);
}
