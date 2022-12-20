#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  // Supongamos que tenemos un conjunto de datos con una variable independiente y una variable dependiente
  vector<double> X = {1, 2, 3, 4};
  vector<double> y = {1, 2, 3, 4};

  // Inicializa los coeficientes del modelo con valores aleatorios
  double beta_0 = 1;
  double beta_1 = 1;

  // Itera hasta que el error cuadrático medio sea lo suficientemente pequeño
  double mse = 1e9;
  double mse_tolerance = 1e-6;
  while (mse > mse_tolerance) {
    // Calcula el error cuadrático medio
    double sum_sq_error = 0;
    for (int i = 0; i < X.size(); i++) {
      double y_pred = beta_0 + beta_1 * X[i];
      sum_sq_error += (y[i] - y_pred) * (y[i] - y_pred);
    }
    mse = sum_sq_error / X.size();

    // Actualiza los coeficientes del modelo utilizando el algoritmo de gradiente descendiente
    double alpha = 0.01; // Tasa de aprendizaje
    for (int i = 0; i < X.size(); i++) {
      double y_pred = beta_0 + beta_1 * X[i];
      beta_0 -= alpha * (y_pred - y[i]);
      beta_1 -= alpha * (y_pred - y[i]) * X[i];
    }
  }

  // Muestra los coeficientes del modelo
  cout << "Coeficientes del modelo: beta_0 = " << beta_0 << ", beta_1 = " << beta_1 << endl;

  return 0;
}
