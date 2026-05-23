<!-- Lab 4: Write a PHP code to create a database named ‘labassignment1’. -->
<?php
$server = "localhost";
$username = "root";
$password = "";
$connection = new mysqli($server, $username, $password);
if ($connection->connect_error)
    die("Connection failed : " . $connection->error);
echo "Connection successful<br>";
$createDatabase = "CREATE DATABASE IF NOT EXISTS labassignment1";
if ($connection->query($createDatabase) === TRUE)
    echo "Database labassignment1 created successfully";
else
    echo "Error creating database: " . $connection->error;
$connection->close();
?>