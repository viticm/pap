#!/bin/bash
files=`find ./ -type f -name "*.h" | sed 's;./;;g'`
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
  if [[ -f $newname && 0 != 0 ]] ; then
    sed -i 's;\t;  ;g' $newname
    dos2unix $newname
    tempfile="rename_"$newname
    touch $tempfile #create temp file from system
    iconv -f GBK -t UTF-8 $newname > $tempfile
    mv $tempfile $newname
  fi
  header=`echo $newname | grep .h`
  if [[ $header != "" ]] ; then
    filename=`echo $newname | sed 's;.h;;g' | tr 'a-z' 'A-Z'`
    cmd="sed -i '1i#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_"
    cmd="${cmd}${filename}_H_' $newname"
    echo $cmd | sh #execute
    cmd="sed -i '2i#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_" 
    cmd="${cmd}${filename}_H_' $newname"
    echo $cmd | sh
    cmd="echo -e \"\n\"\#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_"
    cmd="${cmd}${filename}_H_ >> ${newname}"
    echo $cmd | sh
  fi
done
