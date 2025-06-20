#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*registro para iniciar sesion*/
struct usuarios
{
	char usuario[30];
	char contra[30];
	char name[30];
	bool borrado;
};

/*registros para cargar los datos*/     
struct DatosMasc
{
	char nombre[30];
	char especie[30];
	int edad=0;
	char raza[30];
	char duenio[30];
	bool borrado;
};
     
struct Productos
{
	char nombre[30];
	int cantidad=0;
	float precio=0.0;
	bool borrado;	
};

struct Fecha //este registro lo utilizaremos para la cita medica
{
	int dia=0;
	int mes=0;
	int anio=0;	
};

struct Horario //este registro lo utilizaremos para la cita medica
{
	int hora=0;
	int minuto=0;	
};

struct CitaMedica
{
	Fecha fech;
	Horario hora;
	char veterinario[30]; //nombre del veterinario asignado
	char mascota[30]; //mascota atendida
	bool borrado;
};

usuarios UsuarioAdmin(FILE *user)
{
	/*usuario base del administrador*/
	rewind(user);
	usuarios userdat;
	userdat.borrado=false;
	strcpy(userdat.name, "administrador");
	strcpy(userdat.usuario, "admin");
	strcpy(userdat.contra, "admin123-");
	fwrite(&userdat, sizeof(usuarios), 1, user);
	
	return userdat;
}

int IniciarSesion(FILE *user, char naming[30], char pass[30])
{
	rewind(user);
	usuarios userdat;
	
	printf("Ingresar nombre de usuario: ");
	_flushall();
	gets(naming);
	printf("\n");
	

	while(fread(&userdat, sizeof(usuarios), 1, user)==1)
	{
		if(strcmp(naming, userdat.usuario)==0)
		{
			printf("Ingresar Password: ");
			_flushall();
			gets(pass);
			
			if(strcmp(pass, userdat.contra)==0)
			{
				printf("\nAcceso concedido\n");
				system("pause");
				return 1;
			}
			else
			{
				printf("Acceso denegado");
				exit(1);
			}
		}
	}
	printf("Usuario no encontrado\n");  
    exit(1);
}

void CrearUsuario(FILE *user)
{
	char password1[30];
	char password2[30];
	usuarios userdat;
	
	userdat.borrado=false;
	
	printf("Ingresar nombre del propietario: ");
	_flushall();
	gets(userdat.name);
	strupr(userdat.name);
	printf("\n");
	
	printf("Ingresar Nombre de Usuario: ");  
    _flushall();
	gets(userdat.usuario);
	printf("\n");
	
	printf("Ingresar password: ");
	_flushall();
	gets(password1);
	printf("\n");
	
 	printf("Confirmar password: ");
 	_flushall();
 	gets(password2);
 	printf("\n");
	
	if(strcmp(password1, password2)==0)
	{
		strcpy(userdat.contra, password1);
		fwrite(&userdat, sizeof(usuarios), 1, user);
		printf("usuario creado exitosamente");
	}
	else
	{
		printf("no coinciden");
	}
}

void MostrarUsuarios(FILE *user)
{
	usuarios userdat;
	rewind(user);
	while(fread(&userdat, sizeof(usuarios), 1, user)==1)
	{
		if(userdat.borrado==false)
		{
			printf("\n");
			printf("\n%s", userdat.name);
			/*printf("\n%s", userdat.usuario);
			printf("\n%s", userdat.contra);*/
		}
	}
}

DatosMasc CargarDatosMascota(FILE *datomasc)
{
	DatosMasc datos;
	printf("Ingresar nombre de la mascota: ");
	_flushall();
	gets(datos.nombre);
	strupr(datos.nombre);
	printf("\n");
	
	printf("Ingresar especie de %s: ", datos.nombre);
	_flushall();
	gets(datos.especie);
	printf("\n");
	
	printf("Ingresar edad de %s: ", datos.nombre);
	scanf("%d", & datos.edad);
	printf("\n");
	
	printf("Ingresar raza de %s: ", datos.nombre);
	_flushall();
	gets(datos.raza);
	printf("\n");
	
	printf("Ingresar duenio de %s: ", datos.nombre);
	_flushall();
	gets(datos.duenio);
	printf("\n");
	
	datos.borrado=false;
	fwrite(&datos, sizeof(DatosMasc), 1, datomasc);
	
	return datos;
}

