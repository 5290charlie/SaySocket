<?php

require_once '../inc/config.inc';

$response = array(
  'success' => false,
  'errors' => array(),
);

try {
  $dbc = new DatabaseConnection();

  if (isset($_POST) && isset($_POST['action'])) {
    switch($_POST['action']) {
      case 'generate':
        if (isset($_POST['email'])) {
          $email = $_POST['email'];

          if (filter_var($email, FILTER_VALIDATE_EMAIL)) {
            $email = $dbc->quote($email);
            $query = "SELECT hash, hits FROM " . DB_TABLE_SIGNUP . " WHERE email='$email'";
            $result = $dbc->getArray($query);

            error_log("CHECKQUERY: $query");

            if (count($result) > 0) {
              $response['success'] = true;
              $response['cmd'] = parse_file_contents('cmd', $result[0]['hash']);
              $response['hits'] = $result[0]['hits'];
            } else {
              $hash = md5($email . mt_rand());
              $query = "INSERT INTO " . DB_TABLE_SIGNUP . " (email, hash) VALUES ('$email', '$hash')";

              error_log("RUNNING QUERY: $query");

              if ($dbc->runQuery($query) > 0) {
                $response['success'] = true;
                $response['cmd'] = parse_file_contents('cmd', $hash);
              } else {
                $response['errors'][] = "Invalid id returned for email: '$email'";
              }
            }
          } else {
            $response['errors'][] = 'Invalid email';
          }
        } else {
          $response['errors'][] = 'Missing email';
        }

        break;
      case 'unsub':
        if (isset($_POST['email'])) {
          $email = $_POST['email'];

          if (filter_var($email, FILTER_VALIDATE_EMAIL)) {
            $email = $dbc->quote($email);
            $query = "DELETE FROM " . DB_TABLE_SIGNUP . " WHERE email='$email'";

            if ($dbc->runQuery($query) !== false) {
              $response['success'] = true;
            } else {
              $response['errors'][] = "Unable to remove: '$email' from the database";
            }
          } else {
            $response['errors'][] = 'Invalid email';
          }
        } else {
          $response['errors'][] = 'Missing email';
        }

        break;
      case 'total':
        $query = 'SELECT SUM(hits) AS total FROM ' . DB_TABLE_SIGNUP;
        $result = $dbc->getArray($query);
        $response['total'] = count($result) > 0 ? $result[0]['total'] : 0;
        $response['success'] = true;
        break;
      default:
        $response['errors'][] = 'Unknown action';
        break;
    }

  }
} catch (Exception $e) {
  $response['errors'][] = $e->getMessage();
}

echo json_encode($response);
