#include <stdio.h>
#include <ctype.h>              // for isprint()

/*
 * bindump: Print content of binary file.
 *
 * Expects first command-line argument to be the name of a file.
 * Reads each char from the file and outputs its:
 * - position,
 * - value as integer (decimal and hexadecimal),
 * - value as character, or '.' if not printable.
 *
 */

int main(int argc, const char **argv)
{
        FILE *in;               // Pointer to input file
        int pos = 0;            // Counter for file position

        // Verify input arguments
        if (argc < 2) {
                fprintf(stderr, "Usage: bindump filename\n");
                return -1;
        }
        
        // Try to open the input file
        in = fopen(argv[1], "rb");
        if (in == NULL) {
                fprintf(stderr, "Couldn't open input file %s\n", argv[1]);
                return -1;
        }
        
        // Repeat until end-of-file
        while (!feof(in)) {
                unsigned char c;
                if (fread(&c, sizeof(c), 1, in)) {
                        pos++;
                        // Convert character to integer (required by printf)
                        int i = c;
                        // Print c or a dot if not printable
                        if (!isprint(c)) {
                                c = '.';
                        }
                        printf("%3d: dec: %d, hex: %02x, char: %c\n", pos,
                               i, i, c);
                }
        }

        /* Close file and finish. */
        fclose(in);

        return 0;
}
