#!/bin/sh

qmake && make -j4 && bin/ipc2581 -i test_case1.xml -o bin/odb -y

# update the output "features"
src="/home/cobra/ipc2581/bin/odb"
des="/home/cobra/icons/VirtualBox VMs/shared folder"
cd "$src/steps/pcb/layers";
for i in `ls`; do
  cp "$src/steps/pcb/layers/$i/features" "$des/test/steps/pcb/layers/$i/features"
done
#cp "$src/steps/pcb/layers/top/features" "$des/test/steps/pcb/layers/top/features"

# compress ODB++ to .tgz
cd "$des"
tar zcvf test.tgz test/* >/dev/null

# copy IPC-2581 file for viewing
cp ~/ipc2581/test.xml "$des"
