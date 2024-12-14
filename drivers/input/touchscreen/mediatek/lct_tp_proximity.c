/****************************************************************************************
 *
 * @File Name   : lct_tp_common.c
 * @Author      : sunjiajia
 * @E-mail      : <sunjiajia@longcheer.com>
 * @Create Time : 2023-07-31 16:18:11
 * @Description : Add touchpad proximity switch.
 *
 ****************************************************************************************/

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <linux/module.h>
#include <linux/device.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

/*
 * DEFINE CONFIGURATION
 ****************************************************************************************
 */
#define TP_PROXIMITY_NAME          "tp_proximity"
#define TP_PROXIMITY_LOG_ENABLE
#define TP_PROXIMITY_TAG           "LCT_TP_proximity"

#ifdef TP_PROXIMITY_LOG_ENABLE
#define TP_LOGW(log, ...) printk(KERN_WARNING "[%s] %s (line %d): " log, TP_PROXIMITY_TAG, __func__, __LINE__, ##__VA_ARGS__)
#define TP_LOGE(log, ...) printk(KERN_ERR "[%s] %s ERROR (line %d): " log, TP_PROXIMITY_TAG, __func__, __LINE__, ##__VA_ARGS__)
#else
#define TP_LOGW(log, ...) {}
#define TP_LOGE(log, ...) {}
#endif

/*
 * DATA STRUCTURES
 ****************************************************************************************
 */
typedef int (*tp_proximity_cb_t)(bool enable_tp);

typedef struct lct_tp{
	bool enable_tp_proximity_flag;
	struct proc_dir_entry *proc_entry_tp_proximity;
	tp_proximity_cb_t pfun_prox;
}lct_tp_proximity_t;

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
static lct_tp_proximity_t *lct_tp_proximity_p = NULL;

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */
// --- proc ---
static int lct_creat_proc_tp_proximity_entry(void);
static ssize_t lct_proc_tp_proximity_read(struct file *file, char __user *buf, size_t size, loff_t *ppos);
static ssize_t lct_proc_tp_proximity_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos);
static const struct file_operations lct_proc_tp_proximity_fops = {
	.read = lct_proc_tp_proximity_read,
	.write = lct_proc_tp_proximity_write,
};


int init_lct_tp_proximity(tp_proximity_cb_t callback)
{
	if (NULL == callback) {
		TP_LOGE("callback is NULL!\n");
		return -EINVAL;
	}

	TP_LOGW("Initialization tp_proximity node!\n");
	lct_tp_proximity_p = kzalloc(sizeof(lct_tp_proximity_t), GFP_KERNEL);
	if (IS_ERR_OR_NULL(lct_tp_proximity_p)){
		TP_LOGE("kzalloc() request memory failed!\n");
		return -ENOMEM;
	}
	lct_tp_proximity_p->pfun_prox = callback;
	lct_tp_proximity_p->enable_tp_proximity_flag = false;

	if (lct_creat_proc_tp_proximity_entry() < 0) {
		kfree(lct_tp_proximity_p);
		return -1;
	}

	return 0;
}
EXPORT_SYMBOL(init_lct_tp_proximity);

void uninit_lct_tp_proximity(void)
{
	TP_LOGW("uninit /proc/%s ...\n", TP_PROXIMITY_NAME);
	if (IS_ERR_OR_NULL(lct_tp_proximity_p))
		return;
	if (lct_tp_proximity_p->proc_entry_tp_proximity != NULL) {
		remove_proc_entry(TP_PROXIMITY_NAME, NULL);
		lct_tp_proximity_p->proc_entry_tp_proximity = NULL;
		TP_LOGW("remove /proc/%s\n", TP_PROXIMITY_NAME);
	}
	kfree(lct_tp_proximity_p);
	return;
}
EXPORT_SYMBOL(uninit_lct_tp_proximity);

void set_lct_tp_proximity_status(bool en)
{
	lct_tp_proximity_p->enable_tp_proximity_flag = en;
}
EXPORT_SYMBOL(set_lct_tp_proximity_status);

bool get_lct_tp_proximity_status(void)
{
	return lct_tp_proximity_p->enable_tp_proximity_flag;
}
EXPORT_SYMBOL(get_lct_tp_proximity_status);

static int lct_creat_proc_tp_proximity_entry(void)
{
	lct_tp_proximity_p->proc_entry_tp_proximity = proc_create_data(TP_PROXIMITY_NAME, 0444, NULL, &lct_proc_tp_proximity_fops, NULL);
	if (IS_ERR_OR_NULL(lct_tp_proximity_p->proc_entry_tp_proximity)) {
		TP_LOGE("add /proc/%s error!\n", TP_PROXIMITY_NAME);
		return -1;
	}
	TP_LOGW("/proc/%s is okay!\n", TP_PROXIMITY_NAME);
	return 0;
}

static ssize_t lct_proc_tp_proximity_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	ssize_t cnt=0;
	char *page = NULL;

	if (*ppos)
		return 0;

	page = kzalloc(128, GFP_KERNEL);
	if (IS_ERR_OR_NULL(page))
		return -ENOMEM;

	cnt = sprintf(page, "%s", (lct_tp_proximity_p->enable_tp_proximity_flag ? "1\n" : "0\n"));

	cnt = simple_read_from_buffer(buf, size, ppos, page, cnt);
	if (*ppos != cnt)
		*ppos = cnt;
	TP_LOGW("Touchpad status : %s", page);

	kfree(page);
	return cnt;
}

static ssize_t lct_proc_tp_proximity_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	int ret;
	ssize_t cnt = 0;
	char *page = NULL;
	unsigned int input = 0;

	page = kzalloc(128, GFP_KERNEL);
	if (IS_ERR_OR_NULL(page))
		return -ENOMEM;
	cnt = simple_write_to_buffer(page, 128, ppos, buf, size);
	if (cnt <= 0)
		return -EINVAL;
	if (sscanf(page, "%u", &input) != 1)
		return -EINVAL;

    TP_LOGW("enable_tp_proximity_flag=%d, input=%d\n", lct_tp_proximity_p->enable_tp_proximity_flag, input);

	if (input > 0) {
		if (lct_tp_proximity_p->enable_tp_proximity_flag) {
			goto exit;
		}
		TP_LOGW("Enbale Touchpad proximity ...\n");
		ret = lct_tp_proximity_p->pfun_prox(true);
		if (ret) {
			TP_LOGW("Enable Touchpad proximity Failed! ret=%d\n", ret);
			goto exit;
		}
		lct_tp_proximity_p->enable_tp_proximity_flag = true;
	} else {
		if (!lct_tp_proximity_p->enable_tp_proximity_flag) {
			goto exit;
		}
		TP_LOGW("Disable Touchpad proximity ...\n");
		ret = lct_tp_proximity_p->pfun_prox(false);
		if (ret) {
			TP_LOGW("Disable Touchpad proximity Failed! ret=%d\n", ret);
			goto exit;
		}
		lct_tp_proximity_p->enable_tp_proximity_flag = false;
	}
	TP_LOGW("Set Touchpad proximity successfully!\n");

exit:
	kfree(page);
	return cnt;
}

static int __init tp_proximity_init(void)
{
	TP_LOGW("init");
	return 0;
}

static void __exit tp_proximity_exit(void)
{
	TP_LOGW("exit");
	return;
}

module_init(tp_proximity_init);
module_exit(tp_proximity_exit);

MODULE_DESCRIPTION("Touchpad Proximity Contoller Driver");
MODULE_LICENSE("GPL");


