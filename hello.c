#include <linux/init.h>        //initialize module 
#include <linux/module.h>      // say that this is a module 

// cleanup of resources also need to be done after initialization 
// linux kernel is in C or assembly lang


// signature of function needs to be int so that the macro can accept
static int hello_init(void){

// you cannot use printf or any C library function so use printk to print to console 
//better to write to the logfile and and use demsg
MODULE_LICENSE("GPL");
printk(KERN_ALERT "EST:Hello World,this is soliduscode \n");

return 0;

}

//deallocate the resources probably after unloading the module 

static void hello_exit(void)
{
printk(KERN_ALERT "TEST:Good bye from the soliduscode");

}



//kernel need to know where to begin execution so we pass a pointer
module_init(hello_init);
module_exit(hello_exit);

// after that build this going to a module for that 
//make a makefile


