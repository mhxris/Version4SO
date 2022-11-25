<<<<<<< HEAD
DROP DATABASE IF EXISTS bd_final;
CREATE DATABASE bd_final;
USE bd_final;
CREATE TABLE JUGADOR (

 ID INT NOT NULL,

 NOMBRE VARCHAR(50),

 PASSWORD VARCHAR(50),

 USERNAME VARCHAR(50),

 PRIMARY KEY (ID) -- aqui sobraba una coma con lo cual SQL no compilaba y la tabla no se creaba



);



CREATE TABLE PARTIDA (

 ID INT NOT NULL,

 FECHAFIN DATE,

 DURACION INT NULL,

 GANADOR VARCHAR(50),

 PRIMARY KEY (ID)

);



CREATE TABLE JUGADORPARTIDA (

 JUGADOR_ID INT NOT NULL,

 PARTIDA_ID INT NOT NULL,

 JUGADORES INT,

 FOREIGN KEY (JUGADOR_ID) REFERENCES JUGADOR(ID), -- como la tabla jugador no se habia creado por el error de la coma esto tambien petaba ya que la tabla jugador no existia

 FOREIGN KEY (PARTIDA_ID) REFERENCES PARTIDA(ID)

);



CREATE TABLE cartas ( -- ojo! estabas haciendo los inserts a la tabla cartas en vez de carta, he puesto la s aqui porque era mas rapido que no cambiar todos los inserts
    nombre VARCHAR(60),
    ID INT,
    descripcion VARCHAR(200),
    efecto VARCHAR(60),
    tipo VARCHAR(60)
);

CREATE TABLE recursos(

 id INT NOT NULL,

 nombre VARCHAR(10),

 PRIMARY KEY(id)

);



CREATE TABLE inventario(

 id_j INT NOT NULL,

 id_r INT NOT NULL,

 cantidad INT,

 FOREIGN KEY (id_j) REFERENCES JUGADOR(ID),  -- como la tabla jugador no se habia creado por el error de la coma esto tambien petaba ya que la tabla jugador no existia

 FOREIGN KEY (id_r) REFERENCES recursos(id) -- ademas FOREIGN estaba mal escrito! ojo con las typos porque si no SQL no compila

);



/* DATOS INSERTADOS EN PARTIDA / CARTAS / EQUIPOS HECHO POR MIS

COMPAÑEROS*/



INSERT INTO recursos VALUES (1, 'Piedra');

INSERT INTO recursos VALUES (2, 'Paja');

INSERT INTO recursos VALUES (3, 'Oveja');

INSERT INTO recursos VALUES (4, 'Ladrillo');



INSERT INTO inventario VALUES (1, 2, 6);

INSERT INTO inventario VALUES (1, 3, 1);

INSERT INTO inventario VALUES (1, 4, 2);

INSERT INTO inventario VALUES (1, 1, 3);

INSERT INTO inventario VALUES (2, 1, 4);

INSERT INTO inventario VALUES (2, 2, 1);

INSERT INTO inventario VALUES (2, 3, 7);

INSERT INTO inventario VALUES (2, 4, 2);

INSERT INTO cartas VALUES ('gitanada', 1, 'roba 20 monedas a el enemigo que tu elijas' , 'positivo' , 'monedas');  -- petaban todos los inserts porque la tabla que creabas se llamaba carta en vez de cartas
INSERT INTO cartas VALUES ('volando gente' , 10, 'avanza hasta la casilla del tablero que quieras' , 'premium', 'posicion');
INSERT INTO cartas VALUES ('entre rejas' , 22, 'vas a la carcel durante 3 turnos , con una determinada posibilidad de salir', 'camara oculta' , 'posicion');
INSERT INTO cartas VALUES ('un pasito para atras' , 45 , 'retrocede 3 casillas' , 'malo' , 'posicion'); -- te habias dejado el nombre de la tabla



INSERT INTO JUGADOR VALUES (1, 'Monica', 'mesi123', 'monicagamer', 1);

INSERT INTO JUGADOR VALUES (2, 'Mark', 'marco123', 'mark777', 2);

INSERT INTO JUGADOR VALUES (3, 'Rachel', 'cr7siu', 'rachelthebest', 1);



INSERT INTO PARTIDA VALUES (1, '2022-05-08', 10, 'monicagamer');

INSERT INTO PARTIDA VALUES (2, '2022-06-08', 12, 'monicagamer');

INSERT INTO PARTIDA VALUES (3, '2022-07-07', 12, 'mark777');



INSERT INTO JUGADORPARTIDA VALUES (1, 1, 2);

=======
DROP DATABASE IF EXISTS bd_final;
CREATE DATABASE bd_final;
USE bd_final;
CREATE TABLE JUGADOR (

 ID INT NOT NULL,

 NOMBRE VARCHAR(50),

 PASSWORD VARCHAR(50),

 USERNAME VARCHAR(50),

 ID_TEAM INT NOT NULL,

 PRIMARY KEY (ID) -- aqui sobraba una coma con lo cual SQL no compilaba y la tabla no se creaba



);



