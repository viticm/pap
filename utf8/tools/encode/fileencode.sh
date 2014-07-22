#!/bin/bash
#the encode or decode file script
#@version 1.0
#@author viticm<viticm.ti@gmail.com>
#@date 2014-5-23

flag=$1
source_dir=$2
target_dir=$3
ENCODE_TOOL="fileencode"

is_win32=false
if [[ `uname | grep W32_NT` != "" ]] ; then
  is_win32=true
fi

currentdir=`pwd`
#help text, the script desc
#@param void
#@return void
function help_text() {
  cat <<EOF
${0} ver 1.0

options:
-d define the flag to decode
-e define the flag to encode

example:
sh fileencode.sh -d source_dir target_dir

EOF
}

#print error message, red words
#@param string message
#@return void
function error_message() {
  local message=${1}
  echo -e "\e[0;31;1merror:${message}\e[0m"
  exit 1
}

#print warning message, yellow words
#@param message
#@return string void
function warning_message() {
  local message=${1}
  echo -e "\e[0;33;1merror:${message}\e[0m"
}

#encode or decode files in dirs
#@param string flag
#@param string source_dir
#@param string target_dir
#@return void
function endecode() {
  local flag=$1
  local source_dir=$2
  local target_dir=$3

  if [[ ! -f ${ENCODE_TOOL} && ! -f "${ENCODE_TOOL}.exe" ]] ; then
    error_message "encode tool not found in ${currentdir}"
  fi
  
  if [[ $flag != "-d" && $flag != "-e" ]] ; then
    error_message "encode flag error"
  fi

  if [[ ! -d ${source_dir} ]] ; then
    error_message "source dir not exist"
  fi

  if [[ ${source_dir} == ${target_dir} ]] ; then
    error_message "source dir must diffrent with target dir"
  fi

  warning_message "now will clean your targer dir: rm -rf ${target_dir},
you can use Ctrl + C abort it"
  
  read answer

  rm -rf $target_dir
  if [[ ! -d $target_dir ]] ; then
    mkdir $target_dir
    if [[ $? != 0 ]] ; then
      error_message "mkdir ${target_dir} failed"
    fi
  fi

  dirlist=`find $source_dir -type d`
  for dir in $dirlist 
  do
    if [[ $dir != "." && 
          ${dir} != ${source_dir} ]] ; then
      dirname=`echo $dir | sed "s;${source_dir};;g"`
      mkdir -p ${target_dir}/${dirname}
      if [[ $? != 0 ]] ; then
        error_message "mkdir ${target_dir}/${dirname} failed"
      fi
    fi
  done

  filelist=`find $source_dir -type f`
  for file in $filelist 
  do
    filename=`basename $file`
    if [[ $filename == ${ENCODE_TOOL} || 
          $filename == ${ENCODE_TOOL}.exe ]] ; then
      continue
    fi
    dirname=`dirname $file | sed "s;${source_dir};;g"`
    target_file=${target_dir}/${dirname}/${filename}
    if $is_win32 ; then
      ./${ENCODE_TOOL}.exe ${flag} ${file} ${target_file}
    else
      ./${ENCODE_TOOL} ${flag} ${file} ${target_file}
    fi
  done
}

#the script main function, like c/c++
function main() {
  endecode "${flag}" "${source_dir}" "${target_dir}"
}
if [[ $# != 3 ]] ; then
  error_message "${0}: Need 3 params.You can use <${0} --help> see document"
else
  main "${@}"
  exit 0
fi
