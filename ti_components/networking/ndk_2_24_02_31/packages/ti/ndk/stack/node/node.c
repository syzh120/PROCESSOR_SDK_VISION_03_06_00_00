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
 * ======== node.c ========
 *
 * Route module object
 *
 */

#include <stkmain.h>

/*--------------------- */
/* Node */
/*--------------------- */

/* Node Structure */
typedef struct _node {
    uint                Type;           /* Set to HTYPE_NODE */
    uint                RefCount;       /* # of open alloc's to this entry */
    struct _node        *pUp;           /* Up Node */
    struct _node        *pLeft;         /* 0 Node */
    struct _node        *pRight;        /* 1 Node */
    uint                Flags;          /* See flags */
    uint                BitOffset;      /* 0=MSB 31=LSB */
    IPN                 dwTestMask;     /* Bit `AND' compare value */
    HANDLE              hRt;            /* First Rt entry (leaf node only) */
    uint                LastMaskBits;   /* 0 to 32 (also bit offset of passlft) */
    IPN                 dwLastIPAddr;   /* MASKED Least restrictve IP hRt list */
    IPN                 dwLastIPMask;   /* Least restrictve Mask in hRt list */
    } NODE;

#define NODE_FLG_PASSLEFT    0x0001  /* Pass backtrack from right to left */
#define NODE_FLG_LEAF        0x0002  /* Leaf node */
#define NODE_FLG_ENDL        0x0004  /* Left Endpoint */
#define NODE_FLG_ENDR        0x0008  /* Right Endpoint */

static NODE* pRoot = 0;

/*-------------------------------------------------------------------- */
/* NodeNew() */
/* Create */
/*-------------------------------------------------------------------- */
static HANDLE NodeNew( uint Flags, uint wBitOffset )
{
    NODE  *pn;
    UINT32 dwTmp;

    /* If we can't get a message, we may as well lock up. */
    if( !(pn = mmAlloc(sizeof(NODE))) )
    {
        DbgPrintf(DBG_WARN,"NodeNew: OOM");
        NotifyLowResource();
        return(0);
    }

    /* Initialize type */
    pn->Type = HTYPE_NODE;

    /* Initialize refcount */
    pn->RefCount = 1;

    /* Initialize defaults */
    pn->pUp    = 0;
    pn->pLeft  = 0;
    pn->pRight = 0;
    pn->Flags  = Flags;
    pn->hRt    = 0;

    /* If we're not a leaf, we need to calc the test mask */
    if( !(Flags & NODE_FLG_LEAF) )
    {
        dwTmp = ( 1 << (31 - wBitOffset) );
        pn->BitOffset = wBitOffset;
        pn->dwTestMask = HNC32( dwTmp );
    }

    return( (HANDLE)pn );
}

/*-------------------------------------------------------------------- */
/* NodeFree() */
/* Destroy */
/*-------------------------------------------------------------------- */
static void NodeFree( HANDLE h )
{
    NODE *pn = (NODE *)h;

#ifdef _STRONG_CHECKING
    if( pn->Type != HTYPE_NODE )
    {
        DbgPrintf(DBG_ERROR,"NodeFree: HTYPE %04x",pn->Type);
        return;
    }
#endif

    /* Kill type for debug */
    pn->Type = 0;

    /* Free the handle if we're done with it */
    mmFree( pn );
}

