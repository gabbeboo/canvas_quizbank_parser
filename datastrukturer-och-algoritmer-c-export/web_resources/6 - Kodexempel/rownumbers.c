#include <stdio.h>

#define BUFSIZE 300             // Max 300 char per line

int main(int argc, const char **argv)
{
        char line[BUFSIZE];     // Buffer one line at the time from input
        FILE *in;               // Pointer to input file
        FILE *out;              // Pointer to output file
        int row_number = 1;

        // Verify number of parameters
        if (argc <= 2) {
                fprintf(stderr, "Usage: rownumbers inFile.c outFile.txt\n");
                return -1;
        }

        // Try to open the input file 
        in = fopen(argv[1], "r");
        if (in == NULL) {
                fprintf(stderr, "Couldn't open input file %s\n", argv[1]);
                return -1;
        }

        // Try to open the output file
        out = fopen(argv[2], "w");
        if (out == NULL) {
                fclose(in);     /* Overkill, usually safe to ignore
                                   open-for-read files */
                fprintf(stderr, "Couldn't open output file %s\n", argv[2]);
                return -1;
        }

        /* Read a line at a time from the input file. Write the line,
           preceded by a row number, to the output file. */
        while (fgets(line, BUFSIZE, in) != NULL) {
                fprintf(out, "%-3d ", row_number);
                fprintf(out, "%s", line);
                row_number++;
        }

        // Close files and finish.
        fclose(in);
        fclose(out);
        return 0;
}
