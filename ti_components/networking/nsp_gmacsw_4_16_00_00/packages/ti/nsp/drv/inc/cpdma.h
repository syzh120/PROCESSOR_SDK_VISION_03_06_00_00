/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
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
 */

/*!
 *   \file  cpdma.h
 *
 *   \brief
 *      Header file for CPPI v3.1 definitions.
 *
 */


#ifndef CPDMA_H_
#define CPDMA_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>

/* Project dependency headers */


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* Success and error return codes */
#define CPDMA_SUCCESS                               ((uint32_t)0x00000000U)
#define CPDMA_FAILURE                               ((uint32_t)0xFFFFFFFFU)
#define CPDMA_UNKNOWN_IOCTL                         ((uint32_t)0x00000001U)
#define CPDMA_MALFORMED_IOCTL                       ((uint32_t)0x00000002U)
#define CPDMA_NO_RX_CHANNELS_AVAILABLE              ((uint32_t)0x00000003U)
#define CPDMA_NO_TX_CHANNELS_AVAILABLE              ((uint32_t)0x00000004U)
#define CPDMA_INSUFFICENT_BUFF_DESC                 ((uint32_t)0x00000005U)
#define CPDMA_CHANNEL_NOT_OPEN                      ((uint32_t)0x00000006U)
#define CPDMA_INVALID_PARAM                         ((uint32_t)0x00000007U)


/*!
 *  \defgroup   CPDMA Configuration Mode Flags
 *
 * @{
 */
#define CPDMA_CONFIG_MODEFLG_CHPRIORITY      0x00001U
/*!< Use Tx channel priority                                                */
#define CPDMA_CONFIG_MODEFLG_RXCRC           0x00004U
/*!< Include CRC in RX frames                                               */
#define CPDMA_CONFIG_MODEFLG_TXCRC           0x00008U
/*!< Tx frames include CRC                                                  */
#define CPDMA_CONFIG_MODEFLG_PASSERROR       0x00010U
/*!< Pass error frames                                                      */
#define CPDMA_CONFIG_MODEFLG_PASSCONTROL     0x00020U
/*!< Pass control frames                                                    */
#define CPDMA_CONFIG_MODEFLG_PASSALL         0x00040U
/*!< pass all frames                                                        */
#define CPDMA_CONFIG_MODEFLG_RXQOS           0x00080U
/*!< Enable QOS at receive side                                             */
#define CPDMA_CONFIG_MODEFLG_RXNOCHAIN       0x00100U
/*!< Select no buffer chaining                                              */
#define CPDMA_CONFIG_MODEFLG_RXOFFLENBLOCK   0x00200U
/*!< Enable offset/length blocking                                          */
#define CPDMA_CONFIG_MODEFLG_RXOWNERSHIP     0x00400U
/*!< Use ownership bit as 1                                                 */
#define CPDMA_CONFIG_MODEFLG_RXFIFOFLOWCNTL  0x00800U
/*!< Enable rx fifo flow control                                            */
#define CPDMA_CONFIG_MODEFLG_CMDIDLE         0x01000U
/*!< Enable IDLE command                                                    */
#define CPDMA_CONFIG_MODEFLG_TXSHORTGAPEN    0x02000U
/*!< Enable tx short gap                                                    */
#define CPDMA_CONFIG_MODEFLG_TXPACE          0x04000U
/*!< Enable tx pacing                                                       */
#define CPDMA_CONFIG_MODEFLG_TXFLOWCNTL      0x08000U
/*!< Enable tx flow control                                                 */
#define CPDMA_CONFIG_MODEFLG_RXBUFFERFLOWCNTL    0x10000U
/*!< Enable rx buffer flow control                                          */
/*! @} */

/*!
 * \brief
 *  CPPI Buffer descriptor flags/masks.
 *
 * \details
 *  The following is an enumeration collection of flags and masks
 *  for use with CPPI buffer descriptors
 */
#define CPDMA_BUF_DESC_SOP_FLAG              (0x80000000U)
#define CPDMA_BUF_DESC_EOP_FLAG              (0x40000000U)
#define CPDMA_BUF_DESC_OWNER_FLAG            (0x20000000U)
#define CPDMA_BUF_DESC_EOQ_FLAG              (0x10000000U)
#define CPDMA_BUF_DESC_TDOWNCMPLT_FLAG       (0x08000000U)
#define CPDMA_BUF_DESC_PASSCRC_FLAG          (0x04000000U)
#define CPDMA_BUF_DESC_RX_LONG_FLAG          (0x02000000U)
#define CPDMA_BUF_DESC_RX_SHORT_FLAG         (0x01000000U)
#define CPDMA_BUF_DESC_RX_MAC_CTL_FLAG       (0x00800000U)
#define CPDMA_BUF_DESC_RX_OVERRUN_FLAG       (0x00400000U)
#define CPDMA_BUF_DESC_RX_PKT_ERR_MASK       (0x00300000U)
#define CPDMA_BUF_DESC_RX_VLAN_ENCAP_MASK    (0x00080000U)
#define CPDMA_BUF_DESC_RX_FROM_PORT_MASK     (0x00070000U)
#define CPDMA_BUF_DESC_RX_FROM_PORT_SHIFT    ((uint32_t)0x10U)
#define CPDMA_BUF_DESC_TX_TO_PORT_EN_FLAG    (0x00100000U)
#define CPDMA_BUF_DESC_TX_TO_PORT_MASK       (0x00030000U)
#define CPDMA_BUF_DESC_TX_TO_PORT_SHIFT      ((uint32_t)0x10U)

