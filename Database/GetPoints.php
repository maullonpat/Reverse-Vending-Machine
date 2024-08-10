<?php 
$servername = "localhost"; 
$username = "root"; 
$password = ""; 
$dbname = "rvm-ecotech"; 
 
$conn = new mysqli($servername, $username, $password, $dbname); 
 
$response = array(); 
if($_POST['RFID']){ 
    $RFID = $_POST['RFID']; 
    $stmt = $conn->prepare("SELECT Points FROM tbl_data WHERE RFID = ?"); 
    $stmt->bind_param("s",$RFID); 
    $result = $stmt->execute(); 
    if($result == TRUE){ 
        $stmt->store_result(); 
        $stmt->bind_result($RFID); 
        $stmt->fetch(); 
        $response['RFID'] = $RFID; 
    }  
    else{ 
        $response['error'] = true; 
        $response['message'] = "Points retrieval failed"; 
        $response['code'] = "108"; 
    } 
}  
else{ 
    $response['error'] = true; 
    $response['message'] = "Insufficient Parameters"; 
    $response['code'] = "401"; 
} 
echo json_encode($RFID); 
$conn->close(); 
?>