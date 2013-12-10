<?php
/*
 *  auto_code just use for pap.
 *  @link https://github.com/viticm/pap
 *  @package auto code
 */

include_once SYS_DIR.'include/dict/db.php';

/**
 * Description of Mysql
 * about database some code auto create class(project muse be include base.php)
 * @author viticm<viticm@126.com>
 * @version 1.0
 */
class DBCode extends Mysql {
  
  private $db_config_; //filename or db config
  private $tablename_;
  private $tableprefix_;
  private $outputpath_;
  private $split_createfile_;
  
  /**
   * constrcut function
   * @param void
   * @return void
   */
  public function __construct() {
    $this->db_config_ = null;
    $this->tablename_ = null;
    $this->tableprefix_ = null;
    $this->split_createfile_ = false;
    $this->outputpath_ = './';
  }
  
  /**
   * init function, start the object
   * @param array $db_config
   * @param string $tablename
   * @return bool
   */
  public function init(array $db_config, 
                       $tablename = null, 
                       $tableprefix = null,
                       $outputpath = null,
                       $split_createfile = false) {
    $this->tablename_ = $tablename;
    $this->tableprefix_ = $tableprefix;
    $this->outputpath_ = empty($outputpath) ? './' : $outputpath;
    $this->split_createfile_ = $split_createfile;
    $this->connect($db_config);
    return $this->connect_;
  }
  
  /**
   * get table info: 
   * array('tablename' => array(array('type' => 'int',
   *  'name' => 'test', 'length' => 10)))
   * @param void
   * @return array
   */
  public function get_table_info() {
    $result = array();
    if ($this->tablename_) {
      $result = $this->get_fields($this->tablename_);
    }
    else {
      $tables = $this->get_tables();
      if (is_array($tables)) {
        foreach ($tables as $key => $tablename) {
          $row = $this->get_fields($tablename);
          if(is_array($row)) array_push($result, $row);
        }
      }
    }
    return $result;
  }
  
  /**
   * create db struct cpp files(.h and .cc)
   * @param string $tablename
   * @return bool
   */
  public function create_structfile($tablename = null) {
    $headinfo = "";
    $sourceinfo = "";
    $structname = "";
    $headfile = "";
    $sourcefile = "";
    $tablename = $tablename ? $tablename : $this->tablename_;
    if (empty($tablename)) return false;
    $structname = $tablename.'_t';
    if (!empty($this->tableprefix_)) 
      $structname = str_replace($this->tableprefix_, '', $tablename).'_t';
    $headinfo .= "struct $structname {\n";
    $sourceinfo .= "$structname::{$structname}() {\n";
    $sourceinfo .= "  cleanup();\n";
    $sourceinfo .= "}\n";
    $sourceinfo .= "$structname::~{$structname}() {\n";
    $sourceinfo .= "  __ENTER_FUNCTION\n";
    $sourceinfo .= "    //do nothing\n";
    $sourceinfo .= "  __LEAVE_FUNCTION\n";
    $sourceinfo .= "}\n";
    $sourceinfo .= "void $structname::cleanup() {\n";
    $sourceinfo .= "  __ENTER_FUNCTION\n";
    $fields = $this->get_fields($tablename);
    if (is_array($fields)) {
      foreach ($fields as $k => $field) {
        $name = $field['name'];
        $type = dict\db\get_type($field['type']);
        $length = 0;
        if ('char' == $type) {
          $length = 1024;
        }
        $length_str = 0 == $length ? '' : "[$length]";
        $headinfo .= "  $type $name$length_str;\n";
        if (preg_match('/int/', $type) > 0) {
          $sourceinfo .= "    $name = 0;\n";
        }
        else {
          $sourceinfo .= "    memset($name, '\0', sizeof($name));\n";
        }
      }
    }
    $headinfo .= "  $structname();\n";
    $headinfo .= "  ~$structname(); \n";
    $headinfo .= "  void cleanup();\n";
    $headinfo .= "};\n";
    $sourceinfo .= "  __LEAVE_FUNCTION\n";
    $sourceinfo .= "}\n";
    if ($this->split_createfile_) {
      $headfile = "$structname.h";
      $sourcefile = "$structname.cc";
      @unlink($this->outputpath_.$headfile);
      @unlink($this->outputpath_.$sourcefile);
    }
    else { //in sigle file clean will in outside
      $headfile = 'struct.h';
      $sourcefile = 'struct.cc';
    }
    file_put_contents($this->outputpath_.$headfile, $headinfo, FILE_APPEND);
    file_put_contents($this->outputpath_.$sourcefile, $sourceinfo, FILE_APPEND);
    return true;
  }
  