/* Calculate buffer descriptor total count for internal CPPI memory */
#define GMACSW_CPPI_MEM_SIZE            ((uint32_t) 0x2000U)
#define GMACSW_CPPI_DSC_ENTRY_SIZE      ((uint32_t) sizeof(CPDMA_BuffDesc))
#define CPDMA_CPPI_BUF_DESC_MAX_COUNT   (GMACSW_CPPI_MEM_SIZE/GMACSW_CPPI_DSC_ENTRY_SIZE)

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/



/*!
 * \brief
 *      CPPI Buffer Descriptor format.
 *
 * \details
 *      The following is the format of a single buffer descriptor
 *      for the CPDMA.
 */
typedef struct CPDMA_BUFF_DESC_
{
    /*!
     * \brief        Pointer to next descriptor in chain.
     */
    struct CPDMA_BUFF_DESC_ *pNextBufferDescriptor;
    /*!
     * \brief        Pointer to data buffer.
     */
    uint8_t *pDataBuffer;
    /*!
     * \brief        Buffer Offset (MSW) and Length (LSW)
     */
    uint32_t bufferOffsetAndLength;
    /*!
     * \brief        Buffer Descriptor Flags (MSW) and Packet Length (LSW)
     */
    uint32_t flagsAndPacketLength;
}
CPDMA_BuffDesc, *CPDMA_BuffDescHandle;

/*!
 * \brief
 *      CPPI Buffer Descriptor Queue
 *
 * \details
 *      The following is a structure that defines a chain of buffer descriptors
 *      for the CPDMA.
 */
typedef struct CPDMA_BUFF_DESC_QUEUE_
{
    /*!
     * \brief        Count of elements in the buffer descriptor queue
     */
    uint32_t count;
    /*!
     * \brief        Pointer to the front of the buffer descriptor queue
     */
    CPDMA_BuffDesc *pHead;
    /*!
     * \brief        Pointer to the back of the buffer descriptor queue
     */
    CPDMA_BuffDesc *pTail;
}
CPDMA_BuffDescQueue;

/*!
 * \brief
 *      CPPI Packet.
 *
 * \details
 *      The following is the format of a single packet to be transmitted
 *      via the CPDMA. For the CPDMA, a packets consists of one or more
 *      buffer descriptors, linked in a chain (or queue).  The first buffer
 *      descriptor is the Start-Of-Packet (SOP) descriptor, and the last
 *      buffer descriptor is the End-Of-Packet descriptor.
 */
typedef struct CPDMA_PACKET_
{
    /*!
     * \brief  Pointer to next packet in the queue.
     */
    struct CPDMA_PACKET_    *pNextPacket;
    /*!
     * \brief  Pointer to application layer specific data blob
     */
    void                    *hPrivate;
    /*!
     * \brief  Buffer descriptor queue/chain that makes up the packet
     */
    CPDMA_BuffDescQueue     buffDescQueue;
}
CPDMA_Packet;

/*!
 * \brief Packet Queue
 *
 * \details
 *      A queue of packets, which are use for managing the active queue of
 *      of packets given to the hardware driver.  Can alos be used by the
 *      translation/application layer to manage packets that are not
 *      currently active.
 *
 */
typedef struct CPDMA_PACKET_QUEUE_
{
    uint32_t            count;
    /*!< Number of packets in queue                                           */
    CPDMA_Packet        *pHead;
    /*!< Pointer to first packet                                              */
    CPDMA_Packet        *pTail;
    /*!< Pointer to last packet                                               */
}
CPDMA_PacketQueue;

/*!
 * \brief Callback function types
 *
 * \details
 *      Callback function typedefs so that the CPDMA layer can call into the app layer
 *      and let it translate between the hardware buffer descriptors and packets and the
 *      stack/translation layer's buffers and packets.
 */
typedef void            (*CPDMA_UsedPacketNotifyCallback)(void * hCallbackArg);
/*!< Packet notify call back                                           */
typedef void            (*CPDMA_CloseChannelCallback)(void * hCallbackArg);
/*!< Close Channel call back                                           */

/*!
 * \brief Callback function types
 *
 * \details
 *      Callback function typedefs so that the CPDMA layer can call into the app layer
 *      and let it translate between the hardware buffer descriptors and packets and the
 *      stack/translation layer's buffers and packets.
 */
typedef struct CPDMA_CALLBACKS_
{
    /*!
     * \brief  Pointer to the close callback function for this channel
     */
    CPDMA_CloseChannelCallback      pFxnCbCloseChannel;
    /*!
     * \brief  Pointer to the notify packets callback function for this channel
     */
    CPDMA_UsedPacketNotifyCallback  pFxnCbUsedPacketNotify;
    /*!
     * \brief  Argument to be used for the callback routines (it should mean something to
     *         layer into which the callback calls)
     */
    void                            *hCallbackArg;
}
CPDMA_Callbacks;