CREATE TABLE PARTIDA (

 ID INT NOT NULL,

 FECHAFIN DATE,

 DURACION INT NULL,

 GANADOR VARCHAR(50),

 PRIMARY KEY (ID)

);



CREATE TABLE JUGADORPARTIDA (

 JUGADOR_ID INT NOT NULL,

 PARTIDA_ID INT NOT NULL,

 JUGADORES INT,

 FOREIGN KEY (JUGADOR_ID) REFERENCES JUGADOR(ID), -- como la tabla jugador no se habia creado por el error de la coma esto tambien petaba ya que la tabla jugador no existia

 FOREIGN KEY (PARTIDA_ID) REFERENCES PARTIDA(ID)

);



CREATE TABLE EQUIPOS (

    ID INT NOT NULL,

    TEAMNAME VARCHAR(60),

    USER_LIDER VARCHAR(60),

    COLOR VARCHAR(60),

    PRIMARY KEY(ID)

);


CREATE TABLE cartas ( -- ojo! estabas haciendo los inserts a la tabla cartas en vez de carta, he puesto la s aqui porque era mas rapido que no cambiar todos los inserts
    nombre VARCHAR(60),
    ID INT,
    descripcion VARCHAR(200),
    efecto VARCHAR(60),
    tipo VARCHAR(60)
);

CREATE TABLE recursos(

 id INT NOT NULL,

 nombre VARCHAR(10),

 PRIMARY KEY(id)

);



CREATE TABLE inventario(

 id_j INT NOT NULL,

 id_r INT NOT NULL,

 cantidad INT,

 FOREIGN KEY (id_j) REFERENCES JUGADOR(ID),  -- como la tabla jugador no se habia creado por el error de la coma esto tambien petaba ya que la tabla jugador no existia

 FOREIGN KEY (id_r) REFERENCES recursos(id) -- ademas FOREIGN estaba mal escrito! ojo con las typos porque si no SQL no compila

);



/* DATOS INSERTADOS EN PARTIDA / CARTAS / EQUIPOS HECHO POR MIS

COMPAÑEROS*/



INSERT INTO recursos VALUES (1, 'Piedra');

INSERT INTO recursos VALUES (2, 'Paja');

INSERT INTO recursos VALUES (3, 'Oveja');

INSERT INTO recursos VALUES (4, 'Ladrillo');



INSERT INTO inventario VALUES (1, 2, 6);

INSERT INTO inventario VALUES (1, 3, 1);

INSERT INTO inventario VALUES (1, 4, 2);

INSERT INTO inventario VALUES (1, 1, 3);

INSERT INTO inventario VALUES (2, 1, 4);

INSERT INTO inventario VALUES (2, 2, 1);

INSERT INTO inventario VALUES (2, 3, 7);

INSERT INTO inventario VALUES (2, 4, 2);

INSERT INTO cartas VALUES ('gitanada', 1, 'roba 20 monedas a el enemigo que tu elijas' , 'positivo' , 'monedas');  -- petaban todos los inserts porque la tabla que creabas se llamaba carta en vez de cartas
INSERT INTO cartas VALUES ('volando gente' , 10, 'avanza hasta la casilla del tablero que quieras' , 'premium', 'posicion');
INSERT INTO cartas VALUES ('entre rejas' , 22, 'vas a la carcel durante 3 turnos , con una determinada posibilidad de salir', 'camara oculta' , 'posicion');
INSERT INTO cartas VALUES ('un pasito para atras' , 45 , 'retrocede 3 casillas' , 'malo' , 'posicion'); -- te habias dejado el nombre de la tabla


INSERT INTO EQUIPOS VALUES (1, 'ROJOS', 'monicagamer', 'ROJO');

INSERT INTO EQUIPOS VALUES (2, 'JUGONES', 'mark777', 'VERDE');



INSERT INTO JUGADOR VALUES (1, 'Monica', 'mesi123', 'monicagamer', 1);

INSERT INTO JUGADOR VALUES (2, 'Mark', 'marco123', 'mark777', 2);

INSERT INTO JUGADOR VALUES (3, 'Rachel', 'cr7siu', 'rachelthebest', 1);



INSERT INTO PARTIDA VALUES (1, '2022-05-08', 10, 'monicagamer');

INSERT INTO PARTIDA VALUES (2, '2022-06-08', 12, 'monicagamer');

INSERT INTO PARTIDA VALUES (3, '2022-07-07', 12, 'mark777');



INSERT INTO JUGADORPARTIDA VALUES (1, 1, 2);

>>>>>>> 63f6627a6556d8fdb49ae6b8357a5905074171d2
INSERT INTO JUGADORPARTIDA VALUES (2, 2, 2);