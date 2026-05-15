<!-- Lab 10: Write PHP code to fetch the data from HTML form and display using POST and GET method.(also use $_SERVER). -->
<?php
$method = $_SERVER['REQUEST_METHOD'] ?? 'GET';
$data = null;
if ($method === 'GET' && isset($_GET['roll'])) $data = $_GET;
if ($method === 'POST' && isset($_POST['roll'])) $data = $_POST;
?>

<html>

<head>
    <title>Student Registration Form</title>
    <style>
        label {
            display: inline-block;
            width: 140px;
        }
    </style>
</head>

<body>
    <h1>Student Registration</h1>

    <form method="GET" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>">
        <fieldset>
            <legend>Send by GET</legend>

            <label>Roll:</label>
            <input name="roll" value="<?php echo htmlspecialchars($_GET['roll'] ?? ''); ?>"><br>
            
            <label>Name:</label>
            <input name="name" value="<?php echo htmlspecialchars($_GET['name'] ?? ''); ?>"><br>
            
            <label>Address:</label>
            <input name="address" value="<?php echo htmlspecialchars($_GET['address'] ?? ''); ?>"><br>
            
            <label>Contact:</label>
            <input name="contact" value="<?php echo htmlspecialchars($_GET['contact'] ?? ''); ?>"><br>
            
            <button type="submit">Submit GET</button>
        </fieldset>
    </form>

    <form method="POST" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>">
        <fieldset>
            <legend>Send by POST</legend>
            
            <label>Roll:</label>
            <input name="roll" value="<?php echo htmlspecialchars($_POST['roll'] ?? ''); ?>"><br>
            
            <label>Name:</label>
            <input name="name" value="<?php echo htmlspecialchars($_POST['name'] ?? ''); ?>"><br>
            
            <label>Address:</label>
            <input name="address" value="<?php echo htmlspecialchars($_POST['address'] ?? ''); ?>"><br>
            
            <label>Contact:</label>
            <input name="contact" value="<?php echo htmlspecialchars($_POST['contact'] ?? ''); ?>"><br>
            
            <button type="submit">Submit POST</button>
        </fieldset>
    </form>

    <?php if ($data): ?>
        <h2>Received (<?php echo htmlspecialchars($method); ?>)</h2>
        <ul>
            <li>Roll: <?php echo htmlspecialchars($data['roll'] ?? ''); ?></li>
            <li>Name: <?php echo htmlspecialchars($data['name'] ?? ''); ?></li>
            <li>Address: <?php echo htmlspecialchars($data['address'] ?? ''); ?></li>
            <li>Contact: <?php echo htmlspecialchars($data['contact'] ?? ''); ?></li>
        </ul>
    <?php endif; ?>

</body>

</html>