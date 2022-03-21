#include <iostream>
#include <stdio.h>  
#include <string.h> 
#include <windows.h>
#include <fstream>
using namespace std;
const char *nombe_archivo = "archivo.dat";

struct Estudiante{
	int codigo;
	char nombre[50];
	char apellido[50];
	char direccion[50];
	int telefono;
};
 void ingresar_estudiante();
 void abrir_estudiante();
 void modificar_estudiante();
 void buscar_codigo();
 void eliminar();
 
int main (){
	abrir_estudiante();
	eliminar();
	cout<<"Estudiante Eliminado"<<endl;
    ingresar_estudiante();
    modificar_estudiante();
	modificar_estudiante();


	return 0;	
}

void buscar_codigo(){
		FILE* archivo = fopen(nombe_archivo,"rb");	
	int pos=0,indice=0,cod=0;
	cout<<"Que codigo desea ver: ";
	cin>>cod;
	
	Estudiante estudiante;
	fread(&estudiante,sizeof(Estudiante),1,archivo);	
	do{
	   if(estudiante.codigo == cod)	{
	   	cout<<"Codigo: "<<estudiante.codigo<<endl;
	   	cout<<"Nombres: "<<estudiante.nombre<<endl;
	   	cout<<"Apellidos: "<<estudiante.apellido<<endl;
	   	cout<<"Telefono: "<<estudiante.telefono<<endl;
	   	cout<<"Direccion: "<<estudiante.direccion<<endl;
	   }
	   fread(&estudiante,sizeof(Estudiante),1,archivo);	
	} while(feof(archivo)==0);
	
	
	
	fclose(archivo);
}

void buscar_indice(){
	FILE* archivo = fopen(nombe_archivo, "rb");
	
	int pos=0;
	cout<<"Que registro desea ver: ";
	cin>>pos;
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Estudiante), SEEK_SET );
	
	Estudiante estudiante;
	
    fread ( &estudiante, sizeof( Estudiante ), 1, archivo );

    	cout << "Codigo: " << estudiante.codigo << endl;
        cout << "Nombre: " << estudiante.nombre << endl;
        cout << "Apellido: " << estudiante.apellido << endl;
        cout << "Telefono: " << estudiante.telefono << endl;
        cout << "Direccion" << estudiante.direccion <<endl;
        cout << endl;
	
	fclose(archivo);

	
}


void abrir_estudiante(){

	system("cls");
	FILE* archivo = fopen(nombe_archivo, "rb");
	if(!archivo) {
		archivo = fopen(nombe_archivo, "w+b");
	}
	Estudiante estudiante;
	int registro=0;
	fread ( &estudiante, sizeof(Estudiante), 1, archivo );
	cout<<"Datos del Estudiante:";
	cout<<estudiante.nombre<<endl;
	cout<<"____________________________________________________________________"<<endl;
	cout << "id" <<"|"<< "Codigo" <<"|"<< "Nombre Completo"<<" | "<<"Apellido Completo"<<" | "<<"Celular"<<" | "<<"Direccion"<<endl;	
		do{
		cout<<"____________________________________________________________________"<<endl;
		cout << registro <<" |  "<< estudiante.codigo <<" | "<< estudiante.nombre<<" | "<<estudiante.apellido<<" | "<<estudiante.telefono<<" | "<<estudiante.direccion<<endl;
        
        
		fread ( &estudiante, sizeof(Estudiante), 1, archivo );
		registro += 1;	
		} while (feof( archivo ) == 0);
		
    cout<<endl;
    
		fclose(archivo);
	}
void ingresar_estudiante(){
	
	char continuar;
	FILE* archivo = fopen(nombe_archivo, "ab"); // ab
	
	
		Estudiante estudiante;
		 string nombre,apellido;
		do{
			fflush(stdin);
			
		cout<<"Ingrese el Codigo:";
		cin>>estudiante.codigo;
        cin.ignore();
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(estudiante.nombre, nombre.c_str()); 
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(estudiante.apellido, apellido.c_str()); 
		
		cout<<"Ingrese el Telefono:";
		cin>>estudiante.telefono;
		cin.ignore();
		
		cout<<"Ingresa la direccion:";
		cin>>estudiante.direccion;
		cin.ignore();
		
		fwrite( &estudiante, sizeof(Estudiante), 1, archivo );
		
		cout<<"Desea Agregar otro Nombre s/n : ";
		cin>>continuar;
		} while((continuar=='s') || (continuar=='S') );
		
	
	fclose(archivo);
	abrir_estudiante();
	//buscar_indice();	
	buscar_codigo();
}
void modificar_estudiante(){
	
	FILE* archivo = fopen(nombe_archivo, "r+b");
	
		int id;
		string nombre,apellido;	
    	Estudiante estudiante;
    
		cout << "Ingrese el ID que desea Modificar: ";
    		cin >> id;
    		fseek ( archivo, id * sizeof(Estudiante), SEEK_SET );  // esto es lo que permite modificar en la pocision
	
		cout<<"Ingrese el Codigo:";
		cin>>estudiante.codigo;
        cin.ignore();
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(estudiante.nombre, nombre.c_str()); 
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(estudiante.apellido, apellido.c_str()); 
		
		cout<<"Ingrese el Telefono:";
		cin>>estudiante.telefono;
		cin.ignore();
		
		cout<<"Ingresa la direccion:";
		cin>>estudiante.direccion;
		cin.ignore();
		
		fwrite( &estudiante, sizeof(Estudiante), 1, archivo );
		
	fclose(archivo);
	abrir_estudiante();
		system("PAUSE");
}
void eliminar(){
		int id;
//		char nombre[50];
//		char apellido[50];
	   	Estudiante estudiante;
    	 ifstream salida;
    	 salida.open("archivo.data",ios::in);
    	 
    	 ofstream entrada;
    	 entrada.open("espera.data",ios::out);
    	 
    	 if(salida.fail()){
    	 	cout<<"Error al momento de eliminar reinicia el programa";
		 }
		 else{
		 	char aux[50];
		 	cout<<"Ingresa el nombre del alumno que quieres eliminar:";
		 	cin>>aux;
		 	salida>>estudiante.nombre;
		 	
		 	while(!salida.eof()){
		 		salida>>estudiante.codigo>>estudiante.apellido;
		 		if(strcmp(aux,estudiante.nombre)==0){
		 			cout<<"El Alumno ha sido eliminado";
				 }
				 else{
				 	entrada<<estudiante.nombre<<" "<<estudiante.apellido<<" "<<estudiante.codigo;
				 }
				 salida>>estudiante.nombre;
			 }
		 entrada.close();
		 salida.close();
		 remove("archivo.data");
		 rename("espera.data","archivo.data");


		 }

     	 entrada.close();
		 salida.close();
		 remove("archivo.data");
		 rename("espera.data","archivo.data");
    	
}
