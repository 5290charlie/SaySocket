<?php
require_once '../inc/config.inc';

$dbc = new DatabaseConnection();
$user_hash = $dbc->real_escape_string($_GET['h']);
$query = "SELECT email FROM " . DB_TABLE . " WHERE hash='$user_hash'";
$result = $dbc->getArray($query);
$email = 'Email';

if (count($result) > 0) {
    $email = $result[0]['email'];
} else {
    header('Location: /');
    exit();
}
?>

<!doctype html>
<html lang="es">
    <head>
        <meta charset="utf-8" />
        <meta http-equiv="X-UA-Compatible" content="IE=edge" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />

        <title>Say Socket | Unsubscribe</title>

        <link rel="apple-touch-icon" sizes="57x57" href="/apple-icon-57x57.png">
        <link rel="apple-touch-icon" sizes="60x60" href="/apple-icon-60x60.png">
        <link rel="apple-touch-icon" sizes="72x72" href="/apple-icon-72x72.png">
        <link rel="apple-touch-icon" sizes="76x76" href="/apple-icon-76x76.png">
        <link rel="apple-touch-icon" sizes="114x114" href="/apple-icon-114x114.png">
        <link rel="apple-touch-icon" sizes="120x120" href="/apple-icon-120x120.png">
        <link rel="apple-touch-icon" sizes="144x144" href="/apple-icon-144x144.png">
        <link rel="apple-touch-icon" sizes="152x152" href="/apple-icon-152x152.png">
        <link rel="apple-touch-icon" sizes="180x180" href="/apple-icon-180x180.png">
        <link rel="icon" type="image/png" sizes="192x192"  href="/android-icon-192x192.png">
        <link rel="icon" type="image/png" sizes="32x32" href="/favicon-32x32.png">
        <link rel="icon" type="image/png" sizes="96x96" href="/favicon-96x96.png">
        <link rel="icon" type="image/png" sizes="16x16" href="/favicon-16x16.png">
        <link rel="manifest" href="/manifest.json">
        <meta name="msapplication-TileColor" content="#ffffff">
        <meta name="msapplication-TileImage" content="/ms-icon-144x144.png">
        <meta name="theme-color" content="#ffffff">

        <link rel="stylesheet" type="text/css" href="css/reset.css" />
        <link rel="stylesheet" type="text/css" href="css/bootstrap.min.css" />
        <link rel="stylesheet" type="text/css" href="css/bootstrap-theme.min.css" />
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
                        <h1>Say Socket <span class="total-wrap"><span class="total"></span> trolled!</span></h1>
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
                <div class="row unsub-info">
                    <div class="col-xs-12">
                        <p>Please confirm the email address to be removed from the Say Socket database:</p>
                    </div>
                </div>
                <div class="row unsub-info">
                    <div class="col-xs-12">
                        <form method="post" data-action="unsub">
                            <div class="form-group">
                                <label class="sr-only" for="email">Email address</label>
                                <input id="email" type="email" name="email" class="form-control form-input" readonly value="<?php echo $email; ?>"/>
                            </div>
                            <button type="submit" class="btn btn-success form-control">Confirm</button>
                        </form>
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
