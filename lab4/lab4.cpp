#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

using namespace std;

int getElementLine(int element, int matrixDimention) {
    return element / matrixDimention;
}

int getElementColumn(int element, int matrixDimention) {
    return element % (matrixDimention * matrixDimention);
}

bool isConnected(int firstElement, int secondElement, int matrixDimention, int neuronConnectivityDistance) {
    int absoluteNeuronDifference = abs(firstElement - secondElement);
    int neuronDistance = std::min(absoluteNeuronDifference, (matrixDimention - absoluteNeuronDifference));

    if (neuronDistance <= neuronConnectivityDistance) {
        return true;
    }
}

bool isConnectedByLine(int firstElement, int secondElement, int matrixDimention, int neuronConnectivityDistance) {
    if (getElementLine(firstElement, matrixDimention) == getElementLine(secondElement, matrixDimention)) {
        return isConnected(firstElement, secondElement, matrixDimention, neuronConnectivityDistance);
    }

    return false;
}

bool isConnectedByColumn(int firstElement, int secondElement, int matrixDimention, int neuronConnectivityDistance) {
    if (getElementColumn(firstElement, matrixDimention) == getElementColumn(secondElement, matrixDimention)) {
        int firstLineNumber = getElementColumn(firstElement, matrixDimention) / matrixDimention;
        int secondLineNumber = getElementColumn(secondElement, matrixDimention) / matrixDimention;

        return isConnected(firstLineNumber, secondLineNumber, matrixDimention, neuronConnectivityDistance);
    }
}

int isConnectedElements(int matrixDimention, int neuronConnectivityDistance, int firstElement, int secondElement){
    if (isConnectedByColumn(firstElement, secondElement, matrixDimention, neuronConnectivityDistance)
    || isConnectedByLine(firstElement, secondElement, matrixDimention, neuronConnectivityDistance)) {
        return 1;
    } else {
        return 0;
    }
}


int main(int argc, char *argv[]){
    int matrixDimention = atof(argv[1]);
    int neuronConnectivityDistance = atof(argv[2]);

    double timeBefore =  omp_get_wtime();

    int connectivityMatrix[matrixDimention][matrixDimention];

    #pragma omp parallel shared(connectivityMatrix, matrixDimention, neuronConnectivityDistance) private (i) num_threads(10)
    #pragma omp for
    for (int i = 0; i < matrixDimention; i++) {
        #pragma omp parallel shared(connectivityMatrix, matrixDimention, neuronConnectivityDistance, i) private (j) num_threads(10)
        #pragma omp for
        for (int j = 0; j < matrixDimention; j++) {
            connectivityMatrix[i][j] = isConnectedElements(matrixDimention, neuronConnectivityDistance, i, j);
        }
    }

    double spentTime = omp_get_wtime() - timeBefore;

    cout << spentTime << endl;
}
