<?php
/**
 * bacause the vs obj name can't rename, so i will chang it
 * @author viticm<viticm@126.com>
 * @version 2.0
 * @uses to rename source files and visual studio script
 */

/**
 * string replace of php system extend (viticm)
 * @param mixed $search
 * @param mixed $replace
 * @param mixed $subject
 * @param number $count
 * @return mixed
 */
function str_nreplace($search, $replace, $subject, $count = -1) {
  $result = $subject;
  if ($count < -1) return $result;
  if (-1 === $count) {
    $result = str_replace($search, $replace, $subject);
  }
  else {
    for ($i = 0; $i < $count; ++$i) {
      $pos = strpos($result, $search);
      if ($pos === false) {
        break;
      }
      else {
        $result = substr_replace($result, $replace, $pos, strlen($search));
      }
    }
  }
  return $result;
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
 * format the path to use system path
 * and if path like this server/name/../path will chage to server/path
 * @param string $path
 * @param string $from_ostype
 * @return string
 */
function format_systempath($path, $from_ostype = OS_LINUX) {
  $result = $path;
  $current_ostype = get_ostype();
  $find_delimiter = OS_WINDOWS == $from_ostype ? '\\' : '/';
  $delimiter = OS_WINDOWS == $current_ostype ? '\\' : '/';
  $result = str_replace($find_delimiter, $delimiter, $path);
  $fatherpath = '..'.$delimiter;
  while (($fatherpath_pos = strpos($result, $fatherpath)) !== false) {
    $temp = substr($result, 0, $fatherpath_pos);
    $find_fatherpath_pos = strrpos($temp, $fatherpath);
    $find_fatherpath_length = strlen($temp) - $find_fatherpath_pos;
    $result = substr_replace($result, 
                             $find_fatherpath_pos, 
                             $find_fatherpath_pos, 
                             $find_fatherpath_length);
  }
  return $result;
}

//project visual studio script file dirs
$g_scriptdirs = <<<EOF
billing src/server/billing/scripts
sharememory src/server/sharememory/scripts
login src/server/login/scripts
world src/server/world/scripts
server src/server/server/scripts
EOF;

$selfpath = str_replace('\\', '/', dirname(realpath(__FILE__)));
$projectpath = str_replace('script/php', '', $selfpath);
define('PROJECTPATH', $projectpath);
define('PROJECTNAME', 'pap');
define('OS_UNKONWN', 0);
define('OS_WINDOWS', 1);
define('OS_LINUX', 2);

/**
 * get server visual studio script dir(full path)
 * @param string $modelname
 * @return string
 */
function get_scriptdir($modelname) {
  $result = NULL;
  $scriptdir_array = explode("\n", $GLOBALS['g_scriptdirs']);
  foreach ($scriptdir_array as $key => $val) {
    list($model, $dir) = explode(' ', $val);
    if ($model == $modelname) {
      $result = PROJECTPATH.$dir;
      break;
    }
  }
  $result = complementpath($result);
  return $result;
}

/**
 * rename dir or file (form system cmd)
 * @param string $path
 * @param string $old
 * @param string $new
 */
function sys_rename($path, $old, $new) {
  $path = complementpath($path);
  $path = format_systempath($path);
  if (!file_exists($path.$old) && !is_dir($path)) return false;
  $ostype = get_ostype();
  $cmd = '';
  $cmd .= 'cd '.$path;
  $cmd .= ' &&';
  $cmd .= OS_WINDOWS == $ostype ? ' ren' : ' mv';
  $cmd .= ' '.$old.' '.$new;
  execcmd($cmd, $ostype);
  return true;
}

/**
 * get server visual studio script files(full path)
 * @param string $path
 * @return array
 */
function get_scriptfile($path) {
  $result = array();
  $ostype = get_ostype();
  $pathdemiliter = OS_WINDOWS == $ostype ? '\\' : '/';
  if (empty($path) || !is_dir($path)) return $result;
  $path = complementpath($path, $pathdemiliter); //fix it
  $vc9_scriptfiles = glob($path.'*.vcproj');
  $vc11_scriptfiles = glob($path.'*.vcxproj*');
  $result = array_merge($vc9_scriptfiles, $vc11_scriptfiles);
  return $result;
}

/**
 * rewrite visual studio script
 * @param string $model
 * @param string $filename
 * @return bool
 */
function rewrite_vcscript($modelname = NULL, 
                          $revert = false, 
                          $randsuffix = false) {
  $result = true;
  if (empty($modelname)) return false;
  $model_scriptpath = get_scriptdir($modelname);
  $scriptfiles = get_scriptfile($model_scriptpath);
  if (0 == count($scriptfiles)) return false;
  foreach ($scriptfiles as $scriptfile) {
    $scriptfile_info = file_get_contents($scriptfile);
    $match_sourcefiles = array();
    preg_match_all('/".*.cc/', $scriptfile_info, $match_sourcefiles);
    foreach ($match_sourcefiles as $sourcefile) {
      $sourcefile = substr($scriptfile, 1, strlen($scriptfile) - 1);
      $sourcefile_path = $model_scriptpath.$sourcefile;
      $sourcefile_path = dirname(format_systempath($sourcefile_path));
      $sourcefile_name = basename($sourcefile_path);
      $sourcefile_dir = dirname($sourcefile_path);
      $temp = str_replace(format_systempath(PROJECTPATH), '', $sourcefile_dir);
      $new_sourcefile_name = str_replace('\\', '_', $temp);
      $new_sourcefile_name .= true === $randsuffix ? '_'.time().rand(1, 1000) :
        ''; 
      sys_rename($sourcefile_path, $sourcefile_name, $new_sourcefile_name);
    }
    if (!$result) {
      echo 'rewrite '.$scriptfile.' failed!',"\n";
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
// main();
// rewrite_vcscript('sharememory');
echo dirname('F:\servers\develop\Zend\workspaces\pap\utf8\src\server\sharememory\scripts\\'.'..\..\..\..\run/server');