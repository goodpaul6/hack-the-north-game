#pragma once

#include <cstdio>

#define HTN_LOG_INFO(fmt, ...) \
    std::printf("INFO(%s:%d): " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define HTN_LOG_ERROR(fmt, ...) \
    std::fprintf(stderr, "ERROR(%s:%d): " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
