<?php 
$servername = "localhost"; 
$username = "root"; 
$password = ""; 
$dbname = "rvm-ecotech"; 
$conn = new mysqli($servername, $username, $password, $dbname); 
 
$response = array(); 
if($_POST['RFID'] && $_POST['Points'] == 0){ 
 $RFID = $_POST['RFID']; 
 $Points = $_POST['Points']; 
 $stmt = $conn->prepare("INSERT INTO tbl_data (`RFID`, `Points`) VALUES (?,?)"); 
 $stmt->bind_param("ss",$RFID,$Points); 
    if($stmt->execute() == TRUE) 
    { 
        $response = "Successful"; 
    }  
    else 
    { 
        $response = "Failed!"; 
    } 
}  
else 
{ 
 
 $response = "Insufficient Parameters"; 
} 
echo json_encode($response); 
$conn->close(); 
?>