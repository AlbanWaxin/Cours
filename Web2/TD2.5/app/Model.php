<?php

class Database
{
    private $host = "localhost";
    private $dbname = "TP";
    private $username = "root";
    private $password = "root";

    private $table = "doctor";

    private $db;
    private $query;

    public function __construct()
    {
        $this->db = null;
        try {
            $this->db = new PDO(
                "mysql:host=" . $this->host . ";dbname=" . $this->dbname,
                $this->username,
                $this->password
            );
        } catch (PDOException $exception) {
            echo "Error:" . $exception->getMessage();
        }
    }


    public function query($sql)
    {
        $this->query = $this->db->prepare($sql);
    }

    public function execute()
    {
        return $this->query->execute();
    }

    public function single()
    {
        $this->execute();
        return $this->query->fetch();
    }

    public function resultSet()
    {
        $this->execute();
        return $this->query->fetchAll();
    }

    public function rowCount()
    {
        return $this->query->rowCount();
    }
}