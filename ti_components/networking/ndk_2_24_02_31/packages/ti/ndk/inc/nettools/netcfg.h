/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 * ======== netcfg.h ========
 *
 * Standard Configuration Structures
 *
 * Although the Configuration functions are generic, NETTOOLS expects
 * to be able to access a configuration with certain pre-defined
 * configuration tags.
 *
 * If a system needs to use the Service functions of NetTools, it must
 * provide service providers to implement the configuration specification
 * defined here.
 *
 */

#ifndef _C_NETCFG_INC
#define _C_NETCFG_INC

/* Note: *** Default Configuration Handle Required *** */
/* NetTools uses the default configuration handle for things like */
/* DHCP client, DHCP server, DNS, etc.. This handle should be */
/* set by calling CfgSetDefault() before using NetTools */

/*--------------------------------------------------------------------------- */
/* Defined Configuration Tags */
/*--------------------------------------------------------------------------- */
#define CFGTAG_OS               0x0001          /* OS Configuration */
#define CFGTAG_IP               0x0002          /* IP Stack Configuration */
#define CFGTAG_SERVICE          0x0003          /* Service */
#define CFGTAG_IPNET            0x0004          /* IP Network */
#define CFGTAG_ROUTE            0x0005          /* Gateway Route */
#define CFGTAG_CLIENT           0x0006          /* DHCPS Client */
#define CFGTAG_SYSINFO          0x0007          /* System Information */
#define CFGTAG_ACCT             0x0008          /* User Account */

/*--------------------------------------------------------------------------- */
/* Users *are* allowed to add their own tags, however the MAX tag value */
/* (CFGTAG_MAX) can not be altered without rebuilding the NETTOOLS library */
/*--------------------------------------------------------------------------- */
#define CFGTAG_MAX              0x0010

/*--------------------------------------------------------------------------- */
/* Configuration Item Values and Entry Data by Tag Value */
/*--------------------------------------------------------------------------- */

/*--------------------------------------------------------------------------- */
/* Config Tag: CFGTAG_SERVICE */
/*   List of active services */
/*     Item     = Service Type */
/*     Instance = Service Instance (1 to max) */
/* *** USERS CAN ADD THEIR OWN SERVICE ITEM VALUES *** */
#define CFGITEM_SERVICE_TELNET          0x0001
#define CFGITEM_SERVICE_HTTP            0x0002
#define CFGITEM_SERVICE_NAT             0x0003
#define CFGITEM_SERVICE_DHCPSERVER      0x0004
#define CFGITEM_SERVICE_DHCPCLIENT      0x0005
#define CFGITEM_SERVICE_DNSSERVER       0x0006
#define CFGITEM_SERVICE_MAX             0x0006

/* Common Service Arguments */
/* All services have a common argument structure which dictates their */
/* operation under certain circumstances. Also, the use can install a */
/* callback for services to be informed on status change. The callback */
/* function is defined as: */
/*    CallbackFunction( uint Item, uint Status, uint code, HANDLE hCfgEntry ) */
/*       Item      = Item value of entry changed */
/*       Status    = New status */
/*       Code      = Report code (if any) */
/*       hCfgEntry = Non-Ref'd HANDLE to entry with status change */
/*  The value of "Status" does not proceed past "ENABLED". For Task */
/*  specific information, the standard NETTOOLS report code is used. */

/* Common Service Arguments */
typedef struct _ci_srvargs {
        uint    Item;                      /* Copy Item (resets to NULL) */
        HANDLE  hService;                  /* Handle to service (resets to NULL) */
        uint    Mode;                      /* Flags */
#define CIS_FLG_IFIDXVALID      0x0001     /* IfIdx field is supplied to CONFIG */
#define CIS_FLG_RESOLVEIP       0x0002     /* Resolve If to IP before execution */
#define CIS_FLG_CALLBYIP        0x0004     /* Call using IP (set w/RESOLVEIP) */
#define CIS_FLG_RESTARTIPTERM   0x0008     /* Restart serivce on IPTERM */
        uint    Status;                    /* Service Status (resets to NULL) */
#define CIS_SRV_STATUS_DISABLED 0x0000     /* Config not active */
#define CIS_SRV_STATUS_WAIT     0x0001     /* Waiting on IP resolve */
#define CIS_SRV_STATUS_IPTERM   0x0002     /* Service terminated via IP synch */
#define CIS_SRV_STATUS_FAILED   0x0003     /* Service failed to initialize */
#define CIS_SRV_STATUS_ENABLED  0x0004     /* Service enabled */
        uint    ReportCode;                /* Standard NETTOOLS Report Code */
        uint    IfIdx;                     /* If physical index */
        IPN     IPAddr;                    /* Host IP Address */
        void(*pCbSrv)(uint, uint, uint, HANDLE); /* CbFun for status change */
        } CISARGS;

