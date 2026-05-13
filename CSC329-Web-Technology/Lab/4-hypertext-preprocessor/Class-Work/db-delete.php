<?php
    $conn=new mysqli("localhost","root","","studenthub");
    if($conn->connect_error)
            {
                die("Connection error".$conn->connect_error);
            }
            $sql="DELETE FROM userdetail WHERE username='hrikesh'";
            $result=$conn->query($sql);
            if(mysqli_affected_rows($conn)>0)
                {
                    echo "Detele succesful";
                    echo "No of records deleted=".mysqli_affected_rows($conn);
                }
                else{
                    echo "No record deleted";
                }
        ?>