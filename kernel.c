typedef unsigned short uint16_t;

unsigned short* framebuffer = (unsigned short*) 0xB8000;

void write_char(char c, int x, int y) {
    framebuffer[y * 80 + x] = 0x0F00 | c;
}

void write_string(const char* str, int x, int y) {
    int i = 0;
    while (str[i]) {
        write_char(str[i], x + i, y);
        i++;
    }
}

void shutdown() {
    asm volatile(
        "mov $0x604, %%edx;"
        "mov $0x2000, %%eax;"
        "outw %%ax, %%dx"
        : : : "%eax", "%edx"
    );
}

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        framebuffer[i] = 0x0F20;
    }
}

void wait(int milliseconds) {
    for (volatile int i = 0; i < milliseconds * 1000; i++) {
        asm("nop");
    }
}

unsigned char read_port(unsigned short port) {
    unsigned char result;
    asm volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

char pressed_key() {
    unsigned char code = read_port(0x60);
    
    if (code & 0x80) {
        return 0;
    }
    
    if (code == 0x1E) return 'a';
    if (code == 0x30) return 'b';
    if (code == 0x2E) return 'c';
    if (code == 0x20) return 'd';
    if (code == 0x12) return 'e';
    if (code == 0x21) return 'f';
    if (code == 0x22) return 'g';
    if (code == 0x23) return 'h';
    if (code == 0x17) return 'i';
    if (code == 0x24) return 'j';
    if (code == 0x25) return 'k';
    if (code == 0x26) return 'l';
    if (code == 0x32) return 'm';
    if (code == 0x31) return 'n';
    if (code == 0x18) return 'o';
    if (code == 0x19) return 'p';
    if (code == 0x10) return 'q';
    if (code == 0x13) return 'r';
    if (code == 0x1F) return 's';
    if (code == 0x14) return 't';
    if (code == 0x16) return 'u';
    if (code == 0x2F) return 'v';
    if (code == 0x11) return 'w';
    if (code == 0x2D) return 'x';
    if (code == 0x15) return 'y';
    if (code == 0x2C) return 'z';
    
    if (code == 0x0B) return '0';
    if (code == 0x02) return '1';
    if (code == 0x03) return '2';
    if (code == 0x04) return '3';
    if (code == 0x05) return '4';
    if (code == 0x06) return '5';
    if (code == 0x07) return '6';
    if (code == 0x08) return '7';
    if (code == 0x09) return '8';
    if (code == 0x0A) return '9';
    
    if (code == 0x39) return ' ';
    if (code == 0x1C) return '\n';
    if (code == 0x0E) return '\b';
    if (code == 0x0F) return '\t';
    
    if (code == 0x48) return '^';
    if (code == 0x50) return 'v';
    if (code == 0x4B) return '<';
    if (code == 0x4D) return '>';
    
    return 0;
}

void kernel_main() {
    clear_screen();
    write_string("Salut, monde !", 0, 0);
    write_string("Press q", 0, 1);
    
    while (1) {
        char key = pressed_key();
        
        if (key == 'q') {
            write_string("Shutting down...", 0, 2);
            wait(1);
            shutdown();
        }
        
        asm volatile("hlt");
    }
}
