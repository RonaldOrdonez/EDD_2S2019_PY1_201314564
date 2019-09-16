#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

/*****************************************************************************************************************
######################################### CLASS NODE'S MATRIX ###################################################
******************************************************************************************************************/
class NodeMatrix
{
    //-------------------------------------VARIABLES
    public:
    // r,g,b used for colors
        int r;
        int g;
        int b;
    // position x,y,z
        int x;
        int y;
        int z;
    // direction of node
        NodeMatrix *right;
        NodeMatrix *left;
        NodeMatrix *down;
        NodeMatrix *up;

    //-------------------------------------FUNCTIONS AND METHODS
    public:
    //Constructor of class NodeMatrix
        
        //Constructor with parameters
        NodeMatrix(int x,int y, int z, int r, int g, int b)        
        {
            //position x,y,z
            this->x = x;
            this->y = y;
            this->z = z;
            //colors r,g,b
            this->r = r;
            this->g = g;
            this->b = b;
            //direction right,left,down,up
            right = NULL;
            left = NULL;
            down = NULL;
            up = NULL;
        }

        //Constructor witout parameters
        NodeMatrix(){
            this->x=0;
            this->y=0;
            this->z=0;

            this->r=0;
            this->g=0;
            this->b=0;

            right = NULL;
            left = NULL;
            down = NULL;
            up = NULL;
        }   
};

/*****************************************************************************************************************
############################################# CLASS MATRIX ########################################################
******************************************************************************************************************/
class SparseMatrix
{
    public:
        //BEGIN WITH NodeMatrix TYOE CALLED head
        NodeMatrix *head;

        //CONSTRUCTOR  
        SparseMatrix()
        {
            NodeMatrix *temp = new NodeMatrix();
            head = temp;
        }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++ ADD NEW NODE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        //ADD NEW NODE TO MATRIX        
        void add(int x, int y, int z, int r, int g, int b)
        {
            head->z = z;
            add_x_header(x); //create header for axis "x"
            add_y_header(y); //create header for axis "y"
            NodeMatrix *new_node = new NodeMatrix(x,y,z,r,g,b); //create a new content node
            add_node_posX(new_node, x, y);  //add node to axis "x"
            add_node_posY(new_node, y, x);  //add node to axis "y"
        }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++ HEADERS +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        //CREATING HEADER FOR AXIS "X" - COLUMNS
        void add_x_header(int x)
        {
            if(head->right==NULL)   //when matriz dont have nodes in header x, header in x is empty
            {
                NodeMatrix *temp = new NodeMatrix(x,0,0,0,0,0);  //create a new node
                head->right = temp; // head right point to new node temp
                temp->left = head;  // new node temp left point to node head
            }
            else
            {
                NodeMatrix *temp = head; // create auxiliar node with reference to head 
                //travel to list verifying than temp node is less than the value x           
                while(temp->right != NULL && temp->right->x < x)
                {
                    temp = temp->right;
                }
                //add to end of the list
                if(temp->right==NULL)
                {
                    NodeMatrix *new_temp = new NodeMatrix(x,0,0,0,0,0);
                    temp->right = new_temp;
                    new_temp->left = temp;                
                }
                //add in the middle of the list
                else if(temp->right != NULL && temp->right->x != x)
                {
                    NodeMatrix *new_temp = new NodeMatrix(x,0,0,0,0,0);  // create new node with value x
                    NodeMatrix *der = temp->right; // node "der" keep to reference to value right to the node

                    temp->right = new_temp; // reference to current right node equals new node with value "x"
                    new_temp->left =temp;   // node with value "x", its left point to current node
                    new_temp->right = der;  // node with value "x", its right point to node "der"
                    der->left = new_temp;   // node "der" with reference saved point to new node 
                }
            }         
        }

