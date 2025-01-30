/*
Librerias necesarias para el programa
*/
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <algorithm>

class Termino
{
private:
	double coeficiente;
	int exponente;

public:
	double getcoeficiente();
	int getexponente();
	void setcoeficiente(double coeficiente_);
	void setexponente(int exponente_);
};
double Termino::getcoeficiente()
{
	return coeficiente;
}
int Termino::getexponente()
{
	return exponente;
}
void Termino::setexponente(int exponente_)
{
	exponente = exponente_;
}
void Termino::setcoeficiente(double coeficiente_)
{
	coeficiente = coeficiente_;
}

/*
Funcion que calcula el resultado de un polinomio en x
*/
double resolverPolinomio(std::list<Termino> polinomio) {
	std::cout << std::endl;
	double x;
	std::cout << "Introduzca el valor de x para resolver el polinomio final: ";
	std::cin >> x;
	double resultado = 0;
	//Iteracion por los terminos del polinomio
	for (Termino termino : polinomio) {
		//Calculo del resultado de la resolucion del polinomio a x
		resultado += termino.getcoeficiente() * pow(x, termino.getexponente());
	}
	std::cout << "El resultado de evaluar el polinomio en x=" << x << " es de: " << resultado << "" << std::endl;
	return resultado;
}
/*
Imprimir polinomio y sus terminos
*/
void imprimirPolinomio(std::list<Termino> polinomio) {
	std::cout << std::endl;
	if (polinomio.size() > 0) {
		std::cout << "f(x) = ";
		//Imprimir cada uno de los terminos que compone al polinomio
		for (Termino termino : polinomio) {
			if (termino.getexponente() == 0) {
				std::cout << " " << termino.getcoeficiente() << "x^" << termino.getexponente() << " ";
			}
			else if (termino.getexponente() == polinomio.size()) {
				std::cout << "+ " << termino.getcoeficiente() << "x^" << termino.getexponente() << std::endl;
			}
			else {
				std::cout << "+ " << termino.getcoeficiente() << "x^" << termino.getexponente() << " ";
			}
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "f(x) sin terminos o vacia" << std::endl;
	}
}
/*
Funcion que define un polinomio en baso al grado deseado
*/
std::list<Termino> GetPolinomio() {
	int grado;
	//Definir el grado del polinomio a guardar
	std::cout << "Ingrese el grado del polinomio: ";
	std::cin >> grado;
	//Esta funcion retorna un polinomio
	std::list<Termino> tmp;
	//Definir el coeficiente de cada uno de los terminos que componen al polinomio
	for (int i = 0; i <= grado; i++) {
		std::cout << "Introduzca el coeficiente del grado [" << i << "]: ";
		double coeficiente_;
		std::cin >> coeficiente_;
		Termino Termino;
		Termino.setcoeficiente(coeficiente_);
		Termino.setexponente(i);
		tmp.push_back(Termino);
	}
	return tmp;
}
/*
Funcion que calcula la suma de dos polinomios
*/
std::list<Termino> SumarPolinomios(std::list<Termino> polinomio_1, std::list<Termino> polinomio_2) {
	//Funcion retorna el polinomio resultante de la suma de polinomios
	std::list<Termino> tmp;
	//Definir el polinomio de mayor grado ayuda a organizar la iteracion
	std::list<Termino> polinomio_mayor;
	std::list<Termino> polinomio_menor;
	if (polinomio_1.size() >= polinomio_2.size()) {
		polinomio_mayor = polinomio_1;
		polinomio_menor = polinomio_2;
	}
	else if (polinomio_1.size() < polinomio_2.size()) {
		polinomio_mayor = polinomio_2;
		polinomio_menor = polinomio_1;
	}
	for (Termino termino : polinomio_mayor) {
		for (Termino termino_ : polinomio_menor) {
			if (termino.getexponente() == termino_.getexponente()) {
				double coeficiente = termino.getcoeficiente() + termino_.getcoeficiente();
				Termino Termino;
				Termino.setcoeficiente(coeficiente);
				Termino.setexponente(termino.getexponente());
				tmp.push_back(Termino);
			}
		}
		//En caso de que no haya un termino del mismo grado
		if (termino.getexponente() >= polinomio_menor.size()) {
			tmp.push_back(termino);
		}
	}
	return tmp;
}
/*
Funcion que calcula la resta de dos polinomios
*/
std::list<Termino> RestarPolinomios(std::list<Termino> polinomio_1, std::list<Termino> polinomio_2) {
	//Lista donde se guardan terminos replicados o de coeficiente 0
	std::list<Termino> tmp;
	//Lista final que devuelve la funcion
	std::list<Termino> filtered_tmp;
	for (Termino termino : polinomio_1)
	{
		for (Termino termino_ : polinomio_2)
		{
			if (termino.getexponente() == termino_.getexponente()) {
				double coeficiente = termino.getcoeficiente() - termino_.getcoeficiente();
				Termino Termino;
				Termino.setcoeficiente(coeficiente);
				Termino.setexponente(termino.getexponente());
				tmp.push_back(Termino);
			}
			//En caso de que el polinomio 2 sea de mayor grado
			if (termino_.getexponente() >= polinomio_1.size()) {
				double coeficiente_ = termino_.getcoeficiente() * -1;
				Termino Termino;
				Termino.setcoeficiente(coeficiente_);
				Termino.setexponente(termino_.getexponente());
				tmp.push_back(Termino);
			}
		}
		//En caso de que el polinomio 1 sea de mayor grado
		if (termino.getexponente() >= polinomio_2.size()) {
			tmp.push_back(termino);
		}
	}
	//Iteracion para devolver solo un termino de cada grado
	for (int i = 0; i < tmp.size(); i++) {
		for (Termino item_ : tmp) {
			if (i == item_.getexponente()) {
				if (item_.getcoeficiente() != 0) {
					filtered_tmp.push_back(item_);
					break;
				}
			}
		}
	}
	return filtered_tmp;
}
/*
Funcion que calcula la multiplicacion de dos polinomios
*/
std::list<Termino> MultiplicarPolinomios(std::list<Termino> polinomio_1, std::list<Termino> polinomio_2) {
	//Lista con multiplicacion en bruto
	std::list<Termino> tmp;
	//Lista con coeficientes sumados de cada termino del mismo grado
	std::list<Termino> filtered_tmp;
	//Multiplicacion de termino por termino entre polinomios
	for (Termino termino : polinomio_1) {
		for (Termino termino_ : polinomio_2) {
			double coeficiente = termino.getcoeficiente() * termino_.getcoeficiente();
			int exponente = termino.getexponente() + termino_.getexponente();
			Termino Termino;
			Termino.setcoeficiente(coeficiente);
			Termino.setexponente(exponente);
			tmp.push_back(Termino);
		}
	}
	//Iteracion que sirve como filtro
	for (int i = 0; i < tmp.size(); i++) {
		double coeficiente = 0;
		for (Termino item_ : tmp) {
			if (i == item_.getexponente()) {
				coeficiente += item_.getcoeficiente();
			}
		}
		//Se excluyen los terminos de coeficiente 0
		if (coeficiente > 0) {
			Termino termino;
			termino.setcoeficiente(coeficiente);
			termino.setexponente(i);
			filtered_tmp.push_back(termino);
		}
	}
	return filtered_tmp;
}
/*
Funcion que guarda los polinomios en un archivo
*/
void guardarPolinomios(std::list<Termino> polinomio, std::string Archivo) {
	std::ofstream archivo(Archivo);

	if (!archivo.is_open()) {
		std::cerr << "No se pudo abrir el archivo para guardar." << std::endl;
		return;
	}

	for (Termino termino : polinomio) {
		archivo << termino.getcoeficiente() << " " << termino.getexponente() << " ";
	}

	archivo.close();
	std::cout << "Polinomio guardado en " << Archivo << std::endl;
}
/*
Funcion que carga los polinomios en un archivo
*/
std::list<Termino> cargarPolinomio(std::string Archivo) {
	std::ifstream archivo(Archivo);
	std::list<Termino> polinomio;
	if (!archivo.is_open()) {
		std::cerr << "No se pudo abrir el archivo para cargar." << std::endl;
		return polinomio;
	}
	std::string linea;
	while (getline(archivo, linea)) {
		std::istringstream linestream(linea);
		Termino termino;
		double coeficiente;
		int exponente;

		while (linestream >> coeficiente >> exponente) {
			termino.setcoeficiente(coeficiente);
			termino.setexponente(exponente);
			polinomio.push_back(termino);
		}
	}
	std::cout << "Polinomio cargado:";
	archivo.close();
	return polinomio;
}
/*
Funcion principal
*/
int main() {
	//Lista de terminos: Polinomio
	std::list<Termino> polinomio_2;
	std::list<Termino> polinomio_1;
	try {
		polinomio_1 = cargarPolinomio("polinomio_1.txt");
		imprimirPolinomio(polinomio_1);
	}
	catch (...) {
		std::cout << "ERROR: NO se pudo cargar el polinomio";
	}
	try {
		polinomio_2 = cargarPolinomio("polinomio_2.txt");
		imprimirPolinomio(polinomio_2);
	}
	catch (...) {
		std::cout << "ERROR: NO se pudo cargar el polinomio";
	}
	//En caso de no haber guardado polinomios, cargarlos con el usuario
	if (polinomio_1.size() <= 0) {
		std::cout << "Definiendo primer polinomio: " << std::endl;
		polinomio_1 = GetPolinomio();
		imprimirPolinomio(polinomio_1);
		guardarPolinomios(polinomio_1, "polinomio_1.txt");
	}
	else {
		std::cout << "Informacion del primer polinomio leida del archivo" << std::endl;
	}
	if (polinomio_2.size() <= 0) {
		std::cout << "Definiendo segundo polinomio: " << std::endl;
		polinomio_2 = GetPolinomio();
		imprimirPolinomio(polinomio_2);
		guardarPolinomios(polinomio_1, "polinomio_2.txt");
	}
	else {
		std::cout << "Informacion del segundo polinomio leida del archivo" << std::endl;
	}
	int accion;
	do {
		//Menu de opciones
		std::cout << "--------------- MENU --------------------" << std::endl;
		std::cout << "1. Modificar primer polinomio" << std::endl;
		std::cout << "2. Modificar segundo polinomio" << std::endl;
		std::cout << "3. Sumar polinomios y calcular resultado" << std::endl;
		std::cout << "4. Restar primer polinomio menos el segundo polinomio y calcular resultado" << std::endl;
		std::cout << "5. Restar segundo polinomio menos el primer polinomio y calcular resultado" << std::endl;
		std::cout << "6. Multiplicar polinomios y calcular resultado total" << std::endl;
		std::cout << "7. Salir" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Numero de opcion que desea realizar: ";
		std::cin >> accion;

		switch (accion) {
			//Modificar primer polinomio
		case 1: {
			polinomio_1 = GetPolinomio();
			imprimirPolinomio(polinomio_1);
			guardarPolinomios(polinomio_1, "polinomio_1.txt");
			std::cout << "Primer polinomio modificado" << std::endl;
			break;
		}
			  //Modificar segundo polinomio
		case 2: {
			polinomio_2 = GetPolinomio();
			imprimirPolinomio(polinomio_2);
			guardarPolinomios(polinomio_2, "polinomio_2.txt");
			std::cout << "Segundo polinomio modificado" << std::endl;
			break;
		}
			  //Sumar polinomios
		case 3: {
			std::cout << "Sumando primer y segundo polinomio: " << std::endl;
			std::list<Termino> polinomio_resultante = SumarPolinomios(polinomio_1, polinomio_2);
			std::cout << "Resultado de suma de polinomios: " << std::endl;
			imprimirPolinomio(polinomio_resultante);
			resolverPolinomio(polinomio_resultante);
			std::cout << std::endl;
			break;
		}
			  //Restar el primer polinomio menos el segundo
		case 4: {
			std::cout << "Restando el primer polinomio menos el segundo polinomio: " << std::endl;
			std::list<Termino> polinomio_resultante = RestarPolinomios(polinomio_1, polinomio_2);
			std::cout << "Resultado de la resta de polinomios: " << std::endl;
			imprimirPolinomio(polinomio_resultante);
			resolverPolinomio(polinomio_resultante);
			std::cout << std::endl;
			break;
		}
			  //Restar segundo polinomio menos el primero
		case 5: {
			std::cout << "Restando el segundo polinomio menos el primer polinomio: " << std::endl;
			std::list<Termino> polinomio_resultante = RestarPolinomios(polinomio_2, polinomio_1);
			std::cout << "Resultado de la resta de polinomios: " << std::endl;
			imprimirPolinomio(polinomio_resultante);
			resolverPolinomio(polinomio_resultante);
			std::cout << std::endl;
			break;
		}
			  //Multiplicar polinomios
		case 6: {
			std::cout << "Multiplicando primer y segundo polinomio: " << std::endl;
			std::list<Termino> polinomio_resultante = MultiplicarPolinomios(polinomio_1, polinomio_2);
			std::cout << "Resultado de multiplicacion de polinomios: " << std::endl;
			imprimirPolinomio(polinomio_resultante);
			resolverPolinomio(polinomio_resultante);
			std::cout << std::endl;
			break;
		}
			  //Cerrar programa
		case 7: {
			std::cout << "Este programa ha sido finalizado.";
			break;
		}
			  //Opcion ingresada no valida
		default: {
			std::cout << "Por favor, ingrese un numero que se encuentre en el rango de opciones." << std::endl;
		}
		}

	} while (accion != 7);
}