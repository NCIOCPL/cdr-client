struct Dimensions {
    unsigned long height;
    unsigned long width;
};

static inline unsigned short getNetworkShort(const unsigned char* buf) {
    return (((unsigned short)buf[0]) << 8) + (unsigned short)buf[1];
}

static inline unsigned short getLittleEndianShort(const unsigned char* buf) {
    return (((unsigned short)buf[1]) << 8) + (unsigned short)buf[0];
}

static inline unsigned short getNetworkLong(const unsigned char* buf) {
    return (((unsigned long)buf[0]) << 24) +
           (((unsigned long)buf[1]) << 16) +
           (((unsigned long)buf[2]) <<  8) +
             (unsigned long)buf[3];
}

bool getImageDimensions(const unsigned char* buf, int len, Dimensions& dim) {

    // Try GIF.
    if (len >= 10 && buf[0] == 'G' && buf[1] == 'I' && buf[2] == 'F') {
        dim.width  = getLittleEndianShort(buf + 6);
        dim.height = getLittleEndianShort(buf + 8);
        return true;
    }

    // Try PNG
    if (len >= 24      && buf[0]  == 137 && 
        buf[1]  == 'P' && buf[2]  == 'N' && buf[3]  == 'G' &&
        buf[4]  == 13  && buf[5]  == 10  && buf[6]  == 26  && buf[7]  == 10 &&
        buf[12] == 'I' && buf[13] == 'H' && buf[14] == 'D' && buf[15] == 'R') {
        dim.width  = getNetworkLong(buf + 16);
        dim.height = getNetworkLong(buf + 20);
        return true;
    }

    // Try JPEG
    int i = 2, skip = 0;
    if (len >= 2 && buf[0] == 0xFF && buf[1] == 0xD8) { // SOI marker
        while (i < len) {
            if (buf[i++] == 0xFF) {
                while (buf[i] == 0xFF)
                    ++i;
                switch (buf[i++]) {
                case 0xC0: case 0xC1: case 0xC2: case 0xC3:
                case 0xC5: case 0xC6: case 0xC7: case 0xC9:
                case 0xCA: case 0xCB: case 0xCD: case 0xCE:
                case 0xCF: // SOF (Start Of Frame) markers
                    dim.height = getNetworkShort(buf + i + 3);
                    dim.width  = getNetworkShort(buf + i + 5);
                    return true;
                case 0xDA: // SOS (Start of Scan) marker
                case 0xD9: // EOI (End of Image) marker
                    return false;
                default:
                    skip = (int)getNetworkShort(buf + i);
                    if (skip < 2)
                        return false;
                    i += skip;
                    break;
                }
            }
        }
    }

    // Give up.
    return false;
}

#ifdef TESTMAIN
#include <cstdio>
#include <cstdlib>
int main(int ac, char** av) {
    for (int i = 1; i < ac; ++i) {
        FILE* fp = fopen(av[i], "rb");
        if (fp) {
            fseek(fp, 0L, SEEK_END);
            size_t size = ftell(fp);
            rewind(fp);
            char* buf = new char[size];
            size_t totalRead = 0;
            while (totalRead < size) {
                size_t n = fread(buf + totalRead, 1, size - totalRead, fp);
                if (n < 1) {
                    perror("fread");
                    return EXIT_FAILURE;
                }
                totalRead += n;
            }
            fclose(fp);
            Dimensions dim;
            if (getImageDimensions((const unsigned char*)buf, size, dim))
                printf("%40s: %dx%d\n", av[i], dim.width, dim.height);
            else
                printf("%40s: dimensions not found\n", av[i]);
            delete [] buf;
        }
    }
    return EXIT_SUCCESS;
}
#endif
