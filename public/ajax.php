<?php

require_once '../inc/config.inc';

$response = array(
    'success' => false,
    'errors' => array(),
);

try {
    if (isset($_POST) && isset($_POST['email'])) {
        $email = $_POST['email'];

        if (filter_var($email, FILTER_VALIDATE_EMAIL)) {
            $dbc = new DatabaseConnection();
            $email = $dbc->real_escape_string($email);
            $query = "SELECT hash FROM " . DB_TABLE . " WHERE email='$email'";
            $result = $dbc->getArray($query);

            if (count($result) > 0) {
                $response['success'] = true;
                $response['cmd'] = parse_file_contents('cmd', $result[0]['hash']);
            } else {
                $hash = substr(md5($email . mt_rand()), 0, 16);
                $query = "INSERT INTO " . DB_TABLE . " (email, hash) VALUES ('$email', '$hash')";

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
    }
} catch (Exception $e) {
    $response['errors'][] = $e->getMessage();
}

echo json_encode($response);