/*!
 *  \addtogroup GMACSW_CONFIG_DEFINTIONS
 *
 *  @{
 *
 *  \defgroup CPDMA_CONFIG_DEFINITIONS CPDMA Configuration Definitions
 *
 *  This group contains structure and type definitions needed to properly construct the CPDMA
 *  configuration structure which is part of the top-level GMACSW configuration structure.
 *
 *  @{
 */

/*!
 * \brief CPDMA buffer descriptor memory config
 *
 * \details
 *      Structure to used to configure the CPMDA buffer descriptor memory.
 *      GMACSS has internal 8KB CPPI RAM which will be used if
 *      CPDMA_buffDescMemConfig is not provided.
 */
typedef struct CPDMA_BUFF_DESC_MEM_
{
    /*!
     * \brief  Total no. of buffer descriptors in this memory
     */
    uint32_t buffDescCnt;
    /*!
     * \brief  Pointer to memory to be used for the allocated packets.
     *         NOTE1: The application must ensure that the memory pointed
     *               to is sufficient to contain 'buffDescCnt' copies of the
     *               CPDMA_BUFF_DESC_ structure.
     *         NOTE2: The application must ensure that the memory pointed is
     *                NON-CACHEABLE.
     */
    CPDMA_BuffDesc            *buffDescMem;
}CPDMA_buffDescMemConfig;

/*!
 * \brief CPDMA Init Configuration
 *
 * \details
 *      Configuration information for the CPDMA provided during initialization.
 *
 */
typedef struct CPDMA_MODULE_CONFIG_
{
    /*! Port VLAN priority (7 is highest)                                    */
    uint8_t         portPri;

    /*! Port CFI bit                                                         */
    uint8_t         portCfi;

    /*! Port CFI bit                                                         */
    uint32_t        portVID;

    /*! Receive buffer offset                                                */
    uint32_t        rxBufferOffset;

    uint32_t        PktMTU;

    /*! CPDMA ICLK frequency for interrupt pacing */
    uint32_t        pacingClkFreq;

    uint32_t        rxInterruptPacingEnabled;
    uint32_t        rxInterruptsPerMsec;

    uint32_t        txInterruptPacingEnabled;
    uint32_t        txInterruptsPerMsec;

    /*! CPDMA buffer descriptor configuration */
    CPDMA_buffDescMemConfig buffDescMemCfg;

    /*!Register control fields                                                */
    /* DMA Control register                                                   */
    uint32_t        dmaModeFlags;
    /*!< Configuation Mode Flags                                              */
}
CPDMA_Config;

/*!
 * @}
 * @}
 */

/*!
 * \brief CPDMA Channel Handle
 *
 * \details
 *      Opaque structure to hold software state for the CPDMA hardware channel.
 *
 */
typedef struct CPDMA_CHANNEL_ *CPDMA_ChannelHandle;

/*!
 * \brief CPDMA State Handle
 *
 * \details
 *      Opaque structure to hold software state for the CPDMA hardware.
 *
 */
typedef struct CPDMA_STATE_ *CPDMA_Handle;

/*!
 *  \addtogroup  GMACSW_IOCTLS
 *
 *  @{
 */

/*!
 *  \brief  The CPDMA module IOCTL enums
 */
enum CPDMA_IOCTL_
{
    GMACSW_IOCTL_CPDMA_BASE             = 0x00040000,
    /*! CPDMA open receive channel IOCTL value. IOCTL param should be a structure of type CPDMA_OpenRxChannelIoctlCmd. */
    GMACSW_IOCTL_CPDMA_OPEN_RX_CHANNEL  = 0x00040000,
    /*! CPDMA close receive channel IOCTL value. IOCTL param should be a handle of type CPDMA_ChannelHandle, returned from the CPDMA open receive channel IOCTL call. */
    GMACSW_IOCTL_CPDMA_CLOSE_RX_CHANNEL = 0x00040001,
    /*! CPDMA start receive channel IOCTL value. IOCTL param should be a handle of type CPDMA_ChannelHandle, returned from the CPDMA open receive channel IOCTL call. */
    GMACSW_IOCTL_CPDMA_START_RX_CHANNEL = 0x00040002,
    /*! CPDMA stop receive channel IOCTL value. IOCTL param should be a handle of type CPDMA_ChannelHandle, returned from the CPDMA open receive channel IOCTL call. */
    GMACSW_IOCTL_CPDMA_STOP_RX_CHANNEL  = 0x00040003,
    /*! CPDMA open transmit channel IOCTL value. IOCTL param should be a structure of type CPDMA_OpenTxChannelIoctlCmd. */
    GMACSW_IOCTL_CPDMA_OPEN_TX_CHANNEL  = 0x00040004,
    /*! CPDMA close transmit channel IOCTL value. IOCTL param should be a handle of type CPDMA_ChannelHandle, returned from the CPDMA open transmit channel IOCTL call. */
    GMACSW_IOCTL_CPDMA_CLOSE_TX_CHANNEL = 0x00040005,
    /*! CPDMA start transmit channel IOCTL value. IOCTL param should be a handle of type CPDMA_ChannelHandle, returned from the CPDMA open transmit channel IOCTL call. */
    GMACSW_IOCTL_CPDMA_START_TX_CHANNEL = 0x00040006,
    /*! CPDMA stop transmit channel IOCTL value. IOCTL param should be a handle of type CPDMA_ChannelHandle, returned from the CPDMA open transmit channel IOCTL call. */
    GMACSW_IOCTL_CPDMA_STOP_TX_CHANNEL  = 0x00040007,
    /*! CPDMA retrieve packets from hardware IOCTL value. IOCTL param should be a structure of type CPDMA_RetrievePacketQueueIoctlCmd. */
    GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS = 0x00040008,
    /*! CPDMA submit packets to hardware IOCTL value. IOCTL param should be a structure of type CPDMA_SubmitPacketQueueIoctlCmd. */
    GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS   = 0x00040009
};

