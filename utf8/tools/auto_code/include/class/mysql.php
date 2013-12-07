<?php
/*
 *  auto_code just use for pap.
 *  @link        http://www.gzpindian.com/
 *  @package     mergeserver
 */

/**
 * Description of Mysql
 * Mysql 数据库相关类
 * @author viticm<viticm@126.com>
 * @version 1.1
 */
class Mysql {
  private static $conn = null;
  private $query_result;
  private $rows;
  private $host;
  private $user;
  private $password;
  private $db_name;
  private $charset = 'utf8';
  public  $connect;
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
    $this->host = $config['host'];
    $this->user = $config['user'];
    $this->password = $config['password'];
    $this->db_name = $config['dbname'];
    if (!empty($config['charset'])) $this->charset = $config['charset'];
    if (!is_resource($this->conn)) {
      $link = mysql_connect($this->host, $this->user, $this->password);
      if (!$link){
        $this->connect = false;
        if( true === $debug ) {
          throw new Exception("create connect error :" . mysql_error());
        }
      }
      $this->conn = $link;
      if ($this->dbb_name) {
        if (!mysql_select_db($this->db_name, $link)) {
          $this->connect = false;
            if (true === $debug) {
              throw new Exception("select db error: " . mysql_error());
            }
          }
      }
      mysql_query('set names '.$this->charset, $link);
      $this->bConnect = true;
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
    $this->query_result = mysql_query($sql, $this->conn);
    if (false === $this->query_result) {
      file_put_contents(self::LOG_FILE, 
                        '[' .date('Y-m-d H:i:s'). '] query error in ('.$sql.')'
                        ."\n".'get error[' .mysql_error(). "]\n", 
                        FILE_APPEND);
      if (true === $debug)
        throw new Exception("exceute error, sql= {$sql} ;" .mysql_error());
    }
    return $this->query_result;
  }

  /**
   * 执行select语句并返回结果
   * @param string $sql
   * @return array or bool
   */
  public function fetch_all($sql) {
    $this->query($sql);
    return $this->get_all($this->query_result);
  }
    /**
     *
     * 执行查询，并返回所有结果
     * @param $string $sql
     * @return array or bool
     */
  public function fetch_one($sql) {
    $this->query($sql);
    return $this->get_one($this->query_result);
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
    if ($this->query_result) {
      $result =  mysql_fetch_assoc($this->query_result);
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
    if ($this->query_result) {
      $this->rows = array();
      while (($row = mysql_fetch_assoc($this->query_result)) !== false) {
        array_push($this->rows, $row);
      }
      return $this->rows;
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
    if( !$this->connect ) return false;
    $cmd  = '';
    $cmd .= 'mysql -u' .$this->user. ' -h' 
                .$this->host. ' -p'.$this->password;
    $cmd .= ' ' .$this->db_name. ' < ' .$sqlfile;
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
    if(false === $this->connect) return false;
    $filename = '' == $filename ? $this->db_name.'.sql' : $filename;
    $cmd .= 'mysqldump -u' .$this->user. ' -h' .$this->host
            . ' -p' .$this->password;
    $cmd .= ' --default-character-set=' .$this->charset
            . ' --opt --extended-insert=false --single-transaction';
    $cmd .= ' ' .$this->db_name. ' > ' .$path.DIRECTORY_SEPARATOR.$filename;
    return '' == exec($cmd) ? true : false; // null then is success
  }

  /**
   * get last instsert id
   * @param void
   * @return number
   */
  public function get_last_insert_id() {
    return mysql_insert_id($this->conn);
  }

  /**
   * 析构函数
   */
  public function __destruct() {
    if (is_resource($this->query_result)) {
      mysql_free_result($this->query_result);
    }
    mysql_close($this->conn);
  }
}
