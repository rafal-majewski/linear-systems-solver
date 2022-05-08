#include "./LinearSystemPrinter.hpp"


template <typename T>
void LinearSystemPrinter<T>::printSize(const LinearSystem<T>& linearSystem) const {
	std::cout << linearSystem.coefficients.size.rowsCount << '\t' << linearSystem.coefficients.size.columnsCount << '\n';
}

template <typename T>
void LinearSystemPrinter<T>::printVariables(const LinearSystem<T>& linearSystem) const {
	std::cout << linearSystem.variables[0];
	for (int i = 1; i < linearSystem.variables.size(); ++i) {
		std::cout << '\t' << linearSystem.variables[i];
	}
	std::cout << '\n';
}

template <typename T>
void LinearSystemPrinter<T>::printCoefficientsAndConstants(const LinearSystem<T>& linearSystem) const {
	for (int y = 0; y < linearSystem.coefficients.size.rowsCount; ++y) {
		std::cout << linearSystem.coefficients.get(y, 0);
		for (int x = 1; x < linearSystem.coefficients.size.columnsCount; ++x) {
			std::cout << '\t' << linearSystem.coefficients.get(y, x);
		}
		std::cout << '\t' << linearSystem.constants[y] << '\n';
	}
}

template <typename T>
void LinearSystemPrinter<T>::print(const LinearSystem<T>& linearSystem) const {
	printSize(linearSystem);
	printVariables(linearSystem);
	printCoefficientsAndConstants(linearSystem);
}

template <typename T>
LinearSystemPrinter<T>::LinearSystemPrinter() {
}