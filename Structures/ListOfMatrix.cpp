#include <iostream>
#include <stdlib.h>
#include <string>
#include "SparseMatrix.cpp"
using namespace std;

class NodoListMaxtrix{
    public:
        string nombreCapa;
        int numeroCapa;
        SparseMatrix *capa;
        NodoListMaxtrix *sig;      
    public:
        NodoListMaxtrix(string nombreCapa, int numeroCapa, SparseMatrix* capa){
            this->nombreCapa=nombreCapa;
            this->numeroCapa=numeroCapa;
            this->capa=capa;
            sig=NULL;            
        }
};

class ListaDeMatrices{
    public:
        NodoListMaxtrix *primero;        
    public:
        ListaDeMatrices()
        {            
            primero=NULL;
        }

        void addList(string nombre, int numeroCapa, SparseMatrix *matriz)        
        {
            NodoListMaxtrix *nuevo = new NodoListMaxtrix(nombre,numeroCapa,matriz);           
            
            if(primero==NULL){
                primero=nuevo;                
            }            
            else
            {
                if(primero->numeroCapa < numeroCapa){
                    nuevo->sig=primero;
                    primero=nuevo;
                }
                else
                {
                    NodoListMaxtrix *temp = primero;
                    while((temp->sig!=NULL) && (temp->sig->numeroCapa > numeroCapa)) {
                        temp=temp->sig;
                    }
                    if(temp->sig==NULL){
                        temp->sig=nuevo;                        
                    }else{                    
                    nuevo->sig = temp->sig;
                    temp->sig=nuevo;
                    }
                }              
            }          
        }

        void printLS()        
        {
            NodoListMaxtrix *aux=primero;
            while(aux!=NULL){
                cout<<aux->numeroCapa;
                cout<<"\n";
                aux=aux->sig;
            }               
        }
};

/*
int main(){
    SparseMatrix* mx = new SparseMatrix();
    mx->add(1,1,1,1,1,1);
    mx->add(2,2,1,1,1,1);
    mx->add(3,3,1,1,1,1);

    ListaDeMatrices *ls = new ListaDeMatrices();
    ls->addList("head",4,mx);
    ls->addList("ho",7,mx);
    ls->addList("am",5,mx);
    ls->addList("res",1,mx);
    ls->addList("mac",2,mx);
    ls->printLS();   
    return 0;
}*/