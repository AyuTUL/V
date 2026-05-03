<!-- Lab 6: Write a PHP code to insert 10 records in the table student. -->
<?php
$server = "localhost";
$username = "root";
$password = "";
$database = "labassignment1";
$connection = new mysqli($server, $username, $password, $database);
if ($connection->connect_error)
    die("Connection failed : " . $connection->connect_error);
echo "Connection successful<br>";
$insertRecords = "INSERT INTO student VALUES
(1,'Abhilekh','Lalitpur','9845678901'),
(2,'Alisha','Chhetrapati','9845678902'),
(3,'Anshu','Dillibazaar','9845678903'),
(4,'Anush','Lalitpur','9845678904'),
(5,'Ashlesha','Swoyambhu','9845678905'),
(6,'Ayush','Bangemuda','9845678906'),
(7,'Ayush','Lalitpur','9845678907'),
(8,'Diya','Kalimati','9845678908'),
(9,'Barsha','Lalitpur','9845678909'),
(10,'Gaurav','Kapan','9845678910');";
if ($connection->query($insertRecords) === TRUE)
    echo "Records inserted successfully";
else
    echo "Error inserting records : " . $connection->error;
$connection->close();
?>