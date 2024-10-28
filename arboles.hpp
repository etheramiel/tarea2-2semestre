#ifndef ARBOLES_HPP
#define ARBOLES_HPP

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include <stdio.h>
#include <cmath>
#include "director.hpp"



class Arboles {
private :
    struct aNodo {
    Director * val ;
    aNodo * izq ;
    aNodo * der ;
    };
    aNodo * root_1 ; // raiz arbol ordenado por directores
    aNodo * curr_1 ;
    size_t size_1 ;
    aNodo * root_2 ; // raiz arbol ordenado por rating
    aNodo * curr_2 ;
    size_t size_2 ;

    int index;

public :
    Arboles () ; // constructor
    ~ Arboles () ; // destructor
    void insertar_pelicula ( Pelicula * pelicula ) ; //LISTO
    void copiar_arbol () ;// hace copia de arbol 1 en arbol 2 ordenado respecto de rating
    Director * buscar_director ( std::string director ) ; // retorna arreglo de peliculas   LISTO
    Pelicula * buscar_pelicula ( std::string pelicula ) ; // retorna peliculas  
    void mejores_directores ( int n ) ; // Muestra por pantalla los mejores n directores .Enumerando de 1 a n .
    void peores_directores ( int n ) ; // Muestra por pantalla los peores n directores . Enumerando desde m ( cantidad de directores ) hasta m - n .

    Pelicula *buscar_pelicula_nodo(aNodo *nodo, std::string nombre);
    void copiar_arbol_nodo(aNodo* nodo);
    void insertar_director_por_promedio(Director* director);
    void recorrer_arbol_mayor(aNodo* nodo, int n, int& count);
    void recorrer_arbol_menor(aNodo* nodo, int n, int& count);
};



Arboles::Arboles() : root_1(nullptr), size_1(0), root_2(nullptr), size_2(0) {}

Arboles::~Arboles() {
    while (root_1) {
        aNodo* actual = root_1;
        root_1 = root_1->der;
        delete actual->val;
        delete actual;
    }

    while (root_2) {
        aNodo* actual = root_2;
        root_2 = root_2->der;
        delete actual->val;
        delete actual;
    }
}


/* ****
* void Arboles::copiar_arbol_nodo(aNodo* nodo)
******
* Copia el árbol de directores ordenado por nombre a un nuevo árbol ordenado por promedio de rating.
******
* Input :
* aNodo* nodo : Puntero al nodo actual
* 
* 
******
* Returns :
* 
* Ninguno
*
**** */

void Arboles::copiar_arbol_nodo(aNodo* nodo) {
    if (!nodo) return;

    copiar_arbol_nodo(nodo->izq);

    Director* director_copia = new Director;
    director_copia = nodo->val;

    nodo->val->calcular_rating_promedio(); 

    director_copia->calcular_rating_promedio();

    insertar_director_por_promedio(director_copia);

    copiar_arbol_nodo(nodo->der);
}

/* ****
* void Arboles::mejores_directores(int n)
******
* Muestra por pantalla los mejores n directores, enumerando de 1 a n.
******
* Input :
*
* int n : Número de directores a mostrar
* 
******
* Returns :
* 
* Ninguno
*
**** */

void Arboles::mejores_directores(int n) {
    if (n <= 0) {
        std::cerr << "Error: n debe ser un número positivo." << std::endl;
        return;
    }

    int count = 0;  
    recorrer_arbol_mayor(root_2, n, count);
}
    
/* ****
* void Arboles::recorrer_arbol_mayor(aNodo* nodo, int n, int& count)
******
* Recorre el árbol de directores ordenado por promedio de rating, mostrando los n directores con mayor rating.
******
* Input :
*
* aNodo* nodo : Puntero al nodo actual
* int n : Número de directores a mostrar
* int& count : Contador de directores mostrados
* 
******
* Returns :
* 
* Ninguno
*
**** */

