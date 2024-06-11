#include <stdio.h>
#include <string.h>
#include <errno.h>              /* for better error messages */
int main(void)
{
        FILE *in;
        const char *name = "input_file.txt";
        /* open for reading */
        in = fopen(name, "r");
        if (in == NULL) {
                fprintf(stderr, "Failed to open %s for reading: %s\n",
                        name, strerror(errno));
                return -1;
        }
        /* do stuff with the file ... */

        /* close files before exit */
        if (fclose(in)) {
                fprintf(stderr, "Failed to close %s: %s\n", name,
                        strerror(errno));
                return -1;
        }
        return 0;
}
