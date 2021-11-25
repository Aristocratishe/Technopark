//
// Created by andrew on 31.10.2021.
//
#pragma once
#include <stddef.h>

//структура для инициализации радиус векторов
typedef struct {
    double x;
    double y;
    double z;
} rVector;

rVector *cMassCentroids(rVector *, size_t, size_t);
