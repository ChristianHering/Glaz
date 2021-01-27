#include <ctype.h> //isdigit()
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h> //ptrace

#include "collection.h"
#include "./utils/slice.h"

//isNumerical returns true if the given
//char array only contains characters 0-9.
bool isNumerical(const char *name) {
    while(*name) {
        if(!isdigit(*name)) {
            return false;
        }

        name++;
    }

    return true;
}

int getActivePIDs(struct Slice *pids) {
    struct dirent *entry;
    DIR *dir;

    dir = opendir("/proc");
    if(dir == NULL) {
        perror("Unable to read directory");
        return(-1);
    }

    while(entry = readdir(dir)) {
        if(entry->d_name[0] && isNumerical(entry->d_name)) {
            int pid = atoi(entry->d_name);
            
            int err = append(pids, &pid, sizeof(pid));
            if(err != 0) {
                perror("Failed to append pid to slice");
            }
        }
    }

    closedir(dir);

    return 0;
}

void* collectionMain(void *p) {
    struct Slice activePIDs = {0, 0, (void*)0};
    struct Slice tracedPIDs = {0, 0, (void*)0};
    int err;
    
        err = getActivePIDs(&activePIDs);
        if(err != 0) {
            perror("getActivePIDs returned a non zero return value");
        }

#include <sys/user.h>
//#include <sys/types.h>
#include <sys/wait.h>

        unsigned int pid = 22932;
        
        long l = ptrace(PTRACE_ATTACH, (pid_t)pid, (void*)0, (void*)0);

        /*for(int i = 0; i < activePIDs.used; i++) {
            printf("attaching to %i", *(int*)((char*)activePIDs.values + (i * sizeof(int))));
            long l = ptrace(PTRACE_ATTACH, (pid_t)*(int*)((char*)activePIDs.values + (i * sizeof(int))), (void*)0, (void*)0);

            if(l != 0) {
                printf("Failed.");
                printf("%ld\n", ptrace(PTRACE_DETACH, (pid_t)*((char*)activePIDs.values + (i * sizeof(int))), (void*)0, (void*)0));
            }
        }*/

        printf("%li\n", ptrace(PTRACE_SYSCALL, (pid_t)pid, (void*)0, (void*)0));
        waitpid(pid, 0, 0);

        struct user_regs_struct regs;
        ptrace(PTRACE_GETREGS, pid, 0, &regs);
        long syscall = regs.orig_rax;

        fprintf(stderr, "%ld(%ld, %ld, %ld, %ld, %ld, %ld)\n",
        syscall,
        (long)regs.rdi, (long)regs.rsi, (long)regs.rdx,
        (long)regs.r10, (long)regs.r8,  (long)regs.r9);

        if(syscall == 1) {
            printf("WE GOT A WRITE BOIIIISSSSS --- %ld", syscall);
        }
        
        printf("%li\n", ptrace(PTRACE_SYSCALL, (pid_t)pid, (void*)0, (void*)0));
        waitpid(pid, 0, 0);

        ptrace(PTRACE_GETREGS, pid, 0, &regs);
        fprintf(stderr, " = %ld\n", (long)regs.rax);

    for(;;) {
        //Get all currently running processes

        //Update ptrace'd PID's
        //PTRACE_O_TRACEFORK

        //Get latest syscalls from ptrace

        //Pass syscalls to processing thread

        //Sleep the remainder of 1 second
    }
    return 0;
}
