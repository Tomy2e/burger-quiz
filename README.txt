------------------------
-- Jeu du BURGER QUIZ --
------------------------

> Par Tomy Guichard et Gwenolé Leroy-Ferrec
> Année 2017/2018

------------------------

1/ Prérequis

    Les paquets suivants doivent êtres installées:
        apache2 mysql-server php7.0 libapache2-mod-php7.0 php7.0-gd php7.0-mysql php7.0-bz2 php7.0-json php7.0-curl
        php7.0-intl php7.0-mcrypt php-mbstring php7.0-mbstring phpmyadmin build-essential libmysqlcppconn-dev qt5-default

2/ Base de données

    Les fichiers se trouvent dans le dossier "sql"

    Le fichier contenant la structure de la base de données est le suivant : script_mcd.sql
    Le fichier contenant des données pré-existantes est le suivant : data.sql

    > NOTE : la vérification des clés étrangères doit être désactivée pour l'import des données

3/ Installation de la partie web du Burger Quiz

    3.1/ Serveur web

        > Exemple de VirtualHost pour apache2

        <VirtualHost *:80>
                ServerName www.burgerquiz.local

                ServerAdmin webmaster@localhost
                DocumentRoot /home/isen/Work/burger-quiz/www

                ErrorLog ${APACHE_LOG_DIR}/error.log
                CustomLog ${APACHE_LOG_DIR}/access.log combined

        </VirtualHost>

        Après avoir ajouté l'hôte : sudo a2ensite <nomdufichierdeconf>

    3.2/ Configuration du PC local

        Modifier le fichier /etc/hosts

        Ajouter une nouvelle ligne en reprenant la syntaxe suivante :

        127.0.0.1 www.burgerquiz.local

    3.3/ Configuration du site

        Aller à la racine du site puis dans le dossier 'php'

        Renommer le fichier 'config.example.php' en 'config.php'

        Modifier les constantes 'MYSQL_HOST', 'MYSQL_USERNAME', 'MYSQL_PASSWORD' et 'MYSQL_DBNAME'

4/ Installation de l'interface admin

    Une fois dans le répertoire contenant le code source de l'interface,
    lancer les commandes suivantes:

    qmake -makefile
    make
    ./BurgerQuiz-Admin

    Toutes les informations de configuration seront demandées au moment de la connexion.

    > NOTE : le port utilisé est noté en dur dans le code source et peut être modifié dans le fichier dbconnection.cpp