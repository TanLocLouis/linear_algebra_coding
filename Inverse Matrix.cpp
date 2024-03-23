#include <iostream>
#include <iomanip>

using namespace std;

void inputMatrix(int** &a, int& n) {
	cout << "Input size of matrix: ";
	cin >> n;

	a = new int* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "Input a[" << i << "," << j << "]: ";
			cin >> a[i][j];
		}
	}
}

void outputMatrix(int** a, const int& n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << char(32);
		}
		cout << endl;
	}
	cout << endl;
}

void outputInverseMatrix(double** a, const int& n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2 * n; j++) {
			cout << setw(10) << a[i][j];
		}
		cout << endl;
	}
}

void inverseMatrix(int** a, const int& n) {
	// make (A|I) matrix
	double** matrix;
	matrix = new double* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[2 * n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = a[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				matrix[i][n + j] = 1;
			}
			else {
				matrix[i][n + j] = 0;
			}
		}
	}
	// Apply Gauss-Jordan
	for (int i = 0; i < n; i++) {
		int pivot = matrix[i][i];
		if (pivot == 0) {
			cout << "Not exist inverse matrix" << endl;
			return;
		}

		for (int k = i; k < 2 * n; k++) matrix[i][k] /= pivot;
		for (int j = 0; j < n; j++) {
			if (j == i) continue;
			double ratio = 1.0 * matrix[j][i];
			for (int k = i; k < 2 * n; k++) matrix[j][k] -= ratio * matrix[i][k];
		}

		cout << "Each step: " << endl;
		outputInverseMatrix(matrix, n);
		cout << endl;
	}
}

int detMatrix(int** a, const int& n) {
	// base case
	if (n == 1) return a[0][0];
	// calculate base on first row
	int res = 0;
	for (int i = 0; i < n; i++) {
		// Allocate sub matrix
		int** subMat = new int* [n - 1];
		for (int j = 0; j < n - 1; j++) subMat[j] = new int[n - 1];
		// Fill in sub matrix
		int idx = 0;
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				if (x == 0 || y == i) continue;
				subMat[idx / (n - 1)][idx % (n - 1)] = a[x][y];
				idx++;
			}
		}
		// Calculate each
		res += pow(-1, 0 + i) * a[0][i] * detMatrix(subMat, n - 1);
	}

	return res;
}

int main() {
	int** a;
	int n;
	// Input matrix
	inputMatrix(a, n);
	// Inverse matrix
	cout << "Inverse matrix: " << endl;
	inverseMatrix(a, n);
	// Determinant
	cout << detMatrix(a, n) << endl;

	return 0;
}