#pragma once

#include <stdint.h>
#include "BIT_STRING.h"
#include "OCTET_STRING.h"
#include "SIB-Type.h"


typedef uint8_t bit_container_type;
static uint32_t bit_container_type_size = 8;
typedef SIB_Type_t sib_type;
typedef BIT_STRING_s bit_stream_type;
typedef OCTET_STRING octet_stream_type;

