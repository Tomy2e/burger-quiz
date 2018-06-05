<?php	
	session_start();
	ini_set('display_errors','on');
	error_reporting(E_ALL);
	
	//include('entete.php');
	//include('init-mysql.php');
	
	/********************************/
	
	$mysqlServerIp = "127.0.0.1";

	$mysqlServerPort = "3306";

	$mysqlDbName = "bq";

	$mysqlDbUser = "admin";

	$mysqlDbPwd = "ziuQ_regruB_nimdA";

	$mysqlDbCharset = "UTF8";

	$mysqlDsn = "mysql:host=".$mysqlServerIp.";port=".$mysqlServerPort.";dbname=".$mysqlDbName.";charset=".$mysqlDbCharset.";";
	
	/********************************/
	function chaineAleatoire() {
		$string = str_shuffle('abcdefghijklmnopqrstuvwxyz0123456789');
		$string = substr( $string , 0 , 10 ); // prendre les 10 1ers caractÃ¨res.
		return $string;
	}
	
	
	echo"<h1>Test de connexion</h1>";
	echo"<br>";
	echo"<br>";
	//ouverture de la connection
	try{
		$pdo = new PDO($mysqlDsn,$mysqlDbUser,$mysqlDbPwd, array(PDO::ATTR_PERSISTENT=>true));
	}catch(PDOException $e) {
		echo "Failed to get DB handle: " . $e->getMessage() . "\n";
		exit;
	}
	
	echo"<h1>Base Mysql</h1>";
	
	echo"<h2>Creation de table</h2>";
	
	
	$maRequete = "CREATE TABLE `test1` ";
	$maRequete .= " (`id` int(11) NOT NULL,`test` varchar(50) CHARACTER SET utf8 NOT NULL) ";
	$maRequete .= " ENGINE=InnoDB DEFAULT CHARSET=utf8; ";
	/*
	CREATE TABLE `test` (
	  `id` int(11) NOT NULL,
	  `test` varchar(50) CHARACTER SET utf8 NOT NULL
	) ENGINE=InnoDB DEFAULT CHARSET=utf8;
	* 
	*/
	
	$query = $pdo->prepare($maRequete );
	if($query->execute()){
		echo "creation table test OK <br>";
	}else{
		echo "probleme lors de creation de table <br>";
	}
	
	
	echo"<h2>Insertion de donnÃ©es</h2>";
	
	$chaine1 = chaineAleatoire();
	$chaine2 = chaineAleatoire();
	//echo "chaine1 ".$chaine1;
	
	//INSERT INTO `test1`(`id`, `test`) VALUES ([value-1],[value-2])
	$maRequeteInsert = "INSERT INTO `test1` ";
	$maRequeteInsert .= " (`id`, `test`) ";
	$maRequeteInsert .= "  VALUES ('1', '".$chaine1."'), ('2', '".$chaine2."') ";
	//INSERT INTO `test1` (`id`, `test`) VALUES ('1', 'xdqsd'), ('2', 'wxcvwxcv');
	//ECHO "<BR> req : ".$maRequeteInsert;
	
	$query = $pdo->prepare($maRequeteInsert );
	if($query->execute()){
		echo "Insertion de donnÃ©es => OK <br>";
	}else{
		echo "probleme lors de Insertion de donnÃ©es <br>";
	}
	
	
	
	
	echo"<h2>SELECT simple</h2>";
	

	$query = $pdo->prepare("select * FROM test1");
	$query->execute();
	
	//mise en table des valeurs rÃ©cupÃ©res
	echo "<table border=\"1\">";
		echo "<TR><td>ID</td><td>Value</td></TR>";
	$lesValues = $query->fetchAll();

	foreach($lesValues as $row){
		echo "<TR>";
			echo "<td>";
				echo $row['id'];
			echo "</td>";
			echo "<td>";
				echo $row['test'];
			echo "</td>";
		echo "</TR>";
	}

	
	echo "</table>";
	
	echo"<h2>suppression de la table test</h2>";
	
	
	$query = $pdo->prepare("DROP TABLE test1");
	if($query->execute()){
		echo "Suppresion de table => OK <br>";
	}else{
		echo "probleme lors de Suppresion de table <br>";
	}
	
	//var_dump($voyages);

	unset($pdo); 
	unset($query);
	
	

  unset($pdo); 
  unset($query);

