#ifndef UDEVHELPERL_H
#define UDEVHELPERL_H

#define AR_DEV_MAX_NUM        256

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ar_dev_t{
    char* hid_devnode;
    char* uvc_devnode;
    char* usb_syspath;
    char* usb_devpath;
    char* usb_devnode;
}ar_dev_t;

typedef struct ar_dev_list_t{
    int length;
    ar_dev_t devlist[256];
}ar_dev_list_t;

ar_dev_list_t* get_refresh_dev_list();
ar_dev_list_t* get_current_dev_list();

#ifdef __cplusplus
}
#endif

#endif // UDEVHELPERL_H
