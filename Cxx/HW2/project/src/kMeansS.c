//
// Created by andrew on 31.10.2021.
//
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "kMeans.h"

#define SUCCESS 0
#define ERROR -1
#define EPS 0.00001

//определение начальных координат центроид
static rVector *defCenters(rVector *arrVec, size_t numVectors, size_t NUMCLUSTERS) {
    srand((unsigned int)time(NULL));
    rVector *cMass = NULL;
    if (!(cMass = (rVector *)malloc(NUMCLUSTERS * sizeof(rVector)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        return NULL;
    }
    for (size_t i = 0; i < NUMCLUSTERS; ++i) {
        rVector temp = arrVec[rand() % numVectors];
        for (size_t j = i; j < NUMCLUSTERS; ++j) {
            if (temp.x != cMass[j].x && temp.y != cMass[j].y && temp.z != cMass[j].z) {
                cMass[j] = temp;
            } else {
                --i;
                break;
            }
        }
        if (i > 0) {
            for (size_t j = 0; j < i; ++j) {
                if (cMass[j].x == cMass[i].x && cMass[j].y == cMass[i].y && cMass[j].z == cMass[i].z) {
                    --i;
                }
            }
        }
    }
    return cMass;
}

//определение расстояния между элементами
static double distance(rVector a, rVector b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
}

//копирование текущих центроид в временный буфер для функции сравнения
static void arrCopy(rVector *a, const rVector *b, size_t l) {
    for (size_t i = 0; i < l; ++i) {
        a[i].x = b[i].x;
        a[i].y = b[i].y;
        a[i].z = b[i].z;
    }
}

//проверка смещения новых центроид относительно старых (точность 1e-5)
static short compare(const rVector *a, const rVector *b, size_t l) {
    short flag = 0;
    for (size_t i = 0; i < l; ++i) {
        if ((fabs(a[i].x - b[i].x) <= EPS) && (fabs(a[i].y - b[i].y) <= EPS) &&
            (fabs(a[i].z - b[i].z) <= EPS)) {
            flag = 1;
        }
    }
    return flag;
}

static int writeResults(rVector *arrVec, size_t numVectors, size_t NUMCLUSTERS, size_t *arrIndex) {
    FILE *wbFile;
    if ((wbFile = fopen("static_Clusterization.txt", "wb")) == NULL) {
        fprintf(stderr, "Error: Failed to open file static_Clusterization.txt!\n");
        return ERROR;
    }
    size_t num;
    for (size_t i = 1; i < NUMCLUSTERS; ++i) {
        num = i + 1;
        fwrite(&num, sizeof(size_t), 1, wbFile);
        for (size_t j = 0; j < numVectors; ++j) {
            if (arrIndex[j] == i) {
                fwrite(&arrVec[j], sizeof(rVector), 1, wbFile);
            }
        }
    }
    if (fclose(wbFile)) {
        fprintf(stderr, "Failed to close file Clusterization.txt!\n");
        return ERROR;
    }
    return SUCCESS;
}

//основная функция кластеризации
rVector *cMassCentroids(rVector *arrVec, size_t numVectors, size_t NUMCLUSTERS) {
    if (arrVec == NULL) {
        fprintf(stderr, "Error: empty array!\n");
        return NULL;
    }
    rVector *centroid = defCenters(arrVec, numVectors, NUMCLUSTERS);
    if (!centroid) {
        fprintf(stderr, "Error: can't build initial centroids!\n");
        return NULL;
    }
    double *dist = NULL;
    if (!(dist = (double *)malloc(NUMCLUSTERS * sizeof(double)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        return NULL;
    }
    size_t *arrIndex = NULL;
    if (!(arrIndex = (size_t *)malloc(numVectors * sizeof(size_t)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(dist);
        return NULL;
    }
    rVector *centroidsTemp = NULL;
    if (!(centroidsTemp = (rVector *)malloc(NUMCLUSTERS * sizeof(rVector)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(dist);
        free(arrIndex);
        return NULL;
    }
    size_t *numInCluster = NULL;
    if (!(numInCluster = (size_t *)malloc(NUMCLUSTERS * sizeof(size_t)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(dist);
        free(arrIndex);
        free(centroidsTemp);
        return NULL;
    }
    double *sumX = NULL;
    if (!(sumX = (double *)malloc(NUMCLUSTERS * sizeof(double)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(dist);
        free(arrIndex);
        free(centroidsTemp);
        free(numInCluster);
        return NULL;
    }
    double *sumY = NULL;
    if (!(sumY = (double *)malloc(NUMCLUSTERS * sizeof(double)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(dist);
        free(arrIndex);
        free(centroidsTemp);
        free(numInCluster);
        free(sumX);
        return NULL;
    }
    double *sumZ = NULL;
    if (!(sumZ = (double *)malloc(NUMCLUSTERS * sizeof(double)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(dist);
        free(arrIndex);
        free(centroidsTemp);
        free(numInCluster);
        free(sumX);
        free(sumY);
        return NULL;
    }
    arrCopy(centroidsTemp, centroid, NUMCLUSTERS);
    short flag = 1;
    double distMin;
    unsigned int numCenter;
    while (flag == 1) {
        for (size_t i = 0; i < numVectors; ++i) {
            for (size_t j = 0; j < NUMCLUSTERS; ++j) {
                dist[j] = distance(centroid[j], arrVec[i]);
            }
            distMin = dist[0];
            numCenter = 0;
            for (size_t j = 0; j < NUMCLUSTERS; ++j) {
                if (dist[j] < distMin) {
                    distMin = dist[j];
                    numCenter = j;
                }
                arrIndex[i] = numCenter;
            }
        }
        for (size_t i = 0; i < NUMCLUSTERS; ++i) {
            numInCluster[i] = 0;
            sumX[i] = 0;
            sumY[i] = 0;
            sumZ[i] = 0;
            for (size_t j = 0; j < numVectors; ++j) {
                if (arrIndex[j] == i) {
                    numInCluster[i] += 1;
                    sumX[i] += arrVec[j].x;
                    sumY[i] += arrVec[j].y;
                    sumZ[i] += arrVec[j].z;
                }
            }
            centroid[i].x = sumX[i] / ((double)numInCluster[i]);
            centroid[i].y = sumY[i] / ((double)numInCluster[i]);
            centroid[i].z = sumZ[i] / ((double)numInCluster[i]);
        }
        if (compare(centroidsTemp, centroid, NUMCLUSTERS)) {
            flag = 0;
            for (size_t i = 0; i < numVectors; ++i) {
                for (size_t j = 0; j < NUMCLUSTERS; ++j) {
                    dist[j] = distance(centroid[j], arrVec[i]);
                }
                distMin = dist[0];
                numCenter = 0;
                for (size_t j = 0; j < NUMCLUSTERS; ++j) {
                    if (dist[j] < distMin) {
                        distMin = dist[j];
                        numCenter = j;
                    }
                }
                arrIndex[i] = numCenter;
            }
        } else {
            arrCopy(centroidsTemp, centroid, NUMCLUSTERS);
        }
    }
    free(centroidsTemp);
    free(dist);
    free(sumX);
    free(sumY);
    free(sumZ);
    free(numInCluster);
    if (writeResults(arrVec, numVectors, NUMCLUSTERS, arrIndex) != SUCCESS) {
        free(arrIndex);
        return NULL;
    }
    free(arrIndex);
    return centroid;
}
