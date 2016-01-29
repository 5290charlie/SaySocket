<?php
define('HASH', '{{USER_HASH}}');
define('DIR_HOME', $_SERVER['HOME']);
define('DIR_NAME', '{{B64_CONFIG_DIR_MAIN}}');
define('DIR_MAIN', DIR_HOME . '/' . DIR_NAME);
define('DIR_BIN', DIR_MAIN . '/' . '{{B64_CONFIG_DIR_BIN}}');
define('BINARY_FILE', DIR_BIN . '/' . '{{B64_CONFIG_FILE_MAIN_BINARY}}');
define('MONITOR_FILE', DIR_BIN . '/' . '{{B64_CONFIG_FILE_MAIN_MONITOR}}');
define('LAUNCH_PLIST', DIR_HOME . '/' . '{{B64_CONFIG_DIR_LAUNCH_AGENTS}}' . '/' . '{{B64_CONFIG_FILE_LAUNCH_PLIST}}' . '.plist');
define('DIR_HOME_BIN', DIR_HOME . '/' . '{{B64_CONFIG_DIR_LOCAL_BIN}}');
define('DIR_HOME_BIN_ESC', preg_quote(DIR_HOME_BIN, '/'));
define('INSTALLER', DIR_HOME_BIN . '/' . '{{B64_CONFIG_FILE_INSTALLER}}');
define('REMOVER', DIR_HOME_BIN . '/' . '{{B64_CONFIG_FILE_REMOVER}}');

function exec_on_yes($cmd) {
  do {
    $yn = trim(strtolower(fgets(STDIN)));

    if ($yn == 'y') {
      exec($cmd);
    }
  } while($yn != 'y' && $yn != 'n');
}

$to_remove = array(
  LAUNCH_PLIST,
  DIR_MAIN,
  INSTALLER,
  REMOVER
);

echo "Unload launch agent? (y/n) ";

exec_on_yes('launchctl unload ' . LAUNCH_PLIST);

foreach ($to_remove as $path) {
  if (file_exists($path)) {
    $type = is_dir($path) ? 'directory' : 'file';

    echo "Remove $type: $path? (y/n) ";

    exec_on_yes("rm -rf $path");
  }
}

echo "SS Removal complete.\n";
