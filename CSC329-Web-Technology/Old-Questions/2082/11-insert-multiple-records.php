<?php
$server = "localhost";
$username = "root";
$password = "";
$database = "test";
$connection = new mysqli($server, $username, $password, $database);
if ($connection->connect_error)
    die("Connection failed : " . $connection->connect_error);
echo "Connection successful<br>";
$sql1 = "INSERT INTO Students (name) VALUES ('Ram');";
$sql2 = "INSERT INTO Students (name) VALUES ('Sita');";
$sql3 = "INSERT INTO Students (name) VALUES ('Gita');";

if ($connection->multi_query($sql1 . $sql2 . $sql3) === TRUE)
    echo "Records inserted successfully";
else
    echo "Error inserting records : " . $connection->error;
$connection->close();
?>