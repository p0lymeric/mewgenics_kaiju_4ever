#pragma once

#include <windows.h>

// Virtual memory utilities
//
// polymeric 2026

// Allocate onto the host process' heap
inline void *host_alloc(size_t size) {
    return HeapAlloc(GetProcessHeap(), 0, size);
}

// Free from the host process' heap
inline void host_free(void *ptr) {
    HeapFree(GetProcessHeap(), 0, ptr);
}

// Reallocate within the host process' heap
inline void *host_realloc(void *ptr, size_t size) {
    // based off MSVC's internal realloc (which conditionally dispatches to HeapAlloc or HeapReAlloc)
    if(ptr == nullptr) {
        return HeapAlloc(GetProcessHeap(), 0, size);
    } else {
        return HeapReAlloc(GetProcessHeap(), 0, ptr, size);
    }
}

// Get the size of a mapped image
inline size_t get_pe_image_mapped_size(HMODULE module) {
    auto base = reinterpret_cast<uintptr_t>(module);

    IMAGE_DOS_HEADER *dos_header = reinterpret_cast<IMAGE_DOS_HEADER *>(base);
    IMAGE_NT_HEADERS *nt_headers = reinterpret_cast<IMAGE_NT_HEADERS *>(base + dos_header->e_lfanew);

    return nt_headers->OptionalHeader.SizeOfImage;
}
