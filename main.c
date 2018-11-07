//
//  main.c
//  matrix
//
//  Created by TCHASSE ODJAC on 07.11.18.
//  Copyright © 2018 TCHASSE ODJAC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

/** PROTOTYPES **/
void read3x3Matrix(float[][SIZE]);
void print3x3Matrix(float[][SIZE]);
void print2x2Mat(float[][2]);
void printArray(float[9]);
void transposeSquareMatrix(float const[][SIZE], float[][SIZE]);
float select2x2Mat(float[][3], float[][2], unsigned, unsigned);
float det2x2Mat(float[][2]);
float det3x3Mat(float[3], float[][SIZE]);
void arrayToMatrix(float[9], float[][SIZE]);
void scalarMult(float, float[][SIZE], float[][SIZE]);


/** MAIN **/
int main()
{
    printf("*****  INVERSE OF 3x3 MATRIX  *****");
    printf("\n\n");
    
    // Variables
    float matrixInput[SIZE][SIZE] = {};
    float matrix2x2[2][2] = {};
    float matrixCofactor[SIZE][SIZE] = {};
    float matrixCofactorTranspose[SIZE][SIZE] = {};
    float matrixInverse[SIZE][SIZE] = {};
    
    float detArray[3] = {};
    float cofactorArray[9] = {};
    float determinant = 0;
    
    // Input and Output of Original Matrix
    read3x3Matrix(matrixInput);
    printf("\n");
    printf("Your Matrix: \n");
    print3x3Matrix(matrixInput);
    printf("\n");
    
    // Finding the determinants of the 2x2 Matrices selected from the original 3x3 matrix
    printf("Sub-Matrices with Determinants:\n");
    unsigned k = 0;     // iterator for the array
    float sign = 1.0;   // used to flip the sign on every other cofactor
    for(unsigned i = 0; i < SIZE; i++){
        for(unsigned j = 0; j < SIZE; j++){
            cofactorArray[k] = select2x2Mat(matrixInput, matrix2x2, i, j) * sign;
            k++;
            sign *= (-1.0);
        }
    }
    
    // Storing only the values of the first column of the given matrix
    // to calculate the determinant of the 3x3 matrix
    detArray[0] = select2x2Mat(matrixInput, matrix2x2, 0, 0);
    detArray[1] = select2x2Mat(matrixInput, matrix2x2, 1, 0);
    detArray[2] = select2x2Mat(matrixInput, matrix2x2, 2, 0);
    
    // Printing an array of cofactors
    printf("Array of Cofactors: \n");
    printArray(cofactorArray);
    printf("\n\n");
    
    // Printing the found determinant of the 3x3 matrix
    determinant = det3x3Mat(detArray, matrixInput);
    printf("Determinant = %f \n\n", determinant);
    
    // Turning the cofactor array into a cofactor matrix
    printf("Cofactor Matrix:\n");
    arrayToMatrix(cofactorArray, matrixCofactor);
    print3x3Matrix(matrixCofactor);
    printf("\n");
    
    // Transposing the cofactor matrix
    printf("Adjoint of the Matrix:\n");
    transposeSquareMatrix(matrixCofactor, matrixCofactorTranspose);
    print3x3Matrix(matrixCofactorTranspose);
    printf("\n");
    
    // Finding the Inverse by scalar multiplication
    // of 1/determinant with the transposed cofactor matrix
    printf("Inverse Matrix:\n");
    determinant = 1.0/determinant;
    scalarMult(determinant, matrixCofactorTranspose, matrixInverse);
    print3x3Matrix(matrixInverse);
    printf("\n");
    printf("\n");
    
    return 0;
}

/** FUNCTIONS **/
// READ A 3x3 MATRIX
void read3x3Matrix(float mat[][SIZE]){
    for(unsigned int i = 0; i < SIZE; i++){
        for(unsigned int j = 0; j < SIZE; j++){
            printf("[%u, %u] ", i, j);
            scanf("%f", &mat[i][j]);
        }
    }
}

// PRINT A 3x3 MATRIX
void print3x3Matrix(float mat[][SIZE]){
    for(unsigned int i = 0; i < SIZE; i++){
        for(unsigned int j = 0; j < SIZE; j++){
            printf("%8.2f", mat[i][j]);
        }
        printf("\n");
    }
}

// PRINT A 2x2 Matrix
void print2x2Matrix(float mat[][2]){
    for(unsigned i = 0; i < 2; i++){
        for(unsigned j = 0; j < 2; j++){
            printf("%8.2f", mat[i][j]);
        }
        printf("\n");
    }
}

// PRINT AN ARRAY
void printArray(float a[9]){
    printf("|");
    for(unsigned int i = 0; i < 9; i++){
        printf("%.2f | ", a[i]);
    }
}

// TRANSPOSE OF MATRIX
void transposeSquareMatrix(float const mat[][SIZE], float matT[][SIZE]){
    for(unsigned int i = 0; i < SIZE; i++){
        for(unsigned int j = 0; j < SIZE; j++){
            matT[i][j] = mat[j][i];
        }
    }
}

// SELECTING 2x2 FROM 3x3 MATRIX
float select2x2Mat(float mat3[][3], float mat2[][2], unsigned row, unsigned column){
    float det = 0;
    unsigned n = 0;
    unsigned m = 0;
    unsigned assignCount = 0; // used to skip to next row in 2x2 matrix
    
    for(unsigned i = 0; i < SIZE; i++){
        for(unsigned j = 0; j < SIZE; j++){
            if(row == i || column == j){
                // do nothing;
            }
            else{
                mat2[n][m] = mat3[i][j];
                // to switch column of 2x2 matrix
                if(m == 0){
                    m = 1;
                }
                else{
                    m = 0;
                }
                // to switch row of 2x2 matrix
                assignCount++;
                if(assignCount == 2){
                    n = 1;
                }
            }
        }
    }
    print2x2Matrix(mat2);
    det = det2x2Mat(mat2);
    return det;
}

// DETERMINANT OF 2x2 MATRIX
float det2x2Mat(float mat2[][2]){
    float det = 0;
    float a = mat2[0][0];
    float b = mat2[1][1];
    float c = mat2[0][1];
    float d = mat2[1][0];
    det = (a * b) - (c * d);
    printf("Determinant = %f \n\n", det);
    return det;
}

// DETERMINANT OF 3x3 MATRIX
float det3x3Mat(float detA[3], float mat3[][SIZE]){
    float det = 0;
    det = (mat3[0][0] * detA[0]) - (mat3[1][0] * detA[1]) + (mat3[2][0] * detA[2]);
    return det;
}

// CONVERT ARRAY TO MATRIX
void arrayToMatrix(float a[9], float mat3[][SIZE]){
    unsigned k = 0;
    for(unsigned i = 0; i < SIZE; i++){
        for(unsigned j = 0; j < SIZE; j++){
            mat3[i][j] = a[k];
            k++;
        }
    }
}

//SCALAR MULTIPLICATION
void scalarMult(float det, float mat3[][SIZE], float matRes[][SIZE]){
    for(unsigned i = 0; i < SIZE; i++){
        for(unsigned j = 0; j < SIZE; j++){
            matRes[i][j] = det * mat3[i][j];
        }
    }
}


