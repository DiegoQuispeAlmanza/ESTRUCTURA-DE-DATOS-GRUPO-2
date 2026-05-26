#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// ===============================
//	 VARIABLES GLOABLES
// ===============================
int contador = -1;

// ===============================
//	 ESTRUCTURA LISTA
// ===============================

struct Proceso {
    int id;			// Identificador unico (ID) del proceso
    string nombre;	// Nombre del proceso
    int prioridad;	// Establecer el rango de prioridad ( 0 Minima | 1 Baja | 2 Media | 3 Alta | 4 Maxima)
    int RAM;		// Establecer la memoria RAM usada por el sistema
    string estado;	// Determina si el proceso esta en suspension, ejecucion o finalizado

    Proceso* siguiente;	//Nodo de conexion al siguiente elemento de la lista establecida
};

// ===============================
// FUNCIONES - LISTA ENLAZADA
// ===============================

Proceso* head = NULL;	//La cabeza (head) de la lista debe comenzar vacia (NULL en vez de nullptr)

void insertarProceso(Proceso*& head) {
	
    Proceso* nuevoNodo = new Proceso();

    cout << "\n===== REGISTRAR PROCESO =====" << endl;

	contador = contador + 1;
	nuevoNodo->id = contador;
    cout << "ID asignado: " << nuevoNodo->id << endl;

	cin.ignore();

    cout << "Nombre: ";
    getline(cin, nuevoNodo->nombre);

    cout << "Establezca prioridad ( 0 Minima | 1 Baja | 2 Media | 3 Alta | 4 Maxima): ";
    cin >> nuevoNodo->prioridad;

    cout << "Memoria RAM requerida en MB: ";
    cin >> nuevoNodo->RAM;

    nuevoNodo->estado = "Listo!";
    nuevoNodo->siguiente = NULL;

    if (head == NULL) {		//Si la lista esta vacia, el nuevo nodo sera el inicio
        head = nuevoNodo;
        
    } else {
        Proceso* aux = head;

        while (aux->siguiente != NULL) {
        	aux = aux->siguiente;
        }

        aux->siguiente = nuevoNodo;
    }

    cout << "\nProceso registrado correctamente.\n";
}

void mostrarProcesos(Proceso* head) {

    if (head == NULL) {
        cout << "\nNo hay procesos registrados.\n";
        return;
    }
    Proceso* aux = head;
    
    cout << "\n===== LISTA DE PROCESOS =====\n";

    while (aux != NULL) {

        cout << "ID: " << aux->id << endl;
        cout << "Nombre: " << aux->nombre << endl;
        cout << "Prioridad: " << aux->prioridad << endl;
        cout << "Memoria RAM: " << aux->RAM << " MB" << endl;
        cout << "Estado: " << aux->estado << endl;
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
            cout << "ID: "			<< aux->id			<< endl;
            cout << "Nombre: " 		<< aux->nombre 		<< endl;
            cout << "Prioridad: " 	<< aux->prioridad 	<< endl;
            cout << "Memoria RAM: " << aux->RAM 		<< endl;
            cout << "Estado: " 		<< aux->estado 		<< endl;

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

	//Revisar head si contiene un elemento
    if (head == NULL) {
        cout << "\nLista vacia\n";
        return;
    }

    int buscar;
    cout << "\nIngrese ID a eliminar: ";
    cin >> buscar;

	//Nodos a usar
    Proceso* aux 		= head;
    Proceso* anterior 	= NULL;
    
    // Si el nodo a eliminar es el primero de la lista (head)
	if(aux != NULL && aux->id == buscar){
		head = aux->siguiente;
		delete aux;
		cout << "Elemento de ID " << buscar << " eliminado (cabeza)\n" << endl;
		return;
	}

	//Busqueda general del nodo en el resto de la lista
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

            cout << "Nueva prioridad: ";
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
    string nombre_cola;
    int prioridad_cola;

    NodoCola* siguiente_cola;
};

NodoCola* frente = NULL;
NodoCola* final = NULL;

void encolarProceso() {

    NodoCola* nuevoCola = new NodoCola();

    cout << "\n===== ENCOLAR PROCESO =====" << endl;

    cout << "ID: ";
    cin >> nuevoCola->id_cola;

    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nuevoCola->nombre_cola);

    cout << "Prioridad (1 Alta | 2 Media | 3 Baja): ";
    cin >> nuevoCola->prioridad_cola;

    nuevoCola->siguiente_cola = NULL;

    if (frente == NULL || nuevoCola->prioridad_cola < frente->prioridad_cola) {

        nuevoCola->siguiente_cola = frente;
        frente = nuevoCola;

        if (final == NULL) {
            final = nuevoCola;
        }

    } else {

        NodoCola* aux_cola = frente;

        while (aux_cola->siguiente_cola != NULL && aux_cola->siguiente_cola->prioridad_cola <= nuevoCola->prioridad_cola) {
            aux_cola = aux_cola->siguiente_cola;
        }

        nuevoCola->siguiente_cola = aux_cola->siguiente_cola;
        aux_cola->siguiente_cola = nuevoCola;

        if (nuevoCola->siguiente_cola == NULL) {
            final = nuevoCola;
        }
    }

    cout << "\nProceso encolado correctamente.\n";
}

