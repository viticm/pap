<?php
define('SYS_DIR', realpath(dirname(__FILE__)).'/../');
define('SYS_CLASS_DIR', SYS_DIR.'include/class/');

/**
 * @desc 重写自动载入类的方法，只要类的规则正确，放置的路径也正确，
 * @desc   则在新建对象时自动载入类
 * @desc 类命名规则：所有类都放置在protected/class下，
 * @desc   而且类的规则是目录_+子目录+……+类名
 * @desc  （目录_+子目录+……这里就是类文件在class的相对路径）
 * @desc 类文件命名规则：class.目录+子目录+……+类名.php（目录同上）
 * @desc --注意这里的文件名必须全为小写，如果不清楚请发邮件<duchuanpd@gmail.com>
 * @param string $class_name
 * @return void
 */
function __autoload($class_name) {
  if (class_exists($class_name)) {
    return false;
  }
  $class_name_array = array();
  $path_count = 0;
  $class_path = '';
  $class_filename = '';
  $class_name_array = explode('_', $class_name);
  $path_count = count($class_name_array);
  for ($i = 0; $i < $path_count; ++$i) {
    if ($i < $path_count - 1) {
      $class_path .= $class_name_array[$i].DIRECTORY_SEPARATOR;
    }
  }
  $class_filename = str_replace('_', '', $class_name).'.php';
  require_once(SYS_CLASS_DIR.$class_path.$class_filename);  
}
