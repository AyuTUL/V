<?php
$server = "localhost";
$user = "root";
$pass = "";
$db = "CSIT_A";
$conn = new mysqli($server, $user, $pass, $db);
if ($conn->connect_error)
    die("Connection Failed: " . $conn->connect_error);
echo "Connection successful<br>";
$sql = "CREATE TABLE employee (
    eid INT PRIMARY KEY,
    name VARCHAR(20)
)";
if ($conn->query($sql) === TRUE)
    echo "Table created successfully";
else
    echo "Table creation failed: " . $conn->error;
$conn->close();
?>