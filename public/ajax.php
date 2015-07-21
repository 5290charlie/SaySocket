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
                        $email = $dbc->real_escape_string($email);
                        $query = "SELECT hash, hits FROM " . DB_TABLE . " WHERE email='$email'";
                        $result = $dbc->getArray($query);

                        if (count($result) > 0) {
                            $response['success'] = true;
                            $response['cmd'] = parse_file_contents('cmd', $result[0]['hash']);
                            $response['hits'] = $result[0]['hits'];
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

                break;
            case 'total':
                $query = 'SELECT SUM(hits) AS total FROM ' . DB_TABLE;
                $result = $dbc->getArray($query);
                $response['total'] = $result[0]['total'];
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