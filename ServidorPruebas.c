#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <mysql.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
//#include <my_global.h>
#define MAX 100

// -std=c99 `mysql_config --cflags --libs`

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//
// Estructura para un usuario conectado al servidor.
//
typedef struct
{
<<<<<<< HEAD
	char nombre[20];
	int socket;
} Conectado;
//
// Estructura de lista de conectados.
//
typedef struct
{
	Conectado conectados[100];
	int num;
} ListaConectados;




char ID[3];
ListaConectados miLista;

//
//Funcion que pone en la lista de conectados un usuario
//Anade un nuevo conectado en la lista de conectados o devuelve un -1 si la lista esta llena
//
int Pon(ListaConectados* lista, char nombre[20], int socket)
{
	if (lista->num == 100)
	{
		return -1;
	}
	else
	{
		strcpy(lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket = socket;
		lista->num++;
		return 0;
=======
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	char buff[512];
	//INICIALITZACIONS
	//Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error creant el socket");
	} 
	// Fem el bind al port
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// escucharemos en el port 9050
	serv_adr.sin_port = htons(9050);
	if (bind(sock_listen, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) < 0)
		printf("Error al bind");
	//La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 2) < 0)
		printf("Error en el Listen");
	
	int i;
	// Atenderemos solo 5 peticiones
	for (i = 0; i < 7; i++) {
		printf("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf("He recibido conexi?n\n");
		//sock_conn es el socket que usaremos para este cliente
		
		// Ahora recibimos su nombre, que dejamos en buff
		ret = read(sock_conn, peticion, sizeof(peticion));
		printf("Recibido\n");
		
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret] = '\0';
		
		//Escribimos el nombre en la consola
		
		printf("Se ha conectado: %s\n", peticion);
		
		
		char *p = strtok(peticion, "/");
		int codigo = atoi(p);
		p = strtok(NULL, "/");
		char buff[20];
		strcpy(buff, p);
		p = strtok(NULL, "/");
		char buff2[20];
		strcpy(buff2, p);
		printf("Codigo: %d, Parametro: %s\n", codigo, buff, buff2);
		
		
		if (codigo == 1) 
		{
			i = LogIn(buff, buff2);
			if(i == 0) strcpy(respuesta,"Te has logeado correctamente");
			else strcpy(respuesta,"No has podido iniciar sesión");
				write(sock_conn, respuesta,strlen(respuesta));
		}
		else if (codigo == 2)
		{
			
		}
		
		// Se acabo el servicio para este cliente
		close(sock_conn);
>>>>>>> 63f6627a6556d8fdb49ae6b8357a5905074171d2
	}
}
//
//Devuelve el socket del conectado o un -1 si no lo encuentra
//
int DameSocket(ListaConectados* lista, char nombre[20])
{
	int i = 0;
	int encontrado = 0;
	while ((i < lista->num) && !encontrado)
	{
		if (strcmp(lista->conectados[i].nombre, nombre) == 0)
			encontrado = 1;
		if (!encontrado)
			i = i + 1;
	}
	if (encontrado)
		return lista->conectados[i].socket;
	else
		return -1;
}
//
//Funcion que devuelve la posicion de un usuario pasado por parametro.
//Devuelve la posicion de un usuario en la lista o un -1 si no lo encuentra
//
int DamePosicion(ListaConectados* lista, char nombre[20])
{
	int i = 0;
	int encontrado = 0;
	while ((i < lista->num) && (!encontrado))
	{
		if (strcmp(lista->conectados[i].nombre, nombre) == 0)
		{
			encontrado = 1;
		}
		if (!encontrado)
		{
			i = i + i;
		}
	}
	if (encontrado)
	{
		return i;
	}
	else
	{
		return -1;
	}
}
//
// Funcion que elimina de la lista de conectados el usuario pasado como parametro.
// Devuelve un 0 si se elimina correctamente o un -1 en caso contrario.
//
int Elimina(ListaConectados* lista, char nombre[20])
{
	printf("%s:%d \n", lista->conectados[0].nombre, lista->num);
	printf("Nombre recibido como parametro: %s \n", nombre);
	int pos = DamePosicion(lista, nombre);
	if (pos == -1)
	{
		return -1;
	}
	else
	{
		int i;
		for (i = pos; i < lista->num - 1; i++)
		{
			strcpy(lista->conectados[i].nombre, lista->conectados[i + 1].nombre);
			lista->conectados[i].socket = lista->conectados[i + 1].socket;
		}
		lista->num--;
		printf("Resultado:%d\n", lista->num);
		return 0;
	}
}
//
// Funcion que llena un vector de caracteres con la lista de conectados.
//
void DameConectados(ListaConectados* lista, char conectados[300])
{
	sprintf(conectados, "%d", lista->num);
	int i;
	for (i = 0; i < lista->num; i++)
	{
		sprintf(conectados, "%s/%s", conectados, lista->conectados[i].nombre);
	}
}
//
// Funcion para Loguearse.
// Devuelve un -1 si no se ha encontrado el usuario en la base de datos o un 0 si se logea correctamente
//
int Login(char respuesta[512], char username[20], char password[20], MYSQL* conn)
{
	char consulta[200];
	MYSQL_RES* resultado;
	MYSQL_ROW row;

	strcpy(consulta, "SELECT JUGADOR.USERNAME,JUGADOR.PASSWORD FROM JUGADOR WHERE JUGADOR.USERNAME='");
	strcat(consulta, username);
	strcat(consulta, "' AND JUGADOR.PASSWORD='");
	strcat(consulta, password);
	strcat(consulta, "';\n");

	printf("consulta = %s\n", consulta);

	int err = mysql_query(conn, consulta);
	if (err != 0)
	{
		printf("El USERNAME y el PASSWORD no coinciden %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);

	if (row == NULL)
	{
		printf("El USERNAME y el PASSWORD no coinciden\n");
		strcpy(respuesta, "El usuario NO ha podido loguearse, revise si el usuario y la contrasena coinciden.");
		return -1;
	}

	else
		while (row != NULL)
		{
			printf("Bienvenido %s !\n", row[0]);
			row = mysql_fetch_row(resultado);
			return 0;
		}
}
//
//Funcion para eliminar a un usuario
//Devuelve un -1 si el el usuario o password no coinciden o un 0 si se elimina correctamente
//
int DarDeBaja(char respuesta[200], char username[20], char password[20], MYSQL* conn)
{
	char consulta[200];
	MYSQL_RES* resultado;
	MYSQL_ROW row;

	strcpy(consulta, "SELECT JUGADOR.USERNAME FROM JUGADOR WHERE JUGADOR.USERNAME='");
	strcat(consulta, username);
	strcat(consulta, "'");
	strcat(consulta, " AND JUGADOR.PASSWORD='");
	strcat(consulta, password);
	strcat(consulta, "';");

	printf("consulta = %s\n", consulta);

	int err = mysql_query(conn, consulta);
	if (err != 0)
	{
		printf("El USERNAME y el PASSWORD no coinciden %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);

	if (row == NULL)
	{
		printf("El USERNAME y el PASSWORD no coinciden\n");
		strcpy(respuesta, "2-El usuario NO existe, revise si el usuario y el password coinciden.");
		return -1;
	}

	else
		while (row != NULL)
		{

			strcpy(consulta, "DELETE FROM JUGADOR WHERE JUGADOR.USERNAME='");
			strcat(consulta, username);
			strcat(consulta, "';");

			printf("consulta = %s\n", consulta);

			strcpy(respuesta, "2-El usuario ha sido eliminado de la base de datos ");


			err = mysql_query(conn, consulta);
			if (err != 0)
			{
				printf("Error al introducir datos la base %u %s\n", mysql_errno(conn), mysql_error(conn));
				strcpy(respuesta, "2-El usuario NO ha sido eliminado de la base de datos ");
				return -1;
				exit(1);
			}

			printf("\n");
			printf("Despues de dar baja al jugador deseado la BBDD queda de la siguiente forma:\n");
			err = mysql_query(conn, "SELECT * FROM JUGADOR");
			if (err != 0)
			{
				printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
				exit(1);
			}

			resultado = mysql_store_result(conn);
			row = mysql_fetch_row(resultado);

			if (row == NULL)
			{
				printf("No se han obtenido datos en la consulta\n");
			}
			else
				while (row != NULL)
				{
					printf("Username: %s\n", row[1]);
					row = mysql_fetch_row(resultado);
				}
			return 0;
		}
}
//
// Funcion que retorna el ID del último jugador registrado en la BBDD.
// Retorna un -1 en caso de que no haya ningun jugador registrado en la BBDD.
//
int DameIDJugador(MYSQL* conn)
{
	int err;
	MYSQL_RES* resultado;
	MYSQL_ROW row;
<<<<<<< HEAD
	char consulta[200];
	//int cont;

	strcpy(consulta, "SELECT JUGADOR.ID FROM JUGADOR ORDER BY JUGADOR.ID DESC LIMIT 1 ");
	err = mysql_query(conn, consulta);
	if (err != 0)
	{
		printf("Consulta mal hecha %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);

	if (row == NULL)
	{
		printf("No hay jugadores registrados\n");
		return -1;
	}

	else
	{
		int cont;
		char numero[3];
		while (row != NULL)
		{
			printf("ID del Ãºltimo jugador registrado: %s\n", row[0]);
			cont = atoi(row[0]);
			row = mysql_fetch_row(resultado);
		}
		return cont;
	}
}
//
//
// Funcion para registrar a un usuario.
// Devuelve un 0 si lo registra correctamente o un -1 si hay algun error
//
int Registrar(char respuesta[200], char name[30], char username[20], char password[20], MYSQL* conn)
{

	int err;
	MYSQL_RES* resultado;
	MYSQL_ROW row;
	char consulta[200];

	int IDnum = DameIDJugador(conn);
	IDnum = IDnum + 1;

	sprintf(ID, "%d", IDnum);
	strcpy(consulta, "INSERT INTO JUGADOR VALUES (");
	strcat(consulta, ID);
	strcat(consulta, ",'");
	strcat(consulta, name);
	strcat(consulta, "','");
	strcat(consulta, username);
	strcat(consulta, "','");
	strcat(consulta, password);
	strcat(consulta, "');");

	printf("consulta = %s\n", consulta);

	err = mysql_query(conn, consulta);
=======
	char consulta[80];
	char res[80];
	//parte de mysql
	char user[20], pass[20]; //variables para comparar nombre y contraseña
	
	conn = mysql_init(NULL);
	
	if (conn == NULL)
	{
		printf("Error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	conn = mysql_real_connect(conn, "localhost", "root", "mysql", "bd_final", 0, NULL, 0);
	
	if (conn == NULL)
	{
		printf("Error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	strcpy(consulta, "SELECT JUGADOR.USERNAME,JUGADOR.PASSWORD FROM JUGADOR WHERE JUGADOR.USERNAME = '");
	strcat(consulta, username);
	strcat(consulta, "'");
	printf(consulta);
	err = mysql_query(conn, consulta);
	
>>>>>>> 63f6627a6556d8fdb49ae6b8357a5905074171d2
	if (err != 0)
	{
		printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	printf("\n");
	printf("Despues de dar alta al jugador deseado la BBDD queda de la siguiente forma:\n");
	err = mysql_query(conn, "SELECT * FROM JUGADOR");
	if (err != 0)
	{
		printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	if (row == NULL)
	{
		printf("No se han obtenido datos en la consulta\n");
<<<<<<< HEAD
	}
	else
		while (row != NULL)
		{
			printf("Username: %s\n", row[3]);
			row = mysql_fetch_row(resultado);
			strcpy(respuesta, "3-El usuario se ha REGISTRADO correctamente");
		}
}
//
//
// Funcion que pone en el vector "respuesta"(pasado como parametro) los jugadores registrados en la BBDD.
// Retorna el numero de jugadores en la BBDD o un -1 en caso de que no hayan jugadores registados.
//
int DameTodosUsuarios(MYSQL* conn, char respuesta[200], char username[200])
{
	char consulta[500];
	MYSQL_RES* resultado;
	MYSQL_ROW row;
	int cont;

	strcpy(consulta, "SELECT * FROM JUGADOR WHERE JUGADOR.Username NOT IN ('");
	strcat(consulta, username);
	strcat(consulta, "');");

	int err = mysql_query(conn, consulta);
	if (err != 0)
	{
		printf("Consulta mal hecha %u %s\n", mysql_errno(conn), mysql_error(conn));
		cont = 0;
		exit(1);
	}

	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);

	if (row == NULL)
	{
		printf("No hay jugadores registrados\n");
		return -1;
	}

	else
	{
		cont = 0;
		strcpy(respuesta, "");
		while (row != NULL)
		{
			printf("Username:     %s\n", row[1]);
			sprintf(respuesta, "%s%s/", respuesta, row[1]);
			row = mysql_fetch_row(resultado);
			cont = cont + 1;
		}
		return cont;
	}
}



void* AtenderCliente(void* socket)
{
	int* s;
	s = (int*)socket;
	int sock_conn = *(int*)socket;
	sock_conn = *s;

	int i = miLista.num;
	miLista.conectados[i].socket = *s;


	char peticion[512];
	char respuesta[512];
	char respuesta2[512];
	int ret;
	MYSQL* conn;
	int err;
	MYSQL_RES* resultado;
	MYSQL_ROW row;
	int numID = 6;
	char consulta[80];
	char notificacion[200];
	char connected[200];


	//Conexion con la base de datos
	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		printf("Error al crear la conexion: %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	conn = mysql_real_connect(conn, "localhost", "root", "mysql", "bd_final", 0, NULL, 0);
	if (conn == NULL)
	{
		printf("Error al inicializar la conexion: %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	//Empieza a escuchar las peticiones del cliente
	int terminar = 0;
	while (terminar == 0)
	{
		ret = read(sock_conn, peticion, sizeof(peticion));
		printf("Recibido\n");
		peticion[ret] = '\0';
		printf("Peticion: %s\n", peticion);

		char* p = strtok(peticion, "/");
		int codigo = atoi(p);
		char username[50];
		char password[50];
		char name[50];
		//
		// Peticion de DESCONEXION.
		//
		if (codigo == 0)
		{
			pthread_mutex_lock(&mutex);
			int elim = Elimina(&miLista, username);
			pthread_mutex_unlock(&mutex);
			if (elim == 0)
				printf("Usuario eliminado de la lista de conectados\n");
			else
				printf("Error al eliminar el usuario de la lista de conectados\n");

			DameConectados(&miLista, connected);

			sprintf(notificacion, "1-%s", connected);
			for (int i = 0; i < miLista.num; i++)
			{
				write(miLista.conectados[i].socket, notificacion, strlen(notificacion));
			}
			printf("Estos son los usuarios conectados actualmente: %s\n", connected);

			terminar = 1;

		}
		//
		// Peticion de LOGUEAR.
		//
		else if (codigo == 1)
		{
			p = strtok(NULL, "/");
			strcpy(username, p);

			p = strtok(NULL, "/");
			strcpy(password, p);

			int result = Login(respuesta, username, password, conn);
			if (result == 0)
			{

				pthread_mutex_lock(&mutex);

				int res = Pon(&miLista, username, sock_conn);
				pthread_mutex_unlock(&mutex);
				printf("%s\n", username);
				if (res == 0)
					printf("Anadido a la lista de conectados\n");
				if (res != 0)
					printf("Lista llena. No se pudo anadir el usuario a la lista de conectados.\n");
				DameConectados(&miLista, connected);
				printf("Estos son los usuarios conectados actualmente: %s\n", connected);

				sprintf(notificacion, "1-%s", connected);
				for (int i = 0; i < miLista.num; i++)
				{
					write(miLista.conectados[i].socket, notificacion, strlen(notificacion));
				}
			}
			else
			{
				printf("El usuario NO ha podido loguearse, revise si el usuario y la contrasena coinciden.");
				strcpy(respuesta, "1-11");
				write(sock_conn, respuesta, strlen(respuesta));
			}
		}
		//
		// Peticion de ELIMINAR USUARIO.
		//
		else if (codigo == 2)
		{
			char DeleteUser[20];

			p = strtok(NULL, "/");
			strcpy(DeleteUser, p);

			p = strtok(NULL, "/");
			strcpy(password, p);

			int result = DarDeBaja(respuesta, DeleteUser, password, conn);
			if (result == 0)
			{
				write(sock_conn, respuesta, strlen(respuesta));
			}
			else
				write(sock_conn, respuesta, strlen(respuesta));
		}
		//
		// Peticion de REGISTRAR.
		//
		else if (codigo == 3)
		{
			p = strtok(NULL, "/");
			strcpy(name, p);

			p = strtok(NULL, "/");
			strcpy(username, p);

			p = strtok(NULL, "/");
			strcpy(password, p);


			Registrar(respuesta, name, password, username, conn);

		}
	}
	close(sock_conn);

}
//
// Aqui empieza el MAIN.
//
int main(int argc, char* argv[])
{
	int sock_conn, sock_listen;
	struct sockaddr_in serv_adr;

	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;

	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

	serv_adr.sin_port = htons(9050);
	if (bind(sock_listen, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) < 0)
		printf("Error al bind");

	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");

	int i;
	int sockets[100];

	pthread_t thread[10];
	ListaConectados miLista;
	i = 0;

	for (;;)
	{
		printf("Escuchando\n");

		sock_conn = accept(sock_listen, NULL, NULL);
		printf("He recibido conexion\n");

		sockets[i] = sock_conn;
		miLista.conectados[i].socket = sock_conn;
		miLista.num = i;

		pthread_create(&thread[i], NULL, AtenderCliente, &sockets[i]);
		i++;
	}
}
=======
	
	else
	{
		strcpy(user, row[0]);
		strcpy(pass, row[1]);
		
		printf("nombre recibido: %s, contra recibida: %s\n", user, pass);
		row = mysql_fetch_row(resultado);
	}
	
	if ((strcmp(user, username) == 0) && (strcmp(pass, password) == 0))
	{
		return 0;
	}
	
	else
										  return 1;
}
>>>>>>> 63f6627a6556d8fdb49ae6b8357a5905074171d2