/*!
 * \brief Receive Channel Config Structure
 *
 * \details
 *      Structure to use to configure the receive channel at channel open time.
 *
 */
typedef struct CPDMA_RX_CHANNEL_CONFIG_
{
    /*!
     * \brief  Number of packets allocated for this channel
     */
    uint32_t        packetCount;
    /*!
     * \brief  Number of buffers used per packet for this channel
     */
    uint32_t        buffersPerPacketCount;
    /*!
     * \brief  Pointer to memory to be used for the allocated packets.
     *         NOTE: The application must ensure that the memory pointed
     *               to is sufficient to contain 'packetCount' copies of the
     *               CPDMA_Packet structure.
     */
    void            *packetMem;
    /*!
     * \brief  Free buffer descriptors count threshold to trigger an RX_THRESH interrupt.
     *         Set to zero for no threshold interrupt enablement. Must be less than
     *         'packetCount' * 'buffersPerPacketCount'.
     */
    uint32_t        rxThreshCount;
    /*!
     * \brief  Callback structure for this channel
     */
    CPDMA_Callbacks callbacks;
}
CPDMA_RxChannelConfig;

/*!
 * \brief Transmit Channel Config Structure
 *
 * \details
 *      Structure to use to configure the transmit channel at channel open time.
 *
 */
typedef struct CPDMA_TX_CHANNEL_CONFIG_
{
    /*!
     * \brief  Number of packets allocated for this channel
     */
    uint32_t        packetCount;
    /*!
     * \brief  Number of buffers used per packet for this channel
     */
    uint32_t        buffersPerPacketCount;
    /*!
     * \brief  Pointer to memory to be used for the allocated packets.
     *         NOTE: The application must ensure that the memory pointed
     *               to is sufficient to contain 'packetCount' copies of the
     *               CPDMA_Packet structure.
     */
    void            *packetMem;
    /*!
     * \brief  Callback structure for this channel
     */
    CPDMA_Callbacks callbacks;
}
CPDMA_TxChannelConfig;

/*!
 * \brief Param struct for the Rx channel open IOCTL
 *
 * \details
 *      The Param struct for the Rx channel open IOCTL, containing a pointer
 *      to the channel config structure and a pointer to a channel handle
 *      variable, which will be filled in by the IOCTL. The returned
 *      channel handle is an opaque variable used to access the channel in
 *      other IOCTL commands.
 *
 */
typedef struct CPDMA_OPEN_RX_CHANNEL_IOCTL_CMD_
{
    CPDMA_RxChannelConfig   *pRxChannelConfig;
    CPDMA_ChannelHandle     *pRxChannelHandle;
}
CPDMA_OpenRxChannelIoctlCmd;

/*!
 * \brief Param struct for the Tx channel open IOCTL
 *
 * \details
 *      The Param struct for the Tx channel open IOCTL, containing a pointer
 *      to the channel config structure and a pointer to a channel handle
 *      variable, which will be filled in by the IOCTL. The returned
 *      channel handle is an opaque variable used to access the channel in
 *      other IOCTL commands.
 *
 */
typedef struct CPDMA_OPEN_TX_CHANNEL_IOCTL_CMD_
{
    CPDMA_TxChannelConfig   *pTxChannelConfig;
    CPDMA_ChannelHandle     *pTxChannelHandle;
}
CPDMA_OpenTxChannelIoctlCmd;

/*!
 * \brief Param struct for the retrieve packet queue IOCTL
 *
 * \details
 *      The param struct for the retrieve packet queue IOCTL, containing
 *      the channel handle for the channel we wish to retrieve from, and
 *      a pointer to a packet queue, which will contain the queue of all
 *      the packets retrieved from the channel.
 *
 */
typedef struct CPDMA_RETRIEVE_PACKET_QUEUE_IOCTL_CMD_
{
    CPDMA_ChannelHandle     hChannel;
    CPDMA_PacketQueue       *pFromChannelQueue;
}
CPDMA_RetrievePacketQueueIoctlCmd;

/*!
 * \brief Param struct for the submit packet queue IOCTL
 *
 * \details
 *      The param struct for the submit packet queue IOCTL, containing
 *      the channel handle for the channel we wish to submit to, and
 *      a pointer to a packet queue containing all the packets to be
 *      submitted to the channel.
 *
 */
typedef struct CPDMA_SUBMIT_PACKET_QUEUE_IOCTL_CMD_
{
    CPDMA_ChannelHandle     hChannel;
    CPDMA_PacketQueue       *pToChannelQueue;
}
CPDMA_SubmitPacketQueueIoctlCmd;

