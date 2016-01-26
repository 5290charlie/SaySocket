<?php

require_once '../inc/config.inc';

if (isset($_GET['v']) && preg_match(REGEX_VIDEO_ID, $_GET['v'])) {
  $ss_config['VIDEO_ID'] = $_GET['v'];
  echo parse_file_contents('video');
}
