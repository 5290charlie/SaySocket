<?php

require_once '../inc/config.inc';

$version = trim(parse_file_contents('version'));

if ($version != '' && isset($_GET['v']) && preg_match(REGEX_VALID_VERSION, $_GET['v'])) {
  $server = explode('.', $version);
  $client = explode('.', $_GET['v']);

  foreach ($client as $i => $num) {
    if (isset($server[$i]) && $num < $server[$i]) {
      echo $version;
      break;
    }
  }
}
