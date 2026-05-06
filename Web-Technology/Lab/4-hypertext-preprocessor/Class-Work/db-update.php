<?php
    $conn=new mysqli("localhost","root","","studenthub");
    if($conn->connect_error)
                die("Connection error".$conn->connect_error);
            $sql="UPDATE userdetail SET password='Hero' WHERE username='hrikesh'";
            $result=$conn->query($sql);
            if(mysqli_affected_rows($conn)>0)
                {
                    echo "Update succesful";
                    echo "No of records updated=".mysqli_affected_rows($conn);
                }
                else{
                    echo "No record updated";
                }
        ?>