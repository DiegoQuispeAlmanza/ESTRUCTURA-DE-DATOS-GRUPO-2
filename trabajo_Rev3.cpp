#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// ===============================
//	 ESTRUCTURA LISTA
// ===============================

struct Proceso {
    int id;			// Identificador unico (ID) del proceso
    string nombre;	// Nombre del proceso
    int prioridad;	// Rango de prioridad ( 0 Minima | 1 Baja | 2 Media | 3 Alta | 4 Maxima)
    int RAM;		// Memoria RAM usada en MB
    string estado;	// Estado del proceso: Listo, En ejecucion, Finalizado

    Proceso* siguiente;
};

///////////////////////////////////////////////
void bubbleSort(int array[], int n) {

  for (int i = 0; i < n - 1; ++i) {
      
    for (int j = 0; j < n - i - 1; ++j) {

      if (array[j] > array[j + 1]) {

        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}
/////////////////////////////////////////////////
// ===============================
//	 VARIABLES GLOBALES
// ===============================

Proceso* head = NULL;

// ===============================
// FUNCIONES - LISTA ENLAZADA
// ===============================

//===============================================================================
int contadorID(Proceso*& head){
	
	int cont_lista = 0;
	
	if (head == NULL){
		cout << "\nNo se encontro la cabeza en la lista" << endl;
		return cont_lista;
		
	}else{
		cont_lista++;
		
		Proceso* aux = head;
		
		while(aux->siguiente != NULL){
			cont_lista++;
			aux = aux->siguiente;
		}
		
		cout << "\nLa cantidad de elementos en la lista es: " << cont_lista << endl;
		return cont_lista;
	}
}
//===============================================================================
//===============================================================================
void reordenarProcesos(Proceso*& head){
	
	int comp = contadorID(head);
	
	if (head == NULL){
		cout << "\nLa cabeza esta vacia en la lista" << endl;
		
	}else{
		Proceso* aux = head;
		
		for(int i = 0; i < comp; i++){
			
			if(aux->siguiente != NULL){
				aux->id = i;
				aux = aux->siguiente;	
			}else{
				break;
			}						
		}
		
		cout << "Se reorganizo la lista actual " << endl;
	}
}
//===============================================================================

void insertarProceso(Proceso*& head) {

    Proceso* nuevoNodo = new Proceso();

    cout << "\n===== REGISTRAR PROCESO =====" << endl;

	nuevoNodo->id = contadorID(head);		//Llamando a la funcion contadorID para identificar los elementos existentes
	
    cout << "\nID asignado: " << nuevoNodo->id << endl;

    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nuevoNodo->nombre);

    cout << "Establezca prioridad ( 0 Minima | 1 Baja | 2 Media | 3 Alta | 4 Maxima): ";
    cin >> nuevoNodo->prioridad;

    cout << "Memoria RAM requerida en MB: ";
    cin >> nuevoNodo->RAM;

    nuevoNodo->estado = "Listo";
    nuevoNodo->siguiente = NULL;

    if (head == NULL) {
        head = nuevoNodo;
    } else {
        Proceso* aux = head;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevoNodo;
    }

    cout << "\nProceso registrado correctamente.\n";
    
	reordenarProcesos(head);	//LlAMA A LA FUNCION DE REORDENAR PROCESOS
    
}

void mostrarProcesos(Proceso* head) {

	reordenarProcesos(head);	//LlAMA A LA FUNCION DE REORDENAR PROCESOS

    if (head == NULL) {
        cout << "\nNo hay procesos registrados.\n";
        return;
    }

    Proceso* aux = head;

    cout << "\n===== LISTA DE PROCESOS =====\n";

    while (aux != NULL) {
        cout << "ID: "          << aux->id       << endl;
        cout << "Nombre: "      << aux->nombre   << endl;
        cout << "Prioridad: "   << aux->prioridad << endl;
        cout << "Memoria RAM: " << aux->RAM       << " MB" << endl;
        cout << "Estado: "      << aux->estado   << endl;
        cout << "--------------------------" << endl;
        aux = aux->siguiente;
    }
}

void buscarProceso() {

    int buscar;
    bool encontrado = false;

    cout << "\nIngrese ID a buscar: ";
    cin >> buscar;

    Proceso* aux = head;

    while (aux != NULL) {
        if (aux->id == buscar) {
            cout << "\nProceso encontrado:\n";
            cout << "ID: "          << aux->id        << endl;
            cout << "Nombre: "      << aux->nombre    << endl;
            cout << "Prioridad: "   << aux->prioridad << endl;
            cout << "Memoria RAM: " << aux->RAM       << " MB" << endl;
            cout << "Estado: "      << aux->estado    << endl;
            encontrado = true;
            break;
        }
        aux = aux->siguiente;
    }

    if (encontrado == false) {
        cout << "\nProceso no encontrado.\n";
    }
}

void eliminarProceso(Proceso*& head) {

    if (head == NULL) {
        cout << "\nLista vacia\n";
        return;
    }

    int buscar;
    cout << "\nIngrese ID a eliminar: ";
    cin >> buscar;

    Proceso* aux      = head;
    Proceso* anterior = NULL;

    if (aux != NULL && aux->id == buscar) {
        head = aux->siguiente;
        
        delete aux;
        
        reordenarProcesos(head);	//LLAMA A LA FUNCION REORDENAR PROCESOS
        
        cout << "Elemento de ID " << buscar << " eliminado (cabeza)\n" << endl;
        return;
    }

    while (aux != NULL && aux->id != buscar) {
        anterior = aux;
        aux = aux->siguiente;
    }

    if (aux == NULL) {
        cout << "\nProceso no encontrado.\n";
        return;
    }

    if (anterior == NULL) {
        head = head->siguiente;
    } else {
        anterior->siguiente = aux->siguiente;
    }

    delete aux;
    
    reordenarProcesos(head); //LLAMA AL PROCESO REORDENAR PROCESOS

    cout << "\nProceso eliminado correctamente\n";
}

void modificarPrioridad(Proceso*& head) {

    int buscar;
    bool encontrado = false;

    cout << "\nIngrese ID del proceso: ";
    cin >> buscar;

    Proceso* aux = head;

    while (aux != NULL) {
        if (aux->id == buscar) {
            cout << "Prioridad actual: " << aux->prioridad << endl;
            cout << "Nueva prioridad ( 0 Minima | 1 Baja | 2 Media | 3 Alta | 4 Maxima): ";
            cin >> aux->prioridad;
            encontrado = true;
            cout << "\nPrioridad modificada correctamente.\n";
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "\nProceso no encontrado.\n";
    }
}

// =======================================================================
// COLA DE PRIORIDAD - FILTRO DE SOFTWARE PARA DESTINAR RECURSOS DEL CPU
// =======================================================================

struct NodoCola {
    int id_cola;
    
    int id_lista;
    string nombre_cola;
    int prioridad_cola;	// Escala unificada: 0 Minima | 1 Baja | 2 Media | 3 Alta | 4 Maxima

    NodoCola* siguiente_cola;
};

// ===============================
//	 VARIABLES GLOBALES
// ===============================

NodoCola* frente = NULL;
NodoCola* final  = NULL;

// =======================================================================

int cont_Cola(NodoCola*& frente, NodoCola*& final){
	
	int cont_Cola = 0;
	
    if (frente == NULL) {
        cout << "\nCola vacia.\n";
        return cont_Cola;
    }

    NodoCola* aux_cola = frente;
	cont_Cola++;

    while (aux_cola->siguiente_cola != NULL) {
    	cont_Cola++;
        aux_cola = aux_cola->siguiente_cola;
    }
    
    cout << "Elementos anexados en la cola " << cont_Cola << endl;
    return cont_Cola;
}

// =======================================================================
/*/===============================================================================
void reordenarCola(NodoCola*& frente){
	
	int comp_cola = cont_Cola(frente, final);
	int pos[comp_cola];
	
	if (frente == NULL){
		cout << "\nEl frente de la cola esta vacia" << endl;
		return;
		
	}else{
		NodoCola* aux_cola = frente;
		
		for(int i = 0; i < comp_cola; i++){
			
			if(aux_cola->siguiente_cola != NULL){
				
				pos[i] = aux_cola->prioridad_cola;				
				aux_cola = aux_cola->siguiente_cola;
												
			}else{				
				break;
			}																			
		}
				
		bubbleSort(pos[], comp_cola);
		
		
	}
	
	
	cout << "Se reorganizo la cola actual " << endl;
}
//===============================================================================//*/

void encolarProceso(Proceso*& head, NodoCola*& frente, NodoCola*& final) {

	//REVISA LA MEMORIA DE LA LISTA ENLAZADA EXISTENTE
    if (head == NULL) {
        cout << "\nNo hay procesos en la lista para encolar.\n";
        return;
    }

    Proceso* aux = head;	//LLAMA AL PUNTERO AUX PARA DIRIGIRSE A LA CABEZA (HEAD)

	int encolados = cont_Cola(frente, final);	//Contador de encolado
	
    cout << "\n===== ENCOLAR PROCESOS DESDE LISTA =====\n";
    mostrarProcesos(head);
    cout << "Lista generada de procesos" << endl;

    while (aux != NULL) {
		
        NodoCola* nuevoCola = new NodoCola();

		nuevoCola->id_cola			= encolados;
        nuevoCola->id_lista      	= aux->id;
        nuevoCola->nombre_cola    	= aux->nombre;
        nuevoCola->prioridad_cola 	= aux->prioridad;
        nuevoCola->siguiente_cola 	= NULL;
	
        // Mayor valor = mayor prioridad, va primero en la cola (frente) 
        if (frente == NULL || nuevoCola->prioridad_cola > frente->prioridad_cola) {

            nuevoCola->siguiente_cola = frente;
            frente = nuevoCola;

            if (final == NULL) {
                final = nuevoCola;
            }

        } else {

            NodoCola* aux_cola = frente;

            while (aux_cola->siguiente_cola != NULL && aux_cola->siguiente_cola->prioridad_cola >= nuevoCola->prioridad_cola) {
                aux_cola = aux_cola->siguiente_cola;
            }

            nuevoCola->siguiente_cola = aux_cola->siguiente_cola;
            aux_cola->siguiente_cola  = nuevoCola;

            if (nuevoCola->siguiente_cola == NULL) {
                final = nuevoCola;
            }
        }
        
        aux = aux->siguiente;
        encolados = cont_Cola(frente, final);
    }

    cout << "\n" << encolados << " proceso(s) encolados correctamente.\n";
}

void mostrarCola() {

    if (frente == NULL) {
        cout << "\nCola vacia.\n";
        return;
    }

    NodoCola* aux_cola = frente;

    cout << "\n===== COLA CPU =====\n";

    while (aux_cola != NULL) {
        cout << "Orden en cola: "        			<< aux_cola->id_cola        << endl;
    	cout << "Id_proceso:"						<< aux_cola->id_lista		<< endl;
	    cout << "Nombre: "    						<< aux_cola->nombre_cola    << endl;
        cout << "Prioridad: " 						<< aux_cola->prioridad_cola << endl;
        cout << "-------------------" 				<< endl;
        aux_cola = aux_cola->siguiente_cola;
    }
}

void ejecutarProceso(NodoCola*& frente, NodoCola*& final) {

    if (frente == NULL) {
        cout << "\nNo hay procesos en la cola.\n";
        return;
    }

    NodoCola* aux_cola = frente;

    cout << "\n===== EJECUTANDO =====\n";
    cout << "Proceso: "   << aux_cola->nombre_cola    << endl;
    cout << "Prioridad: " << aux_cola->prioridad_cola << endl;

    frente = frente->siguiente_cola;

    if (frente == NULL) {
        final = NULL;
    }

    delete aux_cola;

    cout << "\nProceso ejecutado correctamente.\n";
}

// ===============================
// PILA MEMORIA
// ===============================

struct NodoPila {
    string nombre_pila;
    int memoria_pila;

    NodoPila* siguiente_pila;
};

NodoPila* tope = NULL;

void cargarMemoriaDesideCola() {

    if (frente == NULL) {
        cout << "\nNo hay procesos en la cola.\n";
        return;
    }

    // Arreglo temporal para ordenar por RAM
    const int MAX = 100;
    NodoPila* temp[MAX];
    int count = 0;

    NodoCola* aux_cola = frente;

    while (aux_cola != NULL && count < MAX) {

        // Buscar RAM del proceso en la lista enlazada por ID
        Proceso* aux_lista = head;
        int ram_encontrada = 0;

        while (aux_lista != NULL) {
            if (aux_lista->id == aux_cola->id_cola) {
                ram_encontrada = aux_lista->RAM;
                break;
            }
            aux_lista = aux_lista->siguiente;
        }

        NodoPila* nuevo = new NodoPila();
        nuevo->nombre_pila  = aux_cola->nombre_cola;
        nuevo->memoria_pila = ram_encontrada;
        nuevo->siguiente_pila = NULL;

        temp[count] = nuevo;
        count++;

        aux_cola = aux_cola->siguiente_cola;
    }

    // Ordenar de menor a mayor RAM (al apilar, el ultimo apilado = mayor RAM = tope)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (temp[j]->memoria_pila > temp[j + 1]->memoria_pila) {
                NodoPila* aux_swap = temp[j];
                temp[j]            = temp[j + 1];
                temp[j + 1]        = aux_swap;
            }
        }
    }

    // Apilar en orden: el ultimo en apilar queda en el tope (mayor RAM)
    for (int i = 0; i < count; i++) {
        temp[i]->siguiente_pila = tope;
        tope = temp[i];
    }

    cout << "\n" << count << " proceso(s) cargados a memoria ordenados por RAM (mayor en tope).\n";
}

