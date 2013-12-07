<?php
include_once '../include/base.php';
include_once '../include/config.php';
$start = time();
$local = new Mysql();
$local->connect($mysql_config);
print_r($local->get_fields('t_char'));
$end = time();
echo 'runtime:',$end-$start;