/*!
 * @}
 */


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|                   Global Inline Function Declarations                       |
\*---------------------------------------------------------------------------*/

static inline void CPDMA_buffDescInit(volatile CPDMA_BuffDesc *pCPDMABuffDesc);
static inline void CPDMA_terminateBufferList(volatile CPDMA_BuffDesc *pDesc);
static inline void CPDMA_extendBufferList(volatile CPDMA_BuffDesc *pThis, CPDMA_BuffDesc *pNext);
static inline void CPDMA_setDataBuffer(volatile CPDMA_BuffDesc *pDesc, uint8_t *pDataBuffer);
static inline uint8_t *CPDMA_getDataBuffer(volatile const CPDMA_BuffDesc *pDesc);
static inline void CPDMA_setBufferLength(volatile CPDMA_BuffDesc *pDesc, uint16_t bufferLength);
static inline uint16_t CPDMA_getBufferLength(volatile const CPDMA_BuffDesc *pDesc);
static inline void CPDMA_setBufferOffset(volatile CPDMA_BuffDesc *pDesc, uint16_t bufferOffset);
static inline uint16_t CPDMA_getBufferOffset(volatile const CPDMA_BuffDesc *pDesc);
static inline void CPDMA_setPacketLength(volatile CPDMA_BuffDesc *pDesc, uint16_t packetLength);
static inline uint16_t CPDMA_getPacketLength(volatile const CPDMA_BuffDesc *pDesc);
static inline void CPDMA_setStartOfPacket(volatile CPDMA_BuffDesc *pDesc);
static inline void CPDMA_clearStartOfPacket(volatile CPDMA_BuffDesc *pDesc);
static inline uint32_t CPDMA_isStartOfPacket(volatile const CPDMA_BuffDesc *pDesc);
static inline void CPDMA_setEndOfPacket(volatile CPDMA_BuffDesc *pDesc);
static inline void CPDMA_clearEndOfPacket(volatile CPDMA_BuffDesc *pDesc);
static inline uint32_t CPDMA_isEndOfPacket(volatile const CPDMA_BuffDesc *pDesc);
static inline void CPDMA_clearEndOfQueue(volatile CPDMA_BuffDesc *pDesc);
static inline uint32_t CPDMA_isEndOfQueue(volatile const CPDMA_BuffDesc *pDesc);
static inline void CPDMA_setHardwareAsOwner(volatile CPDMA_BuffDesc *pDesc);
static inline void CPDMA_clearHardwareAsOwner(volatile CPDMA_BuffDesc *pDesc);
static inline uint32_t CPDMA_isHardwareOwner(volatile const CPDMA_BuffDesc *pDesc);
static inline void CPDMA_setTxToPort(volatile CPDMA_BuffDesc *pDesc, uint32_t portNum);
static inline uint32_t CPDMA_getRxFromPort(volatile const CPDMA_BuffDesc *pDesc);
static inline void CPDMA_setDescriptorFlags(volatile CPDMA_BuffDesc *pDesc, uint32_t flags);
static inline uint32_t CPDMA_getDescriptorFlags(volatile const CPDMA_BuffDesc *pDesc);
static inline void CPDMA_buffDescQueueInit(CPDMA_BuffDescQueue *pCPDMABuffDescQueue);
static inline uint32_t CPDMA_getBuffDescQueueCount(const CPDMA_BuffDescQueue *pCPDMABuffDescQueue);
static inline void CPDMA_packetInit(CPDMA_Packet *pCPDMAPacket);
static inline CPDMA_BuffDesc *CPDMA_packetGetFirstDesc(const CPDMA_Packet *pCPDMAPacket);
static inline CPDMA_BuffDesc *CPDMA_packetGetLastDesc(const CPDMA_Packet *pCPDMAPacket);
static inline uint32_t CPDMA_packetGetDescCount(const CPDMA_Packet *pCPDMAPacket);
static inline uint32_t CPDMA_isPacketOwnedByHardware(const CPDMA_Packet *pCPDMAPacket);
static inline uint32_t CPDMA_isPacketEndOfQueue(const CPDMA_Packet *pCPDMAPacket);
static inline uint32_t CPDMA_packetGetLength(const CPDMA_Packet *pCPDMAPacket);
static inline void CPDMA_packetQueueInit(CPDMA_PacketQueue *pCPDMAPacketQueue);
static inline void CPDMA_packetQueueCopy(CPDMA_PacketQueue *pCPDMAPacketQueueDest, const CPDMA_PacketQueue *pCPDMAPacketQueueSrc);
static inline void CPDMA_appendPacketQueue(CPDMA_PacketQueue *pCPDMAPacketQueueDest, const CPDMA_PacketQueue *pCPDMAPacketQueueSrc);
static inline CPDMA_Packet *CPDMA_getFirstPacketOfPacketQueue(const CPDMA_PacketQueue *pCPDMAPacketQueue);
static inline CPDMA_Packet *CPDMA_getLastPacketOfPacketQueue(const CPDMA_PacketQueue *pCPDMAPacketQueue);
static inline uint32_t CPDMA_getPacketQueueCount(const CPDMA_PacketQueue *pCPDMAPacketQueue);

/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/

/*!
 * \defgroup CPDMA_HELPERS CPDMA Helper Routines
 *
 * @{
 */

