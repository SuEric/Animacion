#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int> > crearTabla(int nFil)
{
    vector< vector<int> > tabla(4, vector<int>(2));
    
    int n1, n2;
    
    for (int i = 0; i < nFil; i++) {
        cout << "Ingrese fila " << i+1 << ": "; cin >> n1 >> n2;
        tabla[i][0] = n1;
        tabla[i][1] = n2;
    }
    
    return tabla;
}

string crearPolinomioLangrange(vector<vector<int> > tabla)
{
    vector<string> lagranges(tabla.size());
    vector<int>denominadores(3);
    int x = 0;
    
    // Calculo de coeficientes Lagranges
    for (int j = 0; j < tabla.size(); j++) {
        for (int i = 0; i < tabla.size(); i++) {
            if (i == j) continue; // Salto sig iteracion
            else {
                
                denominadores[x] = tabla[j][0] - tabla[i][0];
                x++;
                
                if (i == tabla.size() - 1 || (i == tabla.size() - 2 & j == tabla.size() - 1) ) { // Ultimo
                    int denominador = denominadores[0] * denominadores[1] * denominadores[2];
                    lagranges[j] += "(x - " + to_string(tabla[i][0]) + ") / " + to_string(denominador);
                }
                else {
                    lagranges[j] += "(x - " + to_string(tabla[i][0]) + ") * ";
                }
            }
        }
        x = 0;
        cout << endl;
    }
    
    cout << "Polinomio de lagrange: " << lagranges[0] << endl;
    cout << "Polinomio de lagrange: " << lagranges[1] << endl;
    cout << "Polinomio de lagrange: " << lagranges[2] << endl;
    cout << "Polinomio de lagrange: " << lagranges[3] << endl;
    
    string polinomio;
    
    // Construccion Polinomio grado N
    for (int i = 0; i < tabla.size(); i++) {
        if (i != tabla.size() - 1) polinomio += to_string(tabla[i][1]) + " * " + lagranges[i] + " + ";
        else polinomio += to_string(tabla[i][1]) + " * " + lagranges[i];
    }
    
    cout << "Polinomio de lagrange: " << polinomio << endl;
    
    return polinomio;
}

int interpolacionLagrange(int interpolante , string polinomio)
{
    
    return interpolante;
}

int main()
{
    int gradoPoli, numDatos;
    
    cout << "Ingrese grado de polinomio: "; cin >> gradoPoli;
    cout << "Ingrese cantidad de datos: "; cin >> numDatos;
    
    vector< vector<int> > tabla = crearTabla(numDatos);
    
    string polinomioLagrange = "";
    
    cout << endl;
    cout << endl;
    
    cout << "TABLA" << endl;
    
    for (int i = 0; i < tabla.size(); i++) {
        cout << tabla[i][0] << "\t\t" << tabla[i][1] << endl;
    }
    
    polinomioLagrange = crearPolinomioLangrange(tabla);

    int interpolante;
    cout << "Ingrese numero a interpolar: "; cin >> interpolante;
    
    interpolante = interpolacionLagrange(interpolante, polinomioLagrange);
    
    return 0;
}