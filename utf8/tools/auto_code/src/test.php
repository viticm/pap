<?php
include_once '../include/base.php';
include_once '../include/config.php';
include_once '../include/dict/db.php';
$start = time();
$local = new Mysql();
$local->connect($mysql_config);
print_r($local->get_fields('t_xinfa'));
$end = time();
echo 'runtime:',$end-$start;
