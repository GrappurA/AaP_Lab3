#include <iostream>
#include <cmath> 
#include <iomanip>
#include <G:\Apps\GIT\colors\color-console\include\color.hpp>

using namespace std;

#define EPSILON 1e-15 // making a 0 output to look so

//task1
double f(double x) {
	return atan(x) + atan((1 - x) / (1 + x));  // No need for x = ...
}
double trapezoidalRule(double a, double b, int n) {
	double h = (b - a) / n; // Calculate step size
	double integral = (f(a) + f(b)) / 2.0; // Start with the first and last term

	for (int i = 1; i < n; ++i) { // Iterate over the subintervals
		integral += f(a + i * h); // Sum the function values at the subintervals
	}

	integral *= h; // Multiply by the width of the subintervals
	return integral;
}
double simpsonsRule(double a, double b, int n) {
	if (n % 2 != 0) {
		n++; // n must be even for Simpson's rule
	}
	double h = (b - a) / n; // Calculate step size
	double integral = f(a) + f(b); // Start with the first and last term

	int i = 1; // Initialize the counter
	while (i < n) { // Use a while loop to iterate
		integral += (i % 2 == 0 ? 2 * f(a + i * h) : 4 * f(a + i * h)); // Weighting terms
		i++; // Increment the counter
	}

	integral *= h / 3.0; // Final multiplication
	return integral;
}
double rightRiemannSum(double a, double b, int n) {
	double h = (b - a) / n; // Calculate step size
	double sum = 0.0; // Initialize the sum
	int i = 1; // Initialize the counter

	do {
		sum += f(a + i * h); // Calculate the height using the right endpoint
		i++; // Increment the counter
	} while (i <= n); // Continue until the end of the intervals

	return h * sum; // Multiply by the width of the subintervals
}
double* Task1(int NUMBER_OF_PLACES_TO_STUDY_FUNCTION)
{
	double x;
	double y;
	int size = NUMBER_OF_PLACES_TO_STUDY_FUNCTION + 3;
	double* arr = new double[size];
	//integration
	double a = -1.0; // Lower limit
	double b = 1.0; // Upper limit
	int n = 1000; // accuracy

	int counter = 0;

	cout << left << setw(10) << dye::blue("x") << setw(20) << dye::red("f(x)") << endl;
	cout << "----------------------\n";
	for (x = -1.0; x < 1.0; x += 0.1) {
		y = f(x);
		arr[counter] = y;
		if (abs(x) < EPSILON)
		{
			cout << setw(10) << "0" << setw(20) << y << endl;
		}
		else
		{
			cout << setw(10) << x << setw(20) << y << endl;
		}
		counter++;
		if (counter == NUMBER_OF_PLACES_TO_STUDY_FUNCTION)
		{
			break;
		}

	}
	cout << "\n";
	arr[size - 3] = trapezoidalRule(a, b, n);
	arr[size - 2] = simpsonsRule(a, b, n);
	arr[size - 1] = rightRiemannSum(a, b, n);

	return arr;
}
//task1

//task2
double f_Task2(double x)
{
	return exp(cos(x)) * cos(sin(x));
}
double taylorSeries(double x, double epsilon, int& terms) {
	double sum = 0.0;    // Наближене значення
	double term = 1.0;   // Перший член ряду
	int k = 0;           // Лічильник кроків
	terms = 0;           // Лічильник кількості кроків

	while (fabs(term) >= epsilon) {
		sum += term;     // Додаємо член до суми
		terms++;
		k++;
		term = cos(k * x) / tgamma(k + 1);  // Наступний член ряду Тейлора
	}

	return sum;
}
double* Task2(double x, double epsilon)
{
	if (fabs(x) >= 1 || epsilon <= 0 || epsilon >= 1) {
		cout << "Wrong data" << endl;
		return 0;
	}

	double exact = f_Task2(x);
	int terms = 0;
	double approx = taylorSeries(x, epsilon, terms);
	double error = fabs(approx - exact);

	double* arr = new double[3];
	arr[0] = exact;
	arr[1] = approx;
	arr[2] = error;
	return arr;

}
//
int main()
{
	int userInput = 1;

	cout << "Enter 1 for Task 1 || 2 for Task 2: ";
	cin >> userInput;

	int NUMBER_OF_PLACES_TO_STUDY_FUNCTION;
	string s[3] = { "Trapezoidal","Simpson's ","Right-Triangle" };

	double x;
	double epsilon;

	switch (userInput)
	{
	case 1:
	{
		cout << "Enter NUMBER_OF_PLACES_TO_STUDY_FUNCTION" << endl;
		cin >> NUMBER_OF_PLACES_TO_STUDY_FUNCTION;
		cout << "\n";
		double* task1_array = Task1(NUMBER_OF_PLACES_TO_STUDY_FUNCTION);

		cout << dye::green("\nIntegration:\n");
		cout << left << setw(30) << "Trapezoidal Rule: " << task1_array[NUMBER_OF_PLACES_TO_STUDY_FUNCTION] << endl;
		cout << left << setw(30) << "Simpson's Rule: " << task1_array[NUMBER_OF_PLACES_TO_STUDY_FUNCTION + 1] << endl;
		cout << left << setw(30) << "Right Riemann Sum: " << task1_array[NUMBER_OF_PLACES_TO_STUDY_FUNCTION + 2] << "\n\n";

		delete[] task1_array;
		break;
	}
	case 2:
	{
		cout << "enter x: ";
		cin >> x;
		cout << "Enter epsilon: ";
		cin >> epsilon;
		double* task2_array = Task2(x, epsilon);
		cout << "\n";
		cout << left << setw(20) << dye::green("Exact Value") << task2_array[0] << "\n";
		cout << left << setw(20) << dye::green("Approximate Value") << task2_array[1] << "\n";
		cout << left << setw(20) << dye::green("Error") << task2_array[2] << "\n";

		delete[] task2_array;
		break;
	}
	default:

		cout << "wrong data\n";
		break;
	}

	system("pause");
	cout << "\n";
	return 0;
}