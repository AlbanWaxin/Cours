<?php
class Articles extends Controller
{
    public function index()
    {
        echo "<h1>Bienvenue sur l'accueil</h1>";
        $this->loadModel('Article');
        $articles = $this->Article->getALL();
        //var_dump($articles); comme un printf
        $this->render("index" , ["articles" => $articles]);
    }
}
?>