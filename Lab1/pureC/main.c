#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define SIZE 256
#define CHUNK_LEN 1048576

float entropy_calc(long long byte_count[], int length) {
    float entropy = 0.0f;
    float count;
    int i;

    /* entropy calculation */
    for (i = 0; i < SIZE; i++) {
        if (byte_count[i] != 0) {
            count = (float) byte_count[i] / (float) length;
            entropy -= count * log2f(count);
        }
    }
    return entropy;
}

int main(int argc, char **argv) {
    FILE *inFile;
    int i;
    int j;
    unsigned long long int n;              // Bytes read by fread;
    unsigned long long int length = 0;         // length of file
    long long byte_count[SIZE];
    unsigned char buffer[CHUNK_LEN];

    /* do this for all files */
    for (j = 1; j < argc; j++) {
        memset(byte_count, 0, sizeof(long long) * SIZE);

        inFile = fopen(argv[j], "rb");    // opens the file given on command line

        if (inFile == NULL)                // error-checking to see if file exists
        {
            printf("Files does not exist. `%s`\n", argv[j]);
            continue;
        }

        fseek(inFile, 0L, SEEK_END);
        unsigned long long int sz = ftell(inFile);
        fseek(inFile, 0L, SEEK_SET);
        /* Read the whole file in parts of CHUNK_LEN */
        float progress = 0.0f;
        int barWidth = 70;

        clock_t start, end = 2;
        start = clock();
        unsigned long long int read_cnt = 0;
        printf("\e[?25l");
        while ((n = fread(buffer, 1, CHUNK_LEN, inFile)) != 0) {
            printf("%.2f %% [", progress * 100.0);
            int pos = (int)((float)barWidth * progress);
            for (int k = 0; k < barWidth; ++k) {
                if (k < pos) printf("=");
                else if (k == pos) printf(">");
                else printf(" ");
            }
            double elapsed_mkseconds = (double)(end - start)/CLOCKS_PER_SEC;
            double remain_time = (int) (((float) elapsed_mkseconds) / progress);
            printf("] %.2dk/%.2luk [%.2fs < %.2fs, %.2fMB/s]\r", read_cnt * CHUNK_LEN / 1000, sz / 1000,
                   elapsed_mkseconds, remain_time,
                   ((float)(read_cnt * CHUNK_LEN) / ((float)elapsed_mkseconds)) / 1000000);
            fflush(stdin);
            /* Add the buffer to the byte_count */
            for (i = 0; i < n; i++) {
                byte_count[(int) buffer[i]]++;
                length++;
            }
            end = clock();
            read_cnt++;
            progress = (float) read_cnt * (float) CHUNK_LEN / (float) sz;
        }
        fclose(inFile);

        printf("%.2f %% [", progress * 100.0);
        int pos = (int)((float)barWidth * progress);
        for (int k = 0; k < barWidth; ++k) {
            if (k < pos) printf("=");
            else if (k == pos) printf(">");
            else printf(" ");
        }
        double elapsed_seconds = (double)(end - start)/CLOCKS_PER_SEC;
        double remain_time = (int) (((float) elapsed_seconds) / progress);
        printf("] %.2dk/%.2luk [%.2fs < %.2fs, %.2fMB/s]\r", read_cnt * CHUNK_LEN / 1000, sz / 1000,
               elapsed_seconds, remain_time,
               ((float)(read_cnt * CHUNK_LEN) / ((float)elapsed_seconds)) / 1000000);
        fflush(stdin);
        printf("\e[?25h");
        printf("\n");

        float entropy = entropy_calc(byte_count, length);
        printf("%02.5f \t%s\n", entropy, argv[j]);
    }
    return 0;
}

