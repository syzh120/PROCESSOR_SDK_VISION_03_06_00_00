/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/file_api.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <include/link_api/system_trace.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/devices/bsp_device.h>

#if ( defined(FATFS_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(FATFS_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

#include <src/rtos/utils_common/src/file_api_priv.h>
#endif
/*******************************************************************************
 *  Function prototype's
 *******************************************************************************
 */
static Int32 Utils_fileCioReadFile(char *fileName, UInt8 *addr, UInt32 readSize, Uint32 *actualReadSize);
static Int32 Utils_fileCioWriteFile(char *fileName, Uint8 *addr, Uint32 size);

#if ( defined(FATFS_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(FATFS_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

static void File_lock(void);
static void File_unlock(void);
static Int32 File_allocObj();
static Void File_freeObj(Int32 fd);
static Void File_registerCioFxns();



FileSys_Obj gFileSys_obj;


Int32 File_init(void)
{
    UInt32 i;

    gFileSys_obj.lock = BspOsal_semCreate((Int32)0, (Bool)TRUE);
    UTILS_assert(gFileSys_obj.lock != NULL);

    gFileSys_obj.edmaDone = BspOsal_semCreate((Int32)0, (Bool)TRUE);
    UTILS_assert(gFileSys_obj.edmaDone != NULL);

    File_unlock();

    gFileSys_obj.hEdma = Utils_dmaGetEdma3Hndl(UTILS_DMA_SYSTEM_EDMA_INST_ID);

    for(i=0; i<UTILS_FILE_MAX; i++)
    {
        gFileSys_obj.isAlloc[i] = (Bool)FALSE;
    }

    #if defined(TDA2XX_FAMILY_BUILD)
    {
        void File_initPinMuxPowerMMCSD_tda2xx();

        /* MMC1 PAD / Power / Clock Configuration*/
        File_initPinMuxPowerMMCSD_tda2xx();

        /* Initialize the MMC driver data structures */
        HSMMCSDInit(MMC1_INST);
    }
    #elif defined(TDA3XX_FAMILY_BUILD)
    {
        void File_initPinMuxPowerMMCSD_tda3xx();

        /* MMC4 PAD / Power / Clock Configuration*/
        File_initPinMuxPowerMMCSD_tda3xx();

        /* Initialize the MMC driver data structures */
        HSMMCSDInit(MMC4_INST);
    }
    #endif

    File_registerCioFxns();

    return 0;
}

void File_deInit(void)
{
    BspOsal_semDelete(&gFileSys_obj.lock);
}

void File_mountFs(void)
{
    #if defined(TDA2XX_FAMILY_BUILD)
    HSMMCSDInit(MMC1_INST);
    #elif defined(TDA3XX_FAMILY_BUILD)
    HSMMCSDInit(MMC4_INST);
    #else
    UTILS_assert(0);
    #endif
}

void File_unmountFs(void)
{
    #if defined(TDA2XX_FAMILY_BUILD)
    HSMMCSDDeInit(MMC1_INST);
    #elif defined(TDA3XX_FAMILY_BUILD)
    HSMMCSDDeInit(MMC4_INST);
    #else
    UTILS_assert(0);
    #endif
}

static void File_lock(void)
{
    UTILS_assert(gFileSys_obj.lock != NULL);
    BspOsal_semWait(gFileSys_obj.lock, BSP_OSAL_WAIT_FOREVER);
}

static void File_unlock(void)
{
    UTILS_assert(gFileSys_obj.lock != NULL);
    BspOsal_semPost(gFileSys_obj.lock);
}

static Int32 File_isAlloc(Int32 fd)
{
    Bool isAlloc = FALSE;

    if( (fd >= 0) && (fd < UTILS_FILE_MAX) )
    {
        if(gFileSys_obj.isAlloc[fd]==(Bool)TRUE)
        {
            isAlloc = TRUE;
        }
    }

    return isAlloc;
}

static Int32 File_allocObj(void)
{
    UInt32 i;
    Int32 fd;

    for(i=0; i<UTILS_FILE_MAX; i++)
    {
        if(gFileSys_obj.isAlloc[i]==(Bool)FALSE)
        {
            break;
        }
    }

    if(i<UTILS_FILE_MAX)
    {
        gFileSys_obj.isAlloc[i]=(Bool)TRUE;
        fd = (Int32)i;
    }
    else
    {
        fd = -1;
    }

    return fd;
}

