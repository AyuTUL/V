<?php
$username='Akash';
$lastname='Biswokarma';
session_start();
$_SESSION['username']=$username;
$_SESSION['lastname']=$lastname;
echo "session started value set";
?>