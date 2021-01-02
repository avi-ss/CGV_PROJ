#pragma once
#include <iostream>

#define PI 3.14159

class cgvMatrix2D
{
	int matrix[2][3];

public:
	cgvMatrix2D() {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (i == j) matrix[i][j] = 1;
				else matrix[i][j] = 0;
			}
		}
	}

	void rotate(float a) {

		float angle = a * (PI / 180);

		int rotMatrix[2][2] = { {round(cos(angle)), round(sin(angle))},{round(-sin(angle)), round(cos(angle))} };

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				matrix[i][j] = rotMatrix[i][j];
			}
		}
	}

	void translate(int x, int y) {
		matrix[0][2] = matrix[0][0] * x + matrix[1][0] * y;
		matrix[1][2] = matrix[0][1] * x + matrix[1][1] * y;
	}

	int getX() { return matrix[0][2]; }
	int getY() { return matrix[1][2]; }
};