static Void File_freeObj(Int32 fd)
{
    if(File_isAlloc(fd)==(Bool)TRUE)
    {
        gFileSys_obj.isAlloc[fd]=(Bool)FALSE;
    }
}


Int32 File_read(Int32 fd, UInt8 *dataBuf, UInt32 bytesToRead, UInt32 *bytesRead)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UINT bytes_read = 0;
    FRESULT fresult;

    File_lock();

    if(File_isAlloc(fd)==(Bool)TRUE)
    {
        fresult = f_read(
                        &gFileSys_obj.fileObj[fd],
                        (void *) dataBuf,
                        bytesToRead,
                        (UINT *) &bytes_read
                    );
        if (fresult == FR_OK)
        {
            status = 0;
        }
    }

    *bytesRead = bytes_read;

    File_unlock();

    return status;
}


Int32 File_write(Int32 fd, UInt8 *dataBuf, UInt32 dataSize)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UINT bytes_written = 0;
    FRESULT fresult;

    File_lock();

    if(File_isAlloc(fd)==(Bool)TRUE)
    {
        fresult = f_write(
                        &gFileSys_obj.fileObj[fd],
                        (void *) dataBuf,
                        dataSize,
                        (UINT *) &bytes_written
                    );
        if( (fresult == FR_OK) && (dataSize == bytes_written) )
        {
            status = 0;
        }
    }

    File_unlock();

    return status;
}

Int32 File_seek(Int32 fd, UInt32 offset)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    FRESULT fresult;

    File_lock();

    if(File_isAlloc(fd)==(Bool)TRUE)
    {
        fresult = f_lseek(
                        &gFileSys_obj.fileObj[fd],
                        (DWORD) offset
                    );
        if (fresult == FR_OK)
        {
            status = 0;
        }
    }

    File_unlock();

    return status;
}

Int32 File_chDir(char *dirName)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    FRESULT fresult;

    UTILS_assert(strlen(dirName) <= 8);

    File_lock();

    fresult = f_chdir(dirName);
    if (fresult == FR_OK)
    {
        status = 0;
    }

    File_unlock();

    return status;
}

Int32 File_getCwd(char *dirName, UInt32 len)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    FRESULT fresult;

    UTILS_assert(len <= 8);

    File_lock();

    fresult = f_getcwd(dirName, len);
    if (fresult == FR_OK)
    {
        status = 0;
    }

    File_unlock();

    return status;
}

Int32 File_stat(char *filename)
{
    Int32 retVal;
    FILINFO fno;
    FRESULT fresult;
    memset(&fno,0x00,sizeof(FILINFO));

    File_lock();
    fresult = f_stat(filename,&fno);

    if(fresult == FR_NO_FILE)
    {
        retVal = SYSTEM_LINK_STATUS_EFILE_NO_FILE;
    }
    else if(fresult == FR_OK)
    {
        retVal = SYSTEM_LINK_STATUS_SOK;
    }
    else
    {
        retVal = SYSTEM_LINK_STATUS_EFAIL;
    }
    File_unlock();
    return retVal;
}

Int32 File_open(char *filename, char *mode)
{
    Int32 fd;
    FRESULT fresult;

    File_lock();

    fd = File_allocObj();
    if(File_isAlloc(fd)==(Bool)TRUE)
    {
        if(mode[0]=='w')
        {
            fresult = f_open(&gFileSys_obj.fileObj[fd], filename, FA_WRITE);
            if (fresult != FR_OK)
            {
                /*If file does not exist. Create new one*/
                fresult = f_open(&gFileSys_obj.fileObj[fd], filename, FA_CREATE_NEW);
                if (fresult != FR_OK)
                {
                    File_freeObj(fd);
                    fd = -1;
                }
                else
                {
                    f_close(&gFileSys_obj.fileObj[fd]);
                    /*Open handle to the newly created file*/
                    fresult = f_open(&gFileSys_obj.fileObj[fd], filename, FA_WRITE);
                    if (fresult != FR_OK)
                    {
                        File_freeObj(fd);
                        fd = -1;
                    }
                }
            }
        }
        else
        if(mode[0]=='r')
        {
            fresult = f_open(&gFileSys_obj.fileObj[fd], filename, FA_READ);
            if (fresult != FR_OK)
            {
                File_freeObj(fd);
                fd = -1;
            }
        }
        else
        {
            File_freeObj(fd);
            fd = -1;
        }
    }

    File_unlock();

    return fd;
}

