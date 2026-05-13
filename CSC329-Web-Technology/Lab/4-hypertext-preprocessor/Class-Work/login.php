<?php

if($_SERVER['REQUEST_METHOD']=="GET")
    {
        $user=$_GET['user'];
         $pass=$_GET['pass'];
         $conn=new mysqli("localhost","root","","studenthub");
         if($conn->connect_error)
            {
                die("Connection error".$conn->connect_error);
            }
            $sql="INSERT INTO userdetail(username,password)VALUES('$user','$pass')";
            if($conn->query($sql)===TRUE)
                {
                    echo "Data inserted";
                }
                else
                    echo "Data insertion failed";
    }

 $conn=new mysqli("localhost","root","","portal");
 if($conn->connect_error)
    {
        die("connection error".$conn->connect_error);

    }
    $sql="INSERT INTO student(username,password) VALUES('$user','$pass')";
    if($conn->query($sql)===TRUE)
    {
        echo "Insertion succesful";
    }
    else{
        echo "Insertion failed";
    }
?>