void liberarMemoria() {

    if (tope == NULL) {
        cout << "\nNo hay memoria asignada.\n";
        return;
    }

    NodoPila* aux_pila = tope;

    cout << "\nLiberando memoria de: " << aux_pila->nombre_pila << endl;

    tope = tope->siguiente_pila;

    delete aux_pila;

    cout << "\nMemoria liberada correctamente.\n";
}

void mostrarMemoria() {

    if (tope == NULL) {
        cout << "\nPila vacia.\n";
        return;
    }

    NodoPila* aux_pila = tope;

    cout << "\n===== MEMORIA RAM =====\n";

    while (aux_pila != NULL) {
        cout << "Proceso: " << aux_pila->nombre_pila  << endl;
        cout << "Memoria: " << aux_pila->memoria_pila << " MB" << endl;
        cout << "----------------------" << endl;
        aux_pila = aux_pila->siguiente_pila;
    }
}

// ===============================
// REPORTES
// ===============================

void generarReportes() {

    cout << "\n===== REPORTES DEL SISTEMA =====\n";

    mostrarProcesos(head);
    mostrarCola();
    mostrarMemoria();
}

// ===============================
// GUARDAR DATOS
// ===============================

void guardarDatos() {

    ofstream archivo("procesos.txt");

    Proceso* aux = head;

    while (aux != NULL) {
        archivo << "----------------------\nID: " << aux->id        << "\n";
        archivo << "Proceso: "                     << aux->nombre    << "\n";
        archivo << "Prioridad: "                   << aux->prioridad << "\n";
        archivo << "Memoria RAM asignada: "        << aux->RAM       << "MB\n";
        archivo << "Estado proceso: "              << aux->estado    << "\n";
        aux = aux->siguiente;
    }

    archivo.close();

    cout << "\nDatos guardados correctamente.\n";
}

