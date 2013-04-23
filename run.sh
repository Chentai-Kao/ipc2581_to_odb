#!/bin/sh

qmake && make -j4 && bin/ipc2581 -i test_case1.xml -o bin/odb -y

##### update the output "features"
src="/home/cobra/ipc2581/bin/odb"
des="/home/cobra/icons/VirtualBox VMs/shared folder/test"
# matrix file
cp "$src/matrix/matrix" "$des/matrix/matrix"
# feature file and attrlist
cp "$src/steps/pcb/attrlist" "$des/steps/pcb/attrlist"
cp "$src/steps/pcb/profile" "$des/steps/pcb/profile"
for i in `ls "$src/steps/pcb/layers/"`; do
  if [ "$i" == "comp_+_bot" ] || [ "$i" == "comp_+_top" ]; then
    cp "$src/steps/pcb/layers/$i/components" \
       "$des/steps/pcb/layers/$i/components"
  else
    cp "$src/steps/pcb/layers/$i/features" "$des/steps/pcb/layers/$i/features"
  fi
  cp "$src/steps/pcb/layers/$i/attrlist" "$des/steps/pcb/layers/$i/attrlist"
done

##### copy the source code (for Windows build)
codesrc="/home/cobra/ipc2581"
codedes="/home/cobra/icons/VirtualBox VMs/shared folder/ipc2581"
cp "$codesrc/ipc2581.pro" "$codedes"
cp -r "$codesrc/src" "$codedes"

##### compress ODB++ to .tgz
cd "$des/.."
tar zcvf test.tgz test/* >/dev/null
