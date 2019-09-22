#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Structures/ListOfMatrix.cpp"
#include "Structures/SparseMatrix.cpp"
#include <vector>
#include <cstdlib>
using namespace std;

int opcionMenu;
ListaDeMatrices *cubo = new ListaDeMatrices("inicio");

void mostrarMenu();
void insertarImagen();
void seleccionarImagen();
void aplicarFiltro();
void edicionManual();
void exportarImagen();
void generarReportes();
void salir();
void regresarAlMenu();


//*****************************************************************************************************************
//*************************************EJECUCION DEL MAIN**********************************************************
//*****************************************************************************************************************
int main(){
    
    mostrarMenu();
    return 0;
}

/*=======================================================================================================*/
/*==============================MENU DE INICIO===========================================================*/
/*=======================================================================================================*/
void mostrarMenu()
{
    cout<<"=========================MENU========================="<<endl;
    cout<<"1 - INSERTAR IMAGEN"<<endl;
    cout<<"2 - SELECCIONAR IMAGEN"<<endl;
    cout<<"3 - APLICAR FILTROS"<<endl;
    cout<<"4 - EDICION MANUAL"<<endl;
    cout<<"5 - EXPORTAR IMAGEN"<<endl;
    cout<<"6 - REPORTES"<<endl;
    cout<<"7 - SALIR"<<endl;
    cout<<"";
    cout<<"Seleccionar Opción: ";
    cin>>opcionMenu;   
    
    switch(opcionMenu){
        case 1:
            insertarImagen();
            break;        
        case 2:
            seleccionarImagen();
            break;
        case 3:
            aplicarFiltro();
            break;
        case 4:
            edicionManual();
            break;
        case 5:
            exportarImagen();
            break;
        case 6:
            generarReportes();
            break;
        case 7:
            salir();
            break;
        default:
            regresarAlMenu();
    }
}

/*=======================================================================================================*/
/*==============================INSERTAR IMAGEN==========================================================*/
/*=======================================================================================================*/
void insertarImagen()
{    
    string rutaEntrada="";
    string carpeta="";   
    string config="";    
    vector<int> numeroCapa;
    vector<string> nombreCapa;
    
    //1. pedir el nombre del archivo a cargar que tambien es el nombre del csv con las configuraciones
    cout<<"\n";
    cout<<"Ingrese nombre de archivo a cargar (archivo .csv): "<<"\n";
    cin>>rutaEntrada;    
    bool bandera=false;
    for(int i=0; i<rutaEntrada.length();i++){
        if(rutaEntrada[i]=='.'){
            bandera=true;            
        }   
        else if((rutaEntrada[i]!='.')&&(bandera==false))
        {
            carpeta+=rutaEntrada[i];
        }     
    } 
    //2. abrir el archivo de entrada
    ifstream ffile("Images/"+carpeta+"/"+rutaEntrada);
    if(!ffile.is_open()) cout<<"ERROR:AL CARGAR ARCHIVO"<<"\n";
    string Layer;
    string File;
    while(ffile.good()){        
        getline(ffile,Layer,',');
        getline(ffile,File,'\n');
        if(Layer=="Layer"){            
        }
        else if(Layer=="0"){
            config=File;
        }
        else{
            numeroCapa.push_back(atoi(Layer.c_str()));
            nombreCapa.push_back(File);
        }
    }
    ffile.close(); 
    cout<<"CARGA EXITOSA DE ARCHIVO"<<"\n";    
    //el nombre de mi lista de matrices es el nombre de la imagen
    cubo->nombreLista=carpeta;
    
    //comenzar a crear las capas
    //1. tomar el nombre de una capa y abrir el archivo, leerlo
    for(int j=0; j < numeroCapa.size(); j++){        
        SparseMatrix *insertCapa = new SparseMatrix();

        ifstream fcapa("Images/"+carpeta+"/"+nombreCapa[j]);
        if(!fcapa.is_open()) cout<<"ERROR:AL CARGAR CAPA "<<nombreCapa[j]<<"\n";        
        int x=j+1;        
        int y=0;
        string color;
        string coordenada;
        while(fcapa.good()){        
            y++;
            getline(fcapa,coordenada);            
            if(coordenada=="x"){}
        }       
        
        cout<<numeroCapa[j];
        cout<<nombreCapa[j];
        cout<<"\n";    
    }



    mostrarMenu();
}

void seleccionarImagen(){}
void aplicarFiltro(){}
void edicionManual(){}
void exportarImagen(){}
void generarReportes(){}
void salir(){exit(-1);}
void regresarAlMenu(){ mostrarMenu();}