void Arboles::recorrer_arbol_mayor(aNodo* nodo, int n, int& count) {
    if(nodo == nullptr || count >= n)return;
    

    recorrer_arbol_mayor(nodo->der, n, count);
    
    if (count < n) {
        std::cout <<"("<< count + 1 << ") " << nodo->val->get_nombre_director()  << std::endl;
        count++;
    }
    
    recorrer_arbol_mayor(nodo->izq, n, count);

}

/* ****
* void Arboles::peores_directores(int n)
******
* Muestra por pantalla los peores n directores, enumerando desde m (cantidad de directores) hasta m - n.
******
* Input :
*
* int n : Número de directores a mostrar
* 
******
* Returns :
* 
* Ninguno
*
**** */

void Arboles::peores_directores(int n) {
    if (n <= 0) {
        std::cerr << "Error: n debe ser un número positivo." << std::endl;
        return;
    }
    index = size_1;
    int count = 0;  
    recorrer_arbol_menor(root_2, n, count);
}
    
/* ****
* void Arboles::recorrer_arbol_menor(aNodo* nodo, int n, int& count)
******
* Recorre el árbol de directores ordenado por promedio de rating, mostrando los n directores con menor rating.
******
* Input :
*
* aNodo* nodo : Puntero al nodo actual
* int n : Número de directores a mostrar
* int& count : Contador de directores mostrados
* 
******
* Returns :
* 
* Ninguno
*
**** */

void Arboles::recorrer_arbol_menor(aNodo* nodo, int n, int& count) {
    if(nodo == nullptr || count >= n)return;

    recorrer_arbol_menor(nodo->izq, n, count);
    
    if (count < n) {
        std::cout <<"("<< index<< ") " << nodo->val->get_nombre_director() << std::endl;
        index --;
        count++;
    }

    recorrer_arbol_menor(nodo->der, n, count);

}

/* ****
* void Arboles::insertar_director_por_promedio(Director* director)
******
* Inserta un director en el árbol ordenado por promedio de rating.
******
* Input :
*
* Director* director : Puntero al director a insertar
* 
******
* Returns :
* 
* Ninguno
*
**** */

void Arboles::insertar_director_por_promedio(Director* director) {
    if (!director) {
        std::cerr << "Error: director es nullptr." << std::endl;
        return;
    }

    aNodo* nuevo_nodo = new aNodo;
    nuevo_nodo->val = director;
    nuevo_nodo->izq = nullptr;
    nuevo_nodo->der = nullptr;
    

    if (root_2 == nullptr) {
        root_2 = nuevo_nodo;
        size_2++;
    }
    
     else {
        aNodo* actual = root_2;
        aNodo* padre = nullptr;
        
        while (actual) {
            
            padre = actual;
            
            if (director->get_rating_promedio() < actual->val->get_rating_promedio()) {
                actual = actual->izq;
            } else {
                actual = actual->der;            
            }
        }

        if (director->get_rating_promedio() < padre->val->get_rating_promedio()) {
            padre->izq = nuevo_nodo;      
        } else {
            padre->der = nuevo_nodo;      
        }
        size_2++;
    }
}

/* ****
* void Arboles::copiar_arbol()
******
* Copia el árbol de directores ordenado por nombre a un nuevo árbol ordenado por promedio de rating.
******
* Input :
*
* Ninguno
* 
******
* Returns :
* 
* Ninguno
*
**** */

void Arboles::copiar_arbol() {
    copiar_arbol_nodo(root_1);
}


/* ****
* void Arboles::buscar_pelicula(std::string pelicula)
******
* Busca una película en el árbol de directores.
******
* Input :
*
* std::string pelicula : Nombre de la película a buscar
* 
******
* Returns :
* 
* Pelicula* : Puntero a la película encontrada, o nullptr si no se encontró.
*
**** */
Pelicula *Arboles::buscar_pelicula(std::string pelicula ){
    return buscar_pelicula_nodo(root_1, pelicula);
}


