#pragma once
#include <stdbool.h>
#include <inttypes.h>

struct uint8_t;

bool windowsIsInputPressed_impl(uint8_t key_code);
bool windowsIsInputDown_impl(uint8_t key_code);