/*Autor:Yago Gonzales
*/
#include <iostream>
#include <string>
using namespace std;


struct Notas {
    float EP;  
    float EF;  
    float PP; 
    
    float calcularPromedio() {
        return EP * 0.3 + EF * 0.5 + PP * 0.2;
    }

    string obtenerEstado() {
        float prom = calcularPromedio();
        if (prom >= 10.5) return "Aprobado";
        else return "Desaprobado";
    }
};


struct Curso {
    string codigo;
    string nombre;
    int creditos;
    string profesor;
    Notas notas;  

    void mostrarInformacion() {
        cout << "Codigo del curso: " << codigo << endl;
        cout << "Nombre del curso: " << nombre << endl;
        cout << "Creditos: " << creditos << endl;
        cout << "Profesor: " << profesor << endl;
    }
};

struct Estudiante {
    string codigo;
    string nombre;
    string carrera;
    int ciclo;
    Curso cursos[6]; 
    int cantidadCursos = 0;

    void mostrarDatos() {
        cout << "Codigo: " << codigo << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Carrera: " << carrera << endl;
        cout << "Ciclo: " << ciclo << endl;
    }
};

void registrarEstudiante(Estudiante estudiantes[], int &cantidad) {
    Estudiante nuevoEstudiante;
    cout << "--- REGISTRAR ESTUDIANTE ---" << endl;
    cout << "Código: ";
    cin >> nuevoEstudiante.codigo;
    cout << "Nombre: ";
    cin.ignore();
    getline(cin, nuevoEstudiante.nombre);
    cout << "Carrera: ";
    getline(cin, nuevoEstudiante.carrera);
    cout << "Ciclo: ";
    cin >> nuevoEstudiante.ciclo;

    estudiantes[cantidad] = nuevoEstudiante;
    cantidad++;
    cout << "Estudiante registrado exitosamente." << endl;
}


void matricularCurso(Estudiante &estudiante) {
    if (estudiante.cantidadCursos >= 6) {
        cout << "El estudiante ya está matriculado en el máximo de cursos." << endl;
        return;
    }
    Curso nuevoCurso;
    cout << "=== MATRICULAR CURSO ===" << endl;
    cout << "Código del curso: ";
    cin >> nuevoCurso.codigo;
    cout << "Nombre del curso: ";
    cin.ignore(); 
    getline(cin, nuevoCurso.nombre);
    cout << "Créditos: ";
    cin >> nuevoCurso.creditos;
    cout << "Profesor: ";
    cin.ignore();
    getline(cin, nuevoCurso.profesor);

    estudiante.cursos[estudiante.cantidadCursos] = nuevoCurso;
    estudiante.cantidadCursos++;
    cout << "Curso matriculado exitosamente." << endl;
}

void ingresarNotas(Estudiante &estudiante) {
    cout << "--- INGRESAR NOTAS ---" << endl;

    for (int i = 0; i < estudiante.cantidadCursos; i++) {
        Curso &curso = estudiante.cursos[i];
        cout << "Curso: " << curso.nombre << endl;
        cout << "Examen Parcial: ";
        cin >> curso.notas.EP;
        cout << "Examen Final: ";
        cin >> curso.notas.EF;
        cout << "Promedio de Prácticas: ";
        cin >> curso.notas.PP;
    }
}

void mostrarCursosEstudiante(const Estudiante &estudiante) {
    cout << "--- CURSOS DEL ESTUDIANTE ---" << endl;
    for (int i = 0; i < estudiante.cantidadCursos; i++) {
        cout << "Curso: " << estudiante.cursos[i].nombre << endl;
        cout << "Estado: " << estudiante.cursos[i].notas.obtenerEstado() << endl;
    }
}

float calcularPromedioPonderado(const Estudiante &estudiante) {
    float sumaPromedios = 0;
    int totalCreditos = 0;

    for (int i = 0; i < estudiante.cantidadCursos; i++) {
        float promedio = estudiante.cursos[i].notas.calcularPromedio();
        sumaPromedios += promedio * estudiante.cursos[i].creditos;
        totalCreditos += estudiante.cursos[i].creditos;
    }

    return totalCreditos > 0 ? sumaPromedios / totalCreditos : 0;
}


