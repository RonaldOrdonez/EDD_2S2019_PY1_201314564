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
    // position for x and y axis
        int position;
    // direction of node
        NodeMatrix *right;
        NodeMatrix *left;
        NodeMatrix *down;
        NodeMatrix *up;

    //-------------------------------------FUNCTIONS AND METHODS
    public:
    //Constructor of class NodeMatrix
        NodeMatrix(int position, int r, int g, int b)        
        {
            this->position = position;              
            this->r = r;
            this->g = g;
            this->b = b;
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
            NodeMatrix *temp = new NodeMatrix(0,0,0,0);
            head = temp;
        }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++ ADD NEW NODE +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        //ADD NEW NODE TO MATRIX        
        void add(int x, int y, int r, int g, int b)
        {
            add_x_header(x); //create header for axis "x"
            add_y_header(y); //create header for axis "y"
            NodeMatrix *new_node = new NodeMatrix(0,r,g,b); //create a new content node
            add_node_posX(new_node,x);  //add node to axis "x"
            add_node_posY(new_node,y);  //add node to axis "y"
        }

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++ HEADERS +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
        //CREATING HEADER FOR AXIS "X" - COLUMNS
        void add_x_header(int x)
        {
            if(head->right==NULL)   //when matriz dont have nodes in header x, header in x is empty
            {
                NodeMatrix *temp = new NodeMatrix(x,0,0,0);  //create a new node
                head->right = temp; // head right point to new node temp
                temp->left = head;  // new node temp left point to node head
            }
            else
            {
                NodeMatrix *temp = head; // create auxiliar node with reference to head 
                //travel to list verifying than temp node is less than the value x           
                while(temp->right != NULL && temp->right->position < x)
                {
                    temp = temp->right;
                }
                //add to end of the list
                if(temp->right==NULL)
                {
                    NodeMatrix *new_temp = new NodeMatrix(x,0,0,0);
                    temp->right = new_temp;
                    new_temp->left = temp;                
                }
                //add in the middle of the list
                else if(temp->right != NULL && temp->right->position != x)
                {
                    NodeMatrix *new_temp = new NodeMatrix(x,0,0,0);  // create new node with value x
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
                NodeMatrix *temp = new NodeMatrix(y,0,0,0);  //create a new node
                head->down = temp; // head down point to new node temp
                temp->up = head;  // new node temp up point to node head
            }
            else
            {
                NodeMatrix *temp = head; // create auxiliar node with reference to head 
                //travel to list verifying than temp node is less than the value y           
                while(temp->down != NULL && temp->down->position < y)
                {
                    temp = temp->down;
                }
                
                //add to end of the list
                if(temp->down==NULL)
                {
                    NodeMatrix *new_temp = new NodeMatrix(y,0,0,0);
                    temp->down = new_temp;
                    new_temp->up = temp;                
                }
                //add in the middle of the list
                else if(temp->down != NULL && temp->down->position != y)
                {
                    NodeMatrix *new_temp = new NodeMatrix(y,0,0,0);  // create new node with value y
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
        void add_node_posX(NodeMatrix* new_node, int x)
        {
            NodeMatrix *temp = head;
            while(temp->position != x)
            {
                temp = temp->right;
            }            
            if(temp->down == NULL)
            {
                temp->down = new_node;
                new_node->up = temp;
            }
        }        

        //ADD NODE IN AXIS "Y"
        void add_node_posY(NodeMatrix* new_node, int y)
        {
            NodeMatrix *temp = head;
            while(temp->position != y)
            {
                temp = temp->down;
            }
            if(temp->right == NULL)
            {
                temp->right = new_node;
                new_node->left = temp;
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
                cout<<temp->position;
                cout<<"->";
                temp = temp->right;
            }        
            cout<< temp->position <<endl;
            cout<<"";
        } 
        
        //PRINT HEADER IN Y- ROWS
        void print_y_header()
        {
            NodeMatrix *temp = head->down;
            while(temp->down != NULL)
            {
                cout<<temp->position;
                cout<<"\n";
                temp = temp->down;
            }
            cout<< temp->position;
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
                cout<<temp->position; 
                cout<<"->";
                if(temp->down!=NULL)
                {
                    cout<<"("<<temp->down->r <<"," <<temp->down->g <<","<< temp->down->b<<")";
                }
                cout<<"\n";
                temp= temp->right;
            }
            cout<< temp->position;
            cout<<"->";
            if(temp->down!=NULL)
            {
                cout<<"("<<temp->down->r <<"," <<temp->down->g <<","<< temp->down->b<<")";
            }
            cout<<"\n";
        }

        //PRINT NODES IN Y
        void print_nodes_y()        
        {
            NodeMatrix *temp = head->down;
            while(temp->down != NULL)
            {
                cout<<temp->position;
                cout<<"->";
                if(temp->right !=NULL)
                {
                    cout<<"("<<temp->right->r <<"," <<temp->right->g <<","<< temp->right->b<<")";
                }
                cout<<"\n";
                temp= temp->down;
            }
            cout<< temp->position;
            cout<<"->";
            if(temp->right !=NULL)
            {
                cout<<"("<<temp->right->r <<"," <<temp->right->g <<","<< temp->right->b<<")";
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
    matrix->add(2,2,256,111,230);
    matrix->add(1,1,257,112,231);
    matrix->add(5,5,258,113,232);
    matrix->add(4,4,259,114,233);
    matrix->add(8,8,260,115,234);
    matrix->printHeaders();
    cout<<"\n";
    cout<<"\n";
    matrix->printNodes();
    return 0;
}