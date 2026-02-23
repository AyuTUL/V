<?php
$server="localhost";
$user="root";
$pass="";
$db="CSIT_A";
$conn=new mysqli($server,$user,$pass,$db);
if($conn->connect_error)
    {
        die("Connection Failed ".$conn->connect_error);
    }
    echo "connection succesful<br>";
  $sql="CREATE TABLE employee(eid int primary key, name varchar(20));";
    if(($conn->query($sql))===TRUE)
        {
            echo "table created";
        }
        else
            {
                echo "table creation failed";
            }

?>