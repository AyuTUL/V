<!-- Q B.1: Create HTML pages with two buttons register and show details.
    Create HTML page for registration page of student with appropriate attributes. On pressing submit button it must store the entered contents into the database named ‘viva’ and table named ‘info’. 
    Create HTML page that shows the details entered by users in appropriate format
 -->
<?php
$conn = new mysqli("localhost", "root", "", "viva");
if ($conn->connect_error)
    die("Connection error" . $conn->connect_error);

$message = "";
$result = null;

if (isset($_POST["register"])) {
    $name = $_POST["name"];
    $college = $_POST["college"];
    $email = $_POST["email"];
    $phone = $_POST["phone"];

    $sql = "INSERT INTO info(name, college, email, phone) VALUES('$name', '$college', '$email', '$phone')";
    if ($conn->query($sql) === TRUE)
        $message = "Record inserted";
    else
        $message = "Insertion failed";
}

if (isset($_POST["show"])) {
    $sql = "SELECT * FROM info";
    $result = $conn->query($sql);
}
?>
<html>

<head>
    <title>College Registration</title>
</head>

<body>
    <h2>College Registration</h2>
    <form method="post">
        Student Name: <input type="text" name="name" required><br><br>
        College Name: <input type="text" name="college" required><br><br>
        Email: <input type="email" name="email" required><br><br>
        Phone: <input type="text" name="phone" required><br><br>
        <input type="submit" name="register" value="Register">
        <input type="submit" name="show" value="Show Details" formnovalidate>
    </form>

    <p><?php echo $message; ?></p>

    <?php
    if ($result != null) {
        if ($result->num_rows == 0) {
            echo "no records";
        } else {
            echo "<table border='1' cellpadding='8' cellspacing='0'><tr><th>ID</th><th>Name</th><th>College</th><th>Email</th><th>Phone</th></tr>";
            while ($row = $result->fetch_object()) {
                echo "<tr><td>" . htmlspecialchars($row->id) . "</td><td>" . htmlspecialchars($row->name) . "</td><td>" . htmlspecialchars($row->college) . "</td><td>" . htmlspecialchars($row->email) . "</td><td>" . htmlspecialchars($row->phone) . "</td></tr>";
            }
            echo "</table>";
        }
    }
    ?>
</body>

</html>