Int32 File_close(Int32 fd)
{
    File_lock();

    if(File_isAlloc(fd)==(Bool)TRUE)
    {
        f_close(&gFileSys_obj.fileObj[fd]);
        File_freeObj(fd);
    }

    File_unlock();

    return 0;
}

Int32 File_delete(char *filename)
{
    Int32 retVal;
    FRESULT fresult;

    File_lock();
    fresult = f_unlink(filename);

    if(fresult == FR_OK)
    {
        retVal = SYSTEM_LINK_STATUS_SOK;
    }
    else
    {
        retVal = SYSTEM_LINK_STATUS_EFAIL;
    }

    File_unlock();
    return retVal;
}

Int32 File_eof(Int32 fd)
{
    if (fd < 0)
    {
        return SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        return(f_eof(&gFileSys_obj.fileObj[fd]));
    }
}

Int32 File_putc(Int32 character, Int32 fd)
{
    if (fd < 0)
        return SYSTEM_LINK_STATUS_EFAIL;
    else
    {
        Int32 status = 0;
        status = f_putc(character, &gFileSys_obj.fileObj[fd]);
        return status;
    }
}

Int32 File_puts(const char* str, Int32 fd)
{
    if (fd < 0)
    {
        return SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        Int32 status = 0;

        File_lock();

        status = f_puts(str, &gFileSys_obj.fileObj[fd]);

        File_unlock();

        return status;
    }
}

char* File_gets(char* buff, Int32 len, Int32 fd)
{
    if (fd < 0)
    {
        return buff;
    }

    else
    {
        File_lock();
        buff = f_gets(buff, len, &gFileSys_obj.fileObj[fd]);
        File_unlock();
        return buff;
    }
}

Int32 File_rewind(Int32 fd)
{
    Int32 status = 0;

    status = File_seek(fd, 0);

    return status;
}

Int64 File_tell(Int32 fd)
{
    Int64 result = -1;

    File_lock();

    if(File_isAlloc(fd)==(Bool)TRUE)
    {
        result = f_tell(&gFileSys_obj.fileObj[fd]);
    }

    File_unlock();
    return result;
}

char* File_getcwd(char* buff, Int32 len)
{
    FRESULT result;
    File_lock();
    result = f_getcwd(buff, len);
    File_unlock();
    if (result == FR_OK)
    {
        return buff;
    }
    else
    {
        return NULL;
    }
}

Int32 File_printf(Int32 fd, char* fmt, ...)
{
    if(fd >= 0)
    {
        Int32 status = 0;
        va_list arguments;
        va_start(arguments, fmt);
        File_lock();
        status = f_printf(&gFileSys_obj.fileObj[fd], fmt, arguments);
        File_unlock();
        va_end(arguments);

        return status;
    }
    else
    {
        va_list arguments;
        va_start(arguments, fmt);
        Vps_vprintf(fmt, arguments);
        va_end(arguments);
        return 0;
    }
}

Int32 File_vprintf(Int32 fd, char* fmt, va_list apr)
{
    if(fd >= 0)
    {
        return SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        Vps_vprintf(fmt, apr);
        return 0;
    }
}

Int32 File_mkdir(const char* path)
{
    Int32 status = 0;
    FRESULT result;
    File_lock();
    result = f_mkdir(path);
    File_unlock();
    if(result != FR_OK)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
}

Int32 File_isdir(const char* path)
{
    Int32 status = 0;
    FRESULT result;
    File_lock();
    result = f_mkdir(path);
    File_unlock();
    if(result == FR_EXIST)
    {
        status = 1;
    }

    return status;
}