void mostrarCola() {

    if (frente == NULL) {
        cout << "\nCola vacia.\n";
        return;
    }

    NodoCola* aux_cola = frente;

    cout << "\n===== COLA CPU =====\n";

    while (aux_cola != NULL) {

        cout << "ID: " << aux_cola->id_cola << endl;
        cout << "Nombre: " << aux_cola->nombre_cola << endl;
        cout << "Prioridad: " << aux_cola->prioridad_cola << endl;
        cout << "-------------------" << endl;

        aux_cola = aux_cola->siguiente_cola;
    }
}

void ejecutarProceso() {

    if (frente == NULL) {
        cout << "\nNo hay procesos en la cola.\n";
        return;
    }

    NodoCola* aux_cola = frente;

    cout << "\n===== EJECUTANDO =====\n";
    cout << "Proceso: " << aux_cola->nombre_cola << endl;
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

void asignarMemoria() {

    NodoPila* nuevoPila = new NodoPila();

    cout << "\n===== ASIGNAR MEMORIA =====" << endl;

    cin.ignore();

    cout << "Nombre proceso: ";
    getline(cin, nuevoPila->nombre_pila);

    cout << "Cantidad MB: ";
    cin >> nuevoPila->memoria_pila;

    nuevoPila->siguiente_pila = tope;
    tope = nuevoPila;

    cout << "\nMemoria asignada correctamente.\n";
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

        cout << "Proceso: " << aux_pila->nombre_pila << endl;
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

        archivo << "----------------------\nID: "	<< aux->id 			<< "\n";
        archivo << "Proceso: " 						<< aux->nombre 		<< "\n";
        archivo << "Prioridad: " 					<< aux->prioridad 	<< "\n";
        archivo << "Memoria RAM asignada: "			<< aux->RAM 		<< "MB\n";
        archivo << "Estado proceso: "				<< aux->estado 		<< "\n";

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
        cout << "1. Insertar proceso" << endl;
        cout << "2. Eliminar proceso" << endl;
        cout << "3. Buscar proceso" << endl;
        cout << "4. Modificar prioridad" << endl;
        cout << "5. Mostrar procesos" << endl;
        cout << "0. Volver" << endl;

        cout << "Seleccione opcion: ";
        cin >> opMenu;

        switch (opMenu) {

            case 1:
                insertarProceso(head);
                break;

            case 2:
                eliminarProceso(head);
                break;

            case 3:
                buscarProceso();
                break;

            case 4:
                modificarPrioridad(head);
                break;

            case 5:
                mostrarProcesos(head);
                break;

            case 0:
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }

    } while (opMenu != 0);
}

void menuCPU(int opMenu) {

    do {

        cout << "\n===== PLANIFICADOR CPU =====" << endl;
        cout << "1. Encolar proceso" << endl;
        cout << "2. Ejecutar proceso" << endl;
        cout << "3. Mostrar cola" << endl;
        cout << "0. Volver" << endl;

        cout << "Seleccione opcion: ";
        cin >> opMenu;

        switch (opMenu) {

            case 1:
                encolarProceso();
                break;

            case 2:
                ejecutarProceso();
                break;

            case 3:
                mostrarCola();
                break;

            case 0:
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }

    } while (opMenu != 0);
}

void menuMemoria(int opMenu) {

    do {

        cout << "\n===== GESTOR DE MEMORIA =====" << endl;
        cout << "1. Asignar memoria" << endl;
        cout << "2. Liberar memoria" << endl;
        cout << "3. Mostrar memoria" << endl;
        cout << "0. Volver" << endl;

        cout << "Seleccione opcion: ";
        cin >> opMenu;

        switch (opMenu) {

            case 1:
                asignarMemoria();
                break;

            case 2:
                liberarMemoria();
                break;

            case 3:
                mostrarMemoria();
                break;

            case 0:
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }

    } while (opMenu != 0);
}

// ===============================
// MAIN
// ===============================

int main() {

	//VARIABLES LOCALES
	int opMenu = -1;

    do {

        cout << "\n========================================" << endl;
        cout << "   SISTEMA DE GESTION DE PROCESOS" << endl;
        cout << "========================================" << endl;

        cout << "1. Gestion de procesos" << endl;
        cout << "2. Planificador CPU" << endl;
        cout << "3. Gestor de memoria" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Guardar datos" << endl;
        cout << "0. Salir" << endl;

        cout << "Seleccione opcion: ";
        cin >> opMenu;

        switch (opMenu) {

            case 1:
                menuProcesos(opMenu);
                break;

            case 2:
                menuCPU(opMenu);
                break;

            case 3:
                menuMemoria(opMenu);
                break;

            case 4:
                generarReportes();
                break;

            case 5:
                guardarDatos();
                break;

            case 0:
                cout << "\nSaliendo del sistema...\n";
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }

    } while (opMenu != 0);

    return 0;
}