void mostrarMejorPromedio(const Estudiante estudiantes[], int cantidad) {
    Estudiante mejorEstudiante;
    float mejorPromedio = 0;

    for (int i = 0; i < cantidad; i++) {
        float promedio = calcularPromedioPonderado(estudiantes[i]);
        if (promedio > mejorPromedio) {
            mejorPromedio = promedio;
            mejorEstudiante = estudiantes[i];
        }
    }

    cout << "Mejor Promedio: " << mejorPromedio << endl;
    cout << "Estudiante: " << mejorEstudiante.nombre << endl;
}

int main() {
    Estudiante estudiantes[100];
    int cantidadEstudiantes = 0;
    int opcion;

    do {
        cout << "--- SISTEMA DE GESTIÓN ACADÉMICA UNI ---" << endl;
        cout << "1. Registrar estudiante" << endl;
        cout << "2. Matricular curso a estudiante" << endl;
        cout << "3. Ingresar notas de curso" << endl;
        cout << "4. Mostrar información de estudiante" << endl;
        cout << "5. Generar boleta de notas" << endl;
        cout << "6. Mostrar mejor promedio" << endl;
        cout << "7. Estudiantes aprobados por curso" << endl;
        cout << "8. Reporte general" << endl;
        cout << "9. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:{
                registrarEstudiante(estudiantes, cantidadEstudiantes);
                break;
            }
            
            case 2:{
              if (cantidadEstudiantes > 0) {
                    string codigo;
                    cout << "Código del estudiante: ";
                    cin >> codigo;
                    for (int i = 0; i < cantidadEstudiantes; i++) {
                        if (estudiantes[i].codigo == codigo) {
                            matricularCurso(estudiantes[i]);
                            break;
                        }
                    }
                } else {
                    cout << "No hay estudiantes registrados." << endl;
                }
                break;
            }
                
            case 3:{
                if (cantidadEstudiantes > 0) {
                    string codigo;
                    cout << "Código del estudiante: ";
                    cin >> codigo;
                    for (int i = 0; i < cantidadEstudiantes; i++) {
                        if (estudiantes[i].codigo == codigo) {
                            ingresarNotas(estudiantes[i]);
                            break;
                        }
                    }
                } else {
                    cout << "No hay estudiantes registrados." << endl;
                }
                break;
            }
            
            case 4:{
                if (cantidadEstudiantes > 0) {
                    string codigo;
                    cout << "Código del estudiante: ";
                    cin >> codigo;
                    for (int i = 0; i < cantidadEstudiantes; i++) {
                        if (estudiantes[i].codigo == codigo) {
                            estudiantes[i].mostrarDatos();
                            mostrarCursosEstudiante(estudiantes[i]);
                            break;
                        }
                    }
                } else {
                    cout << "No hay estudiantes registrados." << endl;
                }
                break;
            }
            
            case 5:{
			
                if (cantidadEstudiantes > 0) {
                    string codigo;
                    cout << "Código del estudiante: ";
                    cin >> codigo;
                    for (int i = 0; i < cantidadEstudiantes; i++) {
                        if (estudiantes[i].codigo == codigo) {
                            cout << "Boleta de Notas de " << estudiantes[i].nombre << endl;
                            mostrarCursosEstudiante(estudiantes[i]);
                            break;
                        }
                    }
                } else {
                    cout << "No hay estudiantes registrados." << endl;
                }
                break;
            }
            case 6:
                mostrarMejorPromedio(estudiantes, cantidadEstudiantes);
                break;
            case 9:{
                cout << "Saliendo..." << endl;
                break;
				}
            default:{
			   cout << "Opción no válida." << endl;
                break;
            }
        }
        
    } while(opcion != 9);

    return 0;
}

