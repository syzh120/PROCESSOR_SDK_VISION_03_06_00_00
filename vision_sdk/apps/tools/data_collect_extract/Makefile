
COMMONUTILS_PATH := /ti/adas/vision_sdk/algorithms/commonutils
PC_SRC_PATH := $(COMMONUTILS_PATH)/geometry/src
LIBSRC := $(PC_SRC_PATH)/pointCloud.c $(PC_SRC_PATH)/rigidTransform.c $(PC_SRC_PATH)/point.c

CFLAGS := -Wall -I$(COMMONUTILS_PATH) -I$(PC_SRC_PATH)

all: lidar_convert

lidar_convert : lidar_convert.c
	gcc $(CFLAGS) -o lidar_convert lidar_convert.c $(LIBSRC)

clean :
	rm lidar_convert