Int32 File_flush(Int32 fd)
{
    if(fd >= 0)
    {
        Int32 status = 0;
        FRESULT result;
        File_lock();
        result = f_sync(&gFileSys_obj.fileObj[fd]);
        File_unlock();
        if(result != FR_OK)
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
        return status;
    }
    else
    {
        return SYSTEM_LINK_STATUS_EFAIL;
    }
}

Int32 File_error(Int32 fd)
{
    if(fd >= 0)
    {
        Int32 status = 0;
        File_lock();
        status = f_error(&gFileSys_obj.fileObj[fd]);
        File_unlock();
        return status;
    }
    else
    {
        Vps_printf(" FILE: Invalid file ID !!!\n");
        return SYSTEM_LINK_STATUS_EFAIL;
    }
}

Int32 File_size(Int32 fd)
{
    if(fd >= 0)
    {
        Int32 result = 0;
        File_lock();
        result = f_size(&gFileSys_obj.fileObj[fd]);
        File_unlock();
        return result;
    }
    else
    {
        Vps_printf(" FILE: Invalid file ID !!!\n");
        return SYSTEM_LINK_STATUS_EFAIL;
    }
}

#if defined(BUILD_DSP) || defined(BUILD_ARP32) || defined(BUILD_M4)

#include <file.h>

int FileCio_open(const char *path, unsigned flags, int llv_fd)
{
    int status = -1;
    int fd;
    char mode[2];

    if( flags & (O_WRONLY))
    {
        mode[0]='w';
        mode[1]=0;
        status = 0;
    }
    else
    if( (flags & O_WRONLY) == 0)
    {
        mode[0]='r';
        mode[1]=0;
        status = 0;
    }

    if(status==0)
    {
        fd = File_open((char*)path, mode);

        status = fd;
    }

    return status;
}

int FileCio_close(int dev_fd)
{
    int status;

    status = File_close(dev_fd);

    return status;
}

int FileCio_read(int dev_fd, char *buf, unsigned count)
{
    Int32 status;
    UInt32 bytesRead;

    status = File_read(dev_fd, (UInt8*)buf, count, &bytesRead);
    if(status == 0)
    {
        status = (Int32)bytesRead;
    }
    return status;
}

int FileCio_write(int dev_fd, const char *buf, unsigned count)
{
    Int32 status;

    status = File_write(dev_fd, (UInt8*)buf, count);
    if(status==0)
    {
        status = count;
    }

    return status;
}

off_t FileCio_lseek(int dev_fd, off_t offset, int origin)
{
    Int32 status = -1;

    if(origin==SEEK_SET)
    {
        status = File_seek(dev_fd, offset);
    }
    else
    if(origin==SEEK_CUR)
    {
        Int64 curOff;

        curOff = File_tell(dev_fd);
        if(curOff>0)
        {
            offset = (UInt32)curOff + offset;
            status = File_seek(dev_fd, offset);
        }
        else
        {
            status = -1;
        }
    }
    else
    if(origin==SEEK_END)
    {
        Int32 fileSize;

        fileSize = File_size(dev_fd);
        if(fileSize>0)
        {
            offset = (UInt32)fileSize + offset;
            status = File_seek(dev_fd, offset);
        }
        else
        {
            status = -1;
        }
    }
    if(status==0)
    {
        status = offset;
    }
    return status;
}

int FileCio_unlink(const char *path)
{
    return 0;
}

int FileCio_rename(const char *old_name, const char *new_name)
{
    return 0;
}

static Void File_registerCioFxns()
{
    int status;

    status = add_device("sd",
                _MSA,
                FileCio_open,
                FileCio_close,
                FileCio_read,
                FileCio_write,
                FileCio_lseek,
                FileCio_unlink,
                FileCio_rename);
    UTILS_assert(status==0);
}
#else
static Void File_registerCioFxns()
{
    /* CIO add_device API NOT supported on A15 GCC tool chain */
}
#endif

#if defined(TDA2XX_FAMILY_BUILD)

void   MMCSD_LDO_PWR()
{
    /*CTRL_CORE_CONTROL_PBIAS*/

    uint32_t reg_val = 0;

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);

    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);
    BspOsal_sleep(1);
    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    /*Enable SDCARD_BIAS_VMODE*/
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_MASK; /* 3v */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);
    BspOsal_sleep(1);

    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    BspOsal_sleep(1);
}