/*-------------------------------------------------------------------- */
/* NodeUpdatePL() */
/* Update pass left values starting at the given leaf node */
/*-------------------------------------------------------------------- */
static void NodeUpdatePL( NODE *pn )
{
    NODE   *pnFrom;
    uint wLastMaskBits;
    IPN    dwLastIPMask;

    wLastMaskBits = pn->LastMaskBits;
    dwLastIPMask  = pn->dwLastIPMask;

    /* Start Updating */
    while( pn->pUp )
    {
        pnFrom = pn;
        pn = pn->pUp;

        /* Only "left" children affect our pass left flag */
        if( pnFrom != pn->pLeft )
            return;

        /* We "pass left" if our bit offset is in the ZERO */
        /* portion of the child's mask bits */
        if( pn->BitOffset >= wLastMaskBits )
        {
            pn->Flags |= NODE_FLG_PASSLEFT;
            pn->LastMaskBits = wLastMaskBits;  /* Required for child updates */
            pn->dwLastIPMask  = dwLastIPMask;   /* This used by "NodeFind" */
        }
        else
        {
            pn->Flags &= ~NODE_FLG_PASSLEFT;
            pn->LastMaskBits = 32;             /* Full Mask */
            pn->dwLastIPMask  = 0xffffffff;     /* Full Mask */
        }
    }
}

/*-------------------------------------------------------------------- */
/* NodeTreeNew() */
/* Initialze the node tree */
/*-------------------------------------------------------------------- */
void NodeTreeNew()
{
    NODE *pnL, *pnR;

    pRoot = (NODE *)NodeNew( 0, 0 );
    pnL   = (NODE *)NodeNew( NODE_FLG_LEAF|NODE_FLG_ENDL, 0 );
    pnR   = (NODE *)NodeNew( NODE_FLG_LEAF|NODE_FLG_ENDR, 0 );

    if( !pRoot || !pnL || !pnR )
    {
        DbgPrintf(DBG_ERROR,"NodeInit: OOM");
        return;
    }

    /* Setup Root */
    pRoot->pLeft  = pnL;
    pRoot->pRight = pnR;

    /* Setup Left */
    pnL->pUp           = pRoot;
    pnL->LastMaskBits = 0;
    pnL->dwLastIPMask  = 0;
    pnL->dwLastIPAddr  = 0;

    /* Setup Right */
    pnR->pUp           = pRoot;
    pnR->LastMaskBits = 32;
    pnR->dwLastIPMask  = 0xFFFFFFFF;
    pnR->dwLastIPAddr  = 0xFFFFFFFF;

    /* Update the Pass Left Flags */
    NodeUpdatePL( pnL );
}

/*-------------------------------------------------------------------- */
/* NodeTreeFree() */
/* Destroy the node table */
/*-------------------------------------------------------------------- */
void NodeTreeFree()
{
    NODE *pnL, *pnR;

    pnL   = pRoot->pLeft;
    pnR   = pRoot->pRight;

    if( !pRoot || !pnL || !pnR )
    {
        DbgPrintf(DBG_WARN,"NodeTreeFree: Null endpoints");
        return;
    }

    if( !(pnL->Flags & NODE_FLG_ENDL ) )
        DbgPrintf(DBG_WARN,"NodeTreeFree: Didn't find left");
    else if( !(pnR->Flags & NODE_FLG_ENDR ) )
        DbgPrintf(DBG_WARN,"NodeTreeFree: Didn't find right");
    else if( pnL->pLeft || pnL->pRight )
        DbgPrintf(DBG_WARN,"NodeTreeFree: Left has Children");
    else if( pnR->pLeft || pnR->pRight )
        DbgPrintf(DBG_WARN,"NodeTreeFree: Right has Children");

    NodeFree( pnL );
    NodeFree( pnR );
    NodeFree( pRoot );
    pRoot = 0;
}

