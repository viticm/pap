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
    $headinfo = '';
    $sourceinfo = '';
    $headfile = '';
    $sourcefile = '';
    $classname = '';
    $tablename = $tablename ? $tablename : $this->tablename_;
    if (empty($tablename)) return false;
    $classname = ucwords($tablename);
    if (!empty($this->tableprefix_))
      $classname = ucwords(str_replace($this->tableprefix_, 
                                       '', 
                                       $tablename));
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
                 .strtoupper($classname).'_H_'.LF;
    $headinfo .= '#define PAP_SERVER_COMMON_DB_'
                 .strtoupper($classname).'_H_'.LF;
    
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
    
    if ($charactertable) {
      $headinfo .= $public;
      $headinfo .= $threespace.'void set_characterguid(uint32_t id);'.LF;
      $headinfo .= $threespace.'uint32_t get_characterguid();'.LF;
      $headinfo .= $threespace.'void set_dbversion(uint32_t id);'.LF;
      $headinfo .= $threespace.'uint32_t get_dbversion();'.LF;
    }
    $headinfo .= LF.'}'.LF; //class end
    $headinfo .= LF.'}; //namespace data';
    $headinfo .= '}; //namespace pap_server_common_db';
    
    $headinfo .= '#endif //PAP_SERVER_COMMON_DB_'
                 .strtoupper($classname).'_H_'.LF;
    
    $sourceinfo .= $classname.'::'.$classname.
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
    
    $sourceinfo .= $classname.'::~'.$classname.'() {'.LF;
    $sourceinfo .= $twospace.'//do nothing'.LF;
    $sourceinfo .= '}'.LF;
    
    $sourceinfo .= 'bool load() {'.LF;
    $sourceinfo .= $twospace.$functionenter;
    $sourceinfo .= $fourspace.'DB_QUERY* query = get_internal_query();'.LF;
    $sourceinfo .= $fourspace.'if (!query) Assert(false);'.LF;
    $sourceinfo .= $fourspace.'query->clear();'.LF;
    
    //-- sql template
    $sql_template_headfile = 'sql_template.h';
    $sql_template_sourcefile = 'sql_template.cc';
    $sql_template_headinfo = '';
    $sql_template_sourceinfo = '';
    //load select, delete --, update --, save update, add instert
    $sql_template_headinfo .= 'extren const char* kLoad'.$classname.LF;
    $sql_template_headinfo .= 'extren const char* kDelete'.$classname.LF;
    $sql_template_headinfo .= 'extren const char* kUpdate'.$classname.LF;
    $sql_template_headinfo .= 'extren const char* kAdd'.$classname.LF;
    $sql_template_headinfo .= 'extren const char* kSave'.$classname.LF;
    $sql_template_headinfo .= LF; //wrap
    
    $fields = $this->get_fields($tablename);
    
    //在这里生成mysql的模板
    if ($charactertable) {
      $sourceinfo .= $fourspace
                     .'if (INVALID_ID == character_guid_) return false;'.LF;
      $_fields = array_keys($fields);
      $sql_template_sourceinfo .= 'kLoad'.$classname.' = '.LF
                                  .'"SELECT '.implode($_fields, ',').'FROM `'
                                  .$tablename.'` WHERE `character_guid` = %d'
                                  .' AND `dbversion` = %d";'.LF;
    }
    else {
      $sql_template_sourceinfo .= 'kLoad'.$classname.' = '.LF
                                  .'SELECT * FROM `'.$tablename.';`'.LF;
    }
    $sql_template_sourceinfo .= 'kDelete'.$classname.' = "";'.LF;
    $sql_template_sourceinfo .= 'kUpdate'.$classname.' = "";'.LF;
    $insert_sql = $this->get_instertstr($tablename, $fields);
    $sql_template_sourceinfo .= 'kAdd'.$classname.' = "'.$insert_sql.'";'.LF;
    $sql_template_sourceinfo .= 'kSave'.$classname.' = "";'.LF;
    file_put_contents($this->outputpath_.$sql_template_headfile, 
                      $sql_template_headinfo,
                      FILE_APPEND);
    file_put_contents($this->outputpath_.$sql_template_sourcefile,
                      $sql_template_sourceinfo,
                      FILE_APPEND);
    
    //sql template --
    $sourceinfo .= $twospace.$functionleave;
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
    }
    else { //from db
      $tables = $this->get_tables();
      if (is_array($tables)) {
        foreach ($tables as $k => $table) {
          $this->create_structfile($table); //struct
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
      $_field = array_keys($fileds);
      $result = 'INSERT INTO `'.$tablename.'`';
      $result .= ' ('.implode($_field, ',').') VALUES (';
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