#include <linux/init.h>        //initialize module 
#include <linux/module.h>      // say that this is a module 

//step 1 to start adding parameter to module include moduleparam.h as below
#include <linux/moduleparam.h>

//step 2below declaring the variable that will hold the value passed to the module

int param_val=0;

/*  -----------------------------------------------
step 3 register the variable created 
 register (macro)

name of variable,type of variable and permissions for the variable 
permissions can be anyone of the following 
 S_IRUSR..etc mentioned below
 

//module_param(name_var,type,permissions)

 S_IRUSR        R stands for read , w for write and usr for user ,grp stands for   group 
 S_IWUSR
 S_IXUSR
 S_IWGRP
 S_IRGRP
   
 S_IRUSR | S_IWUSR

     ------------------------------------------------------
 
*/

module_parameter(param_var,int, S_IRUSR | S_IWUSR)


// cleanup of resources also need to be done after initialization 
// linux kernel is in C or assembly lang


// signature of function needs to be int so that the macro can accept
static int hello_init(void){

// you cannot use printf or any C library function so use printk to print to console 
//better to write to the logfile and and use demsg
MODULE_LICENSE("GPL");
printk(KERN_ALERT "EST:Hello World,this is soliduscode \n");
display();
return 0;

}


void display(){
   printk(KERN_ALERT "Test : %d ",param_var;
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