/* Telnet Entry Data */
typedef struct _ci_service_telnet {
        CISARGS        cisargs;         /* Common arguments */
        NTPARAM_TELNET param;           /* Telnet parameters */
        } CI_SERVICE_TELNET;

/* HTTP Server Entry Data */
typedef struct _ci_service_http {
        CISARGS         cisargs;        /* Common arguments */
        NTPARAM_HTTP    param;          /* HTTP parameters */
        } CI_SERVICE_HTTP;

/* NAT Service Entry Data */
typedef struct _ci_service_nat {
        CISARGS         cisargs;        /* Common arguments */
        NTPARAM_NAT     param;          /* NAT parameters */
        } CI_SERVICE_NAT;

/* DHCP Server Entry Data */
typedef struct _ci_service_dhcps {
        CISARGS         cisargs;        /* Common arguments */
        NTPARAM_DHCPS   param;          /* DHCPS parameters */
        } CI_SERVICE_DHCPS;

/* DHCP Client Service */
typedef struct _ci_service_dhcpc {
        CISARGS         cisargs;        /* Common arguments */
        NTPARAM_DHCP    param;          /* DHCP parameters */
        } CI_SERVICE_DHCPC;

/* DNS Server Service */
typedef struct _ci_service_dnss {
        CISARGS         cisargs;        /* Common arguments */
        } CI_SERVICE_DNSSERVER;

/*--------------------------------------------------------------------------- */
/* Config Tag: CFGTAG_IPNET */
/*   IP networks assigned to physical devices */
/*     Item     = Physical Interface Idx (1 to n) */
/*     Instance = Address Instance (1 to n) */

/* Max IPNet Domain name Length - Change requires NETTOOLS rebuild */
#define CFG_DOMAIN_MAX  64

/* IPNet Instance */
typedef struct _ci_ipnet {
        uint    NetType;                /* Network address type flags */
        IPN     IPAddr;                 /* IP Address */
        IPN     IPMask;                 /* Subnet Mask */
        HANDLE  hBind;                  /* Binding handle (resets to NULL) */
        char    Domain[CFG_DOMAIN_MAX]; /* IPNet Domain Name */
        } CI_IPNET;

/* NetType consists of flags. One or more of the following can be set... */
/* Note: VIRTUAL and non-VIRTUAL networks can not appear on the same interface */
#define CFG_NETTYPE_DYNAMIC     0x0001  /* Address created by DHCP CLIENT */
#define CFG_NETTYPE_VIRTUAL     0x0002  /* Virtual (one per IF) */
#define CFG_NETTYPE_DHCPS       0x0004  /* DHCPS Server IP */

/*--------------------------------------------------------------------------- */
/* Config Tag: CFGTAG_ROUTE */
/*   Static Gateway routes for hosts and networks */
/*     Item     = 0 */
/*     Instance = Route instance index (1 to n) */

/* Route Instance */
typedef struct _ci_route {
        IPN     IPDestAddr;             /* Destination Network Address */
        IPN     IPDestMask;             /* Subnet Mask of Destination */
        IPN     IPGateAddr;             /* Gateway IP Address */
        HANDLE  hRoute;                 /* Route handle (resets to NULL) */
        } CI_ROUTE;

/*--------------------------------------------------------------------------- */
/* Config Tag: CFGTAG_CLIENT */
/*   List of DHCPS clients by manual entry or allocation from pool */
/*     Item     = Physical Interface Idx (1 to n) */
/*     Instance = Client Address Instance (1 to n) */
/*   Used by DHCPS and DNS server for local name resolution */

