/**
 * @file endian.hpp
 * @author your name (you@domain.com)
 * @brief A simple endianess library
 * @version 0.1
 * @date 2024-06-08
 * 
 * @copyright Copyright (c) 2024 Kallen Murphy
 * MIT License
 * 
 * Copyright (c) 2024 Kallen Murphy
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SIMPLE_ENDIAN_HPP
#define SIMPLE_ENDIAN_HPP

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace endian {

/**
 * @brief A function that reverses the byte order of a buffer in place
 * 
 * @param buffer
 * @param size 
 */
inline auto reverse_byte_order(std::uint8_t * const buffer, std::size_t size) -> void {
    std::reverse(buffer, buffer + size);
}

/**
 * @brief A function that makes a reversed copy of the source buffer
 * in the destination buffer.
 * 
 * @param src the source buffer
 * @param dst the destination buffer
 * @param size the size of the source buffer (must be less than or equal to the size of dst)
 */
inline auto reverse_byte_order(std::uint8_t * const src, std::uint8_t * const dst, std::size_t size) -> void {
    std::reverse_copy(src, src + size, dst);
}

inline auto host_to_big_endian(std::uint8_t * const buffer, std::size_t size) -> void {
#if defined (HOST_LITTLE_ENDIAN_M)
    reverse_byte_order(buffer, size);
#elif defined (HOST_BIG_ENDIAN_M)
    // do nothing
#else
    static_assert(false, "Endianness was not properly defined.");
#endif
}

inline auto host_to_big_endian(std::uint8_t * const src, std::uint8_t * const dst, std::size_t size) -> void {
#if defined (HOST_LITTLE_ENDIAN_M)
    reverse_byte_order(src, dst, size);
#elif defined (HOST_BIG_ENDIAN_M)
    // do nothing
#else
    static_assert(false, "Endianness was not properly defined.");
#endif
}

template <typename T>
inline auto host_to_big_endian(T&& data, std::uint8_t * const dst, std::size_t size) -> std::size_t {
    if (sizeof(T) > size) {
        throw std::out_of_range{"The size of the data is greater than the buffer size"};
    }
    host_to_big_endian(reinterpret_cast<std::uint8_t * const>(&data), dst, size);

    return sizeof(T);
}

inline auto host_to_little_endian(std::uint8_t * const buffer, std::size_t size) -> void {
#if defined (HOST_LITTLE_ENDIAN_M)
    // do nothing
#elif defined (HOST_BIG_ENDIAN_M)
    reverse_byte_order(buffer, size);
#else
    static_assert(false, "Endianness was not properly defined.");
#endif
}

inline auto host_to_little_endian(std::uint8_t * const src, std::uint8_t * const dst, std::size_t size) -> void {
#if defined (HOST_LITTLE_ENDIAN_M)
    // do nothing
#elif defined (HOST_BIG_ENDIAN_M)
    reverse_byte_order(src, dst, size);
#else
    static_assert(false, "Endianness was not properly defined.");
#endif
}

template <typename T>
inline auto host_to_little_endian(T&& data, std::uint8_t * const dst, std::size_t size) -> std::size_t {
    if (sizeof(T) > size) {
        throw std::out_of_range{"The size of the data is greater than the buffer size"};
    }
    host_to_little_endian(reinterpret_cast<std::uint8_t * const>(&data), dst, size);

    return sizeof(T);
}

}

#endif /* SIMPLE_ENDIAN_HPP */