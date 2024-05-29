#include "resultados.h"
#include "entrenador.h"
#include "Clinicas.h"
#include "medico.h"
#include "horario.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <iomanip>
#include <string>

using namespace std;
// Constructor
Entrenador entrenador;
Medico medico;
Clinica clinica;
Horario horario; // Cambiado a minuscula

resultados::resultados(string id, string codigo_entre, string nombre_entre, string nom_entre, string clinica, string medico, string horario) {
    this->id = id;
    this->codigo_entre = codigo_entre;
    this->nombre_entre = nombre_entre;
    this->nom_entre = nom_entre;
    this->clinica = clinica;
    this->medico = medico;
    this->horario = horario;
}

// Setters y Getters
string resultados::setid(string id) {
    this->id = id;
    return this->id;
}

string resultados::getid() {
    return this->id;
}

string resultados::setcodigo_entre(string codigo_entre) {
    this->codigo_entre = codigo_entre;
    return this->codigo_entre;
}

string resultados::getcodigo_entre() {
    return this->codigo_entre;
}

string resultados::setnombre_entre(string nombre_entre) {
    this->nombre_entre = nombre_entre;
    return this->nombre_entre;
}

string resultados::getnombre_entre() {
    return this->nombre_entre;
}

string resultados::setnom_entre(string nom_entre) {
    this->nom_entre = nom_entre;
    return this->nom_entre;
}

string resultados::getnom_entre() {
    return this->nom_entre;
}

string resultados::setclinica(string clinica) {
    this->clinica = clinica;
    return this->clinica;
}

string resultados::getclinica() {
    return this->clinica;
}

string resultados::setmedico(string medico) {
    this->medico = medico;
    return this->medico;
}

string resultados::getmedico() {
    return this->medico;
}


string resultados::sethorario(string horario) {
    this->horario = horario;
    return this->horario;
}

string resultados::gethorario() {
    return this->horario;
}

void resultados::Menu_alumno() {
    int opcion;
    if (validarCarnet()) {
        do {
            system("cls");
            cout << "\t\t\t+------------------------------------------+" << endl;
            cout << "\t\t\t|         ASIGNACION DE RESULTADOS         |" << endl;
            cout << "\t\t\t+------------------------------------------+" << endl;
            cout << "\t\t\t|1. Ingreso de sus datos                   |" << endl;
            cout << "\t\t\t|2. Imprimir Boleta de asignacion          |" << endl;
            cout << "\t\t\t|3. regresar al menu anterior              |" << endl;
            cout << "\t\t\t+------------------------------------------+" << endl;
            cout << "\t\t\t|Opcion a escoger:[1/2/3]              |" << endl;
            cout << "\t\t\t+------------------------------------------+" << endl;
            cout << "\t\t\tIngresa tu Opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1: {
                    if (ValidaAsignacion(entrenador.id)) {
                        cout << "\t\t\tEste entrenador ya ha hecho asignaciones..." << endl << endl << endl;
                        system("pause");
                        break;
                    } else {
                        asignacion_entr(entrenador.id); // Cambiado el nombre de la funci�n
                    }
                    break;
                }
                case 2:{
                    desplegarBoleta(entrenador.id,entrenador.nom1);
                    system("pause");
                }
                    break;
                case 3:
                    break;
                default:
                    cout << "\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
                    break;
            }
        } while (opcion != 3);
    }
}

