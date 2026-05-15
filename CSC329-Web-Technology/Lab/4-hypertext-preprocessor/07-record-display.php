<!-- Lab 7: Write a PHP code to display all records in the table student. -->
<?php
$server = "localhost";
$username = "root";
$password = "";
$database = "labassignment1";
$connection = new mysqli($server, $username, $password, $database);
if ($connection->connect_error)
    die("Connection failed : " . $connection->connect_error);
echo "Connection successful<br>";
$displayRecords = "SELECT roll, name, address, contact FROM student;";
$result = $connection->query($displayRecords);
if (mysqli_num_rows($result) == 0)
    echo "No records found.";
else {
    echo "<table border='1' cellpadding='10'><tr><th>Roll</th><th>Name</th><th>Address</th><th>Contact</th></tr>";
    while ($row = $result->fetch_object()) {
        echo "<tr><td>";
        echo $row->roll;
        echo "</td><td>";
        echo $row->name;
        echo "</td><td>";
        echo $row->address;
        echo "</td><td>";
        echo $row->contact;
        echo "</td></tr>";

    }
    echo "</table>";
}
$connection->close();
?>