/* ------------------------- Buffer Descriptor operations -------------------------- */

/*!
 * \defgroup CPDMA_HELPERS_BUFF_DESC CPDMA Buffer Descriptor Helpers
 * @{
 */

/*! Zero init the buffer descriptor */
static inline void CPDMA_buffDescInit(volatile CPDMA_BuffDesc *pCPDMABuffDesc)
{
    pCPDMABuffDesc->pNextBufferDescriptor   = (CPDMA_BuffDesc *) NULL;
    pCPDMABuffDesc->pDataBuffer             = 0x00000000U;
    pCPDMABuffDesc->bufferOffsetAndLength   = 0x00000000U;
    pCPDMABuffDesc->flagsAndPacketLength    = 0x00000000U;
}

/*! Set the buffer descriptor next pointer to NULL */
static inline void CPDMA_terminateBufferList(volatile CPDMA_BuffDesc *pDesc)
{
    pDesc->pNextBufferDescriptor = (CPDMA_BuffDesc *) NULL;
}

/*! Set the buffer descriptor next pointer to the pNext descriptor  */
static inline void CPDMA_extendBufferList(volatile CPDMA_BuffDesc *pThis, CPDMA_BuffDesc *pNext)
{
    pThis->pNextBufferDescriptor = pNext;
}

/*! Set the data buffer pointer in the descriptor */
static inline void CPDMA_setDataBuffer(volatile CPDMA_BuffDesc *pDesc, uint8_t *pDataBuffer)
{
    pDesc->pDataBuffer = pDataBuffer;
}

/*! Get the data buffer pointer from the descriptor */
static inline uint8_t *CPDMA_getDataBuffer(volatile const CPDMA_BuffDesc *pDesc)
{
    return pDesc->pDataBuffer;
}

/*! Set the buffer length field in the descriptor */
static inline void CPDMA_setBufferLength(volatile CPDMA_BuffDesc *pDesc, uint16_t bufferLength)
{
    pDesc->bufferOffsetAndLength = (pDesc->bufferOffsetAndLength & 0xFFFF0000U) | bufferLength;
}

/*! Get the buffer length field from the descriptor */
static inline uint16_t CPDMA_getBufferLength(volatile const CPDMA_BuffDesc *pDesc)
{
    return (uint16_t) (pDesc->bufferOffsetAndLength & 0x0000FFFFU);
}

/*! Set the buffer offset field in the descriptor */
static inline void CPDMA_setBufferOffset(volatile CPDMA_BuffDesc *pDesc, uint16_t bufferOffset)
{
    pDesc->bufferOffsetAndLength = (uint32_t)(pDesc->bufferOffsetAndLength & 0x0000FFFFU) | (((uint32_t)bufferOffset) << (uint32_t)16U);
}

/*! Get the buffer offset field from the descriptor */
static inline uint16_t CPDMA_getBufferOffset(volatile const CPDMA_BuffDesc *pDesc)
{
    return (uint16_t) ((pDesc->bufferOffsetAndLength & 0xFFFF0000U) >> (uint32_t)16U);
}

/*! Set the packet length field in the descriptor */
static inline void CPDMA_setPacketLength(volatile CPDMA_BuffDesc *pDesc, uint16_t packetLength)
{
    pDesc->flagsAndPacketLength = (pDesc->flagsAndPacketLength & 0xFFFF0000U) | packetLength;
}

/*! Get the packet length field from the descriptor */
static inline uint16_t CPDMA_getPacketLength(volatile const CPDMA_BuffDesc *pDesc)
{
    return (uint16_t) (pDesc->flagsAndPacketLength & 0x0000FFFFU);
}

/*! Set the start of packet bit in the descriptor */
static inline void CPDMA_setStartOfPacket(volatile CPDMA_BuffDesc *pDesc)
{
    pDesc->flagsAndPacketLength |= CPDMA_BUF_DESC_SOP_FLAG;
}

/*! Clear the start of packet bit in the descriptor */
static inline void CPDMA_clearStartOfPacket(volatile CPDMA_BuffDesc *pDesc)
{
    pDesc->flagsAndPacketLength &= ~CPDMA_BUF_DESC_SOP_FLAG;
}

/*! Return if the start of packet bit is set in the descriptor */
static inline uint32_t CPDMA_isStartOfPacket(volatile const CPDMA_BuffDesc *pDesc)
{
    return (((pDesc->flagsAndPacketLength & CPDMA_BUF_DESC_SOP_FLAG) == 0U) ? 0U : 1U);
}

/*! Set the end of packet bit in the descriptor */
static inline void CPDMA_setEndOfPacket(volatile CPDMA_BuffDesc *pDesc)
{
    pDesc->flagsAndPacketLength |= CPDMA_BUF_DESC_EOP_FLAG;
}

/*! Clear the end of packet bit in the descriptor */
static inline void CPDMA_clearEndOfPacket(volatile CPDMA_BuffDesc *pDesc)
{
    pDesc->flagsAndPacketLength &= ~CPDMA_BUF_DESC_EOP_FLAG;
}

/*! Return if the end of packet bit is set in the descriptor */
static inline uint32_t CPDMA_isEndOfPacket(volatile const CPDMA_BuffDesc *pDesc)
{
    return (((pDesc->flagsAndPacketLength & CPDMA_BUF_DESC_EOP_FLAG) == 0U) ? 0U : 1U);
}

