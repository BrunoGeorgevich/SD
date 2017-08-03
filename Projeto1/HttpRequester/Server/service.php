<?php
    function checkParameter($param) {
        @$param = trim($param);
        @$param = str_replace("'", "", $param);
        @$param = str_replace("\"", "", $param);
        @$param = str_replace(";", "", $param);
        @$param = str_replace("!", "", $param);
        return $param;
    }
    function parseParameters($parameters) {
        if (!is_array($parameters)) return false;
        $result = array();
        foreach($parameters as $key => $value) {
        $result[$key] = checkParameter($value);
        if (empty($parameters[$key])) return false;
        }
        return $result;
    }

    header('Content-Type: application/json');

    $response = array();

    if($_SERVER['REQUEST_METHOD'] === 'POST') {
        $data = @json_decode($_POST['data'], true);
        if (($data === null) && (json_last_error() !== JSON_ERROR_NONE)) {
            $response = "Invalid JSON in data parameter.";
            exit();
        }

        $ch = curl_init();
        curl_setopt($ch,CURLOPT_POST, 1);
        curl_setopt($ch,CURLOPT_POSTFIELDS, $data["payload"]);
        curl_setopt($ch,CURLOPT_URL, getallheaders()['fulladdress']);
        $result = curl_exec($ch);
        array_push($response, $result);
        curl_close($ch);
    }
    elseif($_SERVER['REQUEST_METHOD'] === 'GET') {
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_URL, getallheaders()['fulladdress']);
        $content = curl_exec($ch);
        array_push($response, $content);
    }
    elseif($_SERVER['REQUEST_METHOD'] === 'PUT') {

        $_PUT = array();

        if (!strcasecmp($_SERVER['REQUEST_METHOD'], 'PUT')) {
            parse_str(file_get_contents('php://input'), $_PUT);
        }

        $data = @json_decode($_PUT['data'], true);

        if (($data === null) && (json_last_error() !== JSON_ERROR_NONE)) {
            $response = "Invalid JSON in data parameter.";
            exit();
        }

        $ch = curl_init();
        curl_setopt($ch,CURLOPT_CUSTOMREQUEST, "PUT");
        curl_setopt($ch,CURLOPT_URL, getallheaders()['fulladdress']);
        curl_setopt($ch,CURLOPT_POSTFIELDS, $data["payload"]);
        $result = curl_exec($ch);
        array_push($response, $result);
        curl_close($ch);
    }
    elseif($_SERVER['REQUEST_METHOD'] === 'DELETE') {
        $data = getallheaders()['university'];

        if ($data === null) {
            $response = "Invalid data parameter.";
            exit();
        }

        $ch = curl_init();
        curl_setopt($ch,CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_setopt($ch,CURLOPT_URL, getallheaders()['fulladdress']);
        curl_setopt($ch,CURLOPT_POSTFIELDS, "university=".$data);
        $result = curl_exec($ch);
        array_push($response, $result);
        curl_close($ch);
    }
    else {
        $response = "Method not available.";
    }

    $responseStr = implode(",",$response);
    echo $responseStr;
?>
