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
    void set_nombre_director(std::string& nombre);
        
};

Director::Director() : head(nullptr), tail(nullptr), size(0) {}

Director::~Director() {
    lNodo* actual = head;
    while (actual != nullptr) {
        lNodo* siguiente = actual->sig;
        delete actual->val; // Liberar la película
        delete actual; // Liberar el nodo
        actual = siguiente;
    }
}

std::string Director::get_nombre_director() {
    return nombre_director;
}

void Director::set_nombre_director(std::string& nombre) {
    nombre_director = nombre;
}

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

Director::lNodo* Director::merge(lNodo* izquierda, lNodo* derecha) {
    if (!izquierda) return derecha;
    if (!derecha) return izquierda;

    lNodo* resultado = nullptr;

    // Compara el nombre de las películas para determinar el orden.
    if (izquierda->val->nombre <= derecha->val->nombre) {
        resultado = izquierda;
        resultado->sig = merge(izquierda->sig, derecha);
    } else {
        resultado = derecha;
        resultado->sig = merge(izquierda, derecha->sig);
    }

    return resultado;
}

void Director::split(lNodo* fuente, lNodo** frente, lNodo** fondo) {
    lNodo* rapido = fuente->sig;
    lNodo* lento = fuente;

    // `rapido` avanza dos nodos y `lento` uno, dividiendo la lista en dos partes.
    while (rapido != nullptr) {
        rapido = rapido->sig;
        if (rapido != nullptr) {
            lento = lento->sig;
            rapido = rapido->sig;
        }
    }

    // Divide la lista en dos mitades
    *frente = fuente;
    *fondo = lento->sig;
    lento->sig = nullptr;
}

void Director::mostrar_peliculas() {
    lNodo* actual = head;

    while (actual != nullptr) {
        if (actual->val) {
            std::cout<<actual->val->nombre<<" / " <<actual->val->rating<<std::endl;
        } else {
            std::cout << "Nodo con pelicula nula." << std::endl;
        }
        actual = actual->sig; // Avanza al siguiente nodo
    }
}

void Director::ordenar2(lNodo** headRef) {
    lNodo* head = *headRef;
    if (!head || !head->sig) return; // Caso base: lista vacía o con un solo elemento

    lNodo* frente;
    lNodo* fondo;

    // Divide la lista en dos mitades
    split(head, &frente, &fondo);

    // Ordena recursivamente las dos mitades
    ordenar2(&frente);
    ordenar2(&fondo);

    // Combina las listas ordenadas
    *headRef = merge(frente, fondo);
}

void Director::ordenar() {
    ordenar2(&head);
}


void Director::calcular_rating_promedio(){
    lNodo *actual=head;
    promedio;
    float suma_rating=0.0;
    while(actual!=nullptr){
        suma_rating+=actual->val->rating;
        actual=actual->sig;
    }
    promedio=suma_rating/size; 
}

#endif