void File_initPinMuxPowerMMCSD_tda2xx()
{
    uint32_t tmpRegVal;
    /*MMC1- CM_L3INIT_MMC1_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC1_CLKCTRL);
    tmpRegVal |= 0x03000000;
    HW_WR_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC1_CLKCTRL, tmpRegVal);

    /*Enable the module - mmc1  */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_MMC1, PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);
    MMCSD_LDO_PWR();

    /*MMC1 PAD Configuration*/
    PlatformMMCSD1SetPinMux();
}
#endif

#if defined(TDA3XX_FAMILY_BUILD)

void File_initPinMuxPowerMMCSD_tda3xx()
{
    uint32_t tmpRegVal;
    /*MMC4- CM_L4INIT_MMC4_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL);
    tmpRegVal |= 0x02000000;
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL, tmpRegVal);

    /*MMC4 PRCM config*/
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL, 0x2);

    /* MMC4 PAD Configuration */
    PlatformMMCSD4SetPinMux();

    /* IOExpander MUX Configuration */
    Bsp_boardSelectDevice(BSP_DRV_ID_MMC, BSP_DEVICE_MMC_INST_ID_4);
}
#endif

#else

/* Dummy APIs for FATFS_PROC = none */
Int32 File_init()
{
    return 0;
}

void File_deInit(void)
{

}

void File_mountFs(void)
{

}

void File_unmountFs(void)
{

}

