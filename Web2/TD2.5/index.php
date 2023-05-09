<?php
session_start();
// $_SESSION['counter']++;
// echo $_SESSION['counter'];
// echo "<br/>";

// $_SESSION['login'] = 'admin';
// $_SESSION['password'] = 'adminp';
// var_dump($_SESSION['login'], $_SESSION['password']);
// echo "<br/>";

// $arr = ['a' => 5, 'b' => 4, 'c' => 3];
// $_SESSION['panier'] = $arr;
// var_dump($_SESSION['panier']);
// echo "<br/>";
// echo "prix a: " . $_SESSION['panier']['a'];
// echo "<br/>";
// echo "prix total: " . array_sum($_SESSION['panier']);
// echo "<br/>";
// var_dump($_COOKIE);
// echo "<br/>";

define("ROOT", str_replace("index.php", "", $_SERVER["SCRIPT_FILENAME"]));
require_once(ROOT . "app/Model.php");
require_once(ROOT . "app/Controller.php");

// var_dump($_GET);
// $a = $_GET['a'];
// var_dump($_SERVER["SCRIPT_FILENAME"]);

// die();
//var_dump($_GET);
$params = explode('/', $_GET['p']);
//var_dump($params);
//echo "<br/>";
//echo $_GET['p'];

if ($params[0] != "") {
    $controller = ucfirst($params[0]); // articles => Articles
    //echo "<h1>$controller= $controller</h1>";
    $action = isset($params[1]) ? $params[1] : 'index';
    //echo "<h1>$action= $action</h1>"; 

    require_once(ROOT . "controllers/". $controller .".php");
    $controller = new $controller();
    if (method_exists($controller, $action)) {
        unset($params[0]);
        unset($params[1]);
        call_user_func_array(array($controller, $action), $params);
        $controller->$action();
    } else {
        http_response_code(404);
        echo "la page demandée n'existe pas";
    }
} else {
    $controller = 'pages';
    $action = 'home';
}