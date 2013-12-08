<?php
/*
 *  auto_code just use for pap.
 *  @link https://github.com/viticm/pap
 *  @package auto code
 */

/**
 * Description of Mysql
 * Mysql 数据库相关类
 * @author viticm<viticm@126.com>
 * @version 1.1
 */
class Mysql {
  private $conn_ = null;
  private $query_result_;
  private $rows_;
  private $host_;
  private $user_;
  private $password_;
  private $db_name_;
  private $charset_ = 'utf8';
  public  $connect_;
  const LOG_FILE = './mysql.log' ;

  /**
   *
   * @desc 连接数据库
   * @param array $config 数据库连接数组
   * @param bool $debug 是否为调试模式，如果是则抛出错误，否则失败时返回false
   * @throws Exception
   * @return void
   */
  public function connect($config, $debug = false) {
    $this->host_ = $config['host'];
    $this->user_ = $config['user'];
    $this->password_ = $config['password'];
    $this->db_name_ = $config['db_name'];
    if (!empty($config['charset'])) $this->charset_ = $config['charset'];
    if (!is_resource($this->conn_)) {
      $link = mysql_connect($this->host_, $this->user_, $this->password_);
      if (!$link){
        $this->connect_ = false;
        if( true === $debug ) {
          throw new Exception("create connect error :" . mysql_error());
        }
      }
    }
    if (is_resource($link)) {
      $this->conn_ = $link;
      if ($this->db_name_) {
        if (!mysql_select_db($this->db_name_, $link)) {
          $this->connect_ = false;
          if (true === $debug) {
            throw new Exception("select db error: " . mysql_error());
          }
        }
      }
      mysql_query('set names '.$this->charset_, $link);
      $this->connect_ = true;
    }
  }

  /**
   * 执行sql语句，并返回Resource
   * @param string $sql 查询sql字符串
   * @param bool $bDebug 是否为调试模式，如果是则抛出错误，否则失败时返回false
   * @throws Exception
   * @return resource
   */
  public function query($sql, $debug = false) {
    if(!$this->connect_) return false;
    $this->query_result_ = mysql_query($sql, $this->conn_);
    if (false === $this->query_result_) {
      file_put_contents(self::LOG_FILE, 
                        '[' .date('Y-m-d H:i:s'). '] query error in ('.$sql.')'
                        ."\n".'get error[' .mysql_error(). "]\n", 
                        FILE_APPEND);
      if (true === $debug)
        throw new Exception("exceute error, sql= {$sql} ;" .mysql_error());
    }
    return $this->query_result_;
  }

  /**
   * 执行select语句并返回结果
   * @param string $sql
   * @return array or bool
   */
  public function fetch_all($sql) {
    $this->query($sql);
    return $this->get_all($this->query_result_);
  }
    /**
     *
     * 执行查询，并返回所有结果
     * @param $string $sql
     * @return array or bool
     */
  public function fetch_one($sql) {
    $this->query($sql);
    return $this->get_one($this->query_result_);
  }

  /**
   *
   * @desc 从结果集中获取一条信息
   * @param obj $result 结果集
   * @param bool $debug 是否为调试模式，如果是则抛出错误，否则失败时返回false
   * @throws Exception
   * @return bool or array
   */
  public function get_one($result, $debug = false) {
    if ($this->query_result_) {
      $result =  mysql_fetch_assoc($this->query_result_);
      if (!$result) {
        return array();
      }
      return $result;
    }
    if (true === $debug) {
        throw new Exception('can not excute sql');
    }
    else {
      return false;
    }
  }
  /**
   *
   * @desc 从结果集中获得所有信息
   * @param obj $result 结果集
   * @param bool $debug 是否为调试模式，如果是则抛出错误，否则失败时返回false
   * @throws Exception
   * @return bool or array
   */
  public function get_all($result, $debug = false) {
    if ($this->query_result_) {
      $this->rows_ = array();
      while (($row = mysql_fetch_assoc($this->query_result_)) !== false) {
        array_push($this->rows_, $row);
      }
      return $this->rows_;
    }
    if (true === $debug) {
        throw new Exception('get query_result error ');
    }
    else {
      return false;
    }
  }

  /**
   * truncate table
   * @param string $tablename
   * @return bool
   */
  public function truncate_table( $tablename )
  {
      $sql = '';
      $sql .= 'TRUNCATE TABLE `' .$tablename. '`';
      return $this->query($sql);
  }

  /**
   * @desc auto source sql file 
   * @desc (work in linux, also can work in windows but you will test it)
   * @param string $sqlfile
   * @return bool
   * @access public
   */
  public function source_sqlfile($sqlfile) {
    if(!$this->connect_) return false;
    $cmd  = '';
    $cmd .= 'mysql -u' .$this->user_. ' -h' 
            .$this->host_. ' -p'.$this->password_;
    $cmd .= ' ' .$this->db_name_. ' < ' .$sqlfile;
    return '' == exec($sqlfile) ? true : false; // null then is success
  }

  /**
   * dump linux db file 
   * (work in linux, also can work in windows but you will test it)
   * @param string $path
   * @param string $filename
   * @return bool
   * @access public
   */
  public function dump_db($path, $filename = '') {
    if(false === $this->connect_) return false;
    $filename = '' == $filename ? $this->db_name_.'.sql' : $filename;
    $cmd .= 'mysqldump -u' .$this->user_. ' -h' .$this->host_
            . ' -p' .$this->password_;
    $cmd .= ' --default-character-set=' .$this->charset_
            . ' --opt --extended-insert=false --single-transaction';
    $cmd .= ' ' .$this->db_name_. ' > ' .$path.DIRECTORY_SEPARATOR.$filename;
    return '' == exec($cmd) ? true : false; // null then is success
  }

  /**
   * get last instsert id
   * @param void
   * @return number
   */
  public function get_last_insert_id() {
    return mysql_insert_id($this->conn_);
  }
  
  /**
   * get tables name as array of database
   * @param void
   * @return mixed
   */
  public function get_tables() {
    $result = array();
    $sql = 'SHOW TABLES';
    $row = $this->fetch_all($sql);
    if(is_array($row)) {
      $_key = 'Tables_in_'.$this->db_name_;
      foreach ($row as $key => $val) {
        array_push($result, $val[$_key]);
      }
    }
    else {
      $result = $row;
    }
    return $result;
  }
  
  /**
   * get table fields
   * @param string $tablename
   * @return array
   */
  public function get_fields($tablename) {
    $result = array();
    $sql = 'SHOW COLUMNS FROM '.$tablename;
    $row = $this->fetch_all($sql);
    if(is_array($row)){
      foreach ($row as $key => $val) {
        $field = $val['Field'];
        $_type = $val['Type'];
        $default = $val['Default'];
        $start = strpos($_type, '(') + 1;
        $end = strpos($_type, ')') - strpos($_type, '(') - 1;
        $length = $start != 1 && $end != -1 ? substr($_type, $start, $end) : 0;
        $type = str_replace('('.$length.')', '', $_type);
        $info = array(
          'name' => $field, 'type' => $type, 'length' => $length,
          'default' => $default
        );
        array_push($result, $info);
      }
    }
    return $result;
  }

  /**
   * 析构函数
   */
  public function __destruct() {
    if (is_resource($this->query_result_)) {
      mysql_free_result($this->query_result_);
    }
    if(is_resource($this->conn_)) mysql_close($this->conn_);
  }
}