// ===============================
// ESTRUCTURA DEL MENU
// ===============================

void menuProcesos(int opMenu) {

    do {

        cout << "\n===== GESTION DE PROCESOS =====" << endl;
        cout << "1. Insertar proceso"   << endl;
        cout << "2. Eliminar proceso"   << endl;
        cout << "3. Buscar proceso"     << endl;
        cout << "4. Modificar prioridad" << endl;
        cout << "5. Mostrar procesos"   << endl;       
        cout << "0. Volver"             << endl;

        cout << "Seleccione opcion: ";
        cin >> opMenu;

        switch (opMenu) {
            case 1: insertarProceso(head);  	break;
            case 2: eliminarProceso(head);  	break;
            case 3: buscarProceso();        	break;
            case 4: modificarPrioridad(head); 	break;
            case 5: mostrarProcesos(head);  	break;
            case 0: break;
            default: cout << "\nOpcion invalida.\n";
        }

    } while (opMenu != 0);
}

void menuCPU(int opMenu) {

    do {

        cout << "\n===== PLANIFICADOR CPU ====="	<< endl;
        cout << "1. Encolar procesos desde lista"	<< endl;
        cout << "2. Ejecutar proceso"				<< endl;
        cout << "3. Mostrar cola"					<< endl;
        
        cout << "4. Contador encolado"				<< endl;	
        
        cout << "0. Volver"							<< endl;

        cout << "Seleccione opcion: ";
        cin >> opMenu;

        switch (opMenu) {
            case 1: encolarProceso(head,frente,final);  break;
            case 2: ejecutarProceso(frente, final); 	break;
            case 3: mostrarCola(); 						break;
            
            case 4: cont_Cola(frente, final);			break;
            
            case 0: break;
            default: cout << "\nOpcion invalida.\n";
        }

    } while (opMenu != 0);
}

