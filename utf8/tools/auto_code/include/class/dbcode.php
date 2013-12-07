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
  
  /**
   * constrcut function
   * @param void
   * @return void
   */
  public function __construct() {
    $this->db_config_ = null;
    $this->tablename_ = null;
  }
  
  /**
   * init function, start the object
   * @param array $db_config
   * @param string $tablename
   * @return bool
   */
  public function init(array $db_config, $tablename = null) {
    if(!empty($tablename)) $this->tablename_ = $tablename;
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
  }
  
  /**
   * (non-PHPdoc)
   * @see Mysql::__destruct()
   */
  public function __destruct() {
    //do nothing
  }
  
}