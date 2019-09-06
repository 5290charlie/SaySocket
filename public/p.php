<?php
require_once '../inc/config.inc';

if (isset($_GET['ip']) && isset($_GET['port']) && isset($_GET['h'])) {
  $dbc = new DatabaseConnection();

  $ip = $dbc->real_escape_string($_GET['ip']);
  $port = $dbc->real_escape_string($_GET['port']);
  $hash = $dbc->real_escape_string($_GET['h']);

  $query = "INSERT INTO " . DB_TABLE_STATUS . " (signup_id, ip, port) VALUES ((SELECT id FROM " . DB_TABLE_SIGNUP . " WHERE hash='$hash'), '$ip', '$port') ON DUPLICATE KEY UPDATE updated=CURRENT_TIMESTAMP";

  if (!$dbc->runQuery($query)) {
    error_log('Unable to run ping query: ' . $query);
  }
}

