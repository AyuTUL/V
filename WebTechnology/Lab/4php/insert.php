<?php
$server = "localhost";
$user = "root";
$pass = "";
$db = "CSIT_A";
$conn = new mysqli($server, $user, $pass, $db);
if ($conn->connect_error)
    die("Connection Failed " . $conn->connect_error);
echo "connection succesful<br>";
$sql = "INSERT INTO employee(eid,name)VALUES(1,'Nirjala'),(2,'Nirjal');";
if (($conn->query($sql)) === TRUE)
    echo "record inserted";
else
    echo "insertion failed";
$conn->close();
?>