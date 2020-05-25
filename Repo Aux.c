#include <stdio.h>
#include <malloc.h> 
#include <string.h>  

#define cantEstado 4
#define valorPila 2
#define posicionCaracter 6

typedef struct{ //relleno de matriz
    int estadoSig;
    char elemento[2];  
}datoTT;

typedef struct pila{ //contenido de la pila
    char dato;
    struct pila *sig;
}Pila;

typedef Pila * PilaPtr; // Puntero para acceder a la pila


//defimos funciones
int selecColumna (char); //Selecciona la columna dependiendo del caracter leido de la expresión
void insertar(PilaPtr *tope, char dato); //mandas puntero y lo q queres agregar
char eliminar(PilaPtr *tope);//elimina ultimo nodo y devuelve su dato
int cimaPila(PilaPtr *tope); //ya devuelve 0=$ o 1=R para saber a cual de las dos matrices entrar

//definimos datos globales
datoTT auxCopiaDatosMatriz;

char caractSalida; //char de condicion de salida
char expresion [50]; //almacena la expresion 

int recExpr;//es i para recorrer la palabra
int caracter;//a que columna corresponde(en relacion al caracter leido de la expresión)
int estado;
int cima;//cima de la pila (1 si hay una r y 0 si hay un $)
char elementoSuperior; //variable donde se guarda la cima
int tamano_maximo=49;

//La matriz se rellena columna por columna primero delante y luego atras
//ejemplo:{{(0,0,0),(0,0,1)},{(0,1,0),(0,1,1)},{(0,2,0),(0,2,1)}... y como es un struck se le incertan los datos en vez de () con {}
datoTT tt[posicionCaracter][cantEstado][valorPila]={
     {{{3,"$"},{3,"R"}},{{1,"$"},{1,"R"}},{{3,"$"},{3,"R"}},{{3,"$"},{3,"R"}}},    //columna1
     {{{1,"$"},{1,"R"}},{{1,"$"},{1,"R"}},{{3,"$"},{3,"R"}},{{3,"$"},{3,"R"}}},    //columna2
     {{{3,"$"},{3,"R"}},{{0,"$"},{0,"R"}},{{0,"$"},{0,"R"}},{{3,"$"},{3,"R"}}},    //columna3
     {{{0,"R$"},{0,"RR"}},{{3,"$"},{3,"R"}},{{3,"$"},{3,"R"}},{{3,"$"},{3,"R"}}},  //columna4
     {{{3,"$"},{3,"R"}},{{3,"$"},{2,"Ɛ"}},{{3,"$"},{2,"Ɛ"}},{{3,"$"},{3,"R"}}},    //columna5
     {{{3,"$"},{3,"R"}},{{3,"$"},{3,"R"}},{{3,"$"},{3,"R"}},{{3,"$"},{3,"R"}}},    //columna6
     
};



int main()
{
    
    do{
        PilaPtr tope=NULL; 
        recExpr=0;
        estado=0;
        insertar(&tope,'$'); //elemento base de la pila
        printf("Ingrese la expresion que desea averiguar si es valida o invalida\n");
        fgets(expresion, tamano_maximo, stdin);   
        while(expresion[recExpr]!='\n' && estado!=3) {
            if(expresion[recExpr]!=32){ // 32 representa espacio en ascii 
                caracter=selecColumna(expresion[recExpr]); //devuelve la columna en la entra el caracter en al matriz
                cima=cimaPila(&tope);//averigua si se debe analizar en matriz delantera o trasera ( , ,0) o ( , ,1)
                auxCopiaDatosMatriz=tt[caracter][estado][cima];
                estado=auxCopiaDatosMatriz.estadoSig;
                
                elementoSuperior=eliminar(&tope);     //Pop obligatorio
                insertar(&tope,elementoSuperior);     //Push obligatorio
                
                //strcmp esta definido en  #include <string.h> y es capaz de comparar cadenas, dando 0 si son iguales   
                if((strcmp(auxCopiaDatosMatriz.elemento,"RR")==0) || (strcmp(auxCopiaDatosMatriz.elemento,"R$")==0)){
                    insertar(&tope,'R');
                }
                if(strcmp(auxCopiaDatosMatriz.elemento,"Ɛ")==0){
                    char inservible=eliminar(&tope); 
                }
            }          
            recExpr++;
        }   
        
        if(estado==3||tope->dato!='$'||estado==0){  //condiciones  para que una expresion sea invalida
            printf("La expresion %s",expresion);
            printf("es invalida \n");
        }else{
            printf("La expresion %s",expresion);
            printf("es valida \n");
        }
        while(tope!=NULL){                      //elimina toda la pila hasta q tope sea null
            char inservible=eliminar(&tope);
        }
        printf("Ingrese el caracter Y/y si desea ingresar otra expresion, sino ingrese N/n\n");
        scanf(" %s",&caractSalida);    //salida del programa
        char c;
        while ((c = fgetc(stdin)) != '\n' && c != EOF);
    }while(caractSalida=='y'||caractSalida=='Y');
    return 0;
}    
    

int selecColumna (char caracter) 
 {
    int columnaCaracter;
        if  (caracter==48)
        {
           //48 es 0 en ascii
           columnaCaracter=0;
       } else if (caracter>=49 && caracter <=57)
       {
           // 1-9
           columnaCaracter=1;
       } else if (caracter==42 || caracter==43 || caracter==45 || caracter==47)
       {
           // * + - /
           columnaCaracter = 2;
       } else if (caracter == 40)
       {
           // (
           columnaCaracter = 3;
       } else if (caracter==41)
       {
           // )
           columnaCaracter = 4;
       } else 
       {
           columnaCaracter = 5;
       }

    return columnaCaracter;
 }


void insertar(PilaPtr *tope, char dato){
    PilaPtr nuevo; 
    nuevo=(PilaPtr) malloc(sizeof(Pila));//reservar memoria
    nuevo->dato=dato;
    nuevo->sig=*tope;   
    *tope=nuevo;

}

char eliminar(PilaPtr *tope){
    PilaPtr temp;
    char dato;
    temp=*tope;
    dato=temp->dato;
    *tope=(*tope)->sig;
    free(temp);
    return dato;
}

int cimaPila(PilaPtr *tope){
    
    char aux;
    aux=(*tope)->dato;
    if(aux=='$'){
        return 0;
    }else{
        return 1;
    }
    
}
