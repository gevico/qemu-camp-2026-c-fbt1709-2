#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
    const char *type_str;
    switch (e_type) {
    case ET_NONE:
        type_str = "Unknown (ET_NONE)";
        break;
    case ET_REL:
        type_str = "Relocatable (ET_REL)";
        break;
    case ET_EXEC:
        type_str = "Executable (ET_EXEC)";
        break;
    case ET_DYN:
        type_str = "Shared Object/PIE (ET_DYN)";
        break;
    case ET_CORE:
        type_str = "Core Dump (ET_CORE)";
        break;
    default:
        type_str = "Unknown";
        break;
    }
    printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(void) {
    char filepath[2][256] = {
        "./17_myfile.o",
        "./17_myfile",
    };

    int fd;
    Elf64_Ehdr ehdr;

    for (int i = 0; i < 2; i++) {
        fd = open(filepath[i], O_RDONLY);
        if (fd < 0) {
            perror(filepath[i]);
            continue;
        }
        if (read(fd, &ehdr, sizeof(ehdr)) != (ssize_t)sizeof(ehdr)) {
            fprintf(stderr, "%s: ELF header read failed\n", filepath[i]);
            close(fd);
            continue;
        }
        if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
            fprintf(stderr, "%s: not an ELF file\n", filepath[i]);
            close(fd);
            continue;
        }
        print_elf_type(ehdr.e_type);
        close(fd);
    }

    return 0;
}
