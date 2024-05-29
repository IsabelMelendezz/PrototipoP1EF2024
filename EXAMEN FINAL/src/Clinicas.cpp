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

// Funci�n que valida si ya existe la cl�nica para evitar redundancia de datos
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

// Aqu� se agregan cl�nicas que son almacenadas
void ClinicaCRUD::IngresarClinica() {
    string codigoPrograma = "5000";
    system("cls");
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Agregar Sede--------------------------------------------" << endl;
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

    cout << "Ingrese la direcci�n: ";
    cin.getline(clinica.direccion, 100);

    ofstream archivo("Clinica.dat", ios::binary | ios::app);
    archivo.write(reinterpret_cast<const char*>(&clinica), sizeof(Clinica));
    archivo.close();

    Bitacora Auditoria;
    string user, pass;

    Auditoria.ingresoBitacora(user, codigoPrograma, "ICL"); // ICL = Insertar Cl�nica

    cout << "Sede agregada exitosamente!" << endl;
}

// Modificar cl�nicas
void ClinicaCRUD::ModificarClinica() {
    string codigoPrograma = "5000";
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Modificacion de sedes--------------------------------------------" << endl;
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

            cout << "Ingrese la nueva direcci�n: ";
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

    Auditoria.ingresoBitacora(user, codigoPrograma, "UCL"); // UCL = Update Cl�nica

    if (!encontrada) {
        cout << "No se encontr� la Sede con el c�digo ingresado." << endl;
    } else {
        cout << "Sede modificada exitosamente!" << endl;
    }
}

void ClinicaCRUD::BorrarClinica() {
    string codigoPrograma = "5000";
    int codigo;
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Eliminar sedes--------------------------------------------" << endl;
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

    Auditoria.ingresoBitacora(user, codigoPrograma, "DCL"); // DCL = Delete Cl�nica

    if (eliminada) {
        cout << "Cl�nica eliminada exitosamente!" << endl;
    } else {
        cout << "No se encontr� la sede con el c�digo ingresado." << endl;
    }
}

void ClinicaCRUD::DesplegarClinica() {
    system("cls");
    string codigoPrograma = "5000";
    cout << "-----------------Despliegue de sedes registradas---------------------" << endl;
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

    Auditoria.ingresoBitacora(user, codigoPrograma, "RCL"); // RCL = Read Cl�nica

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}
