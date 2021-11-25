//
// Created by andrew on 31.10.2021.
//
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "kMeans.h"

#define ERROR -1

int main() {
    struct timespec mt1, mt2;
    long int tt;
    clock_gettime(CLOCK_REALTIME, &mt1);
    const size_t NUMCLUSTERS = 33;
    size_t numVectors;
    rVector *arrVec = NULL;
    char *DirName = NULL;
    if (!(DirName = get_current_dir_name())) {
        fprintf(stderr, "Error: can't read the path!");
        free(DirName);
        return ERROR;
    }
    char str[] = "/project/data/Vectors.txt";
    size_t len = strlen(str) + strlen(DirName) + 1;
    char *path = NULL;
    if (!(path = (char *)malloc(len * sizeof(char)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        free(DirName);
        return ERROR;
    }
    if (!(strcpy(path, DirName))) {
        fprintf(stderr, "Error: can't copy string!");
        free(DirName);
        free(path);
        return ERROR;
    }
    free(DirName);
    if (!(path = strcat(path, str))) {
        fprintf(stderr, "Error: can't concatenate string!");
        return ERROR;
    }
    FILE *rFile;
    if ((rFile = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Error: Failed to open file Vectors.txt!\n");
        return ERROR;
    }
    if (fscanf(rFile, "%zu", &numVectors) == EOF) {
        fprintf(stderr, "Error while reading file Vector.txt!");
        fclose(rFile);
        return ERROR;
    }
    if (!(arrVec = (rVector *)malloc(numVectors * sizeof(rVector)))) {
        fprintf(stderr, "Error: can't allocate memory!");
        fclose(rFile);
        return ERROR;
    }
    while (!feof(rFile)) {
        for (size_t j = 0; j < numVectors; ++j) {
            fscanf(rFile, "%lf%lf%lf", &arrVec[j].x, &arrVec[j].y, &arrVec[j].z);
        }
    }
    if (fclose(rFile)) {
        fprintf(stderr, "Failed to close file Vectors.txt!\n");
        free(arrVec);
        return ERROR;
    }
    rVector *centroids = cMassCentroids(arrVec, numVectors, NUMCLUSTERS);
    if (centroids == NULL) {
        fprintf(stderr, "Clusterization faild!\n");
        free(arrVec);
        return ERROR;
    } else {
        printf(
            "Clusterization completed!\nYou can find the result in "
            "$version$_Clusterization.txt.\n");
    }
    printf("Center mass of centroids:\n");
    for (size_t i = 0; i < NUMCLUSTERS; ++i) {
        printf("%f, %f, %f\n", centroids[i].x, centroids[i].y, centroids[i].z);
    }
    free(centroids);
    free(arrVec);
    clock_gettime(CLOCK_REALTIME, &mt2);
    tt = (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    printf("Затрачено время:\n %ld сек\n", tt);
    return 0;
}
