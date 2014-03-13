#!/bin/bash
files=`find ./ -type f -name *.h`
for file in $files
do
  newfile=`echo ${file} | sed -e 's;\.h;\.cc;g'`
  mv $file $newfile
done
