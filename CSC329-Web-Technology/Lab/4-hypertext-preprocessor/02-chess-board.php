<?php
echo "<table border='1' cellspacing='0' cellpadding='25'>";

$num = 1;
for ($row = 1; $row <= 8; $row++) {
    echo "<tr>";
    for ($col = 1; $col <= 8; $col++) {
        $color = (($row + $col) % 2 == 0) ? "white" : "black";
        $textColor = ($color === "white") ? "black" : "white";
        echo "<td style='background:$color; color:$textColor; text-align:center; vertical-align:middle;'>$num</td>";
        $num++;
    }
    echo "</tr>";
}
echo "</table>";