Productos CargarInventario(FILE *invent)
{
	Productos prod;
	printf("Ingresar nombre del producto: ");
	_flushall();
	gets(prod.nombre);
	strupr(prod.nombre);
	printf("\n");
	
	printf("Ingresar stock de %s: ", prod.nombre);
	scanf("%d", & prod.cantidad);
	printf("\n");
	
	printf("Ingresar precio de %s: ", prod.nombre);
	scanf("%f", & prod.precio);
	printf("\n");
	
	prod.borrado=false;
	fwrite(&prod, sizeof(Productos), 1, invent);
	
	return prod;
}

CitaMedica CargarCitaMedica(FILE *citamed)
{
	CitaMedica cita;
	
	printf("Ingresar fecha de la cita");
	printf("\nDIA: ");
	scanf("%d", & cita.fech.dia);
	printf("MES: ");
	scanf("%d", & cita.fech.mes);
	printf("ANIO: ");
	scanf("%d", & cita.fech.anio);
	printf("\n\n");
	printf("Ingresar horario de la cita del dia %d/%d/%d: ", cita.fech.dia, cita.fech.mes, cita.fech.anio);
	printf("\nHORAS: ");
	scanf("%d", & cita.hora.hora);
	printf("MINUTOS: ");
	scanf("%d", & cita.hora.minuto);
	printf("\n");
	
	printf("Ingresar nombre del veterinario asignado: ");
	_flushall();
	gets(cita.veterinario);
	printf("\n");
	
	printf("Ingresar nombre de la mascota atendida por %s: ", cita.veterinario);
	_flushall();
	gets(cita.mascota);
	strupr(cita.mascota);
	printf("\n");
	
	cita.borrado=false;
	fwrite(&cita, sizeof(CitaMedica), 1, citamed);
	
	return cita;
}

void muestradatos(FILE *datomasc)
{
	DatosMasc datos;
	rewind(datomasc);
	while(fread(&datos, sizeof(DatosMasc),1 , datomasc)==1)
	{
		if(datos.borrado!=true)
		{
			printf("\n\n");
			printf("\nNombre: %s", datos.nombre);
			printf("\nEspecie: %s", datos.especie);
			printf("\nRaza: %s", datos.raza);
			printf("\nEdad: %d", datos.edad);
			printf("\nDuenio: %s", datos.duenio);
		}
	}
}

void muestrainventario(FILE *invent)
{
	Productos prod;
	rewind(invent);
	
	while(fread(&prod, sizeof(Productos), 1, invent)==1)
	{
		if(prod.borrado!=true)
		{
			printf("\n\n");
			printf("\nNombre: %s", prod.nombre);
			printf("\nPrecio: %.2f", prod.precio);
			printf("\nCantidad: %d", prod.cantidad);
		}
	}
}

void muestracitas(FILE *citamed)
{
	CitaMedica cita;
	rewind(citamed);
	
	while(fread(&cita, sizeof(CitaMedica), 1, citamed)==1)
	{
		if(cita.borrado!=true)
		{	
			printf("\n\n");
			printf("\nNombre: %s", cita.mascota);
			printf("\nVeterinario: %s", cita.veterinario);
			printf("\nFecha: %d/%d/%d", cita.fech.dia, cita.fech.mes, cita.fech.anio);
			printf("\nHorario: %d:%d", cita.hora.hora, cita.hora.minuto);
		}
	}
}

bool BajarMascota(FILE *datomasc, char mascot[30])
{
	DatosMasc datos;
	rewind(datomasc);
	bool bandera=false;
	
	fread(&datos, sizeof(DatosMasc), 1, datomasc);
	while(!feof(datomasc) && bandera==false)
	{
		if((strcmp(datos.nombre, mascot)==0) && datos.borrado==false)
		{
			datos.borrado=true;
			fseek(datomasc, (long)-sizeof(DatosMasc), SEEK_CUR);
			fwrite(&datos, sizeof(DatosMasc), 1, datomasc);
			bandera=true;
		}
		else
		{
			fread(&datos, sizeof(DatosMasc), 1, datomasc);
		}
	}
	return bandera;
}

