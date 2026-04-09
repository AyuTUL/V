<?php
    $conn=new mysqli("localhost","root","","studenthub");
    if($conn->connect_error)
            {
                die("Connection error".$conn->connect_error);
            }
            $sql="SELECT * FROM userdetail";
            $result=$conn->query($sql);
            if(mysqli_num_rows($result)==0)
                {
                    echo "no records";
                }
                else{
                    echo "<table border='1'><tr><th>Username</th><th>Password</th></tr>";
                    while($row=$result->fetch_object())
                        {
                            echo "<tr><td>";
                            echo $row->username;
                            echo "</td><td>";
                            echo $row->password;
                            echo "</td></tr>";
    
                        }
                        echo "</table>";
                }
                ?>
         