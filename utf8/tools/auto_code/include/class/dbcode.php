<?php
/*
 *  auto_code just use for pap.
 *  @link https://github.com/viticm/pap
 *  @package auto code
 */

/**
 * Description of Mysql
 * about database some code auto create class
 * @author viticm<viticm@126.com>
 * @version 1.0
 */
class DBCode extends Mysql {
  
  private $db_config_; //filename or db config
  private $tablename_;
  private $tableprefix_;
  
  /**
   * constrcut function
   * @param void
   * @return void
   */
  public function __construct() {
    $this->db_config_ = null;
    $this->tablename_ = null;
    $this->tableprefix_ = null;
  }
  
  /**
   * init function, start the object
   * @param array $db_config
   * @param string $tablename
   * @return bool
   */
  public function init(array $db_config, 
                       $tablename = null, 
                       $tableprefix = null) {
    $this->tablename_ = $tablename;
    $this->tableprefix_ = $tableprefix;
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
    $head_info = "";
    $source_info = "";
    $structname = "";
    $structname = $tablename ? $tablename : $this->tablename_;
    if (empty($structname)) return false;
    if (!empty($this->tableprefix_)) 
      $structname = str_replace($this->tableprefix_, '', $structname);
    $head_info .= "struct $structname {\n";
  }
  
  /**
   * (non-PHPdoc)
   * @see Mysql::__destruct()
   */
  public function __destruct() {
    //do nothing
  }
  
}