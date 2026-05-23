<!-- Lab 9: Write PHP code to delete the records whose address is Lalitpur. -->
<?php
$server = "localhost";
$username = "root";
$password = "";
$database = "labassignment1";
$connection = new mysqli($server, $username, $password, $database);
if ($connection->connect_error)
    die("Connection failed : " . $connection->connect_error);
echo "Connection successful<br>";
$deleteRecord = "DELETE FROM student WHERE address='Lalitpur';";
$result = $connection->query($deleteRecord);
if (mysqli_affected_rows($connection) > 0)
    echo "Delete successful<br>No. of records deleted = " . mysqli_affected_rows($connection);
else
    echo "No record deleted";
$connection->close();
?>