/*-------------------------------------------------------------------- */
/* NodeAdd() */
/* Called to POTENTIALLY create a new leaf node. */
/* Increments Reference Count of the Node it returns. */
/*-------------------------------------------------------------------- */
HANDLE NodeAdd( IPN IPAddr, IPN IPMask, uint wMaskBits )
{
    NODE  *pn = pRoot;
    UINT32 dwMaskedAddr;

    /* Use the most generic address to find a place in the table. This */
    /* way we are guaranteed not to backtrack. */
    dwMaskedAddr = IPAddr & IPMask;

    for(;;)
    {
        /* If we are not a leaf, then get the next node */
        if( !(pn->Flags & NODE_FLG_LEAF) )
        {
            if( (dwMaskedAddr & pn->dwTestMask) == 0 )
                pn = pn->pLeft;
            else
                pn = pn->pRight;
        }
        else
        {
            /* If we got here, we got to a leaf. Now we'll have one */
            /* of two cases. If we are a valid node for this leaf, */
            /* then we'll just task ourselves on. */

            /* A leaf node can be shared if both addrs are equal when */
            /* their own respective masks are applied. */
            if( pn->dwLastIPAddr == dwMaskedAddr )
            {
                /* This leaf can be shared */

                /* Reference it */
                NodeRef( pn );

                /* Set the new "least restritive" mask */
                if( wMaskBits < pn->LastMaskBits )
                {
                    pn->LastMaskBits = wMaskBits;
                    pn->dwLastIPMask  = IPMask;
                    NodeUpdatePL( pn );
                }
                goto NODE_ADD_DONE;
            }
            else
            {
                /* Leaf can not be shared. We thus need two additional */
                /* nodes. One will be a new branch node, and the other */
                /* will be a new leaf. */
                NODE* pnLeaf;
                NODE* pnBranch;

                /* The last thing to determine is the bit offset of the */
                /* first "different" bit in the two addresses. */
                UINT32 dwTest1,dwTest2;
                uint  w;

                dwTest1 = dwMaskedAddr ^ pn->dwLastIPAddr;
                dwTest1 = HNC32( dwTest1 );
                dwTest2 = 0x80000000;
                w = 0;

                /* Find the first "different" bit */
                while( !( dwTest1 & dwTest2 ) )
                {
                    w++;
                    dwTest2 >>= 1;
                }

                /* Now we have the first diffent bit in w, where 0=MSB */
                if( !(pnBranch = (NODE *)NodeNew( 0, w )) )
                {
                    pn = 0;
                    goto NODE_ADD_DONE;
                }

                if( !(pnLeaf = (NODE *)NodeNew( NODE_FLG_LEAF, 0 )) )
                {
                    NodeFree( pnBranch );
                    pn = 0;
                    goto NODE_ADD_DONE;
                }

                /* Now we need to insert the node in its correct location. */
                while( pn->pUp->BitOffset > w )
                    pn = pn->pUp;

                /* Start Inserting */
                pnBranch->pUp = pn->pUp;
                pn->pUp       = pnBranch;
                pnLeaf->pUp   = pnBranch;

                /* Make old node's parent branch to our new branch node */
                if( pnBranch->pUp->pRight == pn )
                {
                    /* Old leaf node was on the right */
                    pnBranch->pUp->pRight = pnBranch;
                }
                else
                {
                    /* Old leaf node was on the left */
                    pnBranch->pUp->pLeft = pnBranch;
                }

                /* Make new branch node brach to our children */
                if( pnBranch->dwTestMask & dwMaskedAddr )
                {
                    /* New leaf node is on the right */
                    pnBranch->pRight = pnLeaf;
                    pnBranch->pLeft  = pn;
                }
                else
                {
                    /* New leaf node is on the left */
                    pnBranch->pLeft  = pnLeaf;
                    pnBranch->pRight = pn;
                }

                /* Init the Leaf Node */
                pnLeaf->dwLastIPAddr  = dwMaskedAddr;
                pnLeaf->dwLastIPMask  = IPMask;
                pnLeaf->LastMaskBits = wMaskBits;

                /* Put return value in pn */
                pn = pnLeaf;

                /* Update new brach with its LEFT node */
                NodeUpdatePL( pnBranch->pLeft );

                goto NODE_ADD_DONE;
            }
        }
    }

NODE_ADD_DONE:
    return( pn );
}

