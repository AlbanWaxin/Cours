<?php
    define("ROOT", str_replace("index.php", "", $_SERVER["SCRIPT_FILENAME"]));
    //$_SERVER variable de type superglobal. clé:valeur
    require_once(ROOT . "app/Model.php");
    require_once(ROOT . 'app/Controller.php');
?>