#!/bin/bash
files=`find ./ -type f | sed 's;./;;g'`
for file in $files 
do
  rename=`echo $file | sed 's;Falagard;;g' | sed 's;Fal;;g' | tr 'A-Z' 'a-z'`
  rename=`echo $rename | sed 's;.cpp;.cc;g'`
  if [[ $file != $rename ]] ; then
    mv $file $rename
  fi
  newname=""
  if [[ -f $file ]] ; then
    newname=$file
  fi
  if [[ -f $rename ]] ; then
    newname=$rename
  fi
  if [[ -f $newname ]] ; then
    sed -i 's;\t;  ;g' $newname
    dos2unix $newname
    tempfile="rename_"$newname
    touch $tempfile #create temp file from system
    iconv -f GBK -t UTF-8 $newname > $tempfile
    mv $tempfile $newname
  fi
done
