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