/* Client Instance */

/*
 *  Maximum size for DHCP client host name.
 *
 *  *** NOTE: changing this value requires a rebuild of NETTOOLS! ***
 *
 *  NOTE: The client hostname size is actually governed by 2 definitions:
 *      1) CFG_HOSTNAME_MAX (defined in netcfg.h)
 *      2) HOSTNAME_LENGTH (defined in dhcp.h)
 *  These two values must be consistent!  If one is changed, both must be
 *  changed.
 *
 *  RFC 2131 and 2132 do not clearly specify what the maximum size for this
 *  value should be.  255 was determined based on MSDN "Host Name Resolution for
 *  IPv4" on Microsoft's website (the size is 255 + 1 to make room for "\0"). 
 *  See notes for fix of CQ15114 for more details.
 *  
 */
#define CFG_HOSTNAME_MAX     256

typedef struct _ci_client {
        uint    ClientType;             /* Entry Status */
        uint    Status;                 /* DHCPS Status (init to ZERO) */
        IPN     IPAddr;                 /* Client IP Address */
        char    MacAddr[6];             /* Client Physical Address */
        char    Hostname[CFG_HOSTNAME_MAX]; /* Client Hostname */
        UINT32  TimeStatus;             /* Time of last status msg (REQ/DEC/INF) */
        UINT32  TimeExpire;             /* Expiration Time from TimeStatus */
        } CI_CLIENT;

/* ClientType and ClientStatus are values and can be one of the following... */
#define CFG_CLIENTTYPE_DYNAMIC     1    /* Entry created via DHCPS */
#define CFG_CLIENTTYPE_STATIC      2    /* Create manually */

#define CFG_CLIENTSTATUS_PENDING   1    /* Supplied by OFFER */
#define CFG_CLIENTSTATUS_VALID     2    /* Validated by REQUEST */
#define CFG_CLIENTSTATUS_STATIC    3    /* Given by a INFORM */
#define CFG_CLIENTSTATUS_INVALID   4    /* Invalidated by DECLINE */

/*--------------------------------------------------------------------------- */
/* Config Tag: CFGTAG_ACCT */
/*   List of user accounts for PPP or similar login */
/*     Item     = 1 for PPP or REALM */
/*     Instance = Client Address Instance (1 to n) */
/*   Used by PPP in server mode for authentication */
/*   Used by file system for REALM authentication */
/*   * Note all NDK accounts use the the same "item" value * */

/* Account Item Types */
#define CFGITEM_ACCT_SYSTEM     1
#define CFGITEM_ACCT_PPP        1
#define CFGITEM_ACCT_REALM      1

#define CFG_ACCTSTR_MAX         32

/* Account Instance */
typedef struct _ci_acct {
        uint    Flags;                     /* Account Flags */
        char    Username[CFG_ACCTSTR_MAX]; /* Username */
        char    Password[CFG_ACCTSTR_MAX]; /* Password */
        } CI_ACCT;

/* Authority consists of flags. One or more of the following can be set... */
#define CFG_ACCTFLG_CH1         0x1000
#define CFG_ACCTFLG_CH2         0x2000
#define CFG_ACCTFLG_CH3         0x4000
#define CFG_ACCTFLG_CH4         0x8000
#define CFG_ACCTFLG_CHALL       0xF000

/*--------------------------------------------------------------------------- */
/* Config Tag: CFGTAG_SYSINFO */
/*   System information */
/*   This tag is for system information that is common for all system */
/*   tasks (DNS server, hostname, domainname, etc.). */
/*   Tag values less than 256 are reserved for DHCP */
/*   ( Item < 256 ) */
/*     (DHCP Info: Item numbers are reserved to match DHCP info tags) */
/*     Item     = DHCP Compatible Tag */
/*     Instance = Data Item Instance (1-n) */
/*   ( Item >= 256 ) */
/*     Item     = System Info Tag */
/*     Instance = Data Item Instance (1-n) */
/* *** USERS CAN ADD THEIR OWN ITEM VALUES *** */
/* For information, there is no structure - purely data */

