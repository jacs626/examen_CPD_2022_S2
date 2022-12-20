#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  // Abre el archivo CSV para lectura
  ifstream file("datos_examen.csv");

  // Almacena los datos leídos del archivo
  vector<vector<string>> data;

  // Lee cada línea del archivo
  string line;
  while (getline(file, line)) {
    // Crea un flujo de entrada para parsear la línea
    istringstream linestream(line);

    // Almacena los valores separados por ;
    vector<string> values;
    string value;
    int i = 0;
    while (getline(linestream, value, ';')) {
        if (i==0)
        {
            cout << "fecha:" << endl;
            cout << value << endl;
        }
        else
        {
            cout << "accidente:" << endl;
            cout << value << endl;
        }
        i=i+1;
        
        
      values.push_back(value);
    }

    // Añade los valores a la matriz de datos
    data.push_back(values);
  }

  // Cierra el archivo
  file.close();

  // Almacena las columnas en variables independientes
  vector<string> column_1;
  vector<string> column_2;
  for (int i = 0; i < data.size(); i++) {
    column_1.push_back(data[i][0]);
    column_2.push_back(data[i][1]);
  }

  // Muestra las columnas
  cout << "Columna 1:" << endl;
  for (int i = 0; i < column_1.size(); i++) {
    cout << column_1[i] << endl;
  }
  cout << endl;
  cout << "Columna 2:" << endl;
  for (int i = 0; i < column_2.size(); i++) {
    cout << column_2[i] << endl;
  }

  return 0;
}
