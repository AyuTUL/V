<!-- Lab 5: Write a PHP code to create a table named ‘student’(roll,name,address,contact) in database labassignment1.  

** insert one record named Suresh and record with address dallu. -->
<?php
$server = "localhost";
$username = "root";
$password = "";
$database = "labassignment1";
$connection = new mysqli($server, $username, $password, $database);
if ($connection->connect_error)
    die("Connection failed : " . $connection->connect_error);
echo "Connection successful<br>";
$createTable = "CREATE TABLE IF NOT EXISTS student (
			roll INT PRIMARY KEY,
			name VARCHAR(20),
			address VARCHAR(15),
			contact CHAR(10)
		);";
$insertRecord = "INSERT INTO student VALUES (7,'Suresh','Dallu','9767488322');";
if ($connection->query($createTable) === TRUE)
    echo "Table created successfully.<br>";
else
    echo "Error creating table.<br>";
if ($connection->query($insertRecord) === TRUE)
    echo "Record inserted successfully.<br>";
else
    echo "Error inserting record.";
$connection->close();
?>