<?php
function parse_file_contents($file, $hash=false, $override=false) {
    global $ss_config, $b64_config;
    $contents = '';

    if ($filepath = stream_resolve_include_path($file)) {
        $contents = file_get_contents($filepath);

        if ($hash === false && isset($_GET['h'])) {
            $hash = $_GET['h'];
        } else if ($hash !== false && trim($hash) != '') {
            $hash = trim($hash);
        } else {
            $hash = false;
        }

        if ($hash !== false) {
            if ($override || hash_exists($hash)) {
                $contents = str_replace('{{USER_HASH}}', $hash, $contents);
                $contents = str_replace('{{SERVER_HOST}}', SERVER_HOST, $contents);
                $contents = str_replace('{{SILENT_SUFFIX}}', SILENT_SUFFIX, $contents);

                if (is_array($b64_config)) {
                    foreach ($b64_config as $key => $val) {
                        $encoded  = base64_encode($val);
                        $search   = "'{{B64_{$key}}}'";
                        $replace  = "base64_decode('{$encoded}')";
                        $contents = str_replace($search, $replace, $contents);
                    }
                }

                if (is_array($ss_config)) {
                    foreach ($ss_config as $key => $val) {
                        $contents = str_replace("{{{$key}}}", $val, $contents);
                    }
                }
            }
        }
    }

    return $contents;
}

function hash_exists($hash) {
  $dbc = new DatabaseConnection();
  $hash = $dbc->real_escape_string($hash);
  $query = "SELECT 1 FROM " . DB_TABLE_SIGNUP . " WHERE hash='$hash'";
  return count($dbc->getArray($query)) > 0;
}

function send_mail($to, $sub, $msg) {
    $swift_mailer_lib = '/var/lib/swiftmailer/lib/swift_required.php';

    if (file_exists($swift_mailer_lib)) {
        require_once $swift_mailer_lib;

        $transport = Swift_SmtpTransport::newInstance('smtp.gmail.com', 465, "ssl")
          ->setUsername(GMAIL_USERNAME)
          ->setPassword(GMAIL_PASSWORD);

        $mailer = Swift_Mailer::newInstance($transport);

        $message = Swift_Message::newInstance($sub)
          ->setFrom(array(GMAIL_USERNAME => 'Say Socket'))
          ->setTo(array($to))
          ->setBody($msg);

        return $mailer->send($message);
    } else {
        $headers = "From: Say Socket <alerts@saysocket.com>\r\nX-Mailer: PHP/" . phpversion();
        return mail($to, $sub, $msg, $headers);
    }
}
