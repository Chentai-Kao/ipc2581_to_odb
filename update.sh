#!/bin/sh

cd ~
cp ipc2581/bin/odb/steps/pcb/layers/top/features icons/VirtualBox\ VMs/shared\ folder/test/steps/pcb/layers/top/features
cd ~/icons/VirtualBox\ VMs/shared\ folder/
tar zcvf test.tgz test/* >/dev/null
