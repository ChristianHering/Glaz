#ifndef SLICE_H_INCLUDED
#define SLICE_H_INCLUDED
    struct Slice {
        unsigned int allocated; //Number of bytes allocated for "values"
        unsigned int used; //Number of "void" instances in "values"

        void* values; //Pointer to the data in our slice
    };
    
    int resize(struct Slice *slice, unsigned int valueSize);
    int append(struct Slice *slice, void* value, unsigned int valueSize);
    int delete(struct Slice *slice, void* value, unsigned int valueSize);
    int pop(struct Slice *slice, unsigned int valueCount, unsigned int valueSize);
#endif
