#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

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

    Director () ; // constructor
    ~ Director () ; // destructor
    lNodo * head ;
    lNodo * curr ;
    lNodo * tail ;
    size_t size ; // longitud lista
    std::string nombre_director ;

public :
    void agregar_pelicula ( Pelicula * pelicula ) ; // agrega pelicula al final de la lista enlazada
    void ordenar () ; // ordena la lista
    void calcular_rating_promedio () ;
    void mostrar_peliculas () ;
};


void Director::agregar_pelicula(Pelicula *pelicula) {
    lNodo *nuevo_nodo = new lNodo;
    nuevo_nodo->val = pelicula;
    nuevo_nodo->sig = nullptr;

    if(!head){
        head = nuevo_nodo;
        tail = nuevo_nodo;
    }

    else{
        lNodo *aux = head;
        lNodo *anterior = nullptr;
        while(aux && aux->val->nombre < pelicula->nombre){
            anterior = aux;
            aux = aux->sig;
        }

        if(!anterior){
            nuevo_nodo->sig = head;
            head = nuevo_nodo;
        }
        
        else{
            anterior->sig = nuevo_nodo;
            nuevo_nodo->sig = aux;

            if(!aux){
                tail = nuevo_nodo;
            }
        }
    }
    size++;
}



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
    void insertar_pelicula ( Pelicula * pelicula ) ;
    void copiar_arbol () ;// hace copia de arbol 1 en arbol 2 ordenado respecto de rating
    Director * buscar_director ( std::string director ) ; // retorna arreglo de peliculas
    Pelicula * buscar_pelicula ( std::string pelicula ) ; // retorna peliculas
    void mejores_directores ( int n ) ; // Muestra por pantalla los mejores n directores .Enumerando de 1 a n .
    void peores_directores ( int n ) ; // Muestra por pantalla los peores n directores . Enumerando desde m ( cantidad de directores ) hasta m - n .
};


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

        for(int i = 0; i<cant_pelis; i++){
            std::cout<<i+1<<". "<<peliculas[i]<<std::endl;
        }
    }
};




int main() {
    std::string *peliculas_arreglo;
    int cant_pelis;
    leer_archivo("Peliculas.txt", peliculas_arreglo, cant_pelis);


    delete[] peliculas_arreglo;
    return 0;
}

/*
void leer_archivo(std::string nombre_archivo, std::string *&peliculas, int &cant_programas, int &largo_max) {


    int cant_instrucciones = 0;
    std::ifstream archivo(nombre_archivo);

    if (archivo.is_open()) {

        std::string linea;
        int largo_maximo, cantidad_programas;
        archivo>>largo_maximo>>cantidad_programas;
        largo_max = largo_maximo;
        cant_programas = cantidad_programas;

        archivo.clear(); // Restablecer el puntero del archivo al inicio
        archivo.seekg(0, std::ios::beg); // Mover el puntºero del archivo al inicio


        while (std::getline(archivo, linea)) {
            cant_instrucciones++;
        }

        archivo.clear(); // Restablecer el puntero del archivo al inicio
        archivo.seekg(0, std::ios::beg); // Mover el puntºero del archivo al inicio
        std::string *aux;
        aux = new std::string[cant_instrucciones];

        instruccion = new std::string[cant_instrucciones];  //BORRAR AL FINALIZAR EL PROGRAMA
        int i = 0;
        while(std::getline(archivo, linea)){

            aux[i] = linea;
            

            i++;
        }
        int j = 0;
        for(int i = 2; i<cant_instrucciones; i++){
            instruccion[j++] = aux[i];
        }
        delete[] aux;

        archivo.clear(); // Restablecer el puntero del archivo al inicio
        archivo.seekg(0, std::ios::beg); // Mover el puntero del archivo al inicio
        archivo.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo " << nombre_archivo << std::endl;
    }
}
    
*/


