<!-- Lab 10: Write PHP code to fetch the data from HTML form and display using POST and GET method.(also use $_SERVER). -->
<?php
if ($_SERVER['REQUEST_METHOD'] === "GET" && isset($_GET['roll'], $_GET['name'], $_GET['address'], $_GET['contact'])) {
    $roll = $_GET['roll'];
    $name = $_GET['name'];
    $address = $_GET['address'];
    $contact = $_GET['contact'];

    $server = "localhost";
    $username = "root";
    $password = "";
    $database = "labassignment1";
    $connection = new mysqli($server, $username, $password, $database);

    if ($connection->connect_error)
        die("Connection failed : " . $connection->connect_error);
    echo "Connection successful<br>";
    $insertRecord = "INSERT INTO student(roll,name,address,contact)VALUES('$roll','$name','$address','$contact');";
    if ($connection->query($insertRecord) === TRUE)
        echo "Records inserted successfully";
    else
        echo "Error inserting record: " . $connection->error;
}
?>
<html>

<head>
    <title>Student Registration Form</title>
</head>

<body>
    <h1>Student Registration</h1>
    <form action="" method="GET" name="studentForm">
        <label>Enter your roll number : </label><input type="number" name="roll"><br>
        <label>Enter your name : </label><input type="text" name="name"><br>
        <label>Enter your address : </label><input type="text" name="address"><br>
        <label>Enter your contact number : </label><input type="text" name="contact"><br><br>
        <input type="submit">
    </form>

</html>