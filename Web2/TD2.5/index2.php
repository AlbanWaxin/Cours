<?php

define("ROOT", str_replace("index2.php", "", $_SERVER["SCRIPT_FILENAME"]));

require_once(ROOT . "controllers/Articles.php");


$articles = new Articles();
$articles->index();
?>