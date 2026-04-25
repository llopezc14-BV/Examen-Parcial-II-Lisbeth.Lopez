#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Funciones
void Menu();
void registrarVenta();
void mostrarVentas();
void generarReporte();
void buscarPorMonto();

double calcularSubtotal(int cantidad, double precio);
double calcularDescuento(double subtotal, int tipoPago);
double calcularTotal(double subtotal, double descuento);

int main() {
    int opcion;

    do {
        Menu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                registrarVenta();
                break;
            case 2:
                mostrarVentas();
                break;
            case 3:
                generarReporte();
                break;
            case 4:
                 buscarPorMonto();
                break;
            case 5:
                cout << "\nSaliendo del sistema..." << endl;
                break;
            default:
                cout << "\nOpcion invalida." << endl;
                continue;
        }

    } while (opcion != 5);
    cout << "\nRealizado por: Lisbeth Vanesa Lopez Catalan" << endl;

    return 0;
}

// Mostrar menu
void Menu() {
    cout << "\n===== SISTEMA DE CONTROL DE VENTAS =====" << endl;
    cout << "1. Registrar una venta" << endl;
    cout << "2. Mostrar todas las ventas" << endl;
    cout << "3. Generar reporte general" << endl;
    cout << "4. Buscar ventas por monto" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

// Funciones
double calcularSubtotal(int cantidad, double precio) {
    return cantidad * precio;
}

double calcularDescuento(double subtotal, int tipoPago) {
    double descuento = 0;

    if (subtotal >= 500) {
        descuento = subtotal * 0.05;
    }

    if (tipoPago == 1 && subtotal >= 300) {
        descuento = descuento + (subtotal * 0.02);
    }

    return descuento;
}

double calcularTotal(double subtotal, double descuento) {
    return subtotal - descuento;
}

// Registrar venta
void registrarVenta() {
    ofstream archivo("ventas.txt", ios::app);

    string cliente, producto;
    int cantidad, tipoPago;
    double precio, subtotal, descuento, total;

    cout << "\nIngrese nombre del cliente: ";
    getline(cin, cliente);

    if (cliente == "0") {
        cout << "Registro cancelado." << endl;
        return;
    }


   cout << "Ingrese nombre del producto: ";
    getline(cin, producto);

    do {
        cout << "Ingrese cantidad: ";
        cin >> cantidad;

        if (cantidad <= 0) {
            cout << "Cantidad invalida." << endl;
            continue;
        }
        break;

    } while (true);

    do {
        cout << "Ingrese precio unitario: ";
        cin >> precio;

        if (precio <= 0) {
            cout << "Precio invalido." << endl;
            continue;
        }
        break;

    } while (true);

    do {
        cout << "Tipo de pago (1=Efectivo, 2=Tarjeta, 3=Transferencia): ";
        cin >> tipoPago;

        if (tipoPago < 1 || tipoPago > 3) {
            cout << "Tipo de pago invalido." << endl;
            continue;
        }
        break;

    } while (true);

    subtotal = calcularSubtotal(cantidad, precio);
    descuento = calcularDescuento(subtotal, tipoPago);
    total = calcularTotal(subtotal, descuento);

    archivo << cliente << "," << producto << "," << cantidad << "," << precio << ","
           << tipoPago << "," << subtotal << "," << descuento << "," << total << endl;

    archivo.close();

    cout << "\nVenta registrada correctamente." << endl;
}

// Mostrar ventas
void mostrarVentas() {
    ifstream archivo("ventas.txt");

    string cliente, producto;
    int cantidad, tipoPago;
    double precio, subtotal, descuento, total;

    cout << "\n===== VENTAS REGISTRADAS =====" << endl;

    while (getline(archivo, cliente, ',')) {
        getline(archivo, producto, ',');
        archivo >> cantidad;
        archivo.ignore();
        archivo >> precio;
        archivo.ignore();
        archivo >> tipoPago;
        archivo.ignore();
        archivo >> subtotal;
        archivo.ignore();
        archivo >> descuento;
        archivo.ignore();
        archivo >> total;
        archivo.ignore();

        cout << "\nCliente: " << cliente << endl;
        cout << "Producto: " << producto << endl;
        cout << "Cantidad: " << cantidad << endl;
        cout << "Precio: Q" << precio << endl;
        cout << "Subtotal: Q" << subtotal << endl;
        cout << "Descuento: Q" << descuento << endl;
        cout << "Total: Q" << total << endl;
    }

    archivo.close();
}

// Reporte
void generarReporte() {
    ifstream archivo("ventas.txt");

    string cliente, producto;
    int cantidad, tipoPago;
    double precio, subtotal, descuento, total;

    int contador = 0, efectivo = 0, tarjeta = 0, transferencia = 0, conDescuento = 0;
    double suma = 0, promedio = 0;

    while (getline(archivo, cliente, ',')) {
        getline(archivo, producto, ',');
        archivo >> cantidad;
        archivo.ignore();
        archivo >> precio;
        archivo.ignore();
        archivo >> tipoPago;
        archivo.ignore();
        archivo >> subtotal;
        archivo.ignore();
        archivo >> descuento;
        archivo.ignore();
        archivo >> total;
        archivo.ignore();

        contador++;
        suma += total;

        if (tipoPago == 1) efectivo++;
        if (tipoPago == 2) tarjeta++;
        if (tipoPago == 3) transferencia++;
        if (descuento > 0) conDescuento++;
    }

    archivo.close();

    if (contador > 0) {
        promedio = suma / contador;
    }

    cout << "\n===== REPORTE GENERAL =====" << endl;
    cout << "Total de ventas: " << contador << endl;
    cout << "Suma total vendida: Q" << suma << endl;
    cout << "Promedio de venta: Q" << promedio << endl;
    cout << "Ventas en efectivo: " << efectivo << endl;
    cout << "Ventas en tarjeta: " << tarjeta << endl;
    cout << "Ventas en transferencia: " << transferencia << endl;
    cout << "Ventas con descuento: " << conDescuento << endl;
}

// Buscar ventas
void buscarPorMonto() {
    ifstream archivo("ventas.txt");

    string cliente, producto;
    int cantidad, tipoPago;
    double precio, subtotal, descuento, total, monto;

    cout << "\nIngrese el monto minimo a buscar: ";
    cin >> monto;

    cout << "\n===== RESULTADOS =====" << endl;

    while (getline(archivo, cliente, ',')) {
        getline(archivo, producto, ',');
        archivo >> cantidad;
        archivo.ignore();
        archivo >> precio;
        archivo.ignore();
        archivo >> tipoPago;
        archivo.ignore();
        archivo >> subtotal;
        archivo.ignore();
        archivo >> descuento;
        archivo.ignore();
        archivo >> total;
        archivo.ignore();

        if (total >= monto) {
            cout << "\nCliente: " << cliente << endl;
            cout << "Producto: " << producto << endl;
            cout << "Total: Q" << total << endl;
        }
    }

    archivo.close();
}
