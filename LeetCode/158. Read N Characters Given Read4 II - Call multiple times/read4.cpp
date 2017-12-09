// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */

    char buffer[4];
    char* end = buffer + 4;
    char* p = end;

    int read(char *buf, int n) {
        int r = 0;
        while (r < n) {
            if (p >= end) {
                p = buffer;
                end = buffer + read4(buffer);
                if (end == buffer) { // EOF, 0 bytes read.
                    return r;
                }
            }
            *buf++ = *p++;
            r++;
        }
        return r;

    }
};
