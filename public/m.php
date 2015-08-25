<?php

require_once '../inc/config.inc';

define('REGEX_VALID_IP_ADDRESS', "/^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/");
define('MSG_SUBJECT', 'New SS Portal Opened!');
define('MSG_HEADERS', "From: Say Socket Alerts <alerts@saysocket.com>\r\nX-Mailer: PHP/" . phpversion());

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

            $msg = "
                SS Portal Opened! IP: $ip, PORT: $port\n\n
                Connection command:\n
                 $ telnet $ip $port\n\n\n
                To remove your email from the Say Socket database, visit: " . SERVER_HOST . "u.php?h=$user_hash";

            sendMail($email, $msg);

            $query = "UPDATE " . DB_TABLE_SIGNUP . " SET hits=hits+1 WHERE hash='$user_hash'";
            $dbc->runQuery($query);
        }
    }
}

function sendMail($to, $msg) {
    error_log("SENDING MSG TO $to ($msg)");
    mail($to, MSG_SUBJECT, $msg, MSG_HEADERS);
}
