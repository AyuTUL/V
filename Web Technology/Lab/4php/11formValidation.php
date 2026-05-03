<!-- Lab 11: Write PHP code to demonstrate form validation. -->
<html>

<head>
    <title>PHP Form Validation</title>

    <h1>Registration Form</h1>
    <form name="Login" action="" method="POST">

        <label>Name:</label>
        <input type="text" name="nameField"><br><br>

        <label>Country:</label>
        <select name="countryField">
            <option value="">--Select--</option>
            <option value="Nepal">Nepal</option>
            <option value="Korea">Korea</option>
        </select><br><br>

        <label>Gender:</label>
        <input type="radio" name="genderField" value="Male"> Male
        <input type="radio" name="genderField" value="Female"> Female<br><br>

        <label>Password:</label>
        <input type="password" name="passwordField"><br><br>

        <input type="checkbox" name="checkboxField"> I agree to terms<br><br>

        <input type="submit" name="submit" value="Validate">
    </form>
</head>

</html>

<?php
if ($_SERVER['REQUEST_METHOD'] === "POST" && isset($_POST['submit'])) {
    $name = $_POST['nameField'];
    $password = $_POST['passwordField'];
    $country = $_POST['countryField'];
    $gender = $_POST['genderField'];
    $agree = $_POST['checkboxField'];

    $namePattern = "/^[A-Za-z0-9]{3,}$/";
    $passwordPattern = "/^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{6,}$/";

    $allowedCountries = ["Nepal", "Korea"];
    $allowedGenders = ["Male", "Female"];

    if (empty($name))
        echo "Name can't be empty.";
    elseif (!preg_match($namePattern, $name))
        echo "Name must be 3-20 chars, letters/numbers/underscore only.";
    elseif (empty($country))
        echo "Country can't be empty.";
    elseif (!in_array($country, $allowedCountries, true))
        echo "Invalid country selected.";
    elseif (empty($gender))
        echo "Gender can't be empty.";
    elseif (!in_array($gender, $allowedGenders, true))
        echo "Invalid gender selected.";
    elseif (empty($password))
        echo "Password can't be empty.";
    elseif (!preg_match($passwordPattern, $password))
        echo "Password must be at least 6 chars and include letters and numbers.";
    elseif (!$agree)
        echo "You must agree to the terms.";
    else
        echo "Validation successful.";
}
?>