/*! Clear the end of queue bit in the descriptor */
static inline void CPDMA_clearEndOfQueue(volatile CPDMA_BuffDesc *pDesc)
{
    pDesc->flagsAndPacketLength &= ~CPDMA_BUF_DESC_EOQ_FLAG;
}

/*! Return if the end of queue bit is set in the descriptor */
static inline uint32_t CPDMA_isEndOfQueue(volatile const CPDMA_BuffDesc *pDesc)
{
    return (((pDesc->flagsAndPacketLength & CPDMA_BUF_DESC_EOQ_FLAG) == 0U) ? 0U : 1U);
}

/*! Set the OWNER bit in the descriptor */
static inline void CPDMA_setHardwareAsOwner(volatile CPDMA_BuffDesc *pDesc)
{
    pDesc->flagsAndPacketLength |= CPDMA_BUF_DESC_OWNER_FLAG;
}

/*! Clear the OWNER bit in the descriptor */
static inline void CPDMA_clearHardwareAsOwner(volatile CPDMA_BuffDesc *pDesc)
{
    pDesc->flagsAndPacketLength &= ~CPDMA_BUF_DESC_OWNER_FLAG;
}

/*! Return if the OWNER bit is set in the descriptor */
static inline uint32_t CPDMA_isHardwareOwner(volatile const CPDMA_BuffDesc *pDesc)
{
    return (((pDesc->flagsAndPacketLength & CPDMA_BUF_DESC_OWNER_FLAG) == 0U) ? 0U : 1U);
}

/*! Set the Tx To Port field in the descriptor */
static inline void CPDMA_setTxToPort(volatile CPDMA_BuffDesc *pDesc, uint32_t portNum)
{
    pDesc->flagsAndPacketLength &= ~CPDMA_BUF_DESC_TX_TO_PORT_MASK;
    pDesc->flagsAndPacketLength |=
        CPDMA_BUF_DESC_TX_TO_PORT_EN_FLAG |
        ((portNum << CPDMA_BUF_DESC_TX_TO_PORT_SHIFT) & CPDMA_BUF_DESC_TX_TO_PORT_MASK);
}

/*! Get Rx From Port field from the descriptor */
static inline uint32_t CPDMA_getRxFromPort(volatile const CPDMA_BuffDesc *pDesc)
{
    return ((pDesc->flagsAndPacketLength & CPDMA_BUF_DESC_RX_FROM_PORT_MASK) >> CPDMA_BUF_DESC_RX_FROM_PORT_SHIFT);
}

/*! Set all the descriptor flags in the descriptor */
static inline void CPDMA_setDescriptorFlags(volatile CPDMA_BuffDesc *pDesc, uint32_t flags)
{
    pDesc->flagsAndPacketLength = (uint32_t)(pDesc->flagsAndPacketLength & 0x0000FFFFU) | (uint32_t)(flags & 0xFFFF0000U);
}

/*! Get all the descriptor flags from the descriptor */
static inline uint32_t CPDMA_getDescriptorFlags(volatile const CPDMA_BuffDesc *pDesc)
{
    return (pDesc->flagsAndPacketLength & 0xFFFF0000U);
}

/*!
 * @}
 */


/* ------------------------- Buffer Descriptor Queue operations ------------------------- */

/*!
 * \defgroup CPDMA_HELPERS_BUFF_DESC_QUEUE CPDMA Buffer Descriptor Queue Helpers
 * @{
 */

/*! Zero init the buffer descriptor queue */
static inline void CPDMA_buffDescQueueInit(CPDMA_BuffDescQueue *pCPDMABuffDescQueue)
{
    pCPDMABuffDescQueue->pHead = NULL;
    pCPDMABuffDescQueue->pTail = NULL;
    pCPDMABuffDescQueue->count = 0;
}

/*! Get the count of buffer descriptors in the buffer descriptor queue */
static inline uint32_t CPDMA_getBuffDescQueueCount(const CPDMA_BuffDescQueue *pCPDMABuffDescQueue)
{
    return pCPDMABuffDescQueue->count;
}

/*!
 * @}
 */


/* ------------------------- Packet operations ------------------------- */

/*!
 * \defgroup CPDMA_HELPERS_PACKET CPDMA Packet Helpers
 * @{
 */

/*! Zero init the packet */
static inline void CPDMA_packetInit(CPDMA_Packet *pCPDMAPacket)
{
    pCPDMAPacket->pNextPacket   = NULL;
    pCPDMAPacket->hPrivate      = NULL;
    CPDMA_buffDescQueueInit(&pCPDMAPacket->buffDescQueue);
}

/*! Return the packet's start-of-packet (SOP) buffer descriptor */
static inline CPDMA_BuffDesc *CPDMA_packetGetFirstDesc(const CPDMA_Packet *pCPDMAPacket)
{
    return pCPDMAPacket->buffDescQueue.pHead;
}

/*! Return the packet's end-of-packet (EOP) buffer descriptor */
static inline CPDMA_BuffDesc *CPDMA_packetGetLastDesc(const CPDMA_Packet *pCPDMAPacket)
{
    return pCPDMAPacket->buffDescQueue.pTail;
}

