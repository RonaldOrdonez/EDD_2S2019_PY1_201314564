#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Nodo{
    public:
        int dato;
        Nodo* sig;
        Nodo* ante;
    
    public:
        Nodo(){
            dato=0;
            sig=NULL;
            ante=NULL;
        }
        Nodo(int dato){
            this->dato=dato;
            sig=NULL;
            ante=NULL;
        }
};
class Lista{    
    public:
        Nodo* primero;
        Nodo* ultimo;
    public:
        Lista(){            
            primero=NULL;
            ultimo=NULL;
        }

        void add(int dato){
            Nodo* nuevo = new Nodo(dato);
            if(primero==NULL){
                primero=nuevo;
                ultimo=nuevo;
                primero->sig=primero;
                primero->ante=ultimo;
            }
            else{
                //verificar primero
                if(dato<primero->dato){
                    primero->ante=nuevo;                    
                    nuevo->sig=primero;
                    nuevo->ante=ultimo;
                    primero=nuevo;
                    ultimo->sig=primero;
                }
                //verificar ultimo
                if(dato>ultimo->dato){
                    ultimo->sig=nuevo;
                    nuevo->ante=ultimo;
                    nuevo->sig=primero;
                    ultimo=nuevo;
                    primero->sig=ultimo;
                }
                //insertar en el centro
                Nodo* aux=primero;
                while(aux->sig!=NULL & dato>aux->sig->dato){
                    aux=aux->sig;
                }
                
            }


        }

};

int main(){
    return 0;
}

