<?php

require_once '../inc/config.inc';

if (isset($_GET) && isset($_GET['ip']) && isset($_GET['port']) && isset($_GET['h'])) {
  $ip = $_GET['ip'];
  $port = $_GET['port'];

  if (preg_match(REGEX_VALID_IP_ADDRESS, $ip) && is_numeric($port)) {
    $dbc = new DatabaseConnection();
    $user_hash = $dbc->real_escape_string($_GET['h']);
    $query = "SELECT email FROM " . DB_TABLE_SIGNUP . " WHERE hash='$user_hash'";
    $result = $dbc->getArray($query);

    if (count($result) > 0) {
      $email = $result[0]['email'];
      $subject = 'New SS Portal Opened!';

      $msg = "
        SS Portal Opened! IP: $ip, PORT: $port\n\n
        Connection command:\n
         $ telnet $ip $port\n\n\n
        To remove your email from the Say Socket database, visit: " . SERVER_HOST . "u.php?h=$user_hash";

      send_mail($email, $subject, $msg);

      $query = "UPDATE " . DB_TABLE_SIGNUP . " SET hits=hits+1 WHERE hash='$user_hash'";
      $dbc->runQuery($query);
    }
  }
}
