<?php
namespace dict\db;

function get_type($dbtype) {
  $db_types = array(
  	'int' => 'int32_t', 'tinyint' => 'int8_t', 'varchar' => 'char',
    'text' => 'char', 'longtext' => 'char', 'smallint' => 'int16_t',
    'bigint' => 'int64_t', 'DATE' => 'char', 'boolean' => 'bool',
    'int unsigned' => 'uint32_t', 'tinyint unsigned' => 'uint8_t',
    'smallint unsigned' => 'uint16_t', 'bigint unsigned' => 'uint64_t'
  );
  $type = $db_types[$dbtype];
  return $type;
}

function is_charactertable($tablename) {
  $not_charactertable = array(
    't_global' => true, 't_general_set' => true, 't_league' => true,
    't_league_apply' => true, 't_league_usr' => true, 't_mail' => true,
    't_petcreate' => true, 
  );
  $result = array_key_exists($tablename, $not_charactertable) ? false : true;
  return $result;
}