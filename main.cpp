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
    void mostrar_arbol_por_promedio(aNodo* nodo) const;
    void mostrar_arbol_ordenado_por_promedio() const;
    void recorrer_arbol_mayor(aNodo* nodo, int n, int& count);
    void recorrer_arbol_menor(aNodo* nodo, int n, int& count);
};



Arboles::Arboles() : root_1(nullptr), size_1(0), root_2(nullptr), size_2(0) {}

Arboles::~Arboles() {
    // Liberar la memoria de los nodos y directores
    // Implementar
}




void Arboles::copiar_arbol_nodo(aNodo* nodo) {
    if (!nodo) return;


    // Recorrer el subárbol izquierdo
    copiar_arbol_nodo(nodo->izq);

    //std::cout<<"2. "<<nodo->val->get_nombre_director()<<" -> "<<nodo->val->get_rating_promedio()<<std::endl; 

    // Crear un nuevo director y copiar películas manualmente
    Director* director_copia = new Director;
    director_copia = nodo->val;
    //director_copia->set_nombre_director(nodo->val->get_nombre_director());

    nodo->val->calcular_rating_promedio(); // Asegurarse de que el promedio esté calculado

    director_copia->calcular_rating_promedio();

    // Insertar en root_2 por promedio
    insertar_director_por_promedio(director_copia);



    // Recorrer el subárbol derecho
    copiar_arbol_nodo(nodo->der);
}


void Arboles::mejores_directores(int n) {
    if (n <= 0) {
        std::cerr << "Error: n debe ser un número positivo." << std::endl;
        return;
    }

    int count = 0;  // Lleva el número de directores mostrados
    recorrer_arbol_mayor(root_2, n, count);
}
    


void Arboles::recorrer_arbol_mayor(aNodo* nodo, int n, int& count) {
    if(nodo == nullptr || count >= n)return;
    

    recorrer_arbol_mayor(nodo->der, n, count);
    
    if (count < n) {
        std::cout <<"("<< count + 1 << ") " << nodo->val->get_nombre_director()  << std::endl;
        count++;
    }
    
    recorrer_arbol_mayor(nodo->izq, n, count);

}

void Arboles::peores_directores(int n) {
    if (n <= 0) {
        std::cerr << "Error: n debe ser un número positivo." << std::endl;
        return;
    }
    index = size_1;
    int count = 0;  // Lleva el número de directores mostrados
    recorrer_arbol_menor(root_2, n, count);
}
    



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


void Arboles::insertar_director_por_promedio(Director* director) {
    //std::cout<<director->get_nombre_director()<<" insertar-> "<<director->get_rating_promedio()<<std::endl;
    if (!director) {
        std::cerr << "Error: director es nullptr." << std::endl;
        return;
    }
    //std::cout<<director->get_nombre_director()<<" -> "<<director->get_rating_promedio()<<std::endl; 

    aNodo* nuevo_nodo = new aNodo;
    nuevo_nodo->val = director;
    nuevo_nodo->izq = nullptr;
    nuevo_nodo->der = nullptr;
    //std::cout<<nuevo_nodo->val->get_nombre_director()<<" nuevo_nodo "<<nuevo_nodo->val->get_rating_promedio()<<std::endl;
    

    if (root_2 == nullptr) {
        root_2 = nuevo_nodo;
        size_2++;
        //std::cout<<"se inserto nueva raiz"<<std::endl;
        //std::cout<<root_2->val->get_nombre_director()<<" root2 "<<root_2->val->get_rating_promedio()<<std::endl;
    }
    
     else {
        aNodo* actual = root_2;
        aNodo* padre = nullptr;
        //std::cout<<"hola"<<std::endl;
        //std::cout<<actual->val->get_nombre_director()<<" direcotttr/ "<<actual->val->get_rating_promedio()<<std::endl;
        while (actual) {
            
            padre = actual;
            
            if (director->get_rating_promedio() < actual->val->get_rating_promedio()) {
                //std::cout<<director->get_nombre_director()<<" if1/ "<<director->get_rating_promedio()<<std::endl;
                actual = actual->izq;
            } else {
                //std::cout<<director->get_nombre_director()<<" else1/ "<<director->get_rating_promedio()<<std::endl;
                actual = actual->der;            
            }
        }

        if (director->get_rating_promedio() < padre->val->get_rating_promedio()) {
            //std::cout<<director->get_nombre_director()<<" if2/ "<<director->get_rating_promedio()<<std::endl;
            padre->izq = nuevo_nodo;      
        } else {
            //std::cout<<director->get_nombre_director()<<" else2/ "<<director->get_rating_promedio()<<std::endl;
            padre->der = nuevo_nodo;      
        }
        size_2++;
    }
    //std::cout<<director->get_nombre_director()<<" / "<<director->get_rating_promedio()<<std::endl;
    //std::cout<<"terminado"<<std::endl;
}



void Arboles::copiar_arbol() {
    copiar_arbol_nodo(root_1);
}