/* ****
* void Arboles::buscar_pelicula_nodo(aNodo *nodo, std::string nombre)
******
* Busca una película en el árbol de directores.
******
* Input :
*
* aNodo *nodo : Puntero al nodo actual
* std::string nombre : Nombre de la película a buscar
* 
******
* Returns :
* 
* Pelicula* : Puntero a la película encontrada, o nullptr si no se encontró.
*
**** */
Pelicula *Arboles::buscar_pelicula_nodo(aNodo *nodo, std::string nombre){

    if (!nodo) {
        return nullptr;
    }

    Pelicula *pelicula_encontrar = buscar_pelicula_nodo(nodo->izq, nombre);
    if (pelicula_encontrar) {
        return pelicula_encontrar;
    }

    pelicula_encontrar = nodo->val->buscar_pelicula_lista(nombre);
    if (pelicula_encontrar) {
        return pelicula_encontrar;
    }

    return buscar_pelicula_nodo(nodo->der, nombre);
}

/* ****
* void Arboles::insertar_pelicula(Pelicula *pelicula)
******
* Inserta una película en el árbol de directores.
******
* Input :
*
* Pelicula *pelicula : Puntero a la película a insertar
* 
******
* Returns :
* 
* Ninguno
*
**** */

void Arboles::insertar_pelicula(Pelicula *pelicula) {
    aNodo *nuevo_nodo = new aNodo;
    nuevo_nodo->val = new Director;
    
    nuevo_nodo->val->set_nombre_director(pelicula->director);
    
    nuevo_nodo->izq = nullptr;
    nuevo_nodo->der = nullptr;

    if (!root_1) {
        nuevo_nodo->val->agregar_pelicula(pelicula);
        nuevo_nodo->val->calcular_rating_promedio();  
        root_1 = nuevo_nodo;
        size_1++;
    } else {
        aNodo *actual = root_1;
        aNodo *padre = nullptr;
        
        while (actual) {
            padre = actual;
            if (pelicula->director < actual->val->get_nombre_director()) {
                actual = actual->izq;
                
            }
            else if (pelicula->director > actual->val->get_nombre_director()) {
                actual = actual->der;
                
            }
            else {
                actual->val->agregar_pelicula(pelicula);
                actual->val->calcular_rating_promedio();  
                
                delete nuevo_nodo->val;
                delete nuevo_nodo;
                return;
            }
        }
            if (pelicula->director < padre->val->get_nombre_director()) {
            
            padre->izq = nuevo_nodo;
            size_1++;
        } else {
            padre->der = nuevo_nodo;
            size_1++;

        }
        nuevo_nodo->val->agregar_pelicula(pelicula); 
        nuevo_nodo->val->calcular_rating_promedio();  
    }
}

/* ****
* Director *Arboles::buscar_director(std::string director)
******
* Busca el director deseado en el arbol
******
* Input :
*
* std::string director
* 
******
* Returns :
* 
* Retorna una variable de clase Director
*
**** */

Director *Arboles::buscar_director(std::string director){
    aNodo *aux = root_1;
    while(aux){
        std::string nombre=aux->val->get_nombre_director();
        
        if(director>nombre){
            aux=aux->der;
        }
        else if(director<nombre){
            aux = aux->izq;
        }
        else if(director==nombre){
            return aux->val;
        }
    }
    return nullptr;    
}


/* ****
* void crear_arbol(std::string *peliculas, int cant_pelis, Arboles &arbol)
******
* crea el arbol a partir de los datos obtenidos de las lineas del archivo.
******
* Input :
*
* std::string *peliculas, int cant_pelis, Arboles &arbol
* 
******
* Returns :
* 
* Ninguno
*
**** */

void crear_arbol(std::string *peliculas, int cant_pelis, Arboles &arbol){
    for(int i = 0; i<cant_pelis; i++){
        std::string nombre_pelicula, nombre_director;
        float rating;
        std::istringstream ss(peliculas[i]);
        std::getline(ss, nombre_pelicula, ';');
        std::getline(ss, nombre_director, ';');
        ss>>rating;
        
        Pelicula *p = new Pelicula{nombre_pelicula, nombre_director, rating};
        arbol.insertar_pelicula(p);
    }
}

#endif