  /**
   * create database data operation class(namespace pap_server_common_db)
   * @param string $tablename
   * @return bool
   */
  public function create_db_datafile($tablename = null) {
    //now this version(1.0) this template code look is not intuition, 
    //next version i need fix it(use eof template).
    $result = true;
    $headinfo = '';
    $sourceinfo = '';
    $headfile = '';
    $sourcefile = '';
    $classname = '';
    $tablename = $tablename ? $tablename : $this->tablename_;
    if (empty($tablename)) return false;
    $fields = $this->get_fields($tablename); //this records will be use in next
    $_fields = array();
    foreach ($fields as $k => $field) {
      array_push($_fields, $field['name']);
    }
    if (!is_array($_fields)) return false;
    if (!is_array($_fields) || count($_fields) < 0) return false;
    $classname = ucwords($tablename);
    if (!empty($this->tableprefix_))
      $real_tablename = str_replace($this->tableprefix_, '', $tablename);
    $headfile = $real_tablename.'.h'; //filename is the tablename, not upper words
    $sourcefile = $real_tablename.'.cc';
    @unlink($this->outputpath_.$headfile);
    @unlink($this->outputpath_.$sourcefile);
    $classname = str_replace('_', ' ', $real_tablename); //class real name
    $classname = str_replace(' ', '', ucwords($classname));
    $modlename = strtolower($classname);
    $datestr = strftime('%Y-%m-%d %H:%M:%S');
    $headnote =
<<<EOF
/**
 * PAP Engine ( https://github.com/viticm/pap )
 * \$Id global_data.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>(by tools auto code)
 * @date $datestr
 * @uses the server database $modlename data for database class
 */
EOF;
//eof string need like this, no indent
    $headinfo .= $headnote.LF;
    $headinfo .= '#ifndef PAP_SERVER_COMMON_DB_'
                 .strtoupper($real_tablename).'_H_'.LF;
    $headinfo .= '#define PAP_SERVER_COMMON_DB_'
                 .strtoupper($real_tablename).'_H_'.LF.LF;
    
    $headinfo .= '#inlcude "server/common/db/data/config.h"'.LF;
    $headinfo .= '#include "server/common/db/system.h"'.LF.LF;
    
    //some define for code
    $public = LF.' public:'.LF;
    $private = LF.' public:'.LF;
    $protected = LF.' protected:'.LF;
    $fourspace = '    '; //use in source functions
    $threespace = '   '; //use in class 
    $twospace = '  ';
    
    $functionenter = '__ENTER_FUNCTION'.LF;
    $functionleave = '__LEAVE_FUNCTION'.LF;
    
    $headinfo .= 'namespace pap_server_common_db {'.LF;
    $headinfo .= LF.'namespace data {'.LF;
    $headinfo .= LF.'class '.$classname.' {'.LF;
    
    $headinfo .= $public; //construct and desctruct
    $headinfo .= $threespace.$classname.'(ODBCInterface* odbc_interface);'.LF;
    $headinfo .= $threespace.'~'.$classname.'();'.LF;
    
    $headinfo .= $public; //variables and virtual functions
    $charactertable = dict\db\is_charactertable($tablename);
    if ($charactertable) {
      $headinfo .= $threespace.'uint32_t character_guid_;'.LF;
      $headinfo .= $threespace.'uint32_t dbversion_;'.LF;
    }
    $headinfo .= $threespace.'virtual bool load();'.LF;
    $headinfo .= $threespace.'virtual bool save(void* source);'.LF;
    $headinfo .= $threespace.'virtual bool _delete();'.LF;
    $headinfo .= $threespace.'virtual bool parse_result(void* result);'.LF;
    
    if ($charactertable) { //character table use functions
      $headinfo .= $public;
      $headinfo .= $threespace.'void set_characterguid(uint32_t id);'.LF;
      $headinfo .= $threespace.'uint32_t get_characterguid();'.LF;
      $headinfo .= $threespace.'void set_dbversion(uint32_t id);'.LF;
      $headinfo .= $threespace.'uint32_t get_dbversion();'.LF;
    }
    $headinfo .= LF.'}'.LF; //class end
    $headinfo .= LF.'}; //namespace data'.LF;
    $headinfo .= LF.'}; //namespace pap_server_common_db';
    
    $headinfo .= LF.'#endif //PAP_SERVER_COMMON_DB_'
                 .strtoupper($classname).'_H_';
    
    $sourceinfo .= '#inlcude "server/common/db/data/'.$headfile.'"'.LF;
    $sourceinfo .= LF.'namespace pap_server_common_db {'.LF;
    $sourceinfo .= LF.'namespace data {'.LF;
    $sourceinfo .= LF.$classname.'::'.$classname.
                   '(ODBCInterface* odbc_interface) {'.LF; //construct
    $sourceinfo .= $twospace.$functionenter;
    $sourceinfo .= $fourspace.'db_type_ = kCharacterDatabase;'.LF;
    $sourceinfo .= $fourspace.'result_ = false;'.LF;
    $sourceinfo .= $fourspace.'result_count_ = 0;'.LF;
    $sourceinfo .= $fourspace.'character_guid = 0;'.LF;
    $sourceinfo .= $fourspace.'Assert(odbc_interface);'.LF;
    $sourceinfo .= $fourspace.'odbc_interface_ = odbc_interface;'.LF;
    $sourceinfo .= $twospace.$functionleave;
    $sourceinfo .= '}'.LF;
    
    $sourceinfo .= LF; //destruct
    $sourceinfo .= $classname.'::~'.$classname.'() {'.LF;
    $sourceinfo .= $twospace.'//do nothing'.LF;
    $sourceinfo .= '}'.LF;
    
    $sourceinfo .= LF; //load start
    $sourceinfo .= 'bool '.$classname.'::load() {'.LF;
    $sourceinfo .= $twospace.$functionenter;
    $sourceinfo .= $fourspace.'bool result = false;'.LF;
    $sourceinfo .= $fourspace.'DB_QUERY* query = get_internal_query();'.LF;
    $sourceinfo .= $fourspace.'if (!query) Assert(false);'.LF;
    $sourceinfo .= $fourspace.'query->clear();'.LF;
    
    //-- sql template
    $sql_template_headfile = 'sql_template.h';
    $sql_template_sourcefile = 'sql_template.cc';
    $sql_template_headinfo = '';
    $sql_template_sourceinfo = '';
    //load select, delete --, update --, save update, add instert
    $sql_template_headinfo .= '//-- table '.$tablename.LF;
    $sql_template_headinfo .= 'extren const char* kLoad'.$classname.';'.LF;
    $sql_template_headinfo .= 'extren const char* kDelete'.$classname.';'.LF;
    $sql_template_headinfo .= 'extren const char* kUpdate'.$classname.';'.LF;
    $sql_template_headinfo .= 'extren const char* kAdd'.$classname.';'.LF;
    $sql_template_headinfo .= 'extren const char* kSave'.$classname.';'.LF;
    $sql_template_headinfo .= '//table '.$tablename.' --'.LF;
    $sql_template_headinfo .= LF; //wrap
    
    $sql_template_sourceinfo .= '//-- table '.$tablename.LF;
    //在这里生成mysql的模板
    if ($charactertable) {
      $sourceinfo .= $fourspace
                     .'if (INVALID_ID == character_guid_) return false;'.LF;
      $sql_template_sourceinfo .= 'const char* kLoad'.$classname.' = '.LF
                                  .'"SELECT '.implode($_fields, ',').'FROM `'
                                  .$tablename.'` WHERE `character_guid` = %d'
                                  .' AND `dbversion` = %d";'.LF;
    }
    else {
      $sql_template_sourceinfo .= 'const char* kLoad'.$classname.' = '.LF
                                  .'SELECT * FROM `'.$tablename.';`'.LF;
    }
    $sql_template_sourceinfo .= 'const char* kDelete'.$classname.' = "";'.LF;
    $sql_template_sourceinfo .= 'const char* kUpdate'.$classname
                                .' = "DELETE FROM `'.$tablename
                                .'` WHERE `character_guid` = %d'
                                .' AND `dbversion` = %d";'.LF;
    $insert_sql = $this->get_instertstr($tablename, $fields);
    $sql_template_sourceinfo .= 'const char* kAdd'.$classname.' = '.LF
                                .'"'.$insert_sql.'";'.LF;
    $sql_template_sourceinfo .= 'const char* kSave'.$classname.' = "";'.LF;
    $sql_template_sourceinfo .= '//table '.$tablename.' --'.LF;
    file_put_contents($this->outputpath_.$sql_template_headfile, 
                      $sql_template_headinfo,
                      FILE_APPEND);
    file_put_contents($this->outputpath_.$sql_template_sourcefile,
                      $sql_template_sourceinfo,
                      FILE_APPEND);
    //sql template --
    $sourceinfo .= $fourspace.'query->parse(kLoad'.$classname.', '
                   .$tablename.', character_guid_, dbversion_);'.LF;
    $sourceinfo .= $fourspace.'result = System::load();'.LF;
    $sourceinfo .= $fourspace.'return result;'.LF;
    $sourceinfo .= $twospace.$functionleave;
    $sourceinfo .= '}'.LF; //load is end
    
    $sourceinfo .= LF; //save
    $sourceinfo .= 'bool '.$classname.'::save(void* source) {'.LF;
    $sourceinfo .= $twospace.$functionenter;
    $sourceinfo .= $fourspace.'bool result = false;'.LF;
    $sourceinfo .= $fourspace.'return result;'.LF;
    $sourceinfo .= $twospace.$functionleave;
    $sourceinfo .= $fourspace.'return false;'.LF;
    $sourceinfo .= '}'.LF; //save
    
    $sourceinfo .= LF; //_delete
    $sourceinfo .= 'bool '.$classname.'::_delete() {'.LF; 
    $sourceinfo .= $twospace.$functionenter;
    $sourceinfo .= $fourspace.'bool result = false;'.LF;
    $sourceinfo .= $fourspace.'DB_QUERY* query = get_internal_query();'.LF;
    $sourceinfo .= $fourspace.'if (!query) Assert(false);'.LF;
    $sourceinfo .= $fourspace.'query->clear();'.LF;
    if ($charactertable){
      $sourceinfo .= $fourspace.'if (!character_guid_) return false;'.LF;
      $sourceinfo .= $fourspace.'query->parse(kDelete'.$tablename.', "'
                     .$tablename.'", character_guid_, dbversion_);'.LF;
    }
    $sourceinfo .= $fourspace.'result = System::_delete();'.LF;
    $sourceinfo .= $fourspace.'return result;'.LF;
    $sourceinfo .= $twospace.$functionleave;
    $sourceinfo .= '}'.LF; //_delete
    
    $sourceinfo .= LF; //parse_result
    $sourceinfo .= 'bool '.$classname.'::parse_result(void* source) {'.LF;
    $sourceinfo .= $twospace.$functionenter;
    $sourceinfo .= $fourspace.'bool result = false;'.LF;
    $enum_fields = $_fields; //next i will chage it
    $enum_fields[0] = $enum_fields[0].' = 1'; //enum first item
    $sourceinfo .= $fourspace.'enum {'.LF;
    $enum_str = implode($enum_fields, ','.LF.$fourspace.$twospace).LF;
    $sourceinfo .= $fourspace.$twospace.$enum_str;
    $sourceinfo .= $fourspace.'}'.LF;
    $sourceinfo .= $fourspace.'return result;'.LF;
    $sourceinfo .= $twospace.$functionleave;
    $sourceinfo .= $fourspace.'return false;';
    $sourceinfo .= '}'.LF; //parse_result
    
    if ($charactertable) {
      $sourceinfo .= LF; //set_character_guid
      $sourceinfo .= 'void '.$classname.'::set_character_guid(uint32_t id) {'
                     .LF;
      $sourceinfo .= $twospace.$functionenter;
      $sourceinfo .= $fourspace.'character_guid_ = id;'.LF;
      $sourceinfo .= $twospace.$functionleave;
      $sourceinfo .= '}'.LF; //set_character_guid
      
      $sourceinfo .= LF; //get_character_guid
      $sourceinfo .= 'uint32 '.$classname.'::get_character_guid() {'.LF;
      $sourceinfo .= $twospace.$functionenter;
      $sourceinfo .= $fourspace.'return character_guid_;'.LF;
      $sourceinfo .= $twospace.$functionleave;
      $sourceinfo .= $fourspace.'return 0;'.LF;
      $sourceinfo .= '}'.LF; //get_character_guid
      
      $sourceinfo .= LF; //set_dbversion
      $sourceinfo .= 'void '.$classname.'::set_dbversion(uint32_t id) {'.LF;
      $sourceinfo .= $twospace.$functionenter;
      $sourceinfo .= $fourspace.'dbversion_ = id;'.LF;
      $sourceinfo .= $twospace.$functionleave;
      $sourceinfo .= '}'.LF; //set_dbversion
      
      $sourceinfo .= LF; //get_dbversion
      $sourceinfo .= 'uint32 '.$classname.'::get_dbversion() {'.LF;
      $sourceinfo .= $twospace.$functionenter;
      $sourceinfo .= $fourspace.'return dbversion_;'.LF;
      $sourceinfo .= $twospace.$functionleave;
      $sourceinfo .= $fourspace.'return 0;'.LF;
      $sourceinfo .= '}'.LF; //get_dbversion
    }
    
    $sourceinfo .= LF.'} //namespace data'.LF;
    $sourceinfo .= LF.'} //namespace pap_server_common_db';
    file_put_contents($this->outputpath_.$headfile, $headinfo, FILE_APPEND);
    file_put_contents($this->outputpath_.$sourcefile, $sourceinfo, FILE_APPEND);
    return $result;
  } 
  
