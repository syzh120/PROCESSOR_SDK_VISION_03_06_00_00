/*
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 * ======== binsrc.c ========
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

unsigned char buffer[0x2000];

int main(int argc, char * argv[])
{
    FILE          *infile, *outfile;
    int           tmp = 0;
    long          size, ltmp;
    unsigned char *pc;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s [InFile] [OutFile] [Name]\n", argv[0]);
        exit(1);
    }

    if (!(infile = fopen(argv[1],"rb"))) {
        fprintf(stderr, "%s: can't open source file: %s\n", argv[0], argv[1]);
        exit(2);
    }

    /* Get the file size */
    fseek(infile, 0, SEEK_END);
    size = ftell(infile);
    rewind(infile);

    printf("input file: %s, %ld bytes\n", argv[1], size);

    if (!(outfile = fopen(argv[2], "wb"))) {
        fprintf(stderr, "%s: can't open output file: %s\n", argv[0], argv[2]);
        exit(3);
    }

    printf("output file: %s\n", argv[2]);

    fprintf(outfile, "#define %s_SIZE %ld\n", argv[3], size);
    fprintf(outfile, "static const unsigned char %s[] = {\n    ", argv[3]);
    tmp = 0;

    while (size) {
	if (size >= sizeof(buffer)) {
            ltmp = sizeof(buffer);
	}
	else {
            ltmp = size;
	}

        fread(buffer, 1, (short)ltmp, infile);

        pc = buffer;
        size -= ltmp;
        while (ltmp--) {
            if (size || ltmp) {
                fprintf(outfile, "0x%02X, ", *pc++);
                if (!(++tmp % 12)) {
                    fprintf(outfile,"\n    ");
		}
            }
            else {
                fprintf(outfile,"0x%02X };\n", *pc++);
	    }
        }
    }

    fclose(infile);
    fclose(outfile);

    return 0;
}
