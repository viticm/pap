<?php
/**
 * auto create visual studio script for standard project on version vc9.0
 * @author viticm<viticm@126.com>
 * @version 1.0
 * @uses standard project vc script auto create(just for full project)
 * ..... What is standard ?
 * ..... project must be have two part: src and include.
 */

/**
 * get vc file from filename for vc script need include
 * @param int $pathdeep
 * @param string $filename
 * @return string
 */
function get_vcfile($pathdeep = 0, $isdir = false, $filename = NULL) {
  if (NULL === $filename) return NULL;
  $deeptab = "\t\t\t";
  if (false == $isdir) $deeptab .= "\t";
  for ($i = 0; $i < $pathdeep; ++$i) {
    $deeptab .= "\t";
  }
  if (true === $isdir) {
    //$vcfile
    $vcfile = $deeptab."<Filter";
		$vcfile	.= $deeptab."\tName=\".$filename.\"";
		$vcfile	.= $deeptab."\t>";
  } else {
    $vcfile = $deeptab."<File";
    $vcfile .= $deeptab."\tRelativePath=\".$filename.\"";
    $vcfile .= $deeptab."\t>";
    $vcfile .= $deeptab."</File>";
  }
  return $vcfile;
}

/**
 * check the dir is in check dir
 * @param string $dir
 * @param string $needle
 * @return bool
 */
function indir($dir, $needle) {
  $pos = strpos($needle, '\\');
  $fatherdir = substr($needle, 0, $pos);
  return $dir === $fatherdir;
}

/**
 * complement full path(add the last delimiter)
 * this function not check the path if exist
 * @param string $path
 * @param string $delimiter
 * @return string
 */
function complementpath($path, $delimiter = '/') {
  $result = $path;
  $lastlimiter = substr($path, -1, 1);
  if ($lastlimiter != $delimiter) $result .= $delimiter;
  return $result;
}

/**
 * find all files from the directory
 * @param string $path
 * @return array
 */
function traverse($path = '.') {
  $current_dir = opendir($path);
  $files = array();
  while(($file = readdir($current_dir)) !== false) {
    $sub_dir = $path . DIRECTORY_SEPARATOR . $file;
    if($file == '.' || $file == '..') {
      continue;
    } else if(is_dir($sub_dir)) {
      traverse($sub_dir);
    } else {
      array_push($files, $sub_dir);
    }
  }
  return $files;
}

/**
 * get vc script need files code from file array
 * @param array $files
 * @param string $projectpath
 * @return string
 */
function get_vcfiles($type, $files = array(), $dirpath = NULL) {
  $temp = array(); //save the has get dirs
  $delimiter = '\\';
  $basedir = array();
  $childdir = array();
  foreach ($files as $file) {
    $filename = basename($file);
    $isdir = is_dir($filename);
    if ($dirpath !== NULL)
      $file = str_replace($dirpath, '', $file);
    $dirname = str_replace($filename, '', $file);
    $pathdeep = substr_count($dirname, $delimiter);
    if (0 == $pathdeep && !in_array($dirname, $basedir)) {
      array_push($basedir, $dirname);
    } else {
      array_push($childdir, $dirname);
    }
    if (!array_key_exists($dirname, $temp)) {
      $temp[$dirname] = array();
    }
    $vcfile = get_vcfile($pathdeep, $isdir, '..'.$delimiter.$type.$dirname);
    array_push($temp[$dirname], $vcfile);
  }
  $vcinfo = array();
  foreach ($basedir as $firstdir) {
    $vcinfo[$firstdir] = array();
    foreach ($childdir as $otherdir) {
      if (indir($firstdir, $otherdir)) {
        $childdeep = substr_count($otherdir, $delimiter);
        $dirdeep = count($vcinfo[$firstdir]);
        if (0 === $dirdeep) { //hash is not has
          for ($i = 0; $i < $childdeep + 1; ++$i) {
            array_push($vcinfo[$firstdir], ''); //first construct
          }
          $vcinfo[$firstdir][0] = get_vcfile(0, false, $firstdir);
          $vcinfo[$firstdir][$childdeep] = 
            get_vcfile($childdeep, false, $otherdir);
        }
        elseif ($childdeep > $dirdeep) {
          $right = $childdeep - $dirdeep;
          for ($i = 0; $right; ++$i) {
            array_push($vcinfo[$firstdir], ''); //first construct
          }
        }
        else {
          
        }
      }
    }
  }
}

/**
 * this php file just a script command like shell, as c/c++ enter function
 * @param void
 * @return int
 */
function main() {
  $argc = $GLOBALS['argc'];
  $argv = $GLOBALS['argv'];
  if ($argc != 2) {
    echo 'param error';
    return 1;
  }
  $projectpath = $argv[1];
  return 0;
}
