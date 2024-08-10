<?php 
$servername = "localhost"; 
$username = "root"; 
$password = ""; 
$dbname = "rvm-ecotech"; 
 
$conn = new mysqli($servername, $username, $password, $dbname); 
 
 
$response = array(); 
if($_POST['RFID']){ 
    $RFID = $_POST['RFID']; 
    $stmt = $conn->prepare("SELECT Points FROM tbl_data WHERE RFID=?"); 
    $stmt->bind_param("s",$RFID); 
    $result = $stmt->execute(); 
    if($result == TRUE){ 
        $stmt->store_result(); 
        $stmt->bind_result($Points); 
        $stmt->fetch(); 
       
        if($Points==null) 
        {           
            $response= "Available";         
        } 
        else 
        { 
            $response= "Used"; 
        } 
    }  
    else 
    { 
        $response['error'] = true; 
        $response['message'] = "Validate username failed!"; 
        $response['code'] = "401"; 
    } 
}  
else{ 
    $response['error'] = true; 
    $response['message'] = "Insufficient Parameters"; 
    $response['code'] = "401"; 
} 
echo json_encode($response); 
$conn->close(); 
?>