#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <cmath>
#include <vector>
#include <algorithm>
#include <omp.h>


using namespace std;


// Calcula el coeficiente de la variable independiente (m) para una regresión lineal
double calc_m(const std::vector<double>& x, const std::vector<double>& y) {
  int n = x.size();
  double sum_x = 0;
  double sum_y = 0;
  double sum_xy = 0;
  double sum_x2 = 0;

  // Añade la directiva #pragma omp parallel for para paralelizar el bucle for
  #pragma omp parallel for reduction(+:sum_x,sum_y,sum_xy,sum_x2)
  for (int i = 0; i < n; i++) {
    sum_x += x[i];
    sum_y += y[i];
    sum_xy += x[i] * y[i];
    sum_x2 += x[i] * x[i];
  }
  return (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
}

// Calcula el término independiente (b) para una regresión lineal
double calc_b(const std::vector<double>& x, const std::vector<double>& y, double m) {
  int n = x.size();
  double sum_x = 0;
  double sum_y = 0;

  // Añade la directiva #pragma omp parallel for para paralelizar el bucle for
  #pragma omp parallel for reduction(+:sum_x,sum_y)
  for (int i = 0; i < n; i++) {
    sum_x += x[i];
    sum_y += y[i];
  }
  return (sum_y - m * sum_x) / n;
}

// Predice el valor de la variable dependiente (y) para un valor dado de la variable independiente (x) utilizando una regresión lineal
double predict(double x, double m, double b) {
  return m * x + b;
}

int di(string iso_date) {
  // Fecha en formato ISO 8601

  // Extrae el año, mes y día de la fecha
  int year = stoi(iso_date.substr(0, 4));
  int month = stoi(iso_date.substr(5, 2));
  int day = stoi(iso_date.substr(8, 2));

  // Transforma la fecha a un número
  // El número es el número de días transcurridos desde el 01 de octubre de 2017
  long long number = (year - 2017) * 365 + day;
  for (int i = 2017; i < year; i++) {
    if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
      number++;
    }
  }
  for (int i = 10; i < month; i++) {
    if (i == 2) {
      if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        number += 29;
      } else {
        number += 28;
      }
    } else if (i == 4 || i == 6 || i == 9 || i == 11) {
      number += 30;
    } else {
      number += 31;
    }
  }
  return number;
}


int main() {
  cout << "Ingrese la fecha en formato ISO 8601 (aaaa-mm-dd): " << endl;
  string fechaStr = "2022-12-20";
  //cin >> fechaStr;
  // Habilita el uso de OpenMP
  #pragma omp parallel
  {
    // Establece el número de hilos a utilizar en el programa
    //omp_set_num_threads(2);
  }

  // Abre el archivo CSV para su lectura
  ifstream file("datos_examen.csv");
  if (!file.is_open()) {
    std::cerr << "Error: no se pudo abrir el archivo" << std::endl;
    return 1;
  }

  // Vector para almacenar las variables independientes (fechas)
  vector<double> X;
  // Vector para almacenar las variables dependientes (enteros)
  vector<double> Y;

  // Lee línea por línea del archivo
  string line;
    // Saltamos la primera fila de encabezado
  getline(file, line);
  while (getline(file, line)) {
    // Divide la línea en campos separados por ';'
    istringstream line_stream(line);
    string field;
    getline(line_stream, field, ';');
    // Almacena el primer campo (fecha) en el vector de variables independientes
    X.push_back(di(field));
    // Lee el segundo campo (entero) y lo almacena en el vector de variables dependientes
    int dependent_var;
    line_stream >> dependent_var;
    Y.push_back(dependent_var);
  }

  // Cierra el archivo
  file.close();

  // Vector de pruebas variables independientes (x)
  //vector<double> x = {1, 2, 3, 4, 5};
  // Vector de pruebas variables dependientes (y)
  //vector<double> y = {2,4,6,8,10};
  
  // Calcula el coeficiente de la variable independiente (m) y el término independiente (b) para la regresión lineal
  double m = calc_m(X, Y);
  double b = calc_b(X, Y, m);

  // Muestra los valores de m y b en pantalla
  //cout << "m: " << m << endl;
  //cout << "b: " << b << endl;

  // Predice el valor de y para x = 6 utilizando la regresión lineal
  double x_pred = di(fechaStr);
  double y_pred = predict(x_pred, m, b);
  cout << "Para la fecha: " << fechaStr << " Se esperan : " << y_pred << " accidentes"<< endl;

  return 0;
}
