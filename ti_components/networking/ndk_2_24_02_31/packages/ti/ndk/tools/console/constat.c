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
 * ======== constat.c ========
 *
 * Console Stat Function
 *      ConCmdStat  -   Console Stat command function
 *
 */

#include <netmain.h>
#include <_stack.h>
#include "console.h"

static void DumpIPStats();
static void DumpICMPStats();
static void DumpTCPStats();
static void DumpUDPStats();
static void DumpNATStats();

/*------------------------------------------------------------------------- */
/* ConCmdStat() */
/* Function to print out stack statistics */
/*------------------------------------------------------------------------- */
void ConCmdStat( int ntok, char *tok1 )
{
    /* Check for 'stat ip' */
    if( ntok == 1 && !stricmp( tok1, "ip" ) )
        DumpIPStats();
    /* Check for 'stat icmp' */
    else if( ntok == 1 && !stricmp( tok1, "icmp" ) )
        DumpICMPStats();
    /* Check for 'stat tcp' */
    else if( ntok == 1 && !stricmp( tok1, "tcp" ) )
        DumpTCPStats();
    /* Check for 'stat udp' */
    else if( ntok == 1 && !stricmp( tok1, "udp" ) )
        DumpUDPStats();
    /* Check for 'stat nat' */
    else if( ntok == 1 && !stricmp( tok1, "nat" ) )
        DumpNATStats();
    else if( ntok == 0 )
    {
        ConPrintf("\n[Stat Command]\n");
        ConPrintf("\nCalled to dump out internal stack statistics.\n\n");
        ConPrintf("stat ip      - Print out IP statistics\n");
        ConPrintf("stat icmp    - Print out ICMP statistics\n");
        ConPrintf("stat tcp     - Print out TCP statistics\n");
        ConPrintf("stat udp     - Print out UDP and RAW statistics\n");
        ConPrintf("stat nat     - Print out NAT statistics\n\n");
    }
    else
        ConPrintf("\nIllegal argument. Type 'stat' for help\n");
}

/*------------------------------------------------------------------------- */
/* DumpIPStats() */
/* Dump out IP Statistics */
/*------------------------------------------------------------------------- */
static void DumpIPStats()
{
    ConPrintf("\nIP Statistics:\n");
    ConPrintf("   Total         = %010u  ", ips.Total        );
    ConPrintf("   Odropped      = %010u\n", ips.Odropped     );
    ConPrintf("   Badsum        = %010u  ", ips.Badsum       );
    ConPrintf("   Badhlen       = %010u\n", ips.Badhlen      );
    ConPrintf("   Badlen        = %010u  ", ips.Badlen       );
    ConPrintf("   Badoptions    = %010u\n", ips.Badoptions   );
    ConPrintf("   Badvers       = %010u  ", ips.Badvers      );
    ConPrintf("   Forward       = %010u\n", ips.Forward      );
    ConPrintf("   Noproto       = %010u  ", ips.Noproto      );
    ConPrintf("   Delivered     = %010u\n", ips.Delivered    );
    ConPrintf("   Cantforward   = %010u  ", ips.Cantforward  );
    ConPrintf("   CantforwardBA = %010u\n", ips.CantforwardBA);
    ConPrintf("   Expired       = %010u  ", ips.Expired      );
    ConPrintf("   Redirectsent  = %010u\n", ips.Redirectsent );
    ConPrintf("   Localout      = %010u  ", ips.Localout     );
    ConPrintf("   Localnoroute  = %010u\n", ips.Localnoroute );
    ConPrintf("   CacheHit      = %010u  ", ips.CacheHit     );
    ConPrintf("   CacheMiss     = %010u\n", ips.CacheMiss    );
    ConPrintf("   Fragments     = %010u  ", ips.Fragments    );
    ConPrintf("   Fragdropped   = %010u\n", ips.Fragdropped  );
    ConPrintf("   Fragtimeout   = %010u  ", ips.Fragtimeout  );
    ConPrintf("   Reassembled   = %010u\n", ips.Reassembled  );
    ConPrintf("   Ofragments    = %010u  ", ips.Ofragments   );
    ConPrintf("   Fragmented    = %010u\n", ips.Fragmented   );
    ConPrintf("   Cantfrag      = %010u  ", ips.Cantfrag     );
    ConPrintf("   Filtered      = %010u\n", ips.Filtered     );
}

