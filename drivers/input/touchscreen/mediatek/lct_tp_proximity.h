/****************************************************************************************
 *
 * @File Name   : lct_tp_common.h
 * @Author      : sunjiajia
 * @E-mail      : <sunjiajia@longcheer.com>
 * @Create Time : 2023-07-31 16:19:02
 * @Description : Add touchpad proximity switch.
 *
 ****************************************************************************************/

#ifndef __LCT_TP_PROXIMITY_H__
#define __LCT_TP_PROXIMITY_H__

/*****************************************************************************
* Included header files
*****************************************************************************/

/*****************************************************************************
* Macro definitions using #define
*****************************************************************************/

/*****************************************************************************
* enumerations, structures and unions
*****************************************************************************/
typedef int (*tp_proximity_cb_t)(bool enable_tp);

/*****************************************************************************
* Global variable or extern global variabls/functions
*****************************************************************************/
extern int init_lct_tp_proximity(tp_proximity_cb_t callback);
extern void uninit_lct_tp_proximity(void);
extern void set_lct_tp_proximity_status(bool en);
extern bool get_lct_tp_proximity_status(void);

#endif //__LCT_TP_GESTURE_H__