/*-------------------------------------------------------------------- */
/* NodeFind() */
/* Called to find the node with the closest IP match. */
/* Increments Reference Count of the Node it returns. */
/* Decrements Reference Count of any Continue Node supplied */
/*-------------------------------------------------------------------- */
HANDLE NodeFind( IPN IPAddr, HANDLE hNodeContinue )
{
    NODE  *pn = pRoot;
    NODE  *pnContinue = (NODE *)hNodeContinue;
    UINT32 dwMaskedAddr;

#ifdef _STRONG_CHECKING
    /* Validate hNodeContinue */
    if( hNodeContinue && ( (pnContinue->Type != HTYPE_NODE)
                           || !(pnContinue->Flags & NODE_FLG_LEAF)) )
    {
        DbgPrintf(DBG_ERROR,"NodeFind: HTYPE %04x : Continue an non-Leaf",pnContinue->Type);
        return(0);
    }
#endif

    /* Start out with the most specific IP address, but be prepared to */
    /* apply as when needed. */
    dwMaskedAddr = IPAddr;

    /* We have the ability to continue off a previous search. If we */
    /* are continuing, we will NEVER match on the first leaf. */
    /* We also start at the continue point */
    if( pnContinue )
        pn = pnContinue;

    /* Start search. Note this algorithm is unconcerned with the */
    /* "no match" case since it is impossible not to match on (at least) */
    /* the left end node. */
    for(;;)
    {
        /* If we are not a leaf, then get the next node */
        if( !(pn->Flags & NODE_FLG_LEAF) )
        {
            if( (dwMaskedAddr & pn->dwTestMask) == 0 )
                pn = pn->pLeft;
            else
                pn = pn->pRight;
        }
        else
        {
            /* If we got here, we got to a leaf. Now we'll have one */
            /* of two cases. If we match this leaf, we're done. Otherwise */
            /* we have to backtrack. */
            if( (pn->dwLastIPAddr == (dwMaskedAddr & pn->dwLastIPMask))
                && pn != pnContinue )
            {
                /* This leaf is the match! */

                /* Reference it */
                NodeRef( pn );

                break;
            }
            else
            {
                /* Leaf it not a match. We must backtrack. We continue */
                /* to backtrack while either of the following is true: */
                /* - We (node just checked) were a left branch */
                /* - The PASSLEFT flag is not set on our parent */
                NODE* pnBranch;

                pnBranch = pn->pUp;
                while( (pnBranch->pLeft == pn) ||
                       !(pnBranch->Flags & NODE_FLG_PASSLEFT) )
                {
                    pn = pnBranch;
                    pnBranch = pn->pUp;
                }

                /* Once we get here (and we always will) we know we */
                /* were a right branch AND the PASSLEFT flag is set */
                /* on pnBranch. Therefore, we KNOW we're going left... */

                /* First apply the mask */
                dwMaskedAddr &= pnBranch->dwLastIPMask;

                /* Then go left */
                pn = pnBranch->pLeft;
            }
        }
    }

    /* If we were continuing, we done with the continue node. */
    if( pnContinue )
        NodeDeRef(pnContinue);

    return( pn );
}