/*! Return the count of buffer descriptors in the packet */
static inline uint32_t CPDMA_packetGetDescCount(const CPDMA_Packet *pCPDMAPacket)
{
    return pCPDMAPacket->buffDescQueue.count;
}

/*! Check if packet owned by hardware */
static inline uint32_t CPDMA_isPacketOwnedByHardware(const CPDMA_Packet *pCPDMAPacket)
{
    return CPDMA_isHardwareOwner(pCPDMAPacket->buffDescQueue.pHead);
}

/*! Check if the end-of-queue flag is set for this packet */
static inline uint32_t CPDMA_isPacketEndOfQueue(const CPDMA_Packet *pCPDMAPacket)
{
    return CPDMA_isEndOfQueue(pCPDMAPacket->buffDescQueue.pTail);
}

/*! Return the packet length (from the field in the SOP buffer descriptor) */
static inline uint32_t CPDMA_packetGetLength(const CPDMA_Packet *pCPDMAPacket)
{
    if (pCPDMAPacket != NULL)
    {
        if (pCPDMAPacket->buffDescQueue.pHead != NULL)
        {
            return (uint32_t)CPDMA_getPacketLength(pCPDMAPacket->buffDescQueue.pHead);
        }
    }

    return 0U;
}

/*!
 * @}
 */

/* ------------------------- Packet Queue operations ------------------------- */

/*!
 * \defgroup CPDMA_HELPERS_PACKET_QUEUE CPDMA Packet Queue Helpers
 * @{
 */

/*! Zero init the packet queue */
static inline void CPDMA_packetQueueInit(CPDMA_PacketQueue *pCPDMAPacketQueue)
{
    pCPDMAPacketQueue->pHead = NULL;
    pCPDMAPacketQueue->pTail = NULL;
    pCPDMAPacketQueue->count = 0;
}

/*! Shallow copy the packet queue to a new one */
static inline void CPDMA_packetQueueCopy(CPDMA_PacketQueue *pCPDMAPacketQueueDest, const CPDMA_PacketQueue *pCPDMAPacketQueueSrc)
{
    pCPDMAPacketQueueDest->pHead = pCPDMAPacketQueueSrc->pHead;
    pCPDMAPacketQueueDest->pTail = pCPDMAPacketQueueSrc->pTail;
    pCPDMAPacketQueueDest->count = pCPDMAPacketQueueSrc->count;
}

/*! Append the source packet queue to the end of the destination queue */
static inline void CPDMA_appendPacketQueue(CPDMA_PacketQueue *pCPDMAPacketQueueDest, const CPDMA_PacketQueue *pCPDMAPacketQueueSrc)
{
    if (pCPDMAPacketQueueDest->pHead == NULL)
    {
        /* Destination packet queue is empty, initialize it with the source packet queue */
        pCPDMAPacketQueueDest->pHead = pCPDMAPacketQueueSrc->pHead;
        pCPDMAPacketQueueDest->count = pCPDMAPacketQueueSrc->count;
    }
    else
    {
        /* Destination queue is not empty, add source queue contents onto end of the destination queue */
        pCPDMAPacketQueueDest->pTail->pNextPacket = pCPDMAPacketQueueSrc->pHead;
        pCPDMAPacketQueueDest->count += pCPDMAPacketQueueSrc->count;
    }
    pCPDMAPacketQueueDest->pTail = pCPDMAPacketQueueSrc->pTail;
}

/*! Return the packet queue head */
static inline CPDMA_Packet *CPDMA_getFirstPacketOfPacketQueue(const CPDMA_PacketQueue *pCPDMAPacketQueue)
{
    return pCPDMAPacketQueue->pHead;
}

/*! Return the packet queue tail */
static inline CPDMA_Packet *CPDMA_getLastPacketOfPacketQueue(const CPDMA_PacketQueue *pCPDMAPacketQueue)
{
    return pCPDMAPacketQueue->pTail;
}

/*! Get the count of packets in the packet queue */
static inline uint32_t CPDMA_getPacketQueueCount(const CPDMA_PacketQueue *pCPDMAPacketQueue)
{
    return pCPDMAPacketQueue->count;
}

/*!
 * @}
 */

/*!
 * @}
 */


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

extern CPDMA_Handle     CPDMA_open(CPDMA_Config *pCPDMAConfig);
extern uint32_t         CPDMA_close(CPDMA_Handle hCpdma);
extern uint32_t         CPDMA_ioctl(CPDMA_Handle hCpdma, uint32_t cmd, void *param, uint32_t size);

/*!
 * \addtogroup CPDMA_HELPERS
 * @{
 */

/*!
 * \addtogroup CPDMA_HELPERS_PACKET_QUEUE
 * @{
 */

/*! Enqueue a new packet to the tail of the packet queue */
extern void             CPDMA_packetEnqueue(CPDMA_PacketQueue *pCPDMAPacketQueue, CPDMA_Packet *pCPDMAPacket);

/*! Dequeue a new packet from the head of the packet queue */
extern CPDMA_Packet     *CPDMA_packetDequeue(CPDMA_PacketQueue *pCPDMAPacketQueue);

/*!
 * @}
 */

/*!
 * @}
 */


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CPDMA_H_ */


