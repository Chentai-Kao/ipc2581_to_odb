#!/bin/sh

qmake && make -j4 && bin/ipc2581 -i test_case1.xml -o bin/odb -y

##### update the output "features"
src="/home/cobra/ipc2581/bin/odb"
des="/home/cobra/icons/VirtualBox VMs/shared folder/test"
# matrix file
cp "$src/matrix/matrix" "$des/matrix/matrix"
# feature file
for i in `ls "$src/steps/pcb/layers/"`; do
  if [ "$i" == "comp_+_bot" ] || [ "$i" == "comp_+_top" ]; then
    cp "$src/steps/pcb/layers/$i/components" \
       "$des/steps/pcb/layers/$i/components"
  else
    cp "$src/steps/pcb/layers/$i/features" "$des/steps/pcb/layers/$i/features"
  fi
  cp "$src/steps/pcb/layers/$i/attrlist" "$des/steps/pcb/layers/$i/attrlist"
done
#cp "$src/steps/pcb/layers/top/features" "$des/test/steps/pcb/layers/top/features"

# compress ODB++ to .tgz
cd "$des/.."
tar zcvf test.tgz test/* >/dev/null

# copy IPC-2581 file for viewing
cp ~/ipc2581/test.xml "$des"
