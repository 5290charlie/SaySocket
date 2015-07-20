<?php

error_log('m script');

require_once '../inc/config.inc';

define('REGEX_VALID_IP_ADDRESS', "/^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/");
define('MSG_SUBJECT', 'New SS Portal Opened!');
define('MSG_HEADERS', "From: Server Alerts <alerts@cmr1.com>\r\nX-Mailer: PHP/" . phpversion());

if (isset($_GET) && isset($_GET['ip']) && isset($_GET['port']) && isset($_GET['h'])) {
    error_log('params set');
//	$hash = md5(file_get_contents('ss'));
//
//	if ($_GET['hash'] == $hash) {
//        error_log('valid hash');

		$ip = $_GET['ip'];
		$port = $_GET['port'];

		if (preg_match(REGEX_VALID_IP_ADDRESS, $ip) && is_numeric($port)) {
            $dbc = new DatabaseConnection();
            $user_hash = $dbc->real_escape_string($_GET['h']);
            $query = "SELECT email FROM " . DB_TABLE . " WHERE hash='$user_hash'";
            $result = $dbc->getArray($query);

            if (count($result) > 0) {
                $msg = "SS Portal Opened! IP: $ip, PORT: $port";

                sendMail($result[0]['email'], $msg);

                $query = "UPDATE " . DB_TABLE . " SET hits=hits+1 WHERE hash='$user_hash'";
                $dbc->runQuery($query);
            }
		}
//	}
}

function sendMail($to, $msg) {
    error_log("SENDING MSG TO $to ($msg)");
    mail($to, MSG_SUBJECT, $msg, MSG_HEADERS);
}
