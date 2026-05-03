<!-- Lab 10: Write PHP code to fetch the data from HTML form and display using POST and GET method.(also use $_SERVER). -->
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