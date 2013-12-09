<?php
include_once '../include/base.php';
include_once '../include/config.php';
include_once '../include/dict/db.php';
$start = time();
// $dbcode = new DBCode();
// $dbcode->init($mysql_config, 't_xinfa', 't_');
// $dbcode->create_all();

function test() {
  $headnote = 
<<<EOF
/**
 * PAP Engine ( https://github.com/viticm/pap )
 * \$Id global_data.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-6 16:28:57
 * @uses the server database \$modlename data for database class
 */
EOF;
  echo $headnote."\n----------------\n";
}
$arr = array('test', 'test1', 'test2');
echo implode($arr, ',')."\n";
test();
echo strftime('%Y-%m-%d %H:%M:%S');
$end = time();
echo 'runtime:',$end-$start,'s';