Int32 File_open(char *name, char *mode)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_read(Int32 fd, UInt8 *dataBuf, UInt32 bytesToRead, UInt32 *bytesRead)
{
    *bytesRead = 0;
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_write(Int32 fd, UInt8 *dataBuf, UInt32 dataSize)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_seek(Int32 fd, UInt32 offset)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_chDir(char *dirName)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_getCwd(char *dirName, UInt32 len)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_close(Int32 fd)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_delete(char *filename)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_eof(Int32 fd)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_putc(Int32 character, Int32 fd)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_puts(const char* str, Int32 fd)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

char* File_gets(char* buff, Int32 len, Int32 fd)
{
    return NULL;
}

Int32 File_rewind(Int32 fd)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int64 File_tell(Int32 fd)
{
    return (Int64)SYSTEM_LINK_STATUS_EFAIL;
}

char* File_getcwd(char* buff, Int32 len)
{
    return NULL;
}

Int32 File_printf(Int32 fd, char* fmt, ...)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_vprintf(Int32 fd, char* fmt, va_list apr)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_mkdir(const char* path)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_isdir(const char* path)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_flush(Int32 fd)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_error(Int32 fd)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_size(Int32 fd)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

Int32 File_stat(char *filename)
{
    return SYSTEM_LINK_STATUS_EFAIL;
}

#endif

Int32 Utils_fileReadFile(char *fileName, UInt8 *addr, UInt32 readSize, Uint32 *actualReadSize)
{
    Int32 retVal = 0;
    UInt8  *curAddr;

    UInt32 readDataSize, fileSize, chunkSize=1024*100;

    Int32 hndlFile;

    Vps_printf(" FILE: Reading file [%s] ... \n", fileName);

    hndlFile = File_open(fileName, "rb");

    if(hndlFile < 0)
    {
        retVal = SYSTEM_LINK_STATUS_EFAIL;
        *actualReadSize=0;
        Vps_printf(" FILE: ERROR: Could not open FILE !!! \n");
    }
    else
    {
        curAddr = addr;
        fileSize = 0;

        while(1)
        {
            if(chunkSize > readSize)
            {
                chunkSize = readSize;
            }

            File_read(hndlFile, curAddr, chunkSize, &readDataSize);
            fileSize += readDataSize;
            if(chunkSize != readDataSize
                ||
               readSize==fileSize
                )
            {
                break;
            }
            curAddr += chunkSize;
        }

        Vps_printf(" FILE: File read Done. [%d bytes] \r\n", fileSize);

        File_close(hndlFile);

        *actualReadSize = fileSize;
    }

    return retVal;
}

Int32 Utils_fileWriteFile(char *fileName, Uint8 *addr, Uint32 size)
{
    Int32 retVal = 0;
    UInt32 writeDataSize;
    Int32 hndlFile;

    Vps_printf(" FILE: Writing to file [%s] (%d bytes) ... ", fileName, size);

    hndlFile = File_open(fileName, "wb");

    if(hndlFile < 0)
    {
        retVal = SYSTEM_LINK_STATUS_EFAIL;
        Vps_printf(" FILE: ERROR: Could not open FILE !!! \n");
    }
    else
    {
        /* write in units of chunkSize */
        Int32 fileSize, chunkSize = 96*1024;
        UInt8  *curAddr;

        fileSize = size;
        curAddr  = addr;

        while(fileSize>0)
        {
            if(fileSize<chunkSize)
            {
                chunkSize = fileSize;
            }

            retVal = File_write(hndlFile, curAddr, (UInt32)chunkSize);
            if(retVal!=0)
            {
                /* error in writing, abort */
                break;
            }

            curAddr += chunkSize;
            fileSize -= chunkSize;
        }
        writeDataSize = size - fileSize;

        Vps_printf(" FILE: File write done. [%d bytes] \r\n", writeDataSize);
        File_close(hndlFile);
    }

    return retVal;
}

static Int32 Utils_fileCioReadFile(char *fileName, UInt8 *addr, UInt32 readSize, Uint32 *actualReadSize)
{
    Int32 retVal = 0;
    UInt8  *curAddr;

    UInt32 readDataSize, fileSize;
    UInt32 chunkSize = (1024U*100U);

    FILE *hndlFile;

    /* MISRA.STDLIB.STDIO
     * MISRAC_2004 Rule_20.9
     * This function can use printf,fopen functions for debug purpose..
     */
    printf(" FILE: Reading file [%s] ... \n", fileName);

    /* MISRA.STDLIB.STDIO
     * MISRAC_2004 Rule_20.9
     * This function can use printf,fopen functions for debug purpose..
     */
    hndlFile = fopen(fileName, "rb");

    if(hndlFile == NULL)
    {
        retVal = SYSTEM_LINK_STATUS_EFAIL;
        *actualReadSize=0;
        /* MISRA.STDLIB.STDIO
         * MISRAC_2004 Rule_20.9
         * This function can use printf,fopen functions for debug purpose..
         */
        printf(" FILE: ERROR: Could not open FILE !!! \n");
    }
    else
    {
        /* MISRA.EXPANSION.UNSAFE
         * MISRA C 20.1, 20.5, 20.6, 20.7
         * MISRAC_WAIVER:
         * This is a requirement of this API and cannot be avoided
         */
        /* MISRA.STDLIB.STDIO
         * MISRAC_2004 Rule_20.9
         * This function can use printf,fopen functions for debug purpose..
         */
        setvbuf(hndlFile, NULL, _IONBF, 0); /* turn off buffering */

        curAddr = addr;
        fileSize = 0;

        while(1)
        {
            if(chunkSize > readSize)
            {
                chunkSize = readSize;
            }

            /* MISRA.STDLIB.STDIO
             * MISRAC_2004 Rule_20.9
             * This function can use printf,fopen functions for debug purpose..
             */
            readDataSize = fread(curAddr, (size_t)1, (size_t)chunkSize, hndlFile);
            fileSize += readDataSize;
            if((chunkSize != readDataSize)
                ||
               (readSize==fileSize)
                )
            {
                break;
            }

            /* MISRA.PTR.ARITH
             * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:Pointer is used in
             *                                             arithmetic or array
             *                                             index expression
             *
             * Pointer arithmetic is required for functional operation of the logic
             */
            curAddr += chunkSize;
        }

        /* MISRA.STDLIB.STDIO
         * MISRAC_2004 Rule_20.9
         * This function can use printf,fopen functions for debug purpose..
         */
        printf(" FILE: File read Done. [%d bytes] \r\n", fileSize);

        /* MISRA.STDLIB.STDIO
         * MISRAC_2004 Rule_20.9
         * This function can use printf,fopen functions for debug purpose..
         */
        fclose(hndlFile);

        *actualReadSize = fileSize;
    }

    return retVal;
}

static Int32 Utils_fileCioWriteFile(char *fileName, Uint8 *addr, Uint32 size)
{
    Int32 retVal = 0;
    UInt32 writeDataSize;
    FILE *hndlFile;

    /* MISRA.STDLIB.STDIO
     * MISRAC_2004 Rule_20.9
     * This function can use printf,fopen functions for debug purpose..
     */
    printf(" FILE: Writing to file [%s] (%d bytes) ... \r\n", fileName, size);

    /* MISRA.STDLIB.STDIO
     * MISRAC_2004 Rule_20.9
     * This function can use printf,fopen functions for debug purpose..
     */
    hndlFile = fopen(fileName, "wb");
    if(hndlFile == NULL )
    {
        retVal = SYSTEM_LINK_STATUS_EFAIL;
        /* MISRA.STDLIB.STDIO
         * MISRAC_2004 Rule_20.9
         * This function can use printf,fopen functions for debug purpose..
         */
        printf(" FILE: ERROR: Could not open FILE !!! \n");
    }
    else
    {
        /* MISRA.EXPANSION.UNSAFE
         * MISRA C 20.1, 20.5, 20.6, 20.7
         * MISRAC_WAIVER:
         * This is a requirement of this API and cannot be avoided
         */

        /* MISRA.STDLIB.STDIO
         * MISRAC_2004 Rule_20.9
         * This function can use printf,fopen functions for debug purpose..
         */
        setvbuf(hndlFile, NULL, _IONBF, 0); /* turn off buffering */

        /* write in units of chunkSize */
        UInt32 fileSize, bytesWritten;
        UInt32 chunkSize = (96U*1024U);
        UInt8  *curAddr;

        fileSize = size;
        curAddr  = addr;

        while(fileSize>0)
        {
            if(fileSize<chunkSize)
            {
                chunkSize = fileSize;
            }

            bytesWritten = fwrite(curAddr, (size_t)1, (size_t)chunkSize, hndlFile);
            if(bytesWritten!=chunkSize)
            {
                retVal = SYSTEM_LINK_STATUS_EFAIL;
                /* error in writing, abort */
                break;
            }

            /* MISRA.PTR.ARITH
             * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:Pointer is used in
             *                                             arithmetic or array
             *                                             index expression
             *
             * Pointer arithmetic is required for functional operation of the logic
             */
            curAddr += (UInt32)chunkSize;
            fileSize -= chunkSize;
        }
        writeDataSize = size - fileSize;

        /* MISRA.STDLIB.STDIO
         * MISRAC_2004 Rule_20.9
         * This function can use printf,fopen functions for debug purpose..
         */
        fclose(hndlFile);
        /* MISRA.STDLIB.STDIO
         * MISRAC_2004 Rule_20.9
         * This function can use printf,fopen functions for debug purpose..
         */
        printf(" FILE: File write done. [%d bytes] \r\n", writeDataSize);
    }

    return retVal;
}

#define UTILS_FILE_TEST_BUF_SIZE        (42U*1024U*1024U)

void Utils_fileTestRun(void)
{
    Ptr pBuf;
    Int32 status;
    UInt32 fileSize;

    pBuf = Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                UTILS_FILE_TEST_BUF_SIZE,
                4U);
    UTILS_assert(pBuf!=NULL);

    #if 1
    status = Utils_fileReadFile("AppImage", (UInt8*)pBuf, UTILS_FILE_TEST_BUF_SIZE, &fileSize);
    if(status==0)
    {
        Utils_fileWriteFile("AppImage.OUT", pBuf, fileSize);
    }
    #endif
    #if 1
    status = Utils_fileCioReadFile("sd:AppImage", (UInt8*)pBuf, UTILS_FILE_TEST_BUF_SIZE, &fileSize);
    if(status==0)
    {
        Utils_fileCioWriteFile("sd:AppImage.OUT", pBuf, fileSize);
    }
    #endif

    status = Utils_memFree(
        UTILS_HEAPID_DDR_CACHED_SR,
        pBuf,
        UTILS_FILE_TEST_BUF_SIZE
    );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);
}

