<?php

define('SERVER_HOST', 'http://test.dev/t/');

define('DB_HOSTNAME', 'localhost');
define('DB_USERNAME', 'test');
define('DB_PASSWORD', 'test');
define('DB_DATABASE', 'testing');

define('DB_TABLE', 't');

require_once 'DatabaseConnection.inc';

function parse_file_contents($file, $hash=false, $override=false) {
    if (file_exists($file)) {
        if ($hash === false && isset($_GET['h'])) {
            $hash = $_GET['h'];
        } else if ($hash !== false && trim($hash) != '') {
            $hash = trim($hash);
        } else {
            $hash = false;
        }

        if ($hash !== false) {
            $dbc = new DatabaseConnection();
            $hash = $dbc->real_escape_string($hash);
            $query = "SELECT 1 FROM " . DB_TABLE . " WHERE hash='$hash'";

            if ($override || count($dbc->getArray($query)) > 0) {
                $contents = file_get_contents($file);

                return str_replace('{{SERVER_HOST}}', SERVER_HOST, str_replace('{{USER_HASH}}', $hash, $contents));
            }
        }
    }

    return '';
}
