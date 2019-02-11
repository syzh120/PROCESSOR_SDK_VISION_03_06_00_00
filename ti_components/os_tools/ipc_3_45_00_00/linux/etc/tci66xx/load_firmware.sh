#!/bin/bash
depmod -a
echo 8 > /proc/sys/kernel/printk
modprobe remoteproc
modprobe keystone_remoteproc
modprobe rpmsg_proto
echo 0 > /proc/sys/kernel/printk