        //CREATING HEADER FOR AXIS "Y" - ROWS
        void add_y_header(int y)
        {
            if(head->down == NULL)   //when matriz dont have nodes in header y, header in y is empty
            {
                NodeMatrix *temp = new NodeMatrix(0,y,0,0,0,0);  //create a new node
                head->down = temp; // head down point to new node temp
                temp->up = head;  // new node temp up point to node head
            }
            else
            {
                NodeMatrix *temp = head; // create auxiliar node with reference to head 
                //travel to list verifying than temp node is less than the value y           
                while(temp->down != NULL && temp->down->y < y)
                {
                    temp = temp->down;
                }
                
                //add to end of the list
                if(temp->down==NULL)
                {
                    NodeMatrix *new_temp = new NodeMatrix(0,y,0,0,0,0);
                    temp->down = new_temp;
                    new_temp->up = temp;                
                }
                //add in the middle of the list
                else if(temp->down != NULL && temp->down->y != y)
                {
                    NodeMatrix *new_temp = new NodeMatrix(0,y,0,0,0,0);  // create new node with value y
                    NodeMatrix *dwn = temp->down; // node "der" keep to reference to value down to the node

                    temp->down = new_temp; // reference to current down node equals new node with value "y"
                    new_temp->up =temp;   // node with value "y", its left point to current node
                    new_temp->down = dwn;  // node with value "y", its right point to node "der"
                    dwn->up = new_temp;   // node "der" with reference saved point to new node 
                }
            }

        }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++ ADD NEW NODE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 
        //ADD NODE IN AXIS "X"
        void add_node_posX(NodeMatrix* new_node, int x, int y)
        {
            NodeMatrix *temp = head;
            //busca la cabecera que coincide con la que queremos insertar
            while(temp->x != x) 
            {
                temp = temp->right; 
            }            
            //significa que aun no hay nodos en la lista de la cabecera actual
            if(temp->down == NULL)
            {
                temp->down = new_node;
                new_node->up = temp;
            }        
            //hay x lo menos un nodo
            else{
                //verificar si el primer nodo de la lista es mayor que el que quiero insertar y si es TRUE, lo inserto antes
                if(temp->down->y > y){
                    NodeMatrix *aux = temp->down;
                    new_node->down = aux;
                    aux->up = new_node;
                    temp->down = new_node;
                    new_node->up = temp;
                }
                //sino se inserta a la primera 
                else{
                    //avanza hasta que "y" sea menor que el aux->down
                    NodeMatrix *aux = temp;
                    while((aux->down!=NULL) && (aux->down->y < y)){
                        aux=aux->down;
                    }
                    //si llego al final de la lista, significa que el aux->down es null y agrega el new_node al final de la lista
                    if(aux->down == NULL){
                        aux->down = new_node;
                        new_node->up = aux;
                    }
                    //sino la insercion se realiza en medio de la lista
                    else{
                        new_node->down = aux->down;
                        aux->down->up = new_node;
                        aux->down = new_node;
                        new_node->up = aux;
                    }
                }             
            }                         
        }        

        //ADD NODE IN AXIS "Y"
        void add_node_posY(NodeMatrix* new_node, int y, int x)
        {
            NodeMatrix *temp = head;
            while(temp->y != y)
            {
                temp = temp->down;
            }
            //significa que aun no hay nodos en la lista de la cabecera actual
            if(temp->right == NULL)
            {
                temp->right = new_node;
                new_node->left = temp;
            }        
            //hay por lo menos un nodo
            else{
                //verificar si el primer nodo de la lista es mayor que el que quiero insertar y si es TRUE, lo inserto antes
                if(temp->right->x > x){
                    NodeMatrix *aux = temp->right;
                    new_node->right = aux;
                    aux->left = new_node;
                    temp->right = new_node;
                    new_node->left = temp;
                }
                //sino se inserta a la primera 
                else{
                    //avanza hasta que "y" sea menor que el aux->down
                    NodeMatrix *aux = temp;
                    while((aux->right!=NULL) && (aux->right->x < x)){
                        aux=aux->right;
                    }
                    //si llego al final de la lista, significa que el aux->down es null y agrega el new_node al final de la lista
                    if(aux->right == NULL){
                        aux->right = new_node;
                        new_node->left = aux;
                    }
                    //sino la insercion se realiza en medio de la lista
                    else{
                        new_node->right = aux->right;
                        aux->right->left = new_node;
                        aux->right = new_node;
                        new_node->left = aux;
                    }
                }             
            }                 
                      
        }

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++ PRINT HEADERS +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

