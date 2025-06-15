/****************************************************************************************
 *
 * @File Name   : lct_tp_common.h
 * @Author      : sunjiajia
 * @E-mail      : <sunjiajia@longcheer.com>
 * @Create Time : 2023-06-06 14:10:32
 * @Description : touchpad common information.
 *
 ****************************************************************************************/

#ifndef __LCT_TP_COMMON_H__
#define __LCT_TP_COMMON_H__

/*****************************************************************************
* Included header files
*****************************************************************************/
#include <linux/uaccess.h>

#include "lct_tp_info.h"
#include "lct_tp_work.h"
#include "lct_tp_selftest.h"
#include "lct_tp_grip_area.h"
#include "lct_tp_gesture.h"
#include "lct_tp_proximity.h"

/*****************************************************************************
* Macro definitions using #define
*****************************************************************************/
#define LCT_TP_COMMON

#define LCT_TP_DATA_DUMP_EN                     1
#define LCT_TP_DATA_DUMP                        "tp_data_dump"

#define LCT_TP_INFO_EN                          1
#define LCT_TP_WORK_EN                          1
#define LCT_TP_SELFTEST_EN                      1
#define LCT_TP_GRIP_AREA_EN                     1
#define LCT_TP_GESTURE_EN                       0
#define LCT_TP_PALM_EN                          0
#define LCT_TP_USB_PLUGIN                       1
#define LCT_TP_PROXIMITY_EN                     1

/*****************************************************************************
* enumerations, structures and unions
*****************************************************************************/
typedef struct lct_tp_mifunc {
    char *tp_info_buff;
    char *tp_lockdown_info_buff;
    int (*tp_info_cb)(const char *);
    int (*tp_work_cb)(bool enable_tp);
    int (*tp_selftest_cb)(unsigned char cmd);
    int (*get_screen_angle_cb)(void);
    int (*set_screen_angle_cb)(int angle);
    int (*tp_gesture_cb)(bool enable_tp);
    int (*tp_palm_cb)(bool enable_tp);
    int (*tp_proximity_cb)(bool enable_tp);
}lct_tp_mifunc_t;

#if LCT_TP_USB_PLUGIN
typedef struct touchscreen_usb_plugin_data {
	bool valid;
	bool usb_plugged_in;
	void (*event_callback)(void);
} touchscreen_usb_plugin_data_t;
#endif

/*****************************************************************************
* Global variable or extern global variabls/functions
*****************************************************************************/
extern char tp_lockdowninfo[24];

extern int lct_tp_create_procfs(lct_tp_mifunc_t *tp_mifunc);
extern void lct_remove_procfs(void);

#if LCT_TP_USB_PLUGIN
extern touchscreen_usb_plugin_data_t g_touchscreen_usb_pulgin;
#endif

#endif //__LCT_TP_COMMON_H__
