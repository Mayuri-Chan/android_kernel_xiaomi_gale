/****************************************************************************************
 *
 * @File Name   : lct_tp_common.c
 * @Author      : sunjiajia
 * @E-mail      : <sunjiajia@longcheer.com>
 * @Create Time : 2023-06-07 15:58:58
 * @Description : touchpad common information.
 *
 ****************************************************************************************/

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "lct_tp_common.h"

/*
 * DEFINE CONFIGURATION
 ****************************************************************************************
 */
#define TP_COMMON_LOG_ENABLE
#define TP_COMMON_TAG           "LCT_TP_COMMON"

#ifdef TP_COMMON_LOG_ENABLE
#define TP_LOGI(log, ...) printk(KERN_INFO "[%s] %s (line %d): " log, TP_COMMON_TAG, __func__, __LINE__, ##__VA_ARGS__)
#define TP_LOGW(log, ...) printk(KERN_WARNING "[%s] %s WARNING(line %d): " log, TP_COMMON_TAG, __func__, __LINE__, ##__VA_ARGS__)
#define TP_LOGE(log, ...) printk(KERN_ERR "[%s] %s ERROR (line %d): " log, TP_COMMON_TAG, __func__, __LINE__, ##__VA_ARGS__)
#else
#define TP_LOGI(log, ...) {}
#define TP_LOGW(log, ...) {}
#define TP_LOGE(log, ...) {}
#endif

/*
 * DATA STRUCTURES
 ****************************************************************************************
 */


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
char tp_lockdowninfo[24] = {0};

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */
int lct_tp_create_procfs(lct_tp_mifunc_t *tp_mifunc)
{
    int ret = 0;

    if(NULL==tp_mifunc)
    {
        TP_LOGE("tp_mifunc is null!!\n");
    }

#if LCT_TP_INFO_EN
    ret = init_lct_tp_info(tp_mifunc->tp_info_buff, tp_mifunc->tp_lockdown_info_buff);
    if(ret) {
        TP_LOGE("create /proc/tp_info & /proc/tp_lockdown_info fail\n");
        goto err_init_lct_tp_info_fail;
    }else {
        set_lct_tp_info_callback(tp_mifunc->tp_info_cb);
        TP_LOGI("create /proc/tp_info & /proc/tp_lockdown_info succeeded\n");
    }
#endif

#if LCT_TP_WORK_EN
    ret = init_lct_tp_work(tp_mifunc->tp_work_cb);
    if (ret < 0) {
        TP_LOGE("init_lct_tp_work Failed!\n");
        goto err_init_lct_tp_work_fail;
    } else {
        TP_LOGI("init_lct_tp_work Succeeded!\n");
    }
#endif

#if LCT_TP_SELFTEST_EN
    ret = init_lct_tp_selftest(tp_mifunc->tp_selftest_cb);
    if (ret < 0) {
        TP_LOGE("init_lct_tp_selftest Failed!\n");
        goto err_init_lct_tp_selftest_fail;
    } else {
        TP_LOGI("init_lct_tp_selftest Succeeded!\n");
    }
#endif

#if LCT_TP_GRIP_AREA_EN
    ret = init_lct_tp_grip_area(tp_mifunc->set_screen_angle_cb, tp_mifunc->get_screen_angle_cb);
    if (ret < 0) {
        TP_LOGE("init_lct_tp_grip_area Failed!\n");
        goto err_init_lct_tp_grip_area_fail;
    } else {
        TP_LOGI("init_lct_tp_grip_area Succeeded!\n");
    }
#endif

#if LCT_TP_GESTURE_EN
    ret = init_lct_tp_gesture(tp_mifunc->tp_gesture_cb);
    if (ret < 0) {
        TP_LOGE("init_lct_tp_gesture Failed!\n");
        goto err_init_lct_tp_gesture_fail;
    } else {
        TP_LOGI("init_lct_tp_gesture Succeeded!\n");
    }
#endif

#if LCT_TP_PALM_EN
    ret = init_lct_tp_palm(tp_mifunc->tp_palm_cb);
    if (ret < 0) {
        TP_LOGE("init_lct_tp_palm Failed!\n");
        goto err_init_lct_tp_palm_fail;
    } else {
        TP_LOGI("init_lct_tp_palm Succeeded!\n");
    }
#endif

#if LCT_TP_PROXIMITY_EN
    ret = init_lct_tp_proximity(tp_mifunc->tp_proximity_cb);
    if (ret < 0) {
        TP_LOGE("init_lct_tp_proximity Failed!\n");
        goto err_init_lct_tp_proximity_fail;
    } else {
        TP_LOGI("init_lct_tp_proximity Succeeded!\n");
    }
#endif

    return ret;

#if LCT_TP_PROXIMITY_EN
err_init_lct_tp_proximity_fail:
    uninit_lct_tp_proximity();
#endif

#if LCT_TP_PALM_EN
err_init_lct_tp_palm_fail:
    uninit_lct_tp_palm();
#endif

#if LCT_TP_GESTURE_EN
err_init_lct_tp_gesture_fail:
    uninit_lct_tp_gesture();
#endif

#if LCT_TP_GRIP_AREA_EN
err_init_lct_tp_grip_area_fail:
    uninit_lct_tp_grip_area();
#endif

#if LCT_TP_SELFTEST_EN
err_init_lct_tp_selftest_fail:
    uninit_lct_tp_selftest();
#endif

#if LCT_TP_WORK_EN
err_init_lct_tp_work_fail:
    uninit_lct_tp_work();
#endif

#if LCT_TP_INFO_EN
err_init_lct_tp_info_fail:
    uninit_lct_tp_info();
#endif

    return ret;
}

void lct_remove_procfs(void)
{
#if LCT_TP_INFO_EN
    uninit_lct_tp_info();
#endif

#if LCT_TP_WORK_EN
    uninit_lct_tp_work();
#endif

#if LCT_TP_SELFTEST_EN
    uninit_lct_tp_selftest();
#endif

#if LCT_TP_GRIP_AREA_EN
    uninit_lct_tp_grip_area();
#endif

#if LCT_TP_GESTURE_EN
    uninit_lct_tp_gesture();
#endif

#if LCT_TP_PALM_EN
    uninit_lct_tp_palm();
#endif

#if LCT_TP_PROXIMITY_EN
    uninit_lct_tp_proximity();
#endif

	return;
}

