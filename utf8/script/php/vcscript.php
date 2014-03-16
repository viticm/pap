<?php
/**
 * auto create visual studio script for standard project on version vc9.0
 * @author viticm<viticm@126.com>
 * @version 1.0
 * @uses standard project vc script auto create(just for full project)
 * ..... What is standard ?
 * ..... project must be have two part: src and include.
 */

define('DELIMITER', '\\');
define('LF', "\r\n");
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
  for ($i = 0; $i < $pathdeep - 1; ++$i) {
    $deeptab .= "\t";
  }
  if (true === $isdir) {
    //$vcfile
    $vcfile = $deeptab."<Filter".LF;
		$vcfile	.= $deeptab."\tName=\"{$filename}\"".LF;
		$vcfile	.= $deeptab."\t>".LF;
  } else {
    $vcfile = $deeptab."<File".LF;
    $vcfile .= $deeptab."\tRelativePath=\"{$filename}\"".LF;
    $vcfile .= $deeptab."\t>".LF;
    $vcfile .= $deeptab."</File>".LF;
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
  $pos = strpos($needle, DELIMITER);
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
 * @param array $files
 * @return array
 */
function traverse($path = '.', &$files = array()) {
  $current_dir = opendir($path);
  while(($file = readdir($current_dir)) !== false) {
    $sub_dir = $path.DIRECTORY_SEPARATOR.$file;
    if($file == '.' || $file == '..') {
      continue;
    } else if(is_dir($sub_dir)) {
      traverse($sub_dir, $files);
    } else {
      array_push($files, $sub_dir);
    }
  }
  return $files;
}

/**
 * get directory path form directory array
 * @param array $directorys
 * @param int $key
 * @return string
 */
function getdirectory($directorys = array(), $key = -1) {
  $delimiter = '\\';
  $result = '';
  if (empty($directorys) || -1 === $key) return $result;
  foreach ($directorys as $deep => $directory) {
    $result .= $directory;
    $result .= $delimiter;
    if ($key == $deep) return $result;
  }
}

/**
 * get filter end info
 * @param int $deep
 * @return string
 */
function get_filterend($deep = -1) {
  $result = '';
  if (-1 === $deep) return $result;
  $deeptab = "\t\t\t";
  for ($i = 0; $i < $deep; ++$i) {
    $deeptab .= "\t";
  }
  $result .= $deeptab."</Filter>\r\n";
  return $result;
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
    $pos = strpos($dirname, '\\');
    $fatherdir = substr($dirname, 0, $pos);
    if (!in_array($fatherdir, $basedir)) {
      array_push($basedir, $fatherdir);
    } 
    if (!in_array($dirname, $childdir)) {
      array_push($childdir, $dirname);
    }
    if (!array_key_exists($dirname, $temp)) {
      $temp[$dirname] = array();
    }
    $vcfile = 
      get_vcfile($pathdeep, $isdir, '..'.DELIMITER.$type.DELIMITER.$file);
    $temp[$dirname] = $vcfile;
  }
  $vcinfo = array();
  //get last directorys
  $lastdirectorys = array();
  foreach ($basedir as $firstdir) {
    $lastdirectorys[$firstdir] = NULL;
    foreach ($childdir as $otherdir) {
      if (indir($firstdir, $otherdir)) {
        $childdeep = substr_count($otherdir, DELIMITER);
        $dirdeep = substr_count($lastdirectorys[$firstdir], DELIMITER);
        if ($childdeep > $dirdeep) $lastdirectorys[$firstdir] = $otherdir;
      }
    }
  }
  var_dump($lastdirectorys);
  //get Filters info
  foreach ($lastdirectorys as $firstdir => $lastdirectory) {
    $vcinfo[$firstdir] = '';
    if (NULL === $lastdirectory) $lastdirectory = $firstdir;
    $directorys = explode($delimiter, $lastdirectory);
    foreach ($directorys as $deep => $directory) {
      echo $directory.LF;
      $vcinfo[$firstdir] .= get_vcfile($deep, true, $directory);
      $finddir = getdirectory($directorys, $deep);
      if (array_key_exists($finddir, $temp))
        $vcinfo[$firstdir] .= $temp[$finddir];
    }
    $maxdeep = count($directorys);
    for ($i = $maxdeep; $i >= 0; --$i) {
      $vcinfo[$firstdir] .= get_filterend($i);
    }
  }
  $vcstring = implode('', $vcinfo);
  return $vcstring;
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
    echo 'param error'.LF;
    return 1;
  }
  $projectpath = $argv[1];
  $projectpath = complementpath($projectpath, DELIMITER);
  $includepath = $projectpath.'include';
  $srcpath = $projectpath.'src';
  if (!is_dir($includepath) || !is_dir($srcpath)) {
    echo 'project not a standard project',LF;
    return 1;
  }
  $includefiles = traverse($includepath);
  echo get_vcfiles('include', $includefiles, $includepath.DELIMITER);
  return 0;
}
main();