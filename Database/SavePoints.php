<?php 
$servername = "localhost"; 
$username = "root"; 
$password = ""; 
$dbname = "rvm-ecotech"; 
 
$conn = new mysqli($servername, $username, $password, $dbname); 
 
$response = array(); 
if($_POST['RFID'] && $_POST['Points'] >= 0){ 
    $RFID = $_POST['RFID']; 
    $Points = $_POST['Points']; 
    $stmt = $conn->prepare("UPDATE tbl_data SET Points = ? WHERE RFID = ?"); 
    $stmt->bind_param("ss", $Points, $RFID); 
    $result = $stmt->execute(); 
    if($result === TRUE) 
    { 
        $response['status'] = "Successfully!"; 
    }  
    else 
    { 
        $response['status'] = "Failed!"; 
    } 
}  
else 
{ 
    $response['status'] = "Insufficient Parameters"; 
} 
 
echo json_encode($response); 
 
// Close the database connection 
$conn->close(); 
?> 