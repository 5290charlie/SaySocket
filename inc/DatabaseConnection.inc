<?php

class DatabaseConnection extends \mysqli {
  private $conn = false;
  private $resp = false;

  private static $required = array(
    'DB_HOSTNAME',
    'DB_USERNAME',
    'DB_PASSWORD',
    'DB_DATABASE',
  );

  public function __construct() {
    foreach (self::$required as $constant) {
      if (!defined($constant)) {
        throw new DatabaseException("Missing required constant ($constant) to initialize class: " . __CLASS__);
      }
    }

    parent::__construct(DB_HOSTNAME, DB_USERNAME, DB_PASSWORD, DB_DATABASE);

    if (mysqli_connect_errno()) {
      throw new DatabaseException('Connection failed: ' . mysqli_connect_errno());
    }
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

  public function reset() {
    if (is_object($this->resp)) {
      $this->resp->close();
    }

    $this->close();

    self::__construct();
  }

  public function runQuery($query, $close = false) {
    if ($this->resp = $this->query($query)) {
      if ($close) {
        $this->reset();
      }

      return $this->insert_id;
    }

    return false;
  }

  public function getCount($query = false, $close = false) {
    if ($query !== false) {
      $this->runQuery($query, false);
    }

    if ($this->resp !== false) {
      $ret = $this->field_count;
    } else {
      $ret = 0;
    }

    if ($close) {
      $this->reset();
    }

    return $ret;
  }

  public function getArray($query = false, $close = false) {
    $arrReturn = array();

    if ($this->getCount($query, false) > 0) {
      while($row = $this->resp->fetch_array(MYSQLI_ASSOC)) {
        $arrReturn[] = $row;
      }
    }

    if ($close) {
      $this->reset();
    }

    return $arrReturn;
  }
}

class DatabaseException extends Exception {
  /**
   * Custom database exception
   */
}
