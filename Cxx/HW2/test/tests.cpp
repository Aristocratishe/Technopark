//
// Created by andrew on 03.11.2021.
//
#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>

extern "C" {
#include "kMeans.h"
}

bool operator>(const rVector &a, const rVector &b) {
    if (a.x > b.x) {
        return true;
    } else {
        return false;
    }
}

bool operator<(const rVector &a, const rVector &b) {
    if (a.x < b.x) {
        return true;
    } else {
        return false;
    }
}

bool operator==(const rVector &a, const rVector &b) {
    if (a.x == b.x) {
        return true;
    } else {
        return false;
    }
}

bool cmp(const rVector &a, const rVector &b) { return (a.x == b.x && a.y == b.y && a.z == b.z); }

TEST(ZERO_TEST, ERROR) {
    struct timespec mt1, mt2;
    long int tt;
    clock_gettime(CLOCK_REALTIME, &mt1);
    size_t numVectors = 0;
    const size_t NUMCLUSTERS = 0;
    rVector *arrVec = NULL;
    rVector *centroids = cMassCentroids(arrVec, numVectors, NUMCLUSTERS);
    EXPECT_TRUE(centroids == nullptr);
    free(centroids);
    clock_gettime(CLOCK_REALTIME, &mt2);
    tt = 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    printf("Затрачено время:\n %ld нс\n", tt);
}

TEST(FIRST_TEST, BUILD_CLUSTERS_1) {
    struct timespec mt1, mt2;
    long int tt;
    clock_gettime(CLOCK_REALTIME, &mt1);
    const rVector arrVec[] = {{1, 1, 1}, {10, 10, 10}, {20, 20, 20}};
    size_t numVectors = 3;
    const size_t NUMCLUSTERS = 3;
    rVector *centroids = cMassCentroids((rVector *)arrVec, numVectors, NUMCLUSTERS);
    EXPECT_TRUE(centroids != nullptr);
    std::sort(centroids, centroids + NUMCLUSTERS);
    bool flag = false;
    for (size_t i = 0; i < NUMCLUSTERS; ++i) {
        if (cmp(arrVec[i], centroids[i])) {
            flag = true;
        } else {
            flag = false;
        }
    }
    EXPECT_TRUE(flag);
    free(centroids);
    clock_gettime(CLOCK_REALTIME, &mt2);
    tt = 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    printf("Затрачено время:\n %ld нс\n", tt);
}

TEST(SECOND_TEST, BUILD_CLUSTERS_1) {
    struct timespec mt1, mt2;
    long int tt;
    clock_gettime(CLOCK_REALTIME, &mt1);
    const rVector arrVec[] = {{1, 1, 1},    {10, 10, 10}, {20, 20, 20},
                              {30, 30, 30}, {40, 40, 40}, {50, 50, 50}};
    size_t numVectors = 6;
    const size_t NUMCLUSTERS = 6;
    rVector *centroids = cMassCentroids((rVector *)arrVec, numVectors, NUMCLUSTERS);
    EXPECT_TRUE(centroids != nullptr);
    std::sort(centroids, centroids + NUMCLUSTERS);
    bool flag = false;
    for (size_t i = 0; i < NUMCLUSTERS; ++i) {
        if (cmp(arrVec[i], centroids[i])) {
            flag = true;
        } else {
            flag = false;
        }
    }
    EXPECT_TRUE(flag);
    free(centroids);
    clock_gettime(CLOCK_REALTIME, &mt2);
    tt = 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    printf("Затрачено время:\n %ld нс\n", tt);
}

TEST(THIRD_TEST, BUILD_CLUSTERS_2) {
    struct timespec mt1, mt2;
    long int tt;
    clock_gettime(CLOCK_REALTIME, &mt1);
    const rVector arrVec[] = {
        {17.51935, 4.83933, 7.31391},  {18.61197, 14.67663, 3.97585}, {6.28084, 8.38299, 10.54547},
        {12.83125, 6.65387, 3.00175},  {3.00069, 7.32514, 7.92534},   {10.14032, 14.32039, 15.46236},
        {4.36395, 16.93418, 19.32989}, {9.79816, 2.65788, 12.40173},  {5.75201, 1.33823, 16.93058},
        {16.23622, 6.35485, 14.99310}, {17.06317, 7.16398, 12.07397}, {3.20934, 0.00995, 13.63433},
        {4.23398, 8.33680, 17.55979},  {3.08422, 1.40629, 1.11867},   {15.28839, 7.11091, 9.05751}};
    size_t numVectors = 15;
    const size_t NUMCLUSTERS = 3;
    rVector *centroids = cMassCentroids((rVector *)arrVec, numVectors, NUMCLUSTERS);
    EXPECT_TRUE(centroids != nullptr);
    free(centroids);
    clock_gettime(CLOCK_REALTIME, &mt2);
    tt = 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    printf("Затрачено время:\n %ld нс\n", tt);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}