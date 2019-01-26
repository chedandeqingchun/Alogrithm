#include <stdio.h> 
#include <stdlib.h> 


struct person
{
    int age; 
    int height; 
    int hehe;
};

static struct person *johndoe;

static void 
dump_structure(void* addr, char* structname) {

    extern const char *__progname;
    char outbuf[4096];

    sprintf(outbuf, "echo 'set print pretty on\nset pagination off\np (struct %s)*%p\n' > gdbcmds", structname, addr);
    system(outbuf);

    sprintf(outbuf, "echo 'where\ndetach' | gdb -batch --command=gdbcmds %s %d > struct.dump", __progname, getpid() );
    system(outbuf);

    sprintf(outbuf, "cat struct.dump");
    system(outbuf);

    return;
}

main ()
{

    johndoe = (struct person *)calloc(1, sizeof(struct person));

    johndoe->age = 6; 
    dump_structure(johndoe, "person"); 

    johndoe->age = 8; 
    dump_structure(johndoe, "person"); 

    printf("Hello World - age: %d\n:", johndoe->age);

    free(johndoe);
}