/*------------------------------------------------------------------------- */
/* DumpICMPStats() */
/* Dump out ICMP Statistics */
/*------------------------------------------------------------------------- */
static void DumpICMPStats()
{
    ConPrintf("\nICMP Statistics:\n");
    ConPrintf("    ICMP Rx Errors: %u\n", _ICMPInErrors);
    ConPrintf("    ICMP Tx Errors: %u\n", _ICMPOutErrors);
    ConPrintf("    ECHO             In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_ECHO], _ICMPOut[ICMP_ECHO] );
    ConPrintf("    ECHOREPLY        In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_ECHOREPLY], _ICMPOut[ICMP_ECHOREPLY] );
    ConPrintf("    TSTAMP           In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_TSTAMP], _ICMPOut[ICMP_TSTAMP] );
    ConPrintf("    TSTAMPREPLY      In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_TSTAMPREPLY], _ICMPOut[ICMP_TSTAMPREPLY] );
    ConPrintf("    IREQ             In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_IREQ], _ICMPOut[ICMP_IREQ] );
    ConPrintf("    IREQREPLY        In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_IREQREPLY], _ICMPOut[ICMP_IREQREPLY] );
    ConPrintf("    MASKREQ          In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_MASKREQ], _ICMPOut[ICMP_MASKREQ] );
    ConPrintf("    MASKREPLY        In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_MASKREPLY], _ICMPOut[ICMP_MASKREPLY] );
    ConPrintf("    UNREACH          In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_UNREACH], _ICMPOut[ICMP_UNREACH] );
    ConPrintf("    SOURCEQUENCH     In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_SOURCEQUENCH], _ICMPOut[ICMP_SOURCEQUENCH] );
    ConPrintf("    REDIRECT         In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_REDIRECT], _ICMPOut[ICMP_REDIRECT] );
    ConPrintf("    ROUTERADVERT     In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_ROUTERADVERT], _ICMPOut[ICMP_ROUTERADVERT] );
    ConPrintf("    ROUTERSOLICIT    In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_ROUTERSOLICIT], _ICMPOut[ICMP_ROUTERSOLICIT] );
    ConPrintf("    TIMXCEED         In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_TIMXCEED], _ICMPOut[ICMP_TIMXCEED] );
    ConPrintf("    PARAMPROB        In: %010u     Out: %010u\n",
           _ICMPIn[ICMP_PARAMPROB], _ICMPOut[ICMP_PARAMPROB] );
}

/*------------------------------------------------------------------------- */
/* DumpTCPStats() */
/* Dump out TCP Statistics */
/*------------------------------------------------------------------------- */
static void DumpTCPStats()
{
    ConPrintf("\nTCP Statistics:\n");
    ConPrintf("  RcvTotal       = %010u  ", tcps.RcvTotal        );
    ConPrintf("  RcvShort       = %010u\n", tcps.RcvShort        );
    ConPrintf("  RcvHdrSize     = %010u  ", tcps.RcvHdrSize      );
    ConPrintf("  RcvBadSum      = %010u\n", tcps.RcvBadSum       );
    ConPrintf("  RcvAfterClose  = %010u  ", tcps.RcvAfterClose   );
    ConPrintf("  RcvDupAck      = %010u\n", tcps.RcvDupAck       );
    ConPrintf("  RcvPack        = %010u  ", tcps.RcvPack         );
    ConPrintf("  RcvByte        = %010u\n", tcps.RcvByte         );
    ConPrintf("  RcvAckPack     = %010u  ", tcps.RcvAckPack      );
    ConPrintf("  RcvAckByte     = %010u\n", tcps.RcvAckByte      );
    ConPrintf("  RcvDupPack     = %010u  ", tcps.RcvDupPack      );
    ConPrintf("  RcvDupByte     = %010u\n", tcps.RcvDupByte      );
    ConPrintf("  RcvPartDupPack = %010u  ", tcps.RcvPartDupPack  );
    ConPrintf("  RcvPartDupByte = %010u\n", tcps.RcvPartDupByte  );
    ConPrintf("  RcvAfterWinPack= %010u  ", tcps.RcvAfterWinPack );
    ConPrintf("  RcvAfterWinByte= %010u\n", tcps.RcvAfterWinByte );
    ConPrintf("  RcvOOPack      = %010u  ", tcps.RcvOOPack       );
    ConPrintf("  RcvOOByte      = %010u\n", tcps.RcvOOByte       );
    ConPrintf("  RcvWinUpd      = %010u  ", tcps.RcvWinUpd       );
    ConPrintf("  RcvWinProbe    = %010u\n", tcps.RcvWinProbe     );
    ConPrintf("  RcvAckTooMuch  = %010u  ", tcps.RcvAckTooMuch   );
    ConPrintf("  SndNoBufs      = %010u\n", tcps.SndNoBufs       );

    ConPrintf("  SndTotal       = %010u  ", tcps.SndTotal        );
    ConPrintf("  SndProbe       = %010u\n", tcps.SndProbe        );
    ConPrintf("  SndPack (data) = %010u  ", tcps.SndPack         );
    ConPrintf("  SndByte (data) = %010u\n", tcps.SndByte         );
    ConPrintf("  SndRexmitPack  = %010u  ", tcps.SndRexmitPack   );
    ConPrintf("  SndRexmitByte  = %010u\n", tcps.SndRexmitByte   );
    ConPrintf("  SndAcks        = %010u  ", tcps.SndAcks         );
    ConPrintf("  SndCtrl        = %010u\n", tcps.SndCtrl         );
    ConPrintf("  SndUrg         = %010u  ", tcps.SndUrg          );
    ConPrintf("  SndWinUp       = %010u\n", tcps.SndWinUp        );

    ConPrintf("  SegsTimed      = %010u  ", tcps.SegsTimed       );
    ConPrintf("  RttUpdated     = %010u\n", tcps.RttUpdated      );
    ConPrintf("  Connects       = %010u  ", tcps.Connects        );
    ConPrintf("  ConnAttempt    = %010u\n", tcps.ConnAttempt     );
    ConPrintf("  Drops          = %010u  ", tcps.Drops           );
    ConPrintf("  ConnDrops      = %010u\n", tcps.ConnDrops       );
    ConPrintf("  Accepts        = %010u  ", tcps.Accepts         );
    ConPrintf("  TimeoutDrops   = %010u\n", tcps.TimeoutDrops    );
    ConPrintf("  KeepDrops      = %010u  ", tcps.KeepDrops       );
    ConPrintf("  DelAck         = %010u\n", tcps.DelAck          );
    ConPrintf("  KeepProbe      = %010u  ", tcps.KeepProbe       );
    ConPrintf("  PersistTimeout = %010u\n", tcps.PersistTimeout  );
    ConPrintf("  KeepTimeout    = %010u  ", tcps.KeepTimeout     );
    ConPrintf("  RexmtTimeout   = %010u\n", tcps.RexmtTimeout    );
}

/*------------------------------------------------------------------------- */
/* DumpUDPStats() */
/* Dump out UDP/RAW Statistics */
/*------------------------------------------------------------------------- */
static void DumpUDPStats()
{
    ConPrintf("\nUDP Statistics:\n");
    ConPrintf("  RcvTotal       = %010u\n", udps.RcvTotal        );
    ConPrintf("  RcvShort       = %010u\n", udps.RcvShort        );
    ConPrintf("  RcvBadLen      = %010u\n", udps.RcvBadLen       );
    ConPrintf("  RcvBadSum      = %010u\n", udps.RcvBadSum       );
    ConPrintf("  RcvFull        = %010u\n", udps.RcvFull         );
    ConPrintf("  RcvNoPort      = %010u\n", udps.RcvNoPort       );
    ConPrintf("  RcvNoPortB     = %010u\n", udps.RcvNoPortB      );
    ConPrintf("  SndTotal       = %010u\n", udps.SndTotal        );
    ConPrintf("  SndNoPacket    = %010u\n", udps.SndNoPacket     );

    ConPrintf("\nRAW Statistics:\n");
    ConPrintf("  RcvTotal       = %010u\n", raws.RcvTotal        );
    ConPrintf("  RcvFull        = %010u\n", raws.RcvFull         );
    ConPrintf("  SndTotal       = %010u\n", raws.SndTotal        );
    ConPrintf("  SndNoPacket    = %010u\n", raws.SndNoPacket     );
}

/*------------------------------------------------------------------------- */
/* DumpNATStats() */
/* Dump out NAT Statistics */
/*------------------------------------------------------------------------- */
static void DumpNATStats()
{
#if NETSRV_ENABLE_NAT
    ConPrintf("\nNAT Statistics:\n");
    ConPrintf("  TxExamined     = %010u\n", nats.TxExamined      );
    ConPrintf("  TxQualified    = %010u\n", nats.TxQualified     );
    ConPrintf("  TxAltered      = %010u\n", nats.TxAltered       );
    ConPrintf("  RxExamined     = %010u\n", nats.RxExamined      );
    ConPrintf("  RxQualified    = %010u\n", nats.RxQualified     );
    ConPrintf("  RxAltered      = %010u\n", nats.RxAltered       );
    ConPrintf("  Entries        = %010u\n", nats.Entries         );
    ConPrintf("  MaxEntries     = %010u\n", nats.MaxEntries      );
    ConPrintf("  LongTerm       = %010u\n", nats.LongTerm        );
    ConPrintf("  MaxLongTerm    = %010u\n", nats.MaxLongTerm     );
#endif
}

