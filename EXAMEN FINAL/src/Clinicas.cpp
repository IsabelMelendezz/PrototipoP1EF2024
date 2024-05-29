#include "clinicas.h"
#include "bitacora.h"
#include "login.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <string>

using namespace std;

void ClinicaCRUD::CrudClinicas() {
    int choice;
    do {
        system("cls");
        cout << "\t\t\t-----------------------------------------------" << endl;
        cout << "\t\t\t| SISTEMA DE CORPORACION - GESTION DE SEDES    |" << endl;
        cout << "\t\t\t-----------------------------------------------" << endl;
        cout << "\t\t\t 1. Ingresar" << endl;
        cout << "\t\t\t 2. Modificar" << endl;
        cout << "\t\t\t 3. Borrar" << endl;
        cout << "\t\t\t 4. Desplegar" << endl;
        cout << "\t\t\t 5. Regresar Menu Anterior" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\t |   Opcion a escoger:[1|2|3|4|5|]           |" << endl;
        cout << "\t\t\t --------------------------------------------" << endl;
        cout << "\t\t\tIngresa tu Opcion: ";
        cin >> choice;

        switch (choice) {
            case 1:
                IngresarClinica();
                system("Pause");
                break;
            case 2:
                system("Cls");
                ModificarClinica();
                system("Pause");
                break;
            case 3:
                system("Cls");
                BorrarClinica();
                system("Pause");
                break;
            case 4:
                DesplegarClinica();
                break;
            case 5:
                break;
            default:
                cout << "\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
                cin.get();
        }
    } while (choice != 5);
}

// Función que valida si ya existe la clínica para evitar redundancia de datos
bool ClinicaCRUD::ValidarClinica(int codigo) {
    fstream archivo("Clinica.dat", ios::binary | ios::in | ios::out);
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

// Aquí se agregan clínicas que son almacenadas
void ClinicaCRUD::IngresarClinica() {
    string codigoPrograma = "5000";
    system("cls");
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Agregar Clínica--------------------------------------------" << endl;
    Clinica clinica;
    cout << "Ingrese el codigo de la sede donde trabajara: ";
    cin >> clinica.codigo;
    cin.ignore();
    if (ValidarClinica(clinica.codigo)) {
        system("cls");
        cout << "El codigo de la sede ya existe, intente de nuevo!!" << endl << endl << endl << endl;
        return;
    }

    cout << "Ingrese el nombre: ";
    cin.getline(clinica.nombre, 50);

    cout << "Ingrese la dirección: ";
    cin.getline(clinica.direccion, 100);

    ofstream archivo("Clinica.dat", ios::binary | ios::app);
    archivo.write(reinterpret_cast<const char*>(&clinica), sizeof(Clinica));
    archivo.close();

    Bitacora Auditoria;
    string user, pass;

    Auditoria.ingresoBitacora(user, codigoPrograma, "ICL"); // ICL = Insertar Clínica

    cout << "Sede agregada exitosamente!" << endl;
}

// Modificar clínicas
void ClinicaCRUD::ModificarClinica() {
    string codigoPrograma = "5000";
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Modificacion de Clínicas--------------------------------------------" << endl;
    int codigo;
    cout << "Ingrese el codigo de la Sede a modificar: ";
    cin >> codigo;

    fstream archivo("Clinica.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No hay Sedes registradas." << endl;
        return;
    }

    Clinica clinica;
    bool encontrada = false;
    while (archivo.read(reinterpret_cast<char*>(&clinica), sizeof(Clinica))) {
        if (clinica.codigo == codigo) {
            cout << "Ingrese el nuevo nombre: ";
            cin.ignore();
            cin.getline(clinica.nombre, 50);

            cout << "Ingrese la nueva dirección: ";
            cin.getline(clinica.direccion, 100);

            archivo.seekp(-static_cast<int>(sizeof(Clinica)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&clinica), sizeof(Clinica));

            encontrada = true;
            break;
        }
    }

    archivo.close();

    Bitacora Auditoria;
    string user, pass;

    Auditoria.ingresoBitacora(user, codigoPrograma, "UCL"); // UCL = Update Clínica

    if (!encontrada) {
        cout << "No se encontró la Sede con el código ingresado." << endl;
    } else {
        cout << "Sede modificada exitosamente!" << endl;
    }
}

void ClinicaCRUD::BorrarClinica() {
    string codigoPrograma = "5000";
    int codigo;
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Eliminar Clínicas--------------------------------------------" << endl;
    cout << "Ingrese el codigo de la Sede a eliminar: ";
    cin >> codigo;

    ifstream archivo("Clinica.dat", ios::binary);
    if (!archivo) {
        cout << "No hay Sedes registradas." << endl;
        return;
    }

    ofstream archivoTmp("Clinica_tmp.dat", ios::binary);
    Clinica clinica;
    bool eliminada = false;
    while (archivo.read(reinterpret_cast<char*>(&clinica), sizeof(Clinica))) {
        if (clinica.codigo != codigo) {
            archivoTmp.write(reinterpret_cast<const char*>(&clinica), sizeof(Clinica));
        } else {
            eliminada = true;
        }
    }

    archivo.close();
    archivoTmp.close();

    remove("Clinica.dat");
    rename("Clinica_tmp.dat", "Clinica.dat");

    Bitacora Auditoria;
    string user, pass;

    Auditoria.ingresoBitacora(user, codigoPrograma, "DCL"); // DCL = Delete Clínica

    if (eliminada) {
        cout << "Clínica eliminada exitosamente!" << endl;
    } else {
        cout << "No se encontró la sede con el código ingresado." << endl;
    }
}

void ClinicaCRUD::DesplegarClinica() {
    system("cls");
    string codigoPrograma = "5000";
    cout << "-----------------Despliegue de clínicas registradas---------------------" << endl;
    ifstream archivo("Clinica.dat", ios::binary);
    if (!archivo) {
        cout << "No hay Sedes registradas." << endl;
        return;
    }

    Clinica clinica;
    while (archivo.read(reinterpret_cast<char*>(&clinica), sizeof(Clinica))) {
        cout << "Codigo: " << clinica.codigo << endl;
        cout << "Nombre: " << clinica.nombre << endl;
        cout << "Direccion: " << clinica.direccion << endl;
        cout << "-----------------------------" << endl;
    }

    archivo.close();

    Bitacora Auditoria;
    string user, pass;

    Auditoria.ingresoBitacora(user, codigoPrograma, "RCL"); // RCL = Read Clínica

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}