bool BajarProducto(FILE *invent, char produ[30])
{
	Productos prod;
	rewind(invent);
	bool bandera=false;
	int cantidad=0;
	int cent=0;
	
	
	fread(&prod, sizeof(Productos), 1, invent);
	while(!feof(invent) && bandera==false)
	{
		if(prod.borrado!=true)
		{
			printf("\n\n");
			printf("\nNombre: %s", prod.nombre);
			printf("\nPrecio: %.2f", prod.precio);
			printf("\nCantidad: %d", prod.cantidad);
		}
		if((strcmp(produ, prod.nombre)==0) && prod.borrado==false)
		{
			do
			{
				printf("\nCantidad a dar de baja: ");
				scanf("%d", & cantidad);
				if(cantidad>prod.cantidad)
				{
					printf("La cantidad ingresada es mayor a la disponible. Intente nuevamente.\n");
				}
			}while(cantidad>prod.cantidad);
			
			if(cantidad==prod.cantidad)
			{
				prod.borrado=true;
				fseek(invent, (long)-sizeof(Productos), SEEK_CUR);
				fwrite(&prod, sizeof(Productos), 1, invent);
				bandera=true;
			}
			else
			{
				prod.cantidad=prod.cantidad-cantidad;
				fseek(invent, (long)-sizeof(Productos), SEEK_CUR);
				fwrite(&prod, sizeof(Productos), 1, invent);
				bandera=true;
			}
			
		}
		else
		{
			fread(&prod, sizeof(Productos), 1, invent);
		}
	}
	return bandera;
}

bool BajarCita(FILE *citamed, char masccita[30])
{
	CitaMedica cita;
	rewind(citamed);
	bool bandera=false;
	
	fread(&cita, sizeof(CitaMedica), 1, citamed);
	while(!feof(citamed) && bandera==false)
	{
		if((strcmp(masccita, cita.mascota)==0) && cita.borrado==false)
		{
			cita.borrado=true;
			fseek(citamed, (long)-sizeof(CitaMedica), SEEK_CUR);
			fwrite(&cita, sizeof(CitaMedica), 1, citamed);
			bandera=true;
		}
		else
		{
			fread(&cita, sizeof(CitaMedica), 1, citamed);
		}
	}
	return bandera;
}

int BajarUsuario(FILE *user, char userborrar[30])
{
	usuarios userdat;
	rewind(user);
	int bandera=0;
	char contra[30];
	
	
	fread(&userdat, sizeof(usuarios), 1, user);
		
	while(!feof(user) && bandera==false)
	{
		if((strcmp(userborrar, userdat.usuario)==0) && userdat.borrado==false)
		{
			printf("Ingresar contrasenia: ");
			_flushall();
			gets(contra);
			if(strcmp(contra, "algoritmo123")==0)//contraseña de serie
			{
				userdat.borrado=true;
				fseek(user, (long)-sizeof(usuarios), SEEK_CUR);
				fwrite(&userdat, sizeof(usuarios), 1, user);
				bandera=1;
			}
			else
			{
				printf("\nContrasenia incorrecta");
				bandera=3;
			}
		}
		else
		{
			fread(&userdat, sizeof(usuarios), 1, user);
		}
	}
	return bandera;
}

int Menu()
{
	int opcion=0;
	
	printf("----MENU DE OPCIONES----");
	printf("\n");
	
	printf("\n0-Salir ");
	
	printf("\n1-Cargar Datos de Mascota ");
	printf("\n2-Cargar Productos en el Inventario ");
	printf("\n3-Cargar Cita Medica ");
	printf("\n");
	printf("\n4-Mostrar Datos de Mascota ");
	printf("\n5-Mostrar Productos en el Inventario ");
	printf("\n6-Mostrar Cita Medica ");
	printf("\n");
	printf("\n7-Dar de baja una mascota ");
	printf("\n8-Dar de baja un producto de inventario ");
	printf("\n9-Dar de baja un cita medica ");
	printf("\n");
	printf("\n10-Crear nuevo usuario ");
	printf("\n11-Dar de baja un usuario ");
	printf("\n12-Mostrar Usuarios ");
	printf("\n\n");
	printf("Seleccione una opcion: ");
	
	scanf("%d", & opcion);
	
	return opcion;
}

