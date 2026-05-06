<!-- Lab 8: Write a PHP code to update address to ‘Dallu’ whose name is ‘Suresh’. -->
<?php
$server = "localhost";
$username = "root";
$password = "";
$database = "labassignment1";
$connection = new mysqli($server, $username, $password, $database);
if ($connection->connect_error)
    die("Connection failed : " . $connection->connect_error);
echo "Connection successful<br>";
$updateRecord = "UPDATE student SET address='Dallu' WHERE name='Suresh';";
$result = $connection->query($updateRecord);
if (mysqli_affected_rows($connection) > 0)
    echo "Update succesful<br>No of records updated = " . mysqli_affected_rows($connection);
else
    echo "No record updated";
$connection->close();
?>