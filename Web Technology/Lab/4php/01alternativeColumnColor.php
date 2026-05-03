<!-- Lab 1: Write a php program to change the color of 10 columns alternatively. -->
<html>

<head>
    <title>String Array Operations</title>

    <script>
        function add() {
            arr.push("banana", "watermelon", "avocado");
        }

        function remove() {
            arr.pop();
            arr.pop();
        }

        arr = ["apple", "orange", "mango"];
        document.write("Original Array : [" + arr + "]" + "<br><br>");

        add();
        document.write("Array after push : [" + arr + "]" + "<br><br>");

        remove();
        document.write("Array after pop : [" + arr + "]" + "<br><br>");

        document.write("String : " + arr.toString());
    </script>
</head>

</html>