/*-------------------------------------------------------------------- */
/* NodeDeRef() */
/* Called to POTENTIALLY remove a new leaf node, but will at least dec */
/* the RefCount. */
/*-------------------------------------------------------------------- */
void NodeDeRef( HANDLE h )
{
    NODE *pn = (NODE *)h;

#ifdef _STRONG_CHECKING
    /* We MUST start with a leaf node! */
    if( (pn->Type != HTYPE_NODE) || !(pn->Flags & NODE_FLG_LEAF) )
    {
        DbgPrintf(DBG_ERROR,"NodeDeRef: HTYPE %04x : Not Leaf",pn->Type);
        return;
    }
#endif

    /* Standard DeRef */
    if( pn->RefCount == 65535 )
        return;
    if( pn->RefCount > 1 )
    {
        pn->RefCount--;                /* Deref one count */
        return;
    }

    /* We only remove non-endpoint leafs */
    else if( !(pn->Flags & (NODE_FLG_ENDL|NODE_FLG_ENDR)) )
    {
        /* Here we must remove the node, and collapse one branch. */
        NODE *pnUp;
        NODE *pnUpUp;
        NODE *pnSurvivor;

        pnUp   = pn->pUp;
        pnUpUp = pnUp->pUp;

        /* Get a pointer to the surviving node */
        if( pnUp->pLeft == pn )
        {
            /* Leaf was left, so the survivor is right */
            pnSurvivor = pnUp->pRight;
        }
        else
        {
            /* Leaf was right, so the survivor is left */
            pnSurvivor = pnUp->pLeft;
        }

        /* Update survivor's parent */
        pnSurvivor->pUp = pnUpUp;

        /* Update removed branch's parent to point to surviving node */
        if( pnUpUp->pRight == pnUp )
        {
            /* Branch was right, so the survivor is now on right */
            pnUpUp->pRight = pnSurvivor;
        }
        else
        {
            /* Branch was left, so the survivor is now on left */
            pnUpUp->pLeft = pnSurvivor;

            /* This case is slightly more complicated, since */
            /* we need to update the pass left flag for (at least) */
            /* the UpUp node. */
            NodeUpdatePL( pnSurvivor );
        }

        /* Now we can remove the nodes */
        NodeFree( pn );
        NodeFree( pnUp );
    }
}

/*-------------------------------------------------------------------- */
/* NodeSetRt() */
/* Set NODE Route list head */
/*-------------------------------------------------------------------- */
void NodeSetRt( HANDLE h, HANDLE hRt )
{
    NODE *pn = (NODE *)h;

#ifdef _STRONG_CHECKING
    /* We MUST start with a leaf node! */
    if( (pn->Type != HTYPE_NODE) || !(pn->Flags & NODE_FLG_LEAF) )
    {
        DbgPrintf(DBG_ERROR,"NodeSetRt: HTYPE %04x : Not Leaf",pn->Type);
        return;
    }
#endif

    /* Set new route head */
    pn->hRt = hRt;
}

/*-------------------------------------------------------------------- */
/* NodeGetRt() */
/* Get Route at head of list */
/*-------------------------------------------------------------------- */
HANDLE NodeGetRt( HANDLE h )
{
    NODE *pn;

    if (!h) {
        DbgPrintf(DBG_ERROR,"NodeGetRt: received NULL handle");
        return(0);
    }

    pn = (NODE *)h;

#ifdef _STRONG_CHECKING
    /* We MUST start with a leaf node! */
    if( (pn->Type != HTYPE_NODE) || !(pn->Flags & NODE_FLG_LEAF) )
    {
        DbgPrintf(DBG_ERROR,"NodeGetRt: HTYPE %04x : Not Leaf",pn->Type);
        return(0);
    }
#endif

    /* Return the route handle */
    return( pn->hRt );
}

/*-------------------------------------------------------------------- */
/* NodeWalk() */
/* This function walks the node tree. It is used by RtWalk. */
/* CALLED IN CRIT SECTION ONLY! */
/*-------------------------------------------------------------------- */
HANDLE NodeWalk( HANDLE h )
{
    NODE *pn = (NODE *)h;
    NODE *pnUse = 0;

    if( !pn )
        pnUse = pRoot;
    else
    {
        /* Here we're continuing an old walk. If we were the left */
        /* node, try the right, else go up */
        NODE *pnParent = pn->pUp;

        while( pnParent && !pnUse )
        {
            if( pn == pnParent->pLeft && pnParent->pRight )
                pnUse = pnParent->pRight;
            else
            {
                pn = pnParent;
                pnParent = pnParent->pUp;
            }
        }
    }

    /* Walk to the first leaf */
    while( pnUse && !(pnUse->Flags & NODE_FLG_LEAF) )
    {
        if( pnUse->pLeft )
            pnUse = pnUse->pLeft;
        else
            pnUse = pnUse->pRight;
    }

    return( pnUse );
}

