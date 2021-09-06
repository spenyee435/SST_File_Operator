# SST_File_Operator
Creation of SST FIle Operation using RocksDB

To first run the SST file functions, you must first install RocksDB. 
```
git clone https://github.com/facebook/rocksdb.git 
cd rocksdb/ 
export LD_LIBRARY_PATH=/usr/local/lib
make all
```
Dependencies:
```
sudo apt-get install libgflags-dev libsnappy-dev zlib1g-dev libbz2-dev libzstd-dev
```
Afterwards, using any of the SST file operators, you can test and create your own SST file to run using RocksDB. 

Inside the Rocksdb directory
```
mkdir SST_Operations
cd SST_Operations
vim sstfile1.cc
```
Inside the rocksdb directory, you must first open the SST file and choose what operation to test or use.
```
Status s = sst_file_writer.Open(file_path);
```
After completing the creation of your SST file, end the operation by closing the file. 
```
s = sst_file_writer.Finish();
```
To compile the code, use the following commands:
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
