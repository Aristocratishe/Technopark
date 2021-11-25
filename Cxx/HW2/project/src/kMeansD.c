//
// Created by andrew on 31.10.2021.
//
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "kMeans.h"

#define ERROR_ALLOCATE_MEMORY -1
#define ERROR_CREATE_THREAD NULL
#define ERROR_JOIN_THREAD NULL
#define SUCCESS 0
#define EPS 0.00001
#define ERROR -1
#define DEFAULT_CPU 4

//структура для работы с потоками
typedef struct {
    size_t nVec;
    rVector *arrV;
    size_t nClus;
    rVector *centroids;
    size_t *arrI;
    size_t startIndex;
    double *sumX;
    double *sumY;
    double *sumZ;
    size_t *numInCluster;
    short *flag;
} argsT;

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

//функция кластеризации для потоков
void *clusterization(void *args) {
    argsT *arg = (argsT *)args;
    double *dis = NULL;
    if (!(dis = (double *)malloc(arg->nClus * sizeof(double)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        return (void *)ERROR_ALLOCATE_MEMORY;
    }
    for (size_t i = arg->startIndex; i < (arg->startIndex + arg->nVec); ++i) {
        for (size_t j = 0; j < arg->nClus; ++j) {
            dis[j] = distance(arg->centroids[j], arg->arrV[i]);
        }
        double distMin = dis[0];
        unsigned int numCenter = 0;
        for (size_t j = 0; j < arg->nClus; ++j) {
            if (dis[j] < distMin) {
                distMin = dis[j];
                numCenter = j;
            }
        }
        arg->arrI[i] = numCenter;
    }
    if (*arg->flag) {
        for (size_t i = 0; i < arg->nClus; ++i) {
            arg->numInCluster[i] = 0;
            arg->sumX[i] = 0;
            arg->sumY[i] = 0;
            arg->sumZ[i] = 0;
            for (size_t j = arg->startIndex; j < (arg->startIndex + arg->nVec); ++j) {
                if (arg->arrI[j] == i) {
                    arg->numInCluster[i] += 1;
                    arg->sumX[i] += arg->arrV[j].x;
                    arg->sumY[i] += arg->arrV[j].y;
                    arg->sumZ[i] += arg->arrV[j].z;
                }
            }
        }
    }
    free(dis);
    return SUCCESS;
}

//определение начальных координат центроид
static rVector *defCenters(rVector *arrVec, size_t numVectors, size_t NUMCLUSTERS) {
    srand(time(NULL));
    rVector *cMass = NULL;
    if (!(cMass = (rVector *)malloc(NUMCLUSTERS * sizeof(rVector)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        return NULL;
    }
    for (size_t i = 0; i < NUMCLUSTERS; ++i) {
        rVector temp = arrVec[0 + rand() % numVectors];
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
//основная функция для создания потоков и записи результатов в bin файл
rVector *cMassCentroids(rVector *arrVec, size_t numVectors, size_t NUMCLUSTERS) {
    int numThreads = sysconf(_SC_NPROCESSORS_CONF);
    if (numThreads == -1) {
        numThreads = DEFAULT_CPU;
    }
    if (arrVec == NULL) {
        fprintf(stderr, "Error: empty array!\n");
        return NULL;
    }
    rVector *centroid = defCenters(arrVec, numVectors, NUMCLUSTERS);
    if (!centroid) {
        fprintf(stderr, "Error: can't build initial centroids!\n");
        return NULL;
    }
    size_t *arrIndex = NULL;
    if (!(arrIndex = (size_t *)malloc(numVectors * sizeof(size_t)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        return NULL;
    }
    rVector *centroidsTemp = NULL;
    if (!(centroidsTemp = (rVector *)malloc(NUMCLUSTERS * sizeof(rVector)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(arrIndex);
        return NULL;
    }
    size_t *summator = NULL;
    if (!(summator = (size_t *)malloc(NUMCLUSTERS * sizeof(size_t)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(arrIndex);
        free(centroidsTemp);
        return NULL;
    }
    arrCopy(centroidsTemp, centroid, NUMCLUSTERS);
    short flag = 1;
    pthread_t thread[numThreads];
    int status;
    argsT args[numThreads];
    for (int i = 0; i < numThreads - 1; ++i) {
        args[i].nVec = numVectors / numThreads;
        args[i].startIndex = i * args[i].nVec;
        args[i].nClus = NUMCLUSTERS;
        args[i].arrV = arrVec;
        args[i].centroids = centroid;
        args[i].arrI = arrIndex;
        args[i].flag = &flag;
        args[i].sumX = NULL;
        args[i].sumY = NULL;
        args[i].sumZ = NULL;
        args[i].numInCluster = NULL;
        if (!(args[i].sumX = (double *)malloc(NUMCLUSTERS * sizeof(double)))) {
            fprintf(stderr, "Error: can't allocate memory!");
            free(arrIndex);
            free(centroidsTemp);
            free(summator);
            return NULL;
        }
        if (!(args[i].sumY = (double *)malloc(NUMCLUSTERS * sizeof(double)))) {
            fprintf(stderr, "Error: can't allocate memory!");
            free(arrIndex);
            free(centroidsTemp);
            free(summator);
            free(args->sumX);
            return NULL;
        }
        if (!(args[i].sumZ = (double *)malloc(NUMCLUSTERS * sizeof(double)))) {
            fprintf(stderr, "Error: can't allocate memory!");
            free(arrIndex);
            free(centroidsTemp);
            free(summator);
            free(args->sumX);
            free(args->sumY);
            return NULL;
        }
        if (!(args[i].numInCluster = (size_t *)malloc(NUMCLUSTERS * sizeof(size_t)))) {
            fprintf(stderr, "Error: can't allocate memory!");
            free(arrIndex);
            free(centroidsTemp);
            free(summator);
            free(args->sumX);
            free(args->sumY);
            free(args->sumZ);
            return NULL;
        }
    }
    args[numThreads - 1].nVec = args[numThreads - 2].nVec + (numVectors % numThreads);
    args[numThreads - 1].startIndex = (numThreads - 1) * args[numThreads - 2].nVec;
    args[numThreads - 1].nClus = NUMCLUSTERS;
    args[numThreads - 1].arrV = arrVec;
    args[numThreads - 1].centroids = centroid;
    args[numThreads - 1].arrI = arrIndex;
    args[numThreads - 1].flag = &flag;
    args[numThreads - 1].sumX = NULL;
    args[numThreads - 1].sumY = NULL;
    args[numThreads - 1].sumZ = NULL;
    args[numThreads - 1].numInCluster = NULL;
    if (!(args[numThreads - 1].sumX = (double *)malloc(NUMCLUSTERS * sizeof(double)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(arrIndex);
        free(centroidsTemp);
        free(summator);
        free(args->sumX);
        free(args->sumY);
        free(args->sumZ);
        free(args->numInCluster);
        return NULL;
    }
    if (!(args[numThreads - 1].sumY = (double *)malloc(NUMCLUSTERS * sizeof(double)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(arrIndex);
        free(centroidsTemp);
        free(summator);
        free(args->sumX);
        free(args->sumY);
        free(args->sumZ);
        free(args->numInCluster);
        return NULL;
    }
    if (!(args[numThreads - 1].sumZ = (double *)malloc(NUMCLUSTERS * sizeof(double)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(arrIndex);
        free(centroidsTemp);
        free(summator);
        free(args->sumX);
        free(args->sumY);
        free(args->sumZ);
        free(args->numInCluster);
        return NULL;
    }
    if (!(args[numThreads - 1].numInCluster = (size_t *)malloc(NUMCLUSTERS * sizeof(size_t)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(arrIndex);
        free(centroidsTemp);
        free(summator);
        free(args->sumX);
        free(args->sumY);
        free(args->sumZ);
        free(args->numInCluster);
        return NULL;
    }
    while (flag == 1) {
        for (int i = 0; i < numThreads; ++i) {
            status = pthread_create(&thread[i], NULL, clusterization, (void *)&args[i]);
            if (status != 0) {
                fprintf(stderr, "Error: can't create thread, status = %d\n", status);
                free(arrIndex);
                free(centroidsTemp);
                free(summator);
                free(args->sumX);
                free(args->sumY);
                free(args->sumZ);
                free(args->numInCluster);
                return ERROR_CREATE_THREAD;
            }
        }
        for (int i = 0; i < numThreads; ++i) {
            status = pthread_join(thread[i], NULL);
            if (status != 0) {
                fprintf(stderr, "Error: can't join thread, status = %d\n", status);
                free(arrIndex);
                free(centroidsTemp);
                free(summator);
                free(args->sumX);
                free(args->sumY);
                free(args->sumZ);
                free(args->numInCluster);
                return ERROR_JOIN_THREAD;
            }
        }
        for (size_t i = 0; i < NUMCLUSTERS; ++i) {
            centroid[i].x = 0;
            centroid[i].y = 0;
            centroid[i].z = 0;
            summator[i] = 0;
            for (int j = 0; j < numThreads; ++j) {
                centroid[i].x += args[j].sumX[i];
                centroid[i].y += args[j].sumY[i];
                centroid[i].z += args[j].sumZ[i];
                summator[i] += args[j].numInCluster[i];
            }
        }
        for (size_t i = 0; i < NUMCLUSTERS; ++i) {
            centroid[i].x = centroid[i].x / ((double)summator[i]);
            centroid[i].y = centroid[i].y / ((double)summator[i]);
            centroid[i].z = centroid[i].z / ((double)summator[i]);
        }
        if (compare(centroidsTemp, centroid, NUMCLUSTERS)) {
            flag = 0;
            for (int i = 0; i < numThreads; ++i) {
                status = pthread_create(&thread[i], NULL, clusterization, (void *)&args[i]);
                if (status != 0) {
                    fprintf(stderr, "Error: can't create thread, status = %d\n", status);
                    free(arrIndex);
                    free(centroidsTemp);
                    free(summator);
                    free(args->sumX);
                    free(args->sumY);
                    free(args->sumZ);
                    free(args->numInCluster);
                    return ERROR_CREATE_THREAD;
                }
            }
            for (int i = 0; i < numThreads; ++i) {
                status = pthread_join(thread[i], NULL);
                if (status != 0) {
                    fprintf(stderr, "Error: can't join thread, status = %d\n", status);
                    free(arrIndex);
                    free(centroidsTemp);
                    free(summator);
                    free(args->sumX);
                    free(args->sumY);
                    free(args->sumZ);
                    free(args->numInCluster);
                    return ERROR_JOIN_THREAD;
                }
            }
        } else {
            arrCopy(centroidsTemp, centroid, NUMCLUSTERS);
        }
    }
    free(args->sumX);
    free(args->sumY);
    free(args->sumZ);
    free(args->numInCluster);
    free(centroidsTemp);
    free(summator);
    if (writeResults(arrVec, numVectors, NUMCLUSTERS, arrIndex) != SUCCESS) {
        free(arrIndex);
        return NULL;
    }
    free(arrIndex);
    return centroid;
}
