#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv) {
    if(argc<3) {
        printf("usage: %s <library> <number>\n", argv[0]);
        exit(1);
    }
    char *librarypath = argv[1];
    int thenumber = atoi(argv[2]);

    void *libhandle = dlopen(librarypath, RTLD_LAZY);
    if(libhandle == NULL) {
        perror("Could not get library.\n");
    }
    // at this point, libhandle has an address to a function
    // I wonder if it can do malicious things to our program?

    int (*opfunc) (int);
    opfunc = dlsym(libhandle, "do_operation");
    
    char* (*libnamefunc) ();
    libnamefunc = dlsym(libhandle, "get_library_name");

    if(opfunc == NULL || libnamefunc == NULL) {
        printf("ERROR: Could not read functions from library");
        exit(1);
    }


    printf("Library: %s\n", libnamefunc());
    printf("%d => %d\n", thenumber, opfunc(thenumber));

    dlclose(libhandle);
    libhandle = NULL;
    return 0;
}