/* Currently Used DHCP Compatible Items */
/* Multiple instances are always to be stored as multiple */
/* config entries, not a concatenated byte string in a */
/* single config entry. */
#define CFGITEM_DHCP_DOMAINNAMESERVER   6       /* Stack's DNS servers */
#define CFGITEM_DHCP_HOSTNAME           12      /* Stack's host name */
#define CFGITEM_DHCP_NBNS               44      /* Stack's NBNS servers */
#define CFGITEM_DHCP_CLIENT_OPTION		61		/* Stack DHCP Client Identifier */

#define CFGITEM_SYSINFO_REALM1          256     /* Realm Name 1 (max 31 chars) */
#define CFGITEM_SYSINFO_REALM2          257     /* Realm Name 2 (max 31 chars) */
#define CFGITEM_SYSINFO_REALM3          258     /* Realm Name 3 (max 31 chars) */
#define CFGITEM_SYSINFO_REALM4          259     /* Realm Name 4 (max 31 chars) */
#define CFGITEM_SYSINFO_REALMPPP        260     /* Realm Name PPP (max 31 chars) */

/*--------------------------------------------------------------------------- */
/* Config Tag: CFGTAG_IP, CFGTAG_OS */
/*   IP Stack Configuration / OS Configuration */
/*   The CFGTAG_IP tag is for setting configuration values in the */
/*   TCP/IP stack. */
/*   The CFGTAG_OS tag is for setting configuration values in the */
/*   system OS (or OS shell). */
/*   Write to either tag results in writes the the internal configuration */
/*   structure of the stack or OS, but being part of the configuration, the */
/*   entry can be stored off in as part of the CfgSave() functionality. */
/*   Removing an entry restores the default value to the configuration. */
/*   Entries that are not present can not be read, but an error on */
/*   read implies the entry is in its default state. */
/*   All items are of type "int" or "uint". */

/* When Tag = CFGTAG_IP, Item values are */
#define CFGITEM_IP_ICMPDOREDIRECT  1   /* Add route on ICMP redirect (1=Yes) */
#define CFGITEM_IP_ICMPTTL         2   /* TTL for ICMP msgs (RFC1700 says 64) */
#define CFGITEM_IP_ICMPTTLECHO     3   /* TTL for ICMP echo (RFC1700 says 64) */
#define CFGITEM_IP_IPINDEXSTART    4   /* IP Protocol Start Index */
#define CFGITEM_IP_IPFORWARDING    5   /* IP Forwarding Enable (1=Yes) */
#define CFGITEM_IP_IPNATENABLE     6   /* IP NAT Translation Enable (1=Yes) */
#define CFGITEM_IP_IPFILTERENABLE  7   /* IP Filtering Enable (1=Yes) */
#define CFGITEM_IP_IPREASMMAXTIME  8   /* Max IP reassembly time in seconds */
#define CFGITEM_IP_IPREASMMAXSIZE  9   /* Max IP reassembly packet size */
#define CFGITEM_IP_DIRECTEDBCAST   10  /* Directed BCast IP addresses (1=Yes) */
#define CFGITEM_IP_TCPREASMMAXPKT  11  /* Out of order pkts held by TCP socket */
#define CFGITEM_IP_RTCENABLEDEBUG  12  /* Route control dbg messages (1=Yes) */
#define CFGITEM_IP_RTCADVTIME      13  /* Seconds to send Router Adv. (0=don't) */
#define CFGITEM_IP_RTCADVLIFE      14  /* Lifetime of route in RtAdv if active */
#define CFGITEM_IP_RTCADVPREF      15  /* Preference of route in RvAdv if active */
#define CFGITEM_IP_RTARPDOWNTIME   16  /* Time 5 failed ARPs keeps route down */
#define CFGITEM_IP_RTKEEPALIVETIME 17  /* Timeout of validated route in seconds */
#define CFGITEM_IP_RTARPINACTIVITY 18  /* Time in seconds beyond which a route if */
                                       /* unused considered "inactive" and is cleaned up. */
