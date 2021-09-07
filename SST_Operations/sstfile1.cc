#include <stdio.h>
#include "rocksdb/db.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace rocksdb;

int main() {

Options options;

SstFileWriter sst_file_writer(EnvOptions(), options);
// Path to where we will write the SST file
std::string file_path = "/home/spenyee435/file1.sst";

// Open the file for writing
Status s = sst_file_writer.Open(file_path);
if (!s.ok()) {
    printf("Error while opening file %s, Error: %s\n", file_path.c_str(),
           s.ToString().c_str());
    return 1;
}

//std::string file_checksum = "file1.sst";
int index = 0;
int intKey = 0;
int intValue = 0;

std::string key;
std::string value;

// Insert rows into the SST file, note that inserted keys must be 
// strictly increasing (based on options.comparator)
for (index = 0; index < 100; index++) {
  Slice key((char*)&intKey,sizeof(int));
  Slice value((char*)&intValue,sizeof(int));
  s = sst_file_writer.Put(key, value);
  intValue++;
  intKey++;
  if (!s.ok()) {
    printf("Error while adding Key: %s, Error: %s\n", (char*)intKey,
           s.ToString().c_str());
    return 1;
  }
}

// Close the file
s = sst_file_writer.Finish();
if (!s.ok()) {
    printf("Error while finishing file %s, Error: %s\n", file_path.c_str(),
           s.ToString().c_str());
    return 1;
}
return 0;
}
