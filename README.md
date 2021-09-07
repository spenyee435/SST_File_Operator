# SST File Operator
To first run the SST file functions, you must first install RocksDB. 
```
git clone https://github.com/facebook/rocksdb.git 
cd rocksdb/ 
make all
```
Dependencies:
```
sudo apt-get install libgflags-dev libsnappy-dev zlib1g-dev libbz2-dev libzstd-dev
```
Afterwards, using any of the operators shown below, you can test and create your own SST file to run using RocksDB. Inside the rocksdb directory, you must first open the SST file and choose what operation to test or use. After completing the creation of your SST file, end the operation by closing the file. To compile the code, use the following commands:
```
g++ -c -I./include -std=c++11 “filename”.cc
g++ -o “filename” “filename”.o -L. -lrocksdb -lsnappy -lpthread -lbz2 -lz -lrt
 ```
Then to run the your SST file operators, type:
```
./”filename”
```
To benchmark the performance of the system, run perf stat both on the regular SST File operations and once again perform perf stat on the SSD simulated device.

Inside the rocksdb directory with your SST file operator, use the command:
```
perf stat ./”filename” 
```
To test your code again using the SSD simulator, you must first clone Peter’s code for SSD emulation through this:
```
git clone https://github.com/pcwilcox/accel.git.
git checkout --
git checkout cheops
git submodule update --init --recursive
```
Then once you are in the /accel directory do:
```
./configure
```
And then
```
make all
```
If there happen to be issues with xNVMe or SPDK, reinstall them by cloning them again.

xNVME:
https://github.com/pcwilcox/xNVMe.git
```
./configure 
make 
```
SPDK:
https://github.com/pcwilcox/spdk_private.git
```
./configure
make
```

Some issues with the script that might pop up in the src files in the /accel root are with the command xnvme_buf_alloc and the fix to this is to simply remove the NULL variable at the end of the function call. 

e.g.:
```
buf_match = xnvme_buf_alloc(dev, lba_nbytes, NULL); to
buf_match = xnvme_buf_alloc(dev, lba_nbytes);
```
If there are issues with the .../block/filter-accel.c file for debug, do the following:

Change the ACCEL_DEBUG to 1 instead of 0.
```
#define ACCEL_DEBUG 0
```
Comment or remove the error that uses the debug call.

After all the issues have been resolved, you can move on with attempting to run the emulator. The first thing you must do is create the images for qcow2 and the img by using the commands inside the /accel root directory.

The line after the -m is the amount of memory you want to use.
```
mkdir -p images
qemu-img create -f qcow2 qemu.qcow2 -m _
qemu-img create qemu_nvme.img -m _
```
Once this is done, implement the following command to get an Ubuntu server ISO and run the emulator:
```
mkdir -p iso
wget https://releases.ubuntu.com/21.04/ubuntu-21.04-live-server-amd64.iso -O iso/ubuntu-20.04.3-live-server-amd64.iso
scripts/run-qemu.sh install  iso/ubuntu-20.04.3-live-server-amd64.iso
```
If the VM emulator fails to boot, then you might have to add the boot device by adding in:
```
-cdrom /home/user/accel/iso/ubuntu-20.04.3-live-server-amd64.iso
-boot d
```
Another thing to change if receiving kernel panic is to change run-qemu cpu. Change the host to any other cpu allowed on your device. More documentation here: https://qemu.readthedocs.io/en/latest/system/invocation.html 
E.g. 
```
-cpu host to
-cpu EPYC
```
To rerun the qemu emulator, in the /accel directory, run the following:
```
scripts/run-qemu.sh
```
With this, you should now have your SSD emulator running. The next step is to then convert your SST file operators with an SSD offload command. This way you can benchmark the performance between the SST file operator and SSD offload command.
