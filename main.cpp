#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include <stdio.h>
#include <cmath>
#include "director.hpp"
#include "arboles.hpp"

/* ****
* void leer_archivo(std::string nombre_archivo, std::string *&peliculas, int &cant_pelis)
******
* Lee el archivo de texto y guarda las peliculas en un arreglo
******
* Input :
*
* std::string nombre_archivo: Nombre del archivo
* std::string *&peliculas: Arreglo de peliculas
* int &cant_pelis: Cantidad de peliculas
* 
******
* Returns :
* 
* Ninguno
*
**** */

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
        archivo.close();

    }
    else{
        std::cout<<"No se pudo abrir el archivo"<<std::endl;
    }
};



/* ****
* int main()
******
* Funcion principal
******
* Input :
*
* Ninguno
* 
******
* Returns :
* 
* Retorna 0 si se ejecutó correctamente
*
**** */
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


