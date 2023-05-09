<?php
session_start();
$_SESSION['login'] = '';
$_SESSION['password'] = '';

if (isset($_POST['submit']))
{
    // bouton submit pressé, je traite le formulaire
    $login = (isset($_POST['login'])) ? $_POST['login'] : '';
    $pass  = (isset($_POST['pass']))  ? $_POST['pass']  : '';

    if (($login == "Matthieu") && ($pass == "NewsletTux"))
    {
        $_SESSION['login'] = "Matthieu";
        $_SESSION['password'] = "tux";
        echo '<a href="../vue/accueil.php" title="Accueil de la section membre" style="display:block;width:120px;border: 1px red solid;">Vers page Accueil</a>';
    }
    else
    {
        // une erreur de saisie ...?
        echo '<p style="color:#FF0000; font-weight:bold;">Erreur de connexion.</p>';
    }
}; // fin if (isset($_POST['submit']))


if (!isset($_POST['submit']))
{
    
    // Bouton submit non pressé j'affiche le formulaire
    echo '
		<form id="conn" method="post" action="">
			<p><label for="login">Login :</label><input type="text" id="login" name="login" /></p>
			<p><label for="pass">Mot de Passe :</label><input type="password" id="pass" name="pass" /></p>
			<p><input type="submit" id="submit" name="submit" value="Connexion" /></p>
		</form>';
}; // fin if (!isset($_POST['submit'])))
?>