Pelicula *Arboles::buscar_pelicula(std::string pelicula ){
    return buscar_pelicula_nodo(root_1, pelicula);

}

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

void Arboles::insertar_pelicula(Pelicula *pelicula) {
    aNodo *nuevo_nodo = new aNodo;
    nuevo_nodo->val = new Director;
    
    // Configuramos el nombre del director usando el setter
    nuevo_nodo->val->set_nombre_director(pelicula->director);
    
    nuevo_nodo->izq = nullptr;
    nuevo_nodo->der = nullptr;

    if (!root_1) {
        // Si el árbol está vacío, añadimos el nuevo nodo y la película
        nuevo_nodo->val->agregar_pelicula(pelicula);
        nuevo_nodo->val->calcular_rating_promedio();  // Calcula el promedio después de la inserción
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
                // Si el director ya existe, agrega la película a su lista
                
                actual->val->agregar_pelicula(pelicula);
                actual->val->calcular_rating_promedio();  // Recalcula el promedio del director actual
                
                delete nuevo_nodo->val;
                delete nuevo_nodo;
                return;
            }
        }
    
        // Insertar el nuevo nodo en la posición correcta y agregar la película
        if (pelicula->director < padre->val->get_nombre_director()) {
            
            padre->izq = nuevo_nodo;
            size_1++;
        } else {
            padre->der = nuevo_nodo;
            size_1++;

        }
        nuevo_nodo->val->agregar_pelicula(pelicula); // Solo se llama aquí si el director es nuevo
        nuevo_nodo->val->calcular_rating_promedio();  // Calcula el promedio para el nuevo director
    }
}


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


void leer_archivo(std::string nombre_archivo, std::string *&peliculas, int &cant_pelis){
    cant_pelis = 0;
    std::ifstream archivo(nombre_archivo);

    if(archivo.is_open()){
        archivo>>cant_pelis;
        archivo.ignore();
        peliculas = new std::string[cant_pelis];

        for(int i = 0; i<cant_pelis; i++){
            std::getline(archivo, peliculas[i]);
        }

        // for(int i = 0; i<cant_pelis; i++){
        //     std::cout<<i+1<<". "<<peliculas[i]<<std::endl;
        // }
    }
    else{
        std::cout<<"No se pudo abrir el archivo"<<std::endl;
    }
};

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




//-------------------------------------------------------------------------------------------------------------------------


void Arboles::mostrar_arbol_por_promedio(aNodo* nodo) const {
    if (!nodo) return;

    // Recorrer el subárbol izquierdo
    mostrar_arbol_por_promedio(nodo->izq);

    // Mostrar el director y su promedio de rating
    std::cout << "Director: " << nodo->val->get_nombre_director()
              << ", Rating Promedio: " << nodo->val->get_rating_promedio() << std::endl;

    // Recorrer el subárbol derecho
    mostrar_arbol_por_promedio(nodo->der);
}

void Arboles::mostrar_arbol_ordenado_por_promedio() const {
    std::cout << "Directores en root_2 ordenados por promedio de rating:" << std::endl;
    mostrar_arbol_por_promedio(root_2);
}



// int main() {
//     Arboles arbol;
//     std::string* peliculas;
//     int cant_pelis;

//     // Cargar las películas y construir root_1
//     leer_archivo("Peliculas.txt", peliculas, cant_pelis);
//     crear_arbol(peliculas, cant_pelis, arbol);
    

//     // Copiar root_1 en root_2, ordenado por promedio de rating
//     arbol.copiar_arbol();
    
//     // Mostrar root_2 para verificar que está ordenado por promedio de rating
//     arbol.mostrar_arbol_ordenado_por_promedio();

//     delete[] peliculas;  // Liberar memoria del arreglo de películas
//     return 0;
// }

int main(){

    Arboles arbol;
    std::string *peliculas;
    int cant_pelis;
    leer_archivo("Peliculas.txt", peliculas, cant_pelis);
    crear_arbol(peliculas, cant_pelis, arbol);
    arbol.copiar_arbol();

    std::string comando;

    while(true){
        std::cin>>comando;
        if(comando == "sd"){
            std::string director;
            std::cin.ignore();
            std::getline(std::cin, director);
            Director *d = arbol.buscar_director(director);
            if(d){
                d->mostrar_peliculas();
            }
            else{
                std::cout<<"Director no encontrado"<<std::endl;
            }
        }
        else if(comando == "sm"){
            std::string pelicula;
            std::cin.ignore();
            std::getline(std::cin, pelicula);
            Pelicula *p = arbol.buscar_pelicula(pelicula);
            if(p){
                std::cout<<p->nombre<<" / "<<p->director<<" / "<<p->rating<<std::endl;
            }
            else{
                std::cout<<"Pelicula no encontrada"<<std::endl;
            }
        }
        else if(comando == "br"){
            int n;
            std::cin>>n;
            arbol.mejores_directores(n);
        }
        else if(comando == "wr"){
            int n;
            std::cin>>n;
            arbol.peores_directores(n);
        }
        else if(comando == "q"){
            break;
        }  
    }
}


