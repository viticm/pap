<?php
/**
 * bacause the vs obj name can't rename, so i will chang it
 * @author viticm<viticm@126.com>
 * @version 1.0
 * @uses to rename source files and visual studio script
 */

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
  $fileinfo = file_get_contents($filename);
  $scriptfiles = explode(' ', $renamelist['scriptfile']);
  foreach ($scriptfiles as $k => $scriptfile) {
    $scriptinfo = file_get_contents($scriptfile);
    $selfsource = $renamelist['source'];
    $selfsource_array = explode(' ', $selfsource);
    foreach ($selfsource_array as $k1 => $sourcefile) {
      $fullpath = PROJECTPATH.$sourcefile;
      if (file_exists($fullpath)) {
        $ostype = get_ostype();
        $filename = basename($fullpath);
        $fatherdir = basename(dirname($fullpath));
        $new_filename = $revert ? str_replace($fatherdir, '', $filename) :
                        $fatherdir.'_'.$filename;
        $cmd = '';
        $cmd .= 'cd '.dirname($fullpath);
        execcmd($cmd, $ostype);
        rename($filename, $new_filename);
        $new_sourcefile = str_replace($filename, '', $sourcefile).$new_filename;
        $scriptinfo = str_replace($sourcefile, $new_sourcefile, $scriptinfo);
      }
    }
    $commonsource = get_renamelist('common');
    foreach ($commonsource as $k => $common_sourcefile) {
      $fullpath = PROJECTPATH.$common_sourcefile;
      if (file_exists($fullpath)) {
        $ostype = get_ostype();
        $filename = basename($fullpath);
        $fatherdir = basename(dirname($fullpath));
        $new_filename = $revert ? str_replace($fatherdir, '', $filename) :
        $fatherdir.'_'.$filename;
        rename($filename, $new_filename);
        $new_sourcefile = str_replace($filename, 
                                      '', 
                                      $common_sourcefile).$new_filename;
        $scriptinfo = str_replace($common_sourcefile, 
                                  $new_sourcefile, 
                                  $scriptinfo);
      }
    }
    $result = file_put_contents($scriptfile, $scriptinfo);
    if (!result) {
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
  if (1 >= $argc || 3 <= $argc) {
    echo 'param error',"\n";
    return 1;
  }
  $revert = false;
  if (3 == $argc && 'yes' == $argv[2]) $revert = true; 
  $models = explode(' ', $argv[1]);
  foreach ($models as $k => $model) {
    $result = 
      2 == $argc ? rewrite_vcscript($model) : rewrite_vcscript($model, $revert);
    if (!result) return 1;
  }
  return 0;
}

main();