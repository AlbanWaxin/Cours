<?php

//modèle des données de haut niveau
abstract class Model
{
    private $host = 'localhost';
    private $dbname = 'blog';
    private $username = 'root';
    private $password = 'orange';

    protected $_connection;
    public $table;
    public $id;

    public function getConnection()
    {
        $this->_connection = null;
        try {
            //PDO = php data object
            $this->_connection = new PDO("mysql:host=" . $this->host . " ;dbname=" . $this->dbname,$this->username,$this->password);
        } catch (PDOException $exception) {
            echo "Error:" . $exception->getMessage();
        }
    }

    public function getALL()
    {
        $sql = "SELECT * FROM " . $this->table;
        $querry = $this->_connection->prepare($sql);
        $querry->execute();
        return $querry->fetchAll();
    }

    public function getOne()
    {
        $sql = "SELECT * FROM " . $this->table . $this->id;
        $querry = $this->_connection->prepare($sql);
        $querry->execute();
        return $querry->fetch();
    }
}

?>