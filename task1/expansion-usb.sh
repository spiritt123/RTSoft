#!/bin/bash
sudo mkdir /media/temp
sudo mount /dev/sdb1 /media/temp
dmesg > /media/temp/dmsg_logs.txt
sudo umount /media/temp
