<?php

require_once(ROOT . "app/Controller.php");

class Articles extends Controller
{
    public function index()
    {
        $this->loadModel('Article');
        $articles = $this->Article->getALL();
        //var_dump($articles);
        $this->render("index" , ["articles" => $articles]);
    }

    public function show($id)
    {
        $this->loadModel('Article');
        $article = $this->Article->getOne($id);
        //var_dump($article);
        $this->render("show" , ["article" => $article]);
    }

    public function searchBySlug($slug)
    {   
        $this->loadModel('Article');
        $article = $this->Article->findBySlug($slug);
        //var_dump($article);
         
        $this->render("slug" , ["article" => $article]);
    }
}

