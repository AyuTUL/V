<!-- Lab 3: Write a program for  change values in numeric array, associative array and multidimensional array. -->
<?php
echo "<h2>Array modification examples</h2>";

echo "<h3>Numeric array</h3><pre>";
$num = [11, -2, 7, 8];
echo "Before: "; print_r($num);

$num[1] = 9;
array_push($num, 5);
array_shift($num);
echo "After: "; print_r(array_values($num));
echo "</pre>";

echo "<h3>Associative array</h3><pre>";
$assoc = ['name' => 'Dragapult', 'type' => 'Dragon', 'bst' => 600];
echo "Before: "; print_r($assoc);

$assoc['name'] = 'Toxtricity';
$assoc['type'] = 'Poison';
unset($assoc['bst']);
echo "After: "; print_r($assoc);
echo "</pre>";

echo "<h3>Multidimensional array</h3><pre>";
$multi = [
	'row1' => ['a' => 1, 'b' => 2],
	'row2' => ['a' => 3, 'b' => 4]
];
echo "Before: "; print_r($multi);

$multi['row2']['b'] = 40;
$multi['row3'] = ['a' => 5, 'b' => 6];
echo "After: "; print_r($multi);
echo "</pre>";
?>
