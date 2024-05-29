#include "medico.h"
#include "bitacora.h"
#include "login.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <string>

using namespace std;

void MedicoCRUD::CrudMedicos() {
    int choice;
    do {
        system("cls");
        cout << "\t\t\t----------------------------------------------" << endl;
        cout << "\t\t\t| SISTEMA DE CORPORACION - GESTION DE GERENTES |" << endl;
        cout << "\t\t\t----------------------------------------------" << endl;
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
                IngresarMedico();
                system("Pause");
                break;
            case 2:
                system("Cls");
                ModificarMedico();
                system("Pause");
                break;
            case 3:
                system("Cls");
                BorrarMedico();
                system("Pause");
                break;
            case 4:
                DesplegarMedico();
                break;
            case 5:
                break;
            default:
                cout << "\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
                cin.get();
        }
    } while (choice != 5);
}

// Funci�n que valida si ya existe el m�dico para evitar redundancia de datos
bool MedicoCRUD::ValidarMedico(int codigo) {
    fstream archivo("Medico.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        return false;
    }

    Medico medico;
    bool encontrado = false;
    while (archivo.read(reinterpret_cast<char*>(&medico), sizeof(Medico))) {
        if (medico.codigo == codigo) {
            encontrado = true;
            break;
        }
    }

    archivo.close();

    return encontrado;
}

// Aqu� se agregan m�dicos que son almacenados
void MedicoCRUD::IngresarMedico() {
    string codigoPrograma = "6000";
    system("cls");
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Agregar Gerente--------------------------------------------" << endl;
    Medico medico;
    cout << "Ingrese el codigo del Gerente: ";
    cin >> medico.codigo;
    cin.ignore();
    if (ValidarMedico(medico.codigo)) {
        system("cls");
        cout << "El codigo del Gerente ya existe, intente de nuevo!!" << endl << endl << endl << endl;
        return;
    }

    cout << "Ingrese el nombre: ";
    cin.getline(medico.nombre, 50);

    cout << "Ingrese el area en la que se especifica: ";
    cin.getline(medico.especialidad, 50);

    ofstream archivo("Medico.dat", ios::binary | ios::app);
    archivo.write(reinterpret_cast<const char*>(&medico), sizeof(Medico));
    archivo.close();

    Bitacora Auditoria;
    string user, pass;

    Auditoria.ingresoBitacora(user, codigoPrograma, "IMED"); // IMED = Insertar Medico

    cout << "Gerente agregado exitosamente!" << endl;
}

// Modificar m�dicos
void MedicoCRUD::ModificarMedico() {
    string codigoPrograma = "6000";
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Modificacion de Gerente--------------------------------------------" << endl;
    int codigo;
    cout << "Ingrese el codigo del Gerente a modificar: ";
    cin >> codigo;

    fstream archivo("Medico.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No hay Gerentes registrados." << endl;
        return;
    }

    Medico medico;
    bool encontrado = false;
    while (archivo.read(reinterpret_cast<char*>(&medico), sizeof(Medico))) {
        if (medico.codigo == codigo) {
            cout << "Ingrese el nuevo nombre: ";
            cin.ignore();
            cin.getline(medico.nombre, 50);

            cout << "Ingrese el nuevo cargo que ocupara: ";
            cin.getline(medico.especialidad, 50);

            archivo.seekp(-static_cast<int>(sizeof(Medico)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&medico), sizeof(Medico));

            encontrado = true;
            break;
        }
    }

    archivo.close();

    Bitacora Auditoria;
    string user, pass;

    Auditoria.ingresoBitacora(user, codigoPrograma, "UMED"); // UMED = Update Medico

    if (!encontrado) {
        cout << "No se encontr� el Gerente con el codigo ingresado." << endl;
    } else {
        cout << "Gerente modificado exitosamente!" << endl;
    }
}

void MedicoCRUD::BorrarMedico() {
    string codigoPrograma = "6000";
    int codigo;
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n-------------------------------------------------Eliminar Gerente--------------------------------------------" << endl;
    cout << "Ingrese el codigo del medico a Gerente: ";
    cin >> codigo;

    ifstream archivo("Medico.dat", ios::binary);
    if (!archivo) {
        cout << "No hay Gerente registrados." << endl;
        return;
    }

    ofstream archivoTmp("Medico_tmp.dat", ios::binary);
    Medico medico;
    bool eliminado = false;
    while (archivo.read(reinterpret_cast<char*>(&medico), sizeof(Medico))) {
        if (medico.codigo != codigo) {
            archivoTmp.write(reinterpret_cast<const char*>(&medico), sizeof(Medico));
        } else {
            eliminado = true;
        }
    }

    archivo.close();
    archivoTmp.close();

    remove("Medico.dat");
    rename("Medico_tmp.dat", "Medico.dat");

    Bitacora Auditoria;
    string user, pass;

    Auditoria.ingresoBitacora(user, codigoPrograma, "DMED"); // DMED = Delete Medico

    if (eliminado) {
        cout << "Gerente eliminado exitosamente!" << endl;
    } else {
        cout << "No se encontr� el Gerente con el codigo ingresado." << endl;
    }
}

void MedicoCRUD::DesplegarMedico() {
    system("cls");
    string codigoPrograma = "6000";
    cout << "-----------------Despliegue de Gerentes registrados---------------------" << endl;
    ifstream archivo("Medico.dat", ios::binary);
    if (!archivo) {
        cout << "No hay medicos registrados." << endl;
        return;
    }

    Medico medico;
    while (archivo.read(reinterpret_cast<char*>(&medico), sizeof(Medico))) {
        cout << "Codigo: " << medico.codigo << endl;
        cout << "Nombre: " << medico.nombre << endl;
        cout << "Especialidad: " << medico.especialidad << endl;
        cout << "-----------------------------" << endl;
    }

    archivo.close();

    Bitacora Auditoria;
    string user, pass;

    Auditoria.ingresoBitacora(user, codigoPrograma, "RMED"); // RMED = Read Medico

    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

