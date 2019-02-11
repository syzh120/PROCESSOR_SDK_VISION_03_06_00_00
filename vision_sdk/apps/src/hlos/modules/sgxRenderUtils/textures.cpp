/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef STANDALONE
#include <links_fw/src/hlos/system/system_gl_egl_utils.h>
#endif
#include "render.h"

int load_texture(GLuint tex, int width, int height, int textureType, void* data)
{
    GLenum target = GL_TEXTURE_2D;
    GLint param = GL_NEAREST;

    if ((textureType == GL_RGB) || (textureType == GL_RGBA)) {
        target = GL_TEXTURE_2D;
        param = GL_NEAREST;

        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            textureType,
            width,
            height,
            0,
            textureType,
            GL_UNSIGNED_BYTE,//textureFormat,
            data
            );
        GL_CHECK(glTexImage2D);
    } else {
        printf("Incorrect texture type %x\n", textureType);
        return -1;
    }

    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, param); //GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, param); //GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    GL_CHECK(glTexParameteri);
    return 0;
}

int load_texture_from_raw_file(GLuint tex, int width, int height, int textureType, const char* filename, int offset)
{
    int ret;
    void* data;
    FILE* fp;
    int dataread;
    int numbytes = 0;
    //open and load raw file

    switch (textureType) {
        case GL_RGBA:
            numbytes = 4 * width * height;
            break;

        case GL_RGB:
            numbytes = 3 * width * height;
            break;


        default:
            printf("Invalid texture type %d\n", textureType);
            return -1;
    }

    fp = fopen(filename, "rb");
    if(!fp)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }

    data = malloc(numbytes);
    fseek(fp, offset, SEEK_CUR);
    dataread = fread(data, 1, numbytes, fp);
    fclose(fp);
    if(dataread != numbytes) {
        printf("Error in file size != width*height\n");
        return -1; //TODO: reinstate this
    }

    ret = load_texture(tex, width, height, textureType, data);

    free(data);

    return ret;
}

int load_texture_bmp(GLuint tex, const char *filename)
{
	FILE *fp;
	uint8_t header[54];
	uint32_t width, height, offset;
	uint16_t bpp;
	int type;

	fp = fopen(filename, "rb");
	if(!fp)
	{
		fprintf(stderr, "cannot open bmp file: %s\n", filename);
		return -1;
	}

	fread(header, sizeof(uint8_t), 54, fp);

#ifdef QNX_BUILD
	offset = (header[10] & 0xFF) | ((header[11] << 8) & 0xFF00) | ((header[12] << 16) & 0xFF0000) | ((header[13] << 24) & 0xFF000000) ;
	width  = (header[18] & 0xFF) | ((header[19] << 8) & 0xFF00) | ((header[20] << 16) & 0xFF0000) | ((header[21] << 24) & 0xFF000000) ;
	height = (header[22] & 0xFF) | ((header[23] << 8) & 0xFF00) | ((header[24] << 16) & 0xFF0000) | ((header[25] << 24) & 0xFF000000) ;
	bpp    = (header[28] & 0xFF) | ((header[29] << 8) & 0xFF00) ;
#else
	offset = *(int *)(&header[10]);
	width  = *(int *)(&header[18]);
	height = *(int *)(&header[22]);
	bpp    = *(int *)(&header[28]);
#endif

	fclose(fp);

	switch(bpp)
	{
		case 24:
			type = GL_RGB;
			break;
		case 32:
			type = GL_RGBA;
			break;
		default:
			printf("Invalid number of bits per pixel: %d in %s\n", bpp, filename);
			return -1;
	}

	return(load_texture_from_raw_file(tex, width, height, type, filename, offset));
}

void get_bmp_info(const char *filename, uint32_t *width, uint32_t *height, uint32_t *bpp)
{
	FILE *fp;
	uint8_t header[54];

	fp = fopen(filename, "rb");
	fread(header, sizeof(uint8_t), 54, fp);

#ifdef QNX_BUILD
	*width  = (header[18] & 0xFF) | ((header[19] << 8) & 0xFF00) | ((header[20] << 16) & 0xFF0000) | ((header[21] << 24) & 0xFF000000) ;
	*height = (header[22] & 0xFF) | ((header[23] << 8) & 0xFF00) | ((header[24] << 16) & 0xFF0000) | ((header[25] << 24) & 0xFF000000) ;
	*bpp    = (header[28] & 0xFF) | ((header[29] << 8) & 0xFF00) ;
#else
	*width  = *(uint32_t *)(&header[18]);
	*height = *(uint32_t *)(&header[22]);
	*bpp    = *(uint32_t *)(&header[28]);
#endif

	fclose(fp);
}