  /**
   * create about database all code file
   * @param void
   * @return void
   */
  public function create_all() {
    if (!$this->split_createfile_) { //clean sigle file
      @unlink($this->outputpath_.'struct.h');
      @unlink($this->outputpath_.'struct.cc');
    }
    if ($this->tablename_) {
      $this->create_structfile(); //struct
      $this->create_db_datafile(); //data
    }
    else { //from db
      $tables = $this->get_tables();
      if (is_array($tables)) {
        foreach ($tables as $k => $table) {
          $this->create_structfile($table); //struct
          $this->create_db_datafile($table); //data
        }
      }
    }
  }
  
  /**
   * get sql instert string
   * @param string $tablename
   * @param string $fileds
   * @return string | bool
   */
  private function get_instertstr($tablename = null, $fileds = null) {
    $result = false;
    $tablename = empty($tablename) ? $this->tablename_ : $tablename;
    if (empty($tablename)) return $result;
    $fileds = is_array($fileds) ? $fileds : $this->get_fields($tablename);
    
    if (is_array($fileds)) {
      $_fields = array();
      foreach ($fileds as $k => $field) {
        array_push($_fields, $field['name']);
      }
      $result = 'INSERT INTO `'.$tablename.'`';
      $result .= ' (`'.implode($_fields, '`,`').'`) VALUES (';
      $format = '';
      foreach ($fileds as $key => $val) {
        $type = dict\db\get_type($val['type']);
        if ('char' == $type) {
          $format .= '%s,';
        }
        else {
          $format .= '%d,';
        }
      }
      $format = substr($format, 0, strlen($format) - 1); //delete the last ','
      $result .= $format.');';
    }
    return $result;
  } 
  
  /**
   * (non-PHPdoc)
   * @see Mysql::__destruct()
   */
  public function __destruct() {
    //do nothing
  }
  
}