<?php
include_once '../include/base.php';
include_once '../include/config.php';
include_once '../include/dict/db.php';
$start = time();
$dbcode = new DBCode();
$dbcode->init($mysql_config, 't_char', 't_');
$dbcode->create_all();
$end = time();
echo 'runtime:',$end-$start,'s';