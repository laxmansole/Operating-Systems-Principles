//////////////////////////////////////////////////////////////////////
//                             North Carolina State University
//
//
//
//                             Copyright 2016
//
////////////////////////////////////////////////////////////////////////
//
// This program is free software; you can redistribute it and/or modify it
// under the terms and conditions of the GNU General Public License,
// version 2, as published by the Free Software Foundation.
//
// This program is distributed in the hope it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
//
////////////////////////////////////////////////////////////////////////
//
//   Author:  Hung-Wei Tseng
//
//   Description:
//     Skeleton of KeyValue Pseudo Device
//
////////////////////////////////////////////////////////////////////////

// Name : Aditya Gulavani, Laxman Sole
// Unity ID: agulava, lsole

#include "keyvalue.h"

#include <asm/uaccess.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/poll.h>
//#include <assert.h>

unsigned transaction_id;

typedef struct node{
	struct keyvalue_set keyval;
	struct node * next;
}node;

node * head = NULL;

DEFINE_SEMAPHORE(sai);

// this function returns:
// -1 if mem allocation failed
// 0 if node not found
// 1 if node found and successfully overwritten
static int search_already_set(struct keyvalue_set __user *ukv){
	node * temp = head;
	while(temp != NULL){
		if(temp->keyval.key == ukv->key){
			// free temp->data and re-malloc, reassign
			kfree(temp->keyval.data);
		    temp->keyval.data = (void *) kmalloc(ukv->size, GFP_ATOMIC);
		    if(temp->keyval.data == NULL){
		    	printk(KERN_ALERT "\nCannot allocate to temp->data in set function");
		    	return -1;
		    }
			    
			temp->keyval.size = ukv->size;
    		memcpy(temp->keyval.data, ukv->data, ukv->size);
			return 1;
		}
		temp = temp->next;
	}
	// assert(temp == NULL);
	return 0;
}

static node * search_already_get(struct keyvalue_get __user *ukv){
	node * temp = head;
	while(temp != NULL){
		if(temp->keyval.key == ukv->key){
			// free temp->data and re-malloc, reassign
			return temp;
		}
		temp = temp->next;
	}
	// assert(temp == NULL);
	return temp;
}

static void free_callback(void *data)
{
}

static long keyvalue_get(struct keyvalue_get __user *ukv)
{
    node * temp;
    if(down_interruptible(&sai)){

    }

    // struct keyvalue_get kv;
    temp = search_already_get(ukv);
    if(temp != NULL){
    	// assert(temp->keyval.key == ukv->key);
    	*(ukv->size) = temp->keyval.size;
    	memcpy(ukv->data, temp->keyval.data, temp->keyval.size);
    }
    else{
    	up(&sai);
    	return -1;
    }
	transaction_id++;
    up(&sai);
    return transaction_id;
}

static long keyvalue_set(struct keyvalue_set __user *ukv)
{
    // struct keyvalue_set kv;
    node * temp;
    int ret_val;
    if(down_interruptible(&sai)){

    }

    ret_val = search_already_set(ukv);
    if(ret_val == 1){
		transaction_id++;
    	up(&sai);
    	return transaction_id;
    }
    else if(-1 == ret_val){
    	up(&sai);
    	return -1;
    }
    else if(0 == ret_val){
	    temp = (node *) kmalloc (sizeof(node), GFP_ATOMIC);
	    if(temp == NULL){
	    	printk(KERN_ALERT "\nCannot allocate to temp in set function");
	    	up(&sai);
	    	return -1;
	    }

	    temp->keyval.data = (void *) kmalloc(ukv->size, GFP_ATOMIC);
	    if(temp->keyval.data == NULL){
	    	printk(KERN_ALERT "\nCannot allocate to temp->data in set function");
	    	up(&sai);
	    	return -1;
	    }

	    temp->keyval.key = ukv->key;
	    temp->keyval.size = ukv->size;
	    memcpy(temp->keyval.data, ukv->data, ukv->size);

    	temp->next = head;
    	head = temp;
	}
	transaction_id++;
    up(&sai);
    return transaction_id;
}

static long keyvalue_delete(struct keyvalue_delete __user *ukv)
{
    // struct keyvalue_delete kv;
    int deleted;
    node *prev, *temp;
    if(down_interruptible(&sai)){

    }

    deleted = 0;
    prev = head;
    temp = head;

    if(temp->keyval.key == ukv->key){
    	head = head->next;
    	kfree(temp);
    	deleted = 1;
    }
    else{
	    while(temp != NULL){
	    	if(temp->keyval.key == ukv->key){
	    		prev->next = temp->next;
	    		temp->next = NULL;
	    		kfree(temp);
	    		deleted = 1;
	    		break;
	    	}
	    	prev = temp;
			temp = temp->next;
	    }
	}

    if(deleted == 0){
        up(&sai);
        return -1;
    }
    else{
        transaction_id++;
        up(&sai);
        return transaction_id;
    }
}

//Added by Hung-Wei
     
unsigned int keyvalue_poll(struct file *filp, struct poll_table_struct *wait)
{
    unsigned int mask = 0;
    printk("keyvalue_poll called. Process queued\n");
    return mask;
}

static long keyvalue_ioctl(struct file *filp, unsigned int cmd,
                                unsigned long arg)
{
    switch (cmd) {
    case KEYVALUE_IOCTL_GET:
        return keyvalue_get((void __user *) arg);
    case KEYVALUE_IOCTL_SET:
        return keyvalue_set((void __user *) arg);
    case KEYVALUE_IOCTL_DELETE:
        return keyvalue_delete((void __user *) arg);
    default:
        return -ENOTTY;
    }
}

static int keyvalue_mmap(struct file *filp, struct vm_area_struct *vma)
{
    return 0;
}

static const struct file_operations keyvalue_fops = {
    .owner                = THIS_MODULE,
    .unlocked_ioctl       = keyvalue_ioctl,
    .mmap                 = keyvalue_mmap,
//    .poll		  = keyvalue_poll,
};

static struct miscdevice keyvalue_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "keyvalue",
    .fops = &keyvalue_fops,
};

static int __init keyvalue_init(void)
{
    int ret;

    if ((ret = misc_register(&keyvalue_dev)))
        printk(KERN_ERR "Unable to register \"keyvalue\" misc device\n");
    return ret;
}

static void __exit keyvalue_exit(void)
{
    misc_deregister(&keyvalue_dev);
}

MODULE_AUTHOR("Hung-Wei Tseng <htseng3@ncsu.edu>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
module_init(keyvalue_init);
module_exit(keyvalue_exit);