void menuMemoria(int opMenu) {

    do {

        cout << "\n===== GESTOR DE MEMORIA =====" << endl;
        cout << "1. Cargar procesos desde cola" << endl;
        cout << "2. Liberar memoria"            << endl;
        cout << "3. Mostrar memoria"            << endl;
        cout << "0. Volver"                     << endl;

        cout << "Seleccione opcion: ";
        cin >> opMenu;

        switch (opMenu) {
            case 1: cargarMemoriaDesideCola(); break;
            case 2: liberarMemoria();          break;
            case 3: mostrarMemoria();          break;
            case 0: break;
            default: cout << "\nOpcion invalida.\n";
        }

    } while (opMenu != 0);
}

// ===============================
// MAIN
// ===============================

int main() {

    int opMenu = -1;

    do {

        cout << "\n========================================" << endl;
        cout << "   SISTEMA DE GESTION DE PROCESOS"        << endl;
        cout << "========================================" << endl;

        cout << "1. Gestion de procesos" << endl;
        cout << "2. Planificador CPU"    << endl;
        cout << "3. Gestor de memoria"  << endl;
        cout << "4. Reportes"           << endl;
        cout << "5. Guardar datos"      << endl;
        cout << "0. Salir"              << endl;

        cout << "Seleccione opcion: ";
        cin >> opMenu;

        switch (opMenu) {
            case 1: menuProcesos(opMenu); break;
            case 2: menuCPU(opMenu);      break;
            case 3: menuMemoria(opMenu);  break;
            case 4: generarReportes();    break;
            case 5: guardarDatos();       break;
            case 0: cout << "\nSaliendo del sistema...\n"; break;
            default: cout << "\nOpcion invalida.\n";
        }

    } while (opMenu != 0);

    return 0;
}
