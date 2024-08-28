#pragma once

#include <cstdint>

namespace rdi {
typedef struct _LinearBuffer {
    uint8_t *mem;        /*!< Указатель на буферную память */
    uint32_t total_size; /*!< Общий размер в байтах */
    uint32_t offset;     /*!< Cмещение */
} LinearBuffer;

/*! Несогласованное распределение из линейного буфера. */
void *linearBufferAlloc(LinearBuffer *buf, uint32_t size)
{
    if (buf == nullptr || size == 0)
        return nullptr;

    uint32_t newOffset = buf->offset + size;
    if (newOffset <= buf->total_size) {
        void *ptr = buf->mem + buf->offset;
        buf->offset = newOffset;
        return ptr;
    }
    return nullptr; /*!< Недостаточно памяти */
}
}
