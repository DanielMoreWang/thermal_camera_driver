#include "udevhelper.h"
#include </usr/include/libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>

#define MY_VID 0x1d6b
#define MY_PID 0x0102

//#define MY_VID 0x0e0f
//#define MY_PID 0x0003

ar_dev_list_t dev_list;

void clear_dev_list(){
    dev_list.length = 0;
    int i;
    for(i=0;i<AR_DEV_MAX_NUM;i++){
        if(dev_list.devlist[i].hid_devnode){
            free(dev_list.devlist[i].hid_devnode);
            dev_list.devlist[i].hid_devnode = NULL;
        }
        if(dev_list.devlist[i].uvc_devnode){
            free(dev_list.devlist[i].uvc_devnode);
            dev_list.devlist[i].uvc_devnode = NULL;
        }
        if(dev_list.devlist[i].usb_syspath){
            free(dev_list.devlist[i].usb_syspath);
            dev_list.devlist[i].usb_syspath = NULL;
        }
        if(dev_list.devlist[i].usb_devpath){
            free(dev_list.devlist[i].usb_devpath);
            dev_list.devlist[i].usb_devpath = NULL;
        }
        if(dev_list.devlist[i].usb_devnode){
            free(dev_list.devlist[i].usb_devnode);
            dev_list.devlist[i].usb_devnode = NULL;
        }
    }
}

void get_arhid_dev_list(){
    
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;
    //struct udev_device *devusb;

    int i;
    
    /* Create the udev object */
    udev = udev_new();
    if (!udev) {
        printf("Can't create udev\n");
        exit(1);
    }
    
    /* Create a list of the devices in the 'hidraw' subsystem. */
    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "hidraw");
    udev_enumerate_add_match_subsystem(enumerate, "video4linux");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);
    /* For each item enumerated, print out its information.
           udev_list_entry_foreach is a macro which expands to
           a loop. The loop will be executed for each member in
           devices, setting dev_list_entry to a list entry
           which contains the device's path in /sys. */
    printf("**************begin detect artosyn usb device**************\n");
    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path;
        const char* dev_node;
        const char* dev_subsys;
        
        /* Get the filename of the /sys entry for the device
               and create a udev_device object (dev) representing it */
        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);
        
        /* usb_device_get_devnode() returns the path to the device node
               itself in /dev. */
        dev_node = udev_device_get_devnode(dev);
        dev_subsys = udev_device_get_subsystem(dev);
        printf("find %s device: %s\n",dev_subsys, dev_node);
        
        /* The device pointed to by dev contains information about
               the hidraw device. In order to get information about the
               USB device, get the parent device with the
               subsystem/devtype pair of "usb"/"usb_device". This will
               be several levels up the tree, but the function will find
               it.*/
        dev = udev_device_get_parent_with_subsystem_devtype(
                    dev,
                    "usb",
                    "usb_device");
        if (!dev) {
            printf("Unable to find parent usb device.");
            udev_device_unref(dev);
            continue;
        }
        
        /* From here, we can call get_sysattr_value() for each file
               in the device's /sys entry. The strings passed into these
               functions (idProduct, idVendor, serial, etc.) correspond
               directly to the files in the directory which represents
               the USB device. Note that USB strings are Unicode, UCS2
               encoded, but the strings returned from
               udev_device_get_sysattr_value() are UTF-8 encoded. */
        printf("\tVID/PID:\t%s %s\n",
               udev_device_get_sysattr_value(dev,"idVendor"),
               udev_device_get_sysattr_value(dev, "idProduct"));
        printf("\tmanuf:\t%s\n\tproduct:\t%s\n",
               udev_device_get_sysattr_value(dev,"manufacturer"),
               udev_device_get_sysattr_value(dev,"product"));
        printf("\tserial:\t%s\n",
               udev_device_get_sysattr_value(dev, "serial"));
        printf("\tdevnodt:\t%s\n",udev_device_get_devnode(dev));
//        printf("  devpath: %s\n",udev_device_get_devpath(dev));
//        printf("  subsystem: %s\n",udev_device_get_subsystem(dev));
//        printf("  devtype: %s\n",udev_device_get_devtype(dev));
//        printf("  syspath: %s\n",udev_device_get_syspath(dev));
//        printf("  sysname: %s\n",udev_device_get_sysname(dev));
//        printf("  sysnum: %s\n",udev_device_get_sysnum(dev));

        int iVid=(int)strtol(udev_device_get_sysattr_value(dev,"idVendor"), NULL, 16);
        int iPid=(int)strtol(udev_device_get_sysattr_value(dev,"idProduct"), NULL, 16);

        if(iVid==MY_VID&&iPid==MY_PID){
            u_int8_t bfind = 0,bfindindex = -1;
            for(i=0;i<dev_list.length;i++){
                if(strcmp(dev_list.devlist[i].usb_devnode,udev_device_get_devnode(dev))==0){
                    bfind = 1;
                    bfindindex = i;
                    break;
                }
            }
            if(bfind){
                if(strcmp("hidraw",dev_subsys)==0){
                    dev_list.devlist[bfindindex].hid_devnode = strdup(dev_node);
                }
                else{
                    dev_list.devlist[bfindindex].uvc_devnode = strdup(dev_node);
                }
            }
            else{
                dev_list.devlist[dev_list.length].usb_devnode = strdup(udev_device_get_devnode(dev));
                if(strcmp("hidraw",dev_subsys)==0){
                    dev_list.devlist[dev_list.length].hid_devnode = strdup(dev_node);
                }
                else{
                    dev_list.devlist[dev_list.length].uvc_devnode = strdup(dev_node);
                }
                dev_list.length++;
            }
        }

        udev_device_unref(dev);

    }
    printf("**************end detect artosyn usb device**************\n");
    /* Free the enumerator object */
    udev_enumerate_unref(enumerate);
    
    udev_unref(udev);
}

ar_dev_list_t *get_refresh_dev_list()
{
    clear_dev_list();
    get_arhid_dev_list();
    return &dev_list;
}

ar_dev_list_t *get_current_dev_list()
{
    return &dev_list;
}
