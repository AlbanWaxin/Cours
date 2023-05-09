<?php
    function firstline($text)
    {
        return explode(".",$text)[0].".";
    }
?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Tilt+Prism&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css2?family=Tilt+Prism&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="/TD2.5/static/article_index.css">

    <title>Document</title>
</head>

<body>
<h1> Liste des Articles </h1>
<div class = "box">
    <?php foreach($articles as $article):?>

        <div class = "articlebox">
            <a href="searchBySlug/<?= $article['slug']?>"><?= $article['title']?></a>
            <p> <?= firstline($article['body'])?></p>
        </div>
    <?php endforeach ?>
</div>
</body>
</html>