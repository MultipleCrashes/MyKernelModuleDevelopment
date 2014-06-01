#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> 
 //file_operations structure which allows us to open/close
    // read/write to device
#include <linux/cdev.h> 
   //char driver which makes cdev available
#include <linux/semaphore.h> 
 //used to access semaphore for sunchronization 
#include <asm/uaccess.h> 
// copy to user or from user


// creating a structure for our fake device 

struct fake_device{

 char data[100]; // struct holds data of size 
 struct semaphore sem;  
} virtual_device;

// if we declare too many variables in a function it will start to 
// create problem as the stack in the kernel is very small 

struct cdev *mcdev; // m stands for my 
int major_number; //will store our major number -extracted from dev_t 

//using macro mknod /directory/file c major minor 

int ret;  // will be used to hold return values of function this is because the 
// kernel stack is very small

dev_t dev_num; //will hold major number that kernel gives us

 //name --> appears in /proc/devices

#define DEVICE_NAME "harishDevice"

// step 7 

int device_open(struct inode *inode, struct file *filp){
// abstract open file - struct file 
if(down_interruptiable(&virtual_device.sem)!=0)
 {
 printk(KERN_ALERT " harish device could not lock device during open");
 return -1;
 }
 printk(KERN_INFO " harish Devive :Opened device ");
 return 0;
}

// step 8 called when user wants to get information from the device
ssize_t device_read(struct file* filp,char* bufStoreData,size_t bufCount,loff_t* curOffset){
//take data from kernerl space(devide) to user space (process)
//copy_to_user (destination,source,sizeToTransfer)
printk(KERN_INFO "harishDevice : Reading from device");
ret=copy_to_user(bufStoreData,virtual_device.data,bufCount);
return ret;
}


// step 9 called when user wants to send information to the device

ssize_t device_write(struct file* filp,const char* bufSourceData,size_t bfCount,loff_t* curOffset){
 //send data from user to kernel 
 // copy_from_user(dest,source,count)
 printk(KERN_INFO " harish writing to deive ");
 ret=copy_from_user(virtual_device.dta,bufSourceData,bufCount);
return ret;
}

// step 10 

int device_close(struct inode *indoe,struct file *filp)
{

// parameters are abstract file inode and struct file  
//by calling up, which is opposte of down for semaphore , we release the mutex that we obtained at device open 
// this has the effeect of allowing other process to use the device now 
up(&vitrual_device.sem);
printk(KERN_INFO "harishDevice closed device");
return 0;
 
}
//inode is the actual physical file 
//abstract open file containing

// step 6
 struct file_operations fops={ 
    .owner=THIS_MODULE,  
//prevent unloading of this module when operations are in use
    .open=device_open, //points to the method to call when opend the deive
    .release=device_close, // points to the method to call when closing the device
    .write=device_write, // points to the method to call when writing tto the deive
    .read=device_read // points to the method to call when reading from the deivce



//entry point for device function 


static int driver_entry(void){
//Register out device with the system : a two step process.

ret=alloc_chrdev_region(&dev_num,0,1,DEVICE_NAME);
if(ret<0){
// at time kernel function returns negative,there is an error
printk(KERN_ALERT " harish Deive function return negative, there is an error");
//step 1 use dynamic allocation to assign to our device 
// a major number -- aclloc_chrdev_region(dev_t*,uuint fminor,uint countm,char* name)
return ret;
}
major_number=MAJOR(dev_num);
 //extracts the major number and store in our varibale (MACR0)
printk(KERN_INFO " harishDevice major numnber is %d",major_number);
printk(KERN_INFO "\tuse \"mknod /dev/%s c %d 0\" for device file,DEVICE_NAME,major_number);
//step 2

mcdev=cdev_alloc(); // create our cdev structure ,initialized our cdev
mcdev->ops=&fops;    // struct file_operation
mcdev->owner=THIS_MODULE;

// now that we have created cdev , we have to add it to the kernel
// int cdev_add(struct cdev* dev,dev_t num,unsigned int count)
ret=cdev_add(mcdev,dev_num,1);
if(ret<0) 
{ 
  //always check errors
printk(KERN_ALERT " HarishDevice unable to add cdev to kernel ");
return ret;
}

// Initialize our semaphore 
sema_init(&virtual_device.sem,1);   //initialize value of one 
return 0;



// unregister everything in reverse order

static void driver_exit(void){
 cdev_del(mcdev);
unregister_chrdev_region(dev_num,1);
printk(KERN_ALERT " harish Device : unloaded module");

}


module_init(driver_entry);
module_exit(driver_exit);

}

