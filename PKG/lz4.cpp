#include <iostream>
#include <lz4.h>

int main() {
    // 原始数据
    const char* originalData = "Hello, LZ4 compression!";
    const int originalSize = strlen(originalData);

    // 分配足够的空间来存储压缩后的数据
    const int maxCompressedSize = LZ4_compressBound(originalSize);
    char* compressedData = new char[maxCompressedSize];

    // 压缩数据
    int compressedSize = LZ4_compress_default(originalData, compressedData, originalSize, maxCompressedSize);

    if (compressedSize > 0) {
        // 输出压缩后的数据
        std::cout << "Compressed data: ";
        for (int i = 0; i < compressedSize; ++i) {
            std::cout << static_cast<int>(compressedData[i]) << " ";
        }
        std::cout << std::endl;

        // 分配足够的空间来存储解压后的数据
        char* decompressedData = new char[originalSize];

        // 解压数据
        int decompressedSize = LZ4_decompress_safe(compressedData, decompressedData, compressedSize, originalSize);

        if (decompressedSize == originalSize) {
            // 输出解压后的数据
            std::cout << "Decompressed data: " << decompressedData << std::endl;
        } else {
            std::cerr << "Decompression failed!" << std::endl;
        }

        // 释放内存
        delete[] decompressedData;
    } else {
        std::cerr << "Compression failed!" << std::endl;
    }

    // 释放内存
    delete[] compressedData;

    return 0;
}
