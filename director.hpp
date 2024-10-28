#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include <iostream>
#include <fstream>
#include <string>


struct Pelicula {
    std::string nombre ;
    std::string director ;
    float rating ;
};

class Director {
private :

    struct lNodo {
        Pelicula * val ;
        lNodo * sig ;
    };


    lNodo * head ;
    lNodo * curr ;
    lNodo * tail ;
    size_t size ; // longitud lista
    std::string nombre_director ;

    float rating_promedio;
    float promedio;

public :
   
    Director () ; // constructor
    ~ Director () ; // destructor
    void agregar_pelicula ( Pelicula * pelicula ) ; // agrega pelicula al final de la lista enlazada
    void ordenar () ; // ordena la lista
    void calcular_rating_promedio () ;
    void mostrar_peliculas () ;

    std::string get_nombre_director () ;
    lNodo * merge ( lNodo* izquierda , lNodo* derecha ) ;
    void split(lNodo* fuente, lNodo** frente, lNodo** fondo);
    void ordenar2(lNodo** headRef);
    void set_nombre_director(const std::string& nombre);
    Pelicula * buscar_pelicula_lista(std::string &nombre_pelicula);
    float get_rating_promedio() const;
        
};

Director::Director() : head(nullptr), tail(nullptr), size(0) {}

Director::~Director() {
    lNodo* actual = head;
    while (actual != nullptr) {
        lNodo* siguiente = actual->sig;
        delete actual->val; 
        delete actual; 
        actual = siguiente;
    }
}


/* ****
* void Director::agregar_pelicula(Pelicula *pelicula)
******
* Agrega una película al final de la lista enlazada del director.
******
* Input :
*
* Pelicula *pelicula : Puntero a la película a agregar
* 
******
* Returns :
* 
* Ninguno
*
**** */
void Director::agregar_pelicula(Pelicula *pelicula){
    lNodo *nuevo_nodo = new lNodo;
    nuevo_nodo->val = pelicula;
    nuevo_nodo->sig = nullptr;
    nuevo_nodo->val->director = nombre_director;
    if(!head){
        head = nuevo_nodo;
        tail = nuevo_nodo;   
    }
    else{
        tail->sig = nuevo_nodo;
        tail = nuevo_nodo;
    }
    size++;
}

/* ****
* void Director::ordenar()
******
* Ordena la lista enlazada de películas del director.
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
void Director::ordenar() {
    ordenar2(&head);
}


/* ****
* void Director::ordenar2(lNodo** headRef)
******
* Ordena una lista enlazada de películas usando el algoritmo de ordenamiento merge sort.
******
* Input :
*
* lNodo** headRef : Puntero al primer nodo de la lista
* 
******
* Returns :
* 
* Ninguno
*
**** */
void Director::ordenar2(lNodo** headRef) {
    lNodo* head = *headRef;
    if (!head || !head->sig) return;

    lNodo* frente;
    lNodo* fondo;

    
    split(head, &frente, &fondo);

    
    ordenar2(&frente);
    ordenar2(&fondo);

    
    *headRef = merge(frente, fondo);
}


/* ****
* void Director::split(lNodo* fuente, lNodo** frente, lNodo** fondo)
******
* Divide una lista enlazada en dos mitades.
******
* Input :
*
* lNodo* fuente : Puntero al primer nodo de la lista a dividir
* lNodo** frente : Puntero al primer nodo de la primera mitad
* lNodo** fondo : Puntero al primer nodo de la segunda mitad
* 
******
* Returns :
* 
* Ninguno
*
**** */
void Director::split(lNodo* fuente, lNodo** frente, lNodo** fondo) {
    lNodo* rapido = fuente->sig;
    lNodo* lento = fuente;

    
    while (rapido != nullptr) {
        rapido = rapido->sig;
        if (rapido != nullptr) {
            lento = lento->sig;
            rapido = rapido->sig;
        }
    }

    
    *frente = fuente;
    *fondo = lento->sig;
    lento->sig = nullptr;
}

/* ****
* Director::lNodo* Director::merge(lNodo* izquierda, lNodo* derecha)
******
* Combina dos listas enlazadas ordenadas en una sola lista ordenada.
******
* Input :
*
* lNodo* izquierda : Puntero al primer nodo de la lista izquierda
* lNodo* derecha : Puntero al primer nodo de la lista derecha
* 
******
* Returns :
* 
* lNodo* : Puntero al primer nodo de la lista combinada
*
**** */
Director::lNodo* Director::merge(lNodo* izquierda, lNodo* derecha) {
    if (!izquierda) return derecha;
    if (!derecha) return izquierda;

    lNodo* resultado = nullptr;

    
    if (izquierda->val->nombre <= derecha->val->nombre) {
        resultado = izquierda;
        resultado->sig = merge(izquierda->sig, derecha);
    } else {
        resultado = derecha;
        resultado->sig = merge(izquierda, derecha->sig);
    }

    return resultado;
}

/* ****
* Pelicula *Director::buscar_pelicula_lista(std::string &nombre_pelicula)
******
* Busca una película en la lista enlazada del director.
******
* Input :
*
* std::string &nombre_pelicula : Nombre de la película a buscar
* 
******
* Returns :
* 
* Pelicula* : Puntero a la película encontrada, o nullptr si no se encontró.
*
**** */

Pelicula *Director::buscar_pelicula_lista(std::string &nombre_pelicula){
    lNodo *actual = head;
    while(actual!=nullptr){
        if(actual->val->nombre == nombre_pelicula){
            return actual->val;
        }
        actual=actual->sig;
    }
    return nullptr;
}

/* ****
* std::string Director::get_nombre_director()
******
* Obtiene el nombre del director.
******
* Input :
*
* Ninguno
* 
******
* Returns :
* 
* std::string : Nombre del director.
*
**** */

std::string Director::get_nombre_director() {
    return nombre_director;
}


/* ****
* void Director::set_nombre_director(const std::string& nombre)
******
* Establece el nombre del director.
******
* Input :
*
* std::string &nombre : Nombre del director
* 
******
* Returns :
* 
* Ninguno
*
**** */
void Director::set_nombre_director(const std::string& nombre) {
    nombre_director = nombre;
}



/* ****
* void Director::mostar_peliculas()
******
* Muestra las películas del director.
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
void Director::mostrar_peliculas() {
    lNodo* actual = head;

    while (actual != nullptr) {
        if (actual->val) {
           std::cout<<actual->val->nombre<<" / " <<actual->val->rating <<std::endl;
        } else {
           std::cout << "Nodo con pelicula nula." << std::endl;
        }
        actual = actual->sig; 
    }
}


/* ****
* void Director::calcular_rating_promedio()
******
* Calcula el promedio de rating de las películas del director.
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
void Director::calcular_rating_promedio() {
    float total = 0;
    for (lNodo* temp = head; temp; temp = temp->sig) {
        total += temp->val->rating;
    }
    rating_promedio = total / size;

}


/* ****
* void Director::get_rating_promedio()
******
* Obtiene el promedio de rating de las películas del director.
******
* Input :
*
* Ninguno
* 
******
* Returns :
* 
* float : Promedio de rating
*
**** */
float Director::get_rating_promedio() const{
    return rating_promedio;
}
    
#endif