        //PRINT IN CONSOLE THE VALUES LIST OF ROWS AND COLUMNS    
        void printHeaders()
        {
            print_x_header();
            print_y_header();
        }

        //PRINT HEADER IN X - COLUMNS
        void print_x_header()
        {
            NodeMatrix *temp = head;
            while(temp->right != NULL)
            {
                cout<<temp->x;
                cout<<"->";
                temp = temp->right;
            }        
            cout<< temp->x <<endl;
            cout<<"";
        } 
        
        //PRINT HEADER IN Y- ROWS
        void print_y_header()
        {
            NodeMatrix *temp = head->down;
            while(temp->down != NULL)
            {
                cout<<temp->y;
                cout<<"\n";
                temp = temp->down;
            }
            cout<< temp->y;
            cout<<"\n";
        }

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++ PRINT NODE CONTENTS++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        //PRINT NODES
        void printNodes()
        {
            print_nodes_x();
            cout<<"\n";
            print_nodes_y();
       }

       //PRINT NODES IN X
        void print_nodes_x()
        {
            NodeMatrix *temp = head->right;
            while(temp->right != NULL)
            {
                NodeMatrix *aux=temp;
                cout<<temp->x; 
                cout<<"->";
                while(temp->down!=NULL){
                    cout<<"("<<temp->down->r <<"," <<temp->down->g <<","<< temp->down->b<<")";
                    cout<<"->";
                    temp = temp->down;                    
                }                
                cout<<"\n";
                temp = aux;
                temp= temp->right;
            }
            cout<< temp->x;
            cout<<"->";
            while(temp->down!=NULL){
                cout<<"("<<temp->down->r <<"," <<temp->down->g <<","<< temp->down->b<<")";
                cout<<"->";
                temp = temp->down;                    
            }   
            cout<<"\n";
        }

        //PRINT NODES IN Y
        void print_nodes_y()        
        {
            NodeMatrix *temp = head->down;
            while(temp->down != NULL)
            {
                NodeMatrix *aux=temp;
                cout<<temp->y;
                cout<<"->";
                while(temp->right!=NULL){
                    cout<<"("<<temp->right->r <<"," <<temp->right->g <<","<< temp->right->b<<")";
                    cout<<"->";
                    temp = temp->right;                    
                }                   
                cout<<"\n";
                temp = aux;
                temp= temp->down;
            }
            cout<< temp->y;
            cout<<"->";
            while(temp->right!=NULL){
                cout<<"("<<temp->right->r <<"," <<temp->right->g <<","<< temp->right->b<<")";
                cout<<"->";
                temp = temp->right;                    
            }  
            cout<<"\n";            
        }
};

/*****************************************************************************************************************
############################################# PRINCIPAL METHOD####################################################
******************************************************************************************************************/
int main()
{
    SparseMatrix *matrix = new SparseMatrix;
    matrix->add(1,1,1,100,110,120);
    matrix->add(2,2,1,101,111,121);
    matrix->add(5,5,1,102,112,122);
    matrix->add(4,4,1,103,113,123);
    matrix->add(7,7,1,104,114,124);

    matrix->add(2,4,1,1,2,3);
    matrix->add(2,7,1,5,6,7);
    matrix->add(7,4,1,9,9,9);
    matrix->add(5,1,1,6,6,6);
    matrix->printHeaders();
    cout<<"\n";
    cout<<"\n";
    matrix->printNodes();
    return 0;
}