<!-- Lab 1: Write a php program to change the color of 10 columns alternatively. -->
<html>

<head>
    <title>Alternate Column Colors</title>
</head>

<body>

    <table border="1" cellspacing="0" cellpadding="20">
        <tr>
            <?php
            for ($i = 1; $i <= 10; $i++) {

                if ($i % 2 == 0)
                    $color = "#FB7299";
                else
                    $color = "#5788CE";

                echo "<td style='background-color:$color'>Column $i</td>";
            }
            ?>
        </tr>
    </table>

</body>

</html>