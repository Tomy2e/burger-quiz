#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------


#------------------------------------------------------------
# Table: utilisateurs
#------------------------------------------------------------

CREATE TABLE utilisateurs(
        id_utilisateur       Int  Auto_increment  NOT NULL ,
        nom_utilisateur      Varchar (64) NOT NULL ,
        password_utilisateur Varchar (128) NOT NULL
	,CONSTRAINT utilisateurs_PK PRIMARY KEY (id_utilisateur)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: questions
#------------------------------------------------------------

CREATE TABLE questions(
        id_question     Int  Auto_increment  NOT NULL ,
        libelle1        Varchar (64) NOT NULL ,
        libelle2        Varchar (64) NOT NULL ,
        active_question TinyINT NOT NULL
	,CONSTRAINT questions_PK PRIMARY KEY (id_question)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: propositions
#------------------------------------------------------------

CREATE TABLE propositions(
        id_proposition      Int  Auto_increment  NOT NULL ,
        libelle_proposition Varchar (128) NOT NULL ,
        reponse_proposition Int NOT NULL ,
        active_proposition  TinyINT NOT NULL ,
        id_question         Int NOT NULL
	,CONSTRAINT propositions_PK PRIMARY KEY (id_proposition)

	,CONSTRAINT propositions_questions_FK FOREIGN KEY (id_question) REFERENCES questions(id_question)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: themes
#------------------------------------------------------------

CREATE TABLE themes(
        id_theme      Int  Auto_increment  NOT NULL ,
        libelle_theme Varchar (64) NOT NULL
	,CONSTRAINT themes_PK PRIMARY KEY (id_theme)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: parties
#------------------------------------------------------------

CREATE TABLE parties(
        id_partie   Int  Auto_increment  NOT NULL ,
        date_partie Datetime NOT NULL
	,CONSTRAINT parties_PK PRIMARY KEY (id_partie)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: scores
#------------------------------------------------------------

CREATE TABLE scores(
        id_score           Int  Auto_increment  NOT NULL ,
        reponses_correctes Int NOT NULL ,
        questions_total    Int NOT NULL ,
        temps_partie       Int NOT NULL ,
        score_final        Int NOT NULL ,
        id_partie          Int NOT NULL ,
        id_utilisateur     Int NOT NULL
	,CONSTRAINT scores_PK PRIMARY KEY (id_score)

	,CONSTRAINT scores_parties_FK FOREIGN KEY (id_partie) REFERENCES parties(id_partie)
	,CONSTRAINT scores_utilisateurs0_FK FOREIGN KEY (id_utilisateur) REFERENCES utilisateurs(id_utilisateur)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: appartient_themes
#------------------------------------------------------------

CREATE TABLE appartient_themes(
        id_theme    Int NOT NULL ,
        id_question Int NOT NULL
	,CONSTRAINT appartient_themes_PK PRIMARY KEY (id_theme,id_question)

	,CONSTRAINT appartient_themes_themes_FK FOREIGN KEY (id_theme) REFERENCES themes(id_theme)
	,CONSTRAINT appartient_themes_questions0_FK FOREIGN KEY (id_question) REFERENCES questions(id_question)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: appartient_parties
#------------------------------------------------------------

CREATE TABLE appartient_parties(
        id_partie   Int NOT NULL ,
        id_question Int NOT NULL
	,CONSTRAINT appartient_parties_PK PRIMARY KEY (id_partie,id_question)

	,CONSTRAINT appartient_parties_parties_FK FOREIGN KEY (id_partie) REFERENCES parties(id_partie)
	,CONSTRAINT appartient_parties_questions0_FK FOREIGN KEY (id_question) REFERENCES questions(id_question)
)ENGINE=InnoDB;


