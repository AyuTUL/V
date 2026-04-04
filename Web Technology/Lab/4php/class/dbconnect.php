<?php
$server = "localhost";
$user = "root";
$pass = "";
$conn = new mysqli($server, $user, $pass);
if ($conn->connect_error)
    die("Connection Failed " . $conn->connect_error);
echo "connection succesful<br>";
$sql = "CREATE DATABASE CSIT_A";
if (($conn->query($sql)) === TRUE)
    echo "database created";
else
    echo "database creation failed";
$conn->close();
?>