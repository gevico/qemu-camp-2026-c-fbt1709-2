#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
 * 14 紧凑网络协议头解析器（位域）
 * 要求：
 *  - 协议头格式：2 字节版本（4 位主版本 + 4 位次版本）、2 字节长度（16 位无符号）、1 字节标志（3 位保留 + 5
 * 位功能标志）。
 *  - 输入示例：\x00\x03\x00\x20\x00  →  version:0.3, length:32, flags:0x00
 *  - 考察点：位域定义、结构体对齐（#pragma pack(1)）、字节流解析
 */

/* 结构体对齐：按 1 字节对齐，确保与网络字节流逐字节一致 */
#pragma pack(push, 1)

/*
 * 原始协议头（与网络字节流逐字节对应，不直接使用位域跨字节）
 */
typedef struct {
    uint8_t reserved;
    uint8_t version_byte;
    uint16_t length_be;
    uint8_t flags_raw;
} proto_header_raw_t;

typedef struct {
    unsigned ver_major;
    unsigned ver_minor;
    unsigned length;
    unsigned flags;
} proto_header_bits_t;

#pragma pack(pop)

/*
 * 将网络序（大端）的 16 位数转换为主机序
 */
static uint16_t be16_to_cpu(uint16_t be) {
    return (uint16_t)(((be & 0xFFu) << 8) | ((be >> 8) & 0xFFu));
}

int main(void) {
    /* 测试输入字节流：00 03 00 20 00 */
    const uint8_t stream[5] = {0x00, 0x03, 0x00, 0x20, 0x00};

    /* 将字节流复制到与其逐字节匹配的原始头结构体中 */
    proto_header_raw_t raw = {0};
    memcpy(&raw, stream, sizeof(raw));

    uint16_t length = be16_to_cpu(raw.length_be);
    unsigned flags = (unsigned)(raw.flags_raw & 0x1Fu);

    proto_header_bits_t view;
    view.ver_major = (unsigned)((raw.version_byte >> 4) & 0xFu);
    view.ver_minor = (unsigned)(raw.version_byte & 0xFu);
    view.length = (unsigned)length;
    view.flags = flags;

    printf("version:%u.%u, length:%u, flags:0x%02X\n", view.ver_major, view.ver_minor, view.length, view.flags & 0xFFu);

    return 0;
}
