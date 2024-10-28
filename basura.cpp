// void Arboles::insertar_director_por_promedio(Director* director) {
//     if (!director) {
//         std::cerr << "Error: director es nullptr." << std::endl;
//         return;
//     }

//     // Verificar que `rating_promedio` esté calculado
//     if (director->get_rating_promedio() == -1) {  // Suponiendo que -1 es el valor por defecto
//         std::cerr << "Error: rating promedio no calculado para " << director->get_nombre_director() << std::endl;
//         return;
//     }

//     aNodo* nuevo_nodo = new aNodo;
//     nuevo_nodo->val = director;
//     nuevo_nodo->izq = nullptr;
//     nuevo_nodo->der = nullptr;

//     if (!root_2) {
//         root_2 = nuevo_nodo;
//     } else {
//         aNodo* actual = root_2;
//         aNodo* padre = nullptr;

//         while (actual) {
//             padre = actual;
//             if (director->get_rating_promedio() < actual->val->get_rating_promedio()) {
//                 actual = actual->izq;
//             } else {
//                 actual = actual->der;
//             }
//         }

//         if (director->get_rating_promedio() < padre->val->get_rating_promedio()) {
//             padre->izq = nuevo_nodo;
//         } else {
//             padre->der = nuevo_nodo;
//         }
//     }
// }

// void Arboles::insertar_director_por_promedio(Director* director) {
//     aNodo* nuevo_nodo = new aNodo;
//     nuevo_nodo->val = director;
//     nuevo_nodo->izq = nullptr;
//     nuevo_nodo->der = nullptr;
//     z++;
//     if (!root_2) {
//         root_2 = nuevo_nodo;
        

//     } else {
//         aNodo* actual = root_2;
//         aNodo* padre = nullptr;
        
//         while (actual) {
//             padre = actual;
//             if (director->get_rating_promedio() < actual->val->get_rating_promedio()) {
//                 actual = actual->izq;
//             } else {
//                 actual = actual->der;
                
//             }
//         }

//         if (director->get_rating_promedio() < padre->val->get_rating_promedio()) {
//             padre->izq = nuevo_nodo;
            
//         } else {
//             padre->der = nuevo_nodo;
//             std::cout<<z<<std::endl;
//         }
//     }
// }





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




// void Arboles::insertar_pelicula(Pelicula *pelicula) {
//     aNodo *nuevo_nodo = new aNodo;
//     nuevo_nodo->val = new Director;
    
//     // Configuramos el nombre del director usando el setter
//     nuevo_nodo->val->set_nombre_director(pelicula->director);
    
//     nuevo_nodo->izq = nullptr;
//     nuevo_nodo->der = nullptr;

//     if (!root_1) {
//         // Si el árbol está vacío, añadimos el nuevo nodo y la película
//         nuevo_nodo->val->agregar_pelicula(pelicula);
//         root_1 = nuevo_nodo;
//     } else {
//         aNodo *actual = root_1;
//         aNodo *padre = nullptr;
        
//         while (actual) {
//             padre = actual;
//             if (pelicula->director < actual->val->get_nombre_director()) {
//                 actual = actual->izq;
//             }
//             else if (pelicula->director > actual->val->get_nombre_director()) {
//                 actual = actual->der;
//             }
//             else {
//                 // Si el director ya existe, agrega la película a su lista y libera el nodo creado
//                 actual->val->agregar_pelicula(pelicula);
//                 delete nuevo_nodo->val;
//                 delete nuevo_nodo;
//                 return;
//             }
//         }
    
//         // Insertar el nuevo nodo en la posición correcta y agregar la película
//         if (pelicula->director < padre->val->get_nombre_director()) {
//             padre->izq = nuevo_nodo;
//         } else {
//             padre->der = nuevo_nodo;
//         }
//         nuevo_nodo->val->agregar_pelicula(pelicula); // Solo se llama aquí si el director es nuevo
//     }
    
// }



// void Arboles::copiar_arbol_nodo(aNodo* nodo) {
//     if (!nodo) return;

//     // Recorrer el subárbol izquierdo
//     copiar_arbol_nodo(nodo->izq);

//     // Clonar el director actual y calcular su promedio
//     Director* director_copia = new Director(*nodo->val);
//     director_copia->calcular_rating_promedio();  // Asegurarse de calcular el promedio aquí

//     // Insertar el director en el nuevo árbol `root_2` por promedio
//     insertar_director_por_promedio(director_copia);

//     // Recorrer el subárbol derecho
//     copiar_arbol_nodo(nodo->der);
// }


// void Director::calcular_rating_promedio() {
//     float total = 0;
//     int count = 0;
//     if (size == 0) {
//         promedio = 0; // Evitar división por cero
//         return;
//     }
//     lNodo* actual = head;
//     float suma_rating = 0.0;
//     while (actual != nullptr) {
//         suma_rating += actual->val->rating;
//         actual = actual->sig;
//     }

//     promedio = suma_rating / size;
//     std::cout << "Promedio calc: " <<actual->val->director<<" "<< promedio << std::endl;

// }


// void Director::calcular_rating_promedio(){
//     lNodo *actual=head;
//     float suma_rating=0.0;
//     while(actual!=nullptr){
//         suma_rating+=actual->val->rating;
//         actual=actual->sig;
//     }
//     promedio=suma_rating/size; 
// }
