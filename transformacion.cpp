#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
  // Fecha en formato ISO 8601
  string iso_date = "1970-01-01";

  // Extrae el año, mes y día de la fecha
  int year = stoi(iso_date.substr(0, 4));
  int month = stoi(iso_date.substr(5, 2));
  int day = stoi(iso_date.substr(8, 2));

  // Transforma la fecha a un número
  // El número es el número de días transcurridos desde el 1 de enero de 1970
  long long number = (year - 1970) * 365 + day;
  for (int i = 1970; i < year; i++) {
    if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
      number++;
    }
  }
  for (int i = 1; i < month; i++) {
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

  // Muestra el número
  cout << number << endl;

  return 0;
}