bool resultados::validarCarnet() {
    system("cls");
    fstream archivo;
    string idPersona;
    bool encontrado = false;

    cout << "+---------------------------------------------------------------------------------+" << endl;
    cout << "+                     BIENVENIDO A NUESTRA VALIDACION                             +" << endl;
    cout << "+---------------------------------------------------------------------------------+" << endl;

    archivo.open("Entrenador.dat", ios::binary | ios::in); // Solo lectura
    if (!archivo) {
        cout << "Error, no se encuentra informacion..." << endl;
        return false;
    }

    cout << "Ingrese su numero de carnet: ";
    cin >> idPersona;

    while (archivo.read(reinterpret_cast<char*>(&entrenador), sizeof(Entrenador))) {

        if (entrenador.id == idPersona) {
            encontrado = true;
            cout << "Bienvenido a nuestro sistema de asignacion : " << entrenador.nom1 << " " << entrenador.ape1 << "!" << endl; // Mostrar el nombre del alumno
            archivo.close(); // Cerrar el archivo antes de continuar
            system("pause");

            return true; // Salir de la funci�n despu�s de la asignaci�n
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "No se encontro un empleado con el ID proporcionado." << endl;
        system("pause");
        cout << "Presione Enter Para Continuar";
        cin.ignore();
        cin.get();
        return false;
    }
    return false; // Asegurando retorno en todas las rutas de ejecuci�n
}

bool resultados::ValidarCL(int codigo) {
    fstream archivo("Clinica.dat", ios::binary | ios::in);
    if (!archivo) {
        return false;
    }
    Clinica clinica;
    bool encontrada = false;
    while (archivo.read(reinterpret_cast<char*>(&clinica), sizeof(Clinica))) {
        if (clinica.codigo == codigo) {
            encontrada = true;
            break;
        }
    }

    archivo.close();
    return encontrada;
}
bool resultados::ValidarME(int codigo) {
    fstream archivo("Medico.dat", ios::binary | ios::in);
    if (!archivo) {
        return false;
    }
    Medico medico;
    bool encontrada = false;
    while (archivo.read(reinterpret_cast<char*>(&medico), sizeof(Medico))) {
        if (medico.codigo == codigo) {
            encontrada = true;
            break;
        }
    }

    archivo.close();
    return encontrada;
}

bool resultados::ValidarHO(int codigo) {
    fstream archivo("Horario.dat", ios::binary | ios::in);
    if (!archivo) {
        return false;
    }
    Horario horario; // Cambiado el nombre de la variable a min�scula

    bool encontrada = false;
    while (archivo.read(reinterpret_cast<char*>(&horario), sizeof(Horario))) { // Cambiado el nombre de la variable a min�scula
        if (horario.codigo == codigo) { // Cambiado el nombre de la variable a min�scula
            encontrada = true;
            break;
        }
    }

    archivo.close();
    return encontrada;
}

bool resultados::ValidaAsignacion(const char* carnet) {
    fstream archivo("RESULTADOS.dat", ios::binary | ios::in);
    if (!archivo) {
        return false;
    }
    Resultados resultados;
    bool encontrada = false;
    while (archivo.read(reinterpret_cast<char*>(&resultados), sizeof(Resultados))) {
        if (strcmp(resultados.carnet, carnet) == 0) {
            encontrada = true;
            break;
        }
    }
    archivo.close();
    return encontrada;
}

void resultados::asignacion_entr(const char* carnet) {
   system("cls");
    Resultados resultados;
    strcpy(resultados.carnet, carnet); // Corregido

    // ----------------------------------------ENTRADA Y VALIDACION DE JUGADORES Y EQUIPOS DEL EQUIPO A-----------------------------------------------------

    cout << "---------------BIENVENIDO-----------------" << endl;
    cout << "--ELIJA LA SEDE DE TRABAJO A LA QUE DESEA IR ----" << endl;
    system("pause");

    bool codigoValido = false;

    // Validar c�digo del jugador principal para el equipo A
    while (!codigoValido) {
        ClinicaCRUD CClinica;
        CClinica.DesplegarClinica();
        cout << "Escriba el codigo de la sede: " << endl;
        cin >> resultados.codigoClinica;
        cin.ignore();

        if (ValidarCL(resultados.codigoClinica)) {
            codigoValido = true;
        } else {
            system("cls");
            cout << "El codigo de la sede seleccionada no existe!! Intente de nuevo." << endl << endl;
            system("pause");
        }
    }

    cout << "Su Sede ha sido asignada exitosamente" << endl;
    system("pause");
    system("cls");


    // ----------------------------------------ENTRADA Y VALIDACION DE SECCIONES-----------------------------------------------------

     cout << "---------------BIENVENIDO-----------------" << endl;
    cout << "-------ELIJA EL GERENTE QUE DESEA ---------" << endl;
    system("pause");

    codigoValido = false; // Reiniciada

    // Validar c�digo de secci�n
    while (!codigoValido) {
        MedicoCRUD MMedico;
        MMedico.DesplegarMedico();
        cout << "Escriba el codigo del gerente que desea :" << endl;
        cin >> resultados.codigoMedico;
        cin.ignore();

        if (ValidarME(resultados.codigoMedico)) {
            codigoValido = true;
        } else {
            system("cls");
            cout << "El codigo del gerente que ha elegido no existe! Intente de nuevo." << endl << endl;
            system("pause");
        }
    }

    cout << "Gerente Asignado exitosamente!" << endl;
    system("pause");
    system("cls");

    // ----------------------------------------ENTRADA Y VALIDACION DE SECCIONES-----------------------------------------------------

    cout << "---------------BIENVENIDO-----------------" << endl;
    cout << "-------ELIJA EL HORARIO DE TRABAJO---------" << endl;
    system("pause");

    codigoValido = false; // Reiniciada

    // Validar c�digo de secci�n
    while (!codigoValido) {
        HorarioCRUD HHorario;
        HHorario.DesplegarHorario();
        cout << "Escriba el codigo del horario que desea:" << endl;
        cin >> resultados.codigoHorario;
        cin.ignore();

        if (ValidarHO(resultados.codigoHorario)) {
            codigoValido = true;
        } else {
            system("cls");
            cout << "El codigo del horario no existe!! Intente de nuevo." << endl << endl;
            system("pause");
        }
    }

    cout << "Su horario fue asignado exitosamente!" << endl;
    system("pause");
    system("cls");


    // ----------------------------------------GUARDAR EN ARCHIVO BINARIO-----------------------------------------------------

    ofstream archivo("RESULTADOS.dat", ios::binary | ios::app);
    if (archivo.is_open()) {
        archivo.write(reinterpret_cast<char*>(&resultados), sizeof(Resultados));
        archivo.close();
        cout << "Cita creada exitosamente!" << endl;
    } else {
        cout << "Error al abrir el archivo para guardar las asignaciones." << endl;
    }

    system("pause");
}

void resultados::desplegarBoleta(const char* carnet,string nombre) {
    system("cls");
    bool encontrado ;
    cout << "+------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "+                                       BIENVENIDO A NUESTRA CORPORACION   !                                 +" << endl;
    cout << "+------------------------------------------------------------------------------------------------------------+" << endl;

    ifstream archivo("RESULTADOS.dat", ios::binary | ios::in);
    if (!archivo) {
        cout << "Error, no se encuentra informaci�n...";
        return;
    }
    string scarnet = carnet ;
    Resultados resultados;

    while (archivo.read(reinterpret_cast<char*>(&resultados), sizeof(Resultados))) {

            if ( resultados.carnet == scarnet) {
                encontrado = true ;
                cout << "--------------------------------------------------------------------------------------------------------------"<<endl;
                cout << "                                                     DESCRIPCION DE SU ASIGNACION                            |"<<endl;
                cout << "--------------------------------------------------------------------------------------------------------------"<<endl;
                cout << "                      -> Nombre del empleado: " << nombre << endl; // Mostrar el carnet
                cout << "                      -> Sede elegida: " << ObtenerClinica(resultados.codigoClinica) << endl;
                cout << "                      -> Gerente Seleccionado: " << ObtenerMedico(resultados.codigoMedico) << endl;
                cout << "---------------------------------------------------------------------------------------------------------------"<<endl;
                cout << "---------------------------------------------------------------------------------------------------------------"<<endl;
                cout << "|                                          DATOS GENERALES DE LA ASIGNACION                                   | "<<endl;
                cout << "---------------------------------------------------------------------------------------------------------------"<<endl;
                cout << "                      -> Jornada: " << ObtenerHorario(resultados.codigoHorario) << endl;
                cout << "                      -> Horario seleccionado: " << ObtenerHorario2(resultados.codigoHorario) << endl;
                cout << "                      -> Especialidad del gerente elegido: " << ObtenerMedicoESP(resultados.codigoMedico) << endl;
                cout << "                      -> Direccion de la Sede: " << ObtenerClinicaDIR(resultados.codigoClinica) << endl;
                cout << "---------------------------------------------------------------------------------------------------------------"<<endl;

            }
    }
}

bool resultados::ValidaAsignacion2 (const char* carnet)
{
    bool encontrado;
    string scarnet = carnet ;
    ifstream archivo("RESULTADOS", ios::binary | ios::in);
    if (!archivo) {
        cout << "Error, no se encuentra informacion...";
        encontrado = false;
    }

    Resultados resultados;

    while (archivo.read(reinterpret_cast<char*>(&resultados), sizeof(Resultados))) {
        if (resultados.carnet == scarnet)
            encontrado = true;
        else
            encontrado = false;
    }
    archivo.close();
    return encontrado;
}

string resultados::ObtenerClinica(int codigo)
{
    string nombre ;
    ifstream archivo("Clinica.dat", ios::binary | ios::in);
    if (!archivo) {
        cout << "Error, no se encuentra informacion...";
        return "";
    }

    Clinica clinica;

    while (archivo.read(reinterpret_cast<char*>(&clinica), sizeof(Clinica))) {
        if (clinica.codigo == codigo) {
            nombre = clinica.nombre;
            break;
        } else {
            nombre = "[No Encontrado]";
        }
    }
    archivo.close();

    return nombre;
}

string resultados::ObtenerClinicaDIR(int codigo)
{
    string nombre ;
    ifstream archivo("Clinica.dat", ios::binary | ios::in);
    if (!archivo) {
        cout << "Error, no se encuentra informacion...";
        return "";
    }

    Clinica clinica;

    while (archivo.read(reinterpret_cast<char*>(&clinica), sizeof(Clinica))) {
        if (clinica.codigo == codigo) {
            nombre = clinica.direccion;
            break;
        } else {
            nombre = "[No Encontrado]";
        }
    }
    archivo.close();

    return nombre;
}
string resultados::ObtenerMedico(int codigo)
{
    string nombre;
    ifstream archivo("Medico.dat", ios::binary | ios::in);
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo de equipos." << endl;
        return "";
    }

    Medico medico;

    bool encontrado = false;
    while (archivo.read(reinterpret_cast<char*>(&medico), sizeof(Medico))) {
        if (medico.codigo == codigo) {
            nombre = medico.nombre;
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        nombre = "[No Encontrado]";
    }

    return nombre;
}
string resultados::ObtenerMedicoESP(int codigo)
{
    string nombre;
    ifstream archivo("Medico.dat", ios::binary | ios::in);
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo de equipos." << endl;
        return "";
    }

    Medico medico;

    bool encontrado = false;
    while (archivo.read(reinterpret_cast<char*>(&medico), sizeof(Medico))) {
        if (medico.codigo == codigo) {
            nombre = medico.especialidad;
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        nombre = "[No Encontrado]";
    }

    return nombre;
}

string resultados::ObtenerHorario(int codigo)
{
    string nombre;
    ifstream archivo("Horario.dat", ios::binary | ios::in);
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo de horarios." << endl;
        return "";
    }

    Horario horario;

    bool encontrado = false;
    while (archivo.read(reinterpret_cast<char*>(&horario), sizeof(Horario))) {
        if (horario.codigo == codigo) {
            nombre = horario.dia;
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        nombre = "[No Encontrado]";
    }

    return nombre;
}

string resultados::ObtenerHorario2(int codigo)
{
    string nombre;
    ifstream archivo("Horario.dat", ios::binary | ios::in);
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo de horarios." << endl;
        return "";
    }

    Horario horario;

    bool encontrado = false;
    while (archivo.read(reinterpret_cast<char*>(&horario), sizeof(Horario))) {
        if (horario.codigo == codigo) {
            nombre = horario.hora;
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        nombre = "[No Encontrado]";
    }

    return nombre;
}

