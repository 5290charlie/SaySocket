<?php

class DatabaseConnection extends PDO {
  private $conn = false;
  private $resp = false;

  private static $required = array(
    'DB_HOSTNAME',
    'DB_USERNAME',
    'DB_PASSWORD',
    'DB_DATABASE',
  );

  // TODO: Fix this hack
  public function quote($string, $paramtype = NULL) {
    return $string;
  }

  public function __construct() {
    foreach (self::$required as $constant) {
      if (!defined($constant)) {
        throw new DatabaseException("Missing required constant ($constant) to initialize class: " . __CLASS__);
      }
    }

    // $dsn = 'mysql:dbname=testdb;host=127.0.0.1'
    $dsn = "mysql:dbname=" . DB_DATABASE . ";host=" . DB_HOSTNAME;

    parent::__construct($dsn, DB_USERNAME, DB_PASSWORD);

    // if (mysqli_connect_errno()) {
    //   throw new DatabaseException('Connection failed: ' . mysqli_connect_errno());
    // }
  }

  public static function &getInstance() {
    static $instance;

    if (!is_object($instance)) {
      $class = __CLASS__;
      $instance = new $class;
      unset($class);
    }

    return $instance;
  }

  // public function reset() {
  //   if (is_object($this->resp)) {
  //     $this->resp->close();
  //   }

  //   $this->close();

  //   self::__construct();
  // }

  public function runQuery($query, $close = false) {
    if ($this->resp = $this->query($query)) {
      // if ($close) {
      //   $this->reset();
      // }

      return $this->lastInsertId();
      // return $this->insert_id;
    }

    return false;
  }

  public function getCount($query = false, $close = false) {
    error_log('getCount query ' . $query);
    if ($query !== false) {
      $this->runQuery($query, false);
    }

    if ($this->resp !== false) {
      $ret = $this->resp->rowCount();
    } else {
      $ret = 0;
    }

    error_log('getCount() returning: '. $ret);

    // if ($close) {
    //   $this->reset();
    // }

    return $ret;
  }

  public function getArray($query = false, $close = false) {
    $arrReturn = array();

    if ($this->getCount($query, false) > 0) {
      while($row = $this->resp->fetchAll(PDO::FETCH_ASSOC)) {
        $arrReturn[] = $row;
      }
    }

    // if ($close) {
    //   $this->reset();
    // }

    return $arrReturn;
  }
}

class DatabaseException extends Exception {
  /**
   * Custom database exception
   */
}
