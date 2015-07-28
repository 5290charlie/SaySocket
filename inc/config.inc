<?php
$protocol = (!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off' || $_SERVER['SERVER_PORT'] == 443) ? "https://" : "http://";

define('SERVER_HOST', $protocol . $_SERVER['HTTP_HOST'] . '/');

require_once 'settings.inc';
require_once 'DatabaseConnection.inc';
require_once 'functions.inc';
