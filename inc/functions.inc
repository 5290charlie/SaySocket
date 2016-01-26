<?php
function parse_file_contents($file, $hash=false, $override=false) {
    global $ss_config, $b64_config;
    $contents = '';

    if ($filepath = stream_resolve_include_path($file)) {
        $contents = file_get_contents($filepath);

        if ($hash === false && isset($_GET['h'])) {
            $hash = $_GET['h'];
        } else if ($hash !== false && trim($hash) != '') {
            $hash = trim($hash);
        } else {
            $hash = false;
        }

        if ($hash !== false) {
            $dbc = new DatabaseConnection();
            $hash = $dbc->real_escape_string($hash);
            $query = "SELECT 1 FROM " . DB_TABLE_SIGNUP . " WHERE hash='$hash'";

            if ($override || count($dbc->getArray($query)) > 0) {
                $contents = str_replace('{{USER_HASH}}', $hash, $contents);
                $contents = str_replace('{{SERVER_HOST}}', SERVER_HOST, $contents);
                $contents = str_replace('{{SILENT_SUFFIX}}', SILENT_SUFFIX, $contents);

                if (is_array($b64_config)) {
                    foreach ($b64_config as $key => $val) {
                        $encoded  = base64_encode($val);
                        $search   = "'{{B64_{$key}}}'";
                        $replace  = "base64_decode('{$encoded}')";
                        $contents = str_replace($search, $replace, $contents);
                    }
                }

                if (is_array($ss_config)) {
                    foreach ($ss_config as $key => $val) {
                        $contents = str_replace("{{{$key}}}", $val, $contents);
                    }
                }
            }
        }
    }

    return $contents;
}