main()
{
	DatosMasc datos;
	Productos prod;
	CitaMedica cita;
	usuarios userdat;
	
	FILE *datomasc;
	FILE *invent;
	FILE *citamed;
	FILE *user;
	
	int opc=0;
	int acceso;
	char naming[30];
	char pass[30];
	
	user=fopen("usuarios.dat","r+b");
	if(user==NULL)
	{
		user=fopen("usuarios.dat","w+b");
		if(user==NULL)
		{
			printf("ERROR al abrir/crear archivo");
			exit(1);
		}
	}
	
	UsuarioAdmin(user);
	
	IniciarSesion(user, naming, pass);
	
	
	datomasc=fopen("mascotas.dat","r+b");
	if(datomasc==NULL)
	{
		datomasc=fopen("mascotas.dat","w+b");
		if(datomasc==NULL)
		{
			printf("ERROR al crear/abrir archivo");
			exit(1);
		}
	}
	
	invent=fopen("inventario.dat","r+b");
	if(invent==NULL)
	{
		invent=fopen("inventario.dat","w+b");
		if(invent==NULL)
		{
			printf("ERROR al crear/abrir archivo");
			exit(1);
		}
	}
	
	citamed=fopen("citamedica.dat","r+b");
	if(citamed==NULL)
	{
		citamed=fopen("citamedica.dat","w+b");
		if(citamed==NULL)
		{
			printf("ERROR al crear/abrir archivo");
			exit(1);
		}
	}
	
	do
	{
		system("cls");
		opc=Menu();
		system("cls");
		
		switch(opc)
		{
			case 1:
				{
					printf("\n");
					printf("CARGAR DATOS DE LA MASCOTA");
					printf("\n\n");
					datos=CargarDatosMascota(datomasc);
					break;
				}
			case 2:
				{
					printf("\n");
					printf("CARGAR PRODUCTOS EN EL INVENTARIO");
					printf("\n\n");
					prod=CargarInventario(invent);
					break;
				}
			case 3:
				{
					printf("\n");
					printf("CARGAR CITA MEDICA");
					printf("\n\n");
					cita=CargarCitaMedica(citamed);
					break;
				}
			case 4:
				{
					printf("\n");
					printf("MOSTRAR DATOS DE LA MASCOTA");
					printf("\n\n");
					muestradatos(datomasc);
					break;
				}
			case 5:
				{
					printf("\n");
					printf("MOSTRAR PRODUCTOS DEL INVENTARIO");
					printf("\n\n");
					muestrainventario(invent);
					break;
				}
			case 6:
				{
					printf("\n");
					printf("MOSTRAR DATOS DE LA CITA MEDICA");
					printf("\n\n");
					muestracitas(citamed);
					break;
				}
			case 7:
				{
					bool bandera;
					char mascot[30];
					printf("\n");
					printf("DAR DE BAJA UNA MASCOTA");
					printf("\nIngresar Nombre de la mascota a dar de baja: ");
					_flushall();
					gets(mascot);
					strupr(mascot);
					bandera=BajarMascota(datomasc, mascot);
					if(bandera==true)
					{
						printf("\nMascota dada de baja.");
					}
					else
					{
						printf("\nNo se encontro la mascota.");
					}
					break;
				}
			case 8:
				{
					bool bandera;
					char produ[30];
					printf("\n");
					printf("DAR DE BAJA UN PRODUCTO DE INVENTARIO");
					printf("\nIngresar nombre del producto a dar de baja: ");
					_flushall();
					gets(produ);
					strupr(produ);
					bandera=BajarProducto(invent, produ);
					if(bandera==true)
					{
						printf("\nSe dio de baja correctamente.");
					}
					else
					{
						printf("\nProducto no encontrado.");
					}
					break;
				}
			case 9:
				{
					bool bandera;
					char masccita[30];
					printf("\n");
					printf("DAR DE BAJA UNA CITA");
					printf("\nIngresar nombre de la mascota para dar de baja su cita: ");
					_flushall();
					gets(masccita);
					strupr(masccita);
					bandera=BajarCita(citamed, masccita);
					if(bandera==true)
					{
						printf("\nCita dada de baja.");
					}
					else
					{
						printf("\nNo se encontro la cita asignada a la mascota.");
					}
					break;
				}
			case 10:
				{
					printf("\n");
					printf("CREAR NUEVO USUARIO: ");
					printf("\n\n");
					CrearUsuario(user);
					break;
				}
			case 11:
				{
					char userborrar[30];
					int bandera=0;
					printf("\n");
					printf("DAR DE BAJA UN USUARIO: ");
					printf("\nIngresar nombre de usuario a dar de baja: ");
					_flushall();
					gets(userborrar);
					
					bandera=BajarUsuario(user, userborrar);
					if(bandera==1 || bandera==0)
					{
						if(bandera==1)
						{
							printf("\nUsuario dado de baja exitosamente");
						}
						else if(bandera==0)
						{
							printf("\nNo se encontro el usuario");
						}
					}
					break;
				}
			case 12:
				{
					printf("\n");
					printf("MOSTRAR USUARIOS");
					printf("\n\n");
					MostrarUsuarios(user);
					break;
				}
			case 0:
				{
					printf("\nSALIR");
					break;
				}
			default:
				{
					printf("\n");
					printf("OPCION INCORRECTA");
					printf("\n\n");
					break;
				}
		}
	
		printf("\n\n");
		system("pause");
		
	}while(opc!=0);
	
	fclose(datomasc);
	fclose(invent);
	fclose(citamed);
	fclose(user);
}
