#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
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
public :
    Arboles () ; // constructor
    ~ Arboles () ; // destructor
    void insertar_pelicula ( Pelicula * pelicula ) ; //LISTO
    void copiar_arbol () ;// hace copia de arbol 1 en arbol 2 ordenado respecto de rating
    Director * buscar_director ( std::string director ) ; // retorna arreglo de peliculas   LISTO
    Pelicula * buscar_pelicula ( std::string pelicula ) ; // retorna peliculas  
    void mejores_directores ( int n ) ; // Muestra por pantalla los mejores n directores .Enumerando de 1 a n .
    void peores_directores ( int n ) ; // Muestra por pantalla los peores n directores . Enumerando desde m ( cantidad de directores ) hasta m - n .
};

Arboles::Arboles() : root_1(nullptr), size_1(0){};

Arboles::~Arboles() {
    // Liberar la memoria de los nodos y directores
    // Implementar
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
        root_1 = nuevo_nodo;
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
                // Si el director ya existe, agrega la película a su lista y libera el nodo creado
                actual->val->agregar_pelicula(pelicula);
                delete nuevo_nodo->val;
                delete nuevo_nodo;
                return;
            }
        }
    
        // Insertar el nuevo nodo en la posición correcta y agregar la película
        if (pelicula->director < padre->val->get_nombre_director()) {
            padre->izq = nuevo_nodo;
        } else {
            padre->der = nuevo_nodo;
        }
        nuevo_nodo->val->agregar_pelicula(pelicula); // Solo se llama aquí si el director es nuevo
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


int main(){

    Arboles arbol;
    std::string *peliculas;
    int cant_pelis;
    leer_archivo("Peliculas.txt", peliculas, cant_pelis);
    crear_arbol(peliculas, cant_pelis, arbol);


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
        else if(comando == "q"){
            break;
        }        
    }


}


//int main() {
    // Crear instancia de Arboles
    // Crear y agregar algunas películas
    //Pelicula* p1 = new Pelicula{"Avatar", "James Cameron", 7.9};
    //Pelicula* p2 = new Pelicula{"Titanic", "James Cameron", 7.8};
    //Pelicula* p3 = new Pelicula{"The Terminator", "James Cameron", 8.0};
    //Pelicula* p4 = new Pelicula{"Pulp Fiction", "Quentin Tarantino", 8.9};
    //Pelicula* p5 = new Pelicula{"Inglourious Basterds", "Quentin Tarantino", 8.3};
    //Pelicula* p6 = new Pelicula{"Aliens", "James Cameron", 7.7};

    // Insertar películas en el árbol
    // arbol.insertar_pelicula(p1);
    // arbol.insertar_pelicula(p2);
    // arbol.insertar_pelicula(p3);
    // arbol.insertar_pelicula(p4);
    // arbol.insertar_pelicula(p5);
    // arbol.insertar_pelicula(p6);

    //Buscar directores y mostrar sus listas de películas ordenadas
    // Director* director1 = arbol.buscar_director("James Cameron");
    // if (director1) {
    //     std::cout << "\nPeliculas de James Cameron antes de ordenar:" << std::endl;
    //     director1->mostrar_peliculas();
    //     director1->ordenar();
    //     std::cout << "\nPeliculas de James Cameron despues de ordenar:" << std::endl;
    //     director1->mostrar_peliculas();
    // } else {
    //     std::cout << "James Cameron no encontrado en el arbol." << std::endl;
    // }
    


    // Director* director2 = arbol.buscar_director("Sam Raimi");
    // if (director2) {
    //     std::cout << "\nPeliculas de Quentin Tarantino antes de ordenar:" << std::endl;
    //     director2->mostrar_peliculas();
    //     director2->ordenar();
    //     std::cout << "\nPeliculas de Quentin Tarantino despues de ordenar:" << std::endl;
    //     director2->mostrar_peliculas();
    // } else {
    //     std::cout << "Quentin Tarantino no encontrado en el arbol." << std::endl;
    // }


    // Liberar la memoria de las películas
    // delete p1;
    // delete p2;
    // delete p3;
    // delete p4;
    // delete p5;
    // delete p6;

    //return 0;
//}



// int main() {
//     // Crear instancias de películas para agregar al director
//     Pelicula* p1 = new Pelicula{"Titanic", "James Cameron", 7.8};
//     Pelicula* p2 = new Pelicula{"Avatar", "James Cameron", 7.9};
//     Pelicula* p3 = new Pelicula{"The Terminator", "James Cameron", 8.0};
//     Pelicula* p4 = new Pelicula{"Aliens", "James Cameron", 7.7};
//     Pelicula* p5 = new Pelicula{"True Lies", "James Cameron", 6.8};

//     // Crear instancia de Director
//     Director director;

//     // Agregar películas en orden aleatorio
//     director.agregar_pelicula(p1);
//     director.agregar_pelicula(p2);
//     director.agregar_pelicula(p3);
//     director.agregar_pelicula(p4);
//     director.agregar_pelicula(p5);

//     // Mostrar las películas antes de ordenar
//     std::cout << "Peliculas antes de ordenar:" << std::endl;
//     director.mostrar_peliculas();

//     // Ordenar la lista de películas
//     director.ordenar();

//     // Mostrar las películas después de ordenar
//     std::cout << "\nPeliculas después de ordenar:" << std::endl;
//     director.mostrar_peliculas();


//     return 0;
// }

// int main() {
//     std::string *peliculas_arreglo;
//     int cant_pelis;
//     leer_archivo("Peliculas.txt", peliculas_arreglo, cant_pelis);


//     delete[] peliculas_arreglo;
//     return 0;
// }