#define CFGITEM_IP_RTCLONETIMEOUT  19  /* Timeout of new cloned route in seconds */
#define CFGITEM_IP_RTDEFAULTMTU    20  /* MTU for internal routes */
#define CFGITEM_IP_SOCKTTLDEFAULT  21  /* Default IP TTL for Sockets */
#define CFGITEM_IP_SOCKTOSDEFAULT  22  /* Default IP TOS for Sockets */
#define CFGITEM_IP_SOCKMAXCONNECT  23  /* Max connections on listening socket */
#define CFGITEM_IP_SOCKTIMECONNECT 24  /* Max time for connect socket */
#define CFGITEM_IP_SOCKTIMEIO      25  /* Default Max time for socket send/rcv */
#define CFGITEM_IP_SOCKTCPTXBUF    26  /* TCP Transmit buffer size */
#define CFGITEM_IP_SOCKTCPRXBUF    27  /* TCP Receive buffer size (copy mode) */
#define CFGITEM_IP_SOCKTCPRXLIMIT  28  /* TCP Receive limit (non-copy mode) */
#define CFGITEM_IP_SOCKUDPRXLIMIT  29  /* UDP Receive limit */
#define CFGITEM_IP_SOCKMINTX       30  /* Default min space for "able to write" */
#define CFGITEM_IP_SOCKMINRX       31  /* Default min data for "able to read" */
#define CFGITEM_IP_PIPETIMEIO      32  /* Max time for pipe send/rcv call */
#define CFGITEM_IP_PIPEBUFMAX      33  /* Pipe internal buffer size */
#define CFGITEM_IP_PIPEMINTX       34  /* Pipe min tx space for "able to write" */
#define CFGITEM_IP_PIPEMINRX       35  /* Pipe min rx data for "able to read" */
#define CFGITEM_IP_TCPKEEPIDLE     36  /* Idle time before 1st TCP keep probe */
#define CFGITEM_IP_TCPKEEPINTVL    37  /* TCP keep probe interval */
#define CFGITEM_IP_TCPKEEPMAXIDLE  38  /* Max TCP keep probing time before drop */
#define CFGITEM_IP_ICMPDONTREPLYBCAST  39  /* Dont Reply To ICMP ECHO REQ  */
                                       /* packets sent to BCast/Directed BCast  */
#define CFGITEM_IP_ICMPDONTREPLYMCAST  40  /* Dont Reply To ICMP ECHO REQ */
                                       /* packets sent to Multi-Cast */

#define CFGITEM_IP_RTGARP          41  /* How to handle received gratuitous ARP  */
                                       /* 0 : discard them. (Default)  */
                                       /* 1 : update MAC address of HOST, if it */
                                       /*     is already in the routing table. */
                                       /* 2 : add HOST to routing table, if it */
                                       /*     does NOT exist. If exists, update */
                                       /*     MAC address. */

#define CFGITEM_IP_ICMPDONTREPLYECHO  42  /* Don't Reply To ICMP ECHO REQ */
#define CFGITEM_IP_UDPSENDICMPPORTUNREACH 43  /* Send ICMP Port Unreachable */
                                       /* packet if UDP port is opened or not  */
#define CFGITEM_IP_TCPSENDRST      44  /* Send RST if TCP port is not    */
                                       /* opened or not.   */
#define CFGITEM_IP_SOCKRAWETHRXLIMIT  45  /* Raw Eth Receive limit */

#define CFGITEM_IP_MAX             46  /* Max CFGTAG_IP item */


/* When Tag = CFGTAG_OS, Item values are */
#define CFGITEM_OS_DBGPRINTLEVEL   1   /* Debug msg print threshhold */
#define CFGITEM_OS_DBGABORTLEVEL   2   /* Debug msg sys abort theshhold */
#define CFGITEM_OS_TASKPRILOW      3   /* Lowest priority for stack task */
#define CFGITEM_OS_TASKPRINORM     4   /* Normal priority for stack task */
#define CFGITEM_OS_TASKPRIHIGH     5   /* High priority for stack task */
#define CFGITEM_OS_TASKPRIKERN     6   /* Kernel-level priority (highest) */
#define CFGITEM_OS_TASKSTKLOW      7   /* Minimum stack size */
#define CFGITEM_OS_TASKSTKNORM     8   /* Normal stack size */
#define CFGITEM_OS_TASKSTKHIGH     9   /* Stack size for high volume tasks */
#define CFGITEM_OS_MAX             9   /* Max CFGTAG_OS item */

#endif

