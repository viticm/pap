<?php
/**
 * bacause the vs obj name can't rename, so i will chang it
 * @author viticm<viticm@126.com>
 * @version 1.0
 * @uses to rename source files and visual studio script
 */

function str_replace_once($needle, $replace, $haystack) {
  // Looks for the first occurence of $needle in $haystack
  // and replaces it with $replace.
  $pos = strpos($haystack, $needle);
  if ($pos === false) {
    // Nothing found
    return $haystack;
  }
  $result = substr_replace($haystack, $replace, $pos, strlen($needle));
  return $result;
}


/**
 * get rename list
 * @param string $modelname
 * @return array
 */
function get_renamelist($modelname) { 
  $renamelist = array( //all path base of project/charset/ dir
    'sharememory' => array(
      'scriptpath' => 'src/server/share_memory/scripts/',
      'scriptfile' => 'share_memory.vc9.vcproj share_memory.vc11.vcxproj'
        .' share_memory.vc11.vcxproj.filters',
      'source' => 'src/server/share_memory/src/main/share_memory.cc'
    ),
    'common' => array( //无论如何公用的都会执行，不管是不是服务器与客户端公用的
      'src/common/sys/util.cc'
    ),
  );
  $result = array_key_exists($modelname, $renamelist) ? $renamelist[$modelname]
    : array();
  return $result; 
}

$selfpath = str_replace('\\', '/', dirname(realpath(__FILE__)));
$projectpath = str_replace('script/php', '', $selfpath);
define('PROJECTPATH', $projectpath);
define('OS_UNKONWN', 0);
define('OS_WINDOWS', 1);
define('OS_LINUX', 2);


/**
 * rewrite visual studio script
 * @param string $model
 * @param string $filename
 * @return bool
 */
function rewrite_vcscript($modelname = NULL, $revert = false) {
  if(empty($modelname)) return false;
  $renamelist = get_renamelist($modelname);
  if (empty($renamelist)) return true;
  $scriptfiles = explode(' ', $renamelist['scriptfile']);
  //specail
  if ('sharememory' == $modelname) $modelname = 'share_memory';
  foreach ($scriptfiles as $k => $scriptfile) {
    $scriptpath = $renamelist['scriptpath'];
    $scriptinfo = file_get_contents(PROJECTPATH.$scriptpath.$scriptfile);
    $selfsource = $renamelist['source'];
    $selfsource_array = explode(' ', $selfsource);
    foreach ($selfsource_array as $k1 => $sourcefile) {
      $fullpath = PROJECTPATH.$sourcefile;
      $fullpath = $revert ? dirname($fullpath).'/'.basename(dirname($fullpath)).
        '_'.basename($fullpath) : $fullpath;
      $sourcefile = str_replace(PROJECTPATH, '', $fullpath);
      $ostype = get_ostype();
      $filename = basename($fullpath);
      $fatherdir = basename(dirname($fullpath));
      $new_filename = $revert ? str_replace($fatherdir.'_', '', $filename) :
                      $fatherdir.'_'.$filename;
      if (file_exists($fullpath)) {
        $cmd = '';
        $cmd .= 'cd '.dirname($fullpath);
        $cmd .= ' &&';
        $cmd .= OS_WINDOWS == $ostype ? ' ren' : ' mv';
        $cmd .= ' '.$filename.' '.$new_filename;
        execcmd($cmd, $ostype);
      }
      $new_sourcefile = str_replace($filename, '', $sourcefile).$new_filename;
      $new_sourcefile = str_replace_once ('src/', '', $new_sourcefile);
      $new_sourcefile = str_replace_once('server/'.$modelname, 
                                         '', 
                                         $new_sourcefile);
      $new_sourcefile = str_replace('/', '\\', $new_sourcefile);
      $sourcefile = str_replace_once('src/', '', $sourcefile);
      $sourcefile = str_replace_once('server/'.$modelname.'/',
                                     '',
                                     $sourcefile);
      $sourcefile = str_replace('/', '\\', $sourcefile);
      $scriptinfo = str_replace($sourcefile, $new_sourcefile, $scriptinfo);
    }
    $commonsource = get_renamelist('common');
    foreach ($commonsource as $k => $common_sourcefile) {
      $fullpath = PROJECTPATH.$common_sourcefile;
      $fullpath = $revert ? dirname($fullpath).'/'.basename(dirname($fullpath)).
        '_'.basename($fullpath) : $fullpath;
      //revert
      $common_sourcefile = str_replace(PROJECTPATH, '', $fullpath);
      $ostype = get_ostype();
      $filename = basename($fullpath);
      $fatherdir = basename(dirname($fullpath));
      $new_filename = $revert ? str_replace($fatherdir.'_', '', $filename) :
        $fatherdir.'_'.$filename;
      if (file_exists($fullpath)) {
        $cmd = '';
        $cmd .= 'cd '.dirname($fullpath);
        $cmd .= ' &&';
        $cmd .= OS_WINDOWS == $ostype ? ' ren' : ' mv';
        $cmd .= ' '.$filename.' '.$new_filename;
        execcmd($cmd, $ostype);
      }
      $new_sourcefile = str_replace($filename, 
                                    '', 
                                    $common_sourcefile).$new_filename;
      $new_sourcefile = str_replace_once('src/', '', $new_sourcefile);
      $new_sourcefile = str_replace('/', '\\', $new_sourcefile);
      $common_sourcefile = str_replace_once('src/', '', $common_sourcefile);
      $common_sourcefile = str_replace('/', '\\', $common_sourcefile);
      $scriptinfo = str_replace($common_sourcefile, 
                                $new_sourcefile, 
                                $scriptinfo);
    }
    $result = file_put_contents(PROJECTPATH.$scriptpath.$scriptfile, 
                                $scriptinfo);
    if (!$result) {
      echo 'rewrite '.$scriptfile.' failed!',"\n";
      return false;
    }
    else {
      echo 'rewrite '.$scriptfile.' success.',"\n";
    }
  }
}

/**
 * get os type(windows/linux)
 * @param void
 * @return int
 */
function get_ostype() {
  if (str_ireplace('windows', '', php_uname('s')) != php_uname('s'))
    return OS_WINDOWS;
  if (str_ireplace('linux', '', php_uname('s')) != php_uname('s'))
    return OS_LINUX;
  return OS_UNKONWN;
}

/**
 * exec command
 * @param string $cmd
 * @param number $ostype
 */
function execcmd($cmd, $ostype) {
  if (OS_WINDOWS == $ostype) {
    $cmdarray = explode(' ', $cmd);
    foreach ($cmdarray as $k => &$val) {
      if (is_dir($val) || is_file($val)) {
        $val = str_replace('/', '\\', $val);
      }
    }
    $cmd = implode(' ', $cmdarray);
  }
  exec($cmd);
}

/**
 * this php file just a script command like shell, as c/c++ enter function
 * @param void
 * @return int
 */
function main() {
  $argc = $GLOBALS['argc'];
  $argv = $GLOBALS['argv'];
  if (1 >= $argc || 3 < $argc) {
    echo 'param error',"\n";
    return 1;
  }
  $revert = false;
  if (3 == $argc && 'yes' == $argv[2]) $revert = true; 
  $models = explode(' ', $argv[1]);
  foreach ($models as $k => $model) {
    $result = 
      2 == $argc ? rewrite_vcscript($model) : rewrite_vcscript($model, $revert);
    if (!$result) return 1;
  }
  return 0;
}

main();