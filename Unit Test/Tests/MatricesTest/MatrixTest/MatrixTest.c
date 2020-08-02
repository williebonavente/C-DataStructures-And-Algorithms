#include "MatrixTest.h"

#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../DataStructure/Matrices/Headers/Matrix.h"



/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerMT(int integer) {
    int *newInt = (int *) malloc(sizeof(int));

    *newInt = integer;
    return newInt;

}




/** This function will compare to integers pointers,
 * then it will return zero if they are equal, negative number if the second integer is bigger,
 * and positive number if the first integer is bigger.
 * @param a the first integer pointer
 * @param b the second integer pointer
 * @return it will return zero if they are equal, negative number if the second integer is bigger, and positive number if the first integer is bigger.
 */

int compareIntPointersMT(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}





/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerMT(char *ch) {

    char *newCh = (char *) malloc( sizeof(char) * (strlen(ch) + 1) );

    strcpy(newCh, ch);

    return newCh;

}





void testInvalidMatrixInitialization(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(0, 0, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);
    DUMMY_TEST_DATASTRUCTURE->errorCode = 0;

    matrix = matrixInitialization(1, 1, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);
    DUMMY_TEST_DATASTRUCTURE->errorCode = 0;

    matrix = matrixInitialization(0, 0, free, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

}


void testValidMatrixInitialization(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(1, 1, free, compareIntPointersMT);
    CuAssertPtrNotNull(cuTest, matrix);

    destroyMatrix(matrix);

}



void testMatrixInsert(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {1, 0, 11}, {1, 1, 12}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);
    matrixInsert(matrix, generateIntPointerMT(12), 1, 1);

    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }

    destroyMatrix(matrix);

}



void testMatrixRemove(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {1, 0, 11}, {1, 1, 12}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(13), 0, 1);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);
    matrixInsert(matrix, generateIntPointerMT(12), 1, 1);

    matrixRemove(matrix, 0, 1);

    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }

    destroyMatrix(matrix);

}




void testMatrixRemoveWtoFr(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {1, 0, 11}, {1, 1, 12}};

    int *tempItem = generateIntPointerMT(13);
    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, tempItem,  0, 1);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);
    matrixInsert(matrix, generateIntPointerMT(12), 1, 1);

    matrixRemoveWtoFr(matrix, 0, 1);
    CuAssertIntEquals(cuTest, 13, *tempItem);

    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }


    free(tempItem);
    destroyMatrix(matrix);

}







void testMatrixGet(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {1, 0, 11}, {1, 1, 12}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);
    matrixInsert(matrix, generateIntPointerMT(12), 1, 1);

    for (int i = 0; i < 3; i++)
        CuAssertIntEquals(cuTest, indicesArr[i][2], *(int *) matrixGet(matrix, indicesArr[i][0], indicesArr[i][1]));

    destroyMatrix(matrix);

}





void testMatrixContains(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {1, 0, 11}, {1, 1, 12}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);
    matrixInsert(matrix, generateIntPointerMT(12), 1, 1);

    for (int i = 0; i < 3; i++)
        CuAssertIntEquals(cuTest, 1,  matrixContains(matrix, &indicesArr[i][2]));

    int tempValue = 13;
    CuAssertIntEquals(cuTest, 0,  matrixContains(matrix, &tempValue));

    destroyMatrix(matrix);

}



void testMatrixGetIndex(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {1, 0, 11}, {1, 1, 12}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);
    matrixInsert(matrix, generateIntPointerMT(12), 1, 1);

    for (int i = 0; i < 3; i++) {
        MatrixIndex *index = matrixGetIndex(matrix, &indicesArr[i][2]);
        CuAssertIntEquals(cuTest, indicesArr[i][0], index->row);
        CuAssertIntEquals(cuTest, indicesArr[i][1], index->col);

        free(index);

    }

    int tempValue = 13;
    CuAssertPtrEquals(cuTest, NULL,  matrixGetIndex(matrix, &tempValue));

    destroyMatrix(matrix);

}





void testMatrixAddRow(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {1, 0, 11}, {2, 0, 12}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);

    matrixAddRow(matrix);
    for (int i = 0; i < matrix->colNum; i++)
        CuAssertPtrEquals(cuTest, NULL, matrix->rows[matrix->rowsNum - 1][i]);


    matrixInsert(matrix, generateIntPointerMT(12), 2, 0);

    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }

    destroyMatrix(matrix);

}



void testMatrixAddRowAtIndex(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0, 0, 10}, {2, 0, 11}, {2, 1, 12}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);

    matrixAddRowAtIndex(matrix, 1);
    for (int i = 0; i < matrix->colNum; i++)
        CuAssertPtrEquals(cuTest, NULL, matrix->rows[1][i]);


    matrixInsert(matrix, generateIntPointerMT(12), 2, 1);


    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }

    destroyMatrix(matrix);

}






void testMatrixAddColumn(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {1, 0, 11}, {1, 2, 12}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);

    matrixAddCol(matrix);
    for (int i = 0; i < matrix->rowsNum; i++)
        CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][matrix->colNum - 1]);


        matrixInsert(matrix, generateIntPointerMT(12), 1, 2);

    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }

    destroyMatrix(matrix);

}





void testMatrixAddColumnAtIndex(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,1, 10}, {1, 1, 11}, {1, 2, 12}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);

    matrixAddColAtIndex(matrix, 0);
    for (int i = 0; i < matrix->rowsNum; i++)
        CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][0]);


    matrixInsert(matrix, generateIntPointerMT(12), 1, 2);

    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }

    destroyMatrix(matrix);

}






void testMatrixRemoveRow(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {0, 1, 11}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 0, 1);
    matrixInsert(matrix, generateIntPointerMT(12), 1, 0);
    matrixInsert(matrix, generateIntPointerMT(13), 1, 1);

    matrixRemoveRow(matrix, 1);

    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }

    destroyMatrix(matrix);

}





void testMatrixRemoveRowWoFr(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {0, 1, 11}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 0, 1);

    int *tempItem1 = generateIntPointerMT(12);
    int *tempItem2 = generateIntPointerMT(13);
    matrixInsert(matrix, tempItem1, 1, 0);
    matrixInsert(matrix, tempItem2, 1, 1);

    matrixRemoveRowWtoFr(matrix, 1);

    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }

    CuAssertIntEquals(cuTest, 12, *tempItem1);
    CuAssertIntEquals(cuTest, 13, *tempItem2);

    free(tempItem1);
    free(tempItem2);

    destroyMatrix(matrix);

}






void testMatrixRemoveColumn(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {1, 0, 12}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 0, 1);
    matrixInsert(matrix, generateIntPointerMT(12), 1, 0);
    matrixInsert(matrix, generateIntPointerMT(13), 1, 1);

    matrixRemoveCol(matrix, 1);

    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }

    destroyMatrix(matrix);

}





void testMatrixRemoveColumnWoFr(CuTest *cuTest) {

    Matrix *matrix = matrixInitialization(2, 2, free, compareIntPointersMT);

    int indicesArr[3][3] = {{0,0, 10}, {1, 0, 11}};

    matrixInsert(matrix, generateIntPointerMT(10), 0, 0);
    matrixInsert(matrix, generateIntPointerMT(11), 1, 0);

    int *tempItem1 = generateIntPointerMT(12);
    int *tempItem2 = generateIntPointerMT(13);
    matrixInsert(matrix, tempItem1, 0, 1);
    matrixInsert(matrix, tempItem2, 1, 1);

    matrixRemoveColWtoFr(matrix, 1);

    for (int i = 0, indicesArrIndex = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (indicesArr[indicesArrIndex][0] == i && indicesArr[indicesArrIndex][1] == j) {
                CuAssertPtrNotNull(cuTest, matrix->rows[i][j]);
                CuAssertIntEquals(cuTest, indicesArr[indicesArrIndex++][2], *(int *) matrix->rows[i][j]);
            }
            else
                CuAssertPtrEquals(cuTest, NULL, matrix->rows[i][j]);

        }

    }

    CuAssertIntEquals(cuTest, 12, *tempItem1);
    CuAssertIntEquals(cuTest, 13, *tempItem2);

    free(tempItem1);
    free(tempItem2);

    destroyMatrix(matrix);

}





CuSuite *createMatrixTestsSuite() {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidMatrixInitialization);
    SUITE_ADD_TEST(suite, testValidMatrixInitialization);
    SUITE_ADD_TEST(suite, testMatrixInsert);
    SUITE_ADD_TEST(suite, testMatrixRemove);
    SUITE_ADD_TEST(suite, testMatrixRemoveWtoFr);
    SUITE_ADD_TEST(suite, testMatrixGet);
    SUITE_ADD_TEST(suite, testMatrixContains);
    SUITE_ADD_TEST(suite, testMatrixGetIndex);
    SUITE_ADD_TEST(suite, testMatrixAddRow);
    SUITE_ADD_TEST(suite, testMatrixAddRowAtIndex);
    SUITE_ADD_TEST(suite, testMatrixAddColumn);
    SUITE_ADD_TEST(suite, testMatrixAddColumnAtIndex);
    SUITE_ADD_TEST(suite, testMatrixRemoveRow);
    SUITE_ADD_TEST(suite, testMatrixRemoveRowWoFr);
    SUITE_ADD_TEST(suite, testMatrixRemoveColumn);
    SUITE_ADD_TEST(suite, testMatrixRemoveColumnWoFr);

    return suite;

}



void matrixUnitTest() {

    DUMMY_TEST_DATASTRUCTURE =  (TestStruct*) malloc(sizeof(TestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Matrix Test**\n");

    CuSuite *suite = createMatrixTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(DUMMY_TEST_DATASTRUCTURE);

}
