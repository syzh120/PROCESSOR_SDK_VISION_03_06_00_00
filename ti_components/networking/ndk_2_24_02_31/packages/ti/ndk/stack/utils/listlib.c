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
 * ======== listlib.c ========
 *
 * Implementation of a doubly linked list.
 *
 */

/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/

#include <stkmain.h>

/**********************************************************************
 *************************** LISTLIB FUNCTIONS ************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function is called to add a node to the list.
 *
 *  @param[in]  ptr_list
 *      This is the list to which the node is to be added. 
 *  @param[in]  ptr_node
 *      This is the node which is to be added.
 *
 *  @retval
 *      Not Applicable
 */
void list_add (LIST_NODE **ptr_list, LIST_NODE *ptr_node)
{
	LIST_NODE*	ptr_head;

	/* Check if the list is empty ? */
	if (*ptr_list == NULL)
	{
		/* YES the list is empty. Initialize the links */
		ptr_node->p_next = NULL;
        ptr_node->p_prev = NULL;

		/* Initialize the LIST */
		*ptr_list = ptr_node;
		return;
	}

	/* No the list was NOT empty. Add the node to the beginning of list. 
     * Get the current head of the list. */
	ptr_head = *ptr_list;

	/* Initialize the new head of the list. */
	ptr_node->p_next  = ptr_head;
    ptr_node->p_prev = NULL;

    /* Update the old head to point to the new head */
    ptr_head->p_prev = ptr_node;

    /* Update the pointer to the head of the list. */
	*ptr_list = ptr_node;
	return;
}

/** 
 *  @b Description
 *  @n  
 *      The function is called to concatenate the src list to the end of the 
 *      destination list.
 *
 *  @param[in]  ptr_dst
 *      This is the head of the destination list.
 *  @param[in]  ptr_src
 *      This is the head of the source list.
 *
 *  @retval
 *      Not Applicable
 */
void list_cat (LIST_NODE **ptr_dst, LIST_NODE **ptr_src)
{
	LIST_NODE*	ptr_node;
	LIST_NODE*	ptr_prev;

	/* Is the source list empty ? */
	if (*ptr_src == NULL)
		return;

	/* Is the destination list empty ? */
	if (*ptr_dst == NULL)
	{
		/* Make the source now as the destination. */
		*ptr_dst = *ptr_src;
		return;
	}

	/* Both the lists are not empty. */
	ptr_node = *ptr_dst;
	ptr_prev = NULL;

	/* Reach the end of the list. */
	while (ptr_node != NULL)
	{
		ptr_prev = ptr_node;
		ptr_node = ptr_node->p_next;
	}

	/* Link the last element to the source list. */
	ptr_prev->p_next = *ptr_src;
    (*ptr_src)->p_prev = ptr_prev;
	return;
}

/**
 *  @b Description
 *  @n  
 *      The function is called to remove the head node from the list. 
 *
 *  @param[in]  ptr_list
 *      This is the pointer to the list from where nodes will be removed.
 *
 *  @retval
 *      Pointer to the head of the list. 
 */
LIST_NODE* list_remove (LIST_NODE **ptr_list)
{
	LIST_NODE*	ptr_head;
	LIST_NODE*	ptr_node;

	/* Check if the list is empty ? */
	if (*ptr_list == NULL)
		return NULL;

	/* Get the head of the list. */
	ptr_node = *ptr_list;

	/* Move the head to the next element in the list. */
	ptr_head = ptr_node->p_next;
	*ptr_list = ptr_head;

    /* Did we remove the last element?*/
    if (ptr_head != NULL)
    {
        /* No; in that case update the pointers for the new head. */
        ptr_head->p_prev = NULL;
    }

	/* Kill the links before returning the OLD head. */
	ptr_node->p_next = NULL;
    ptr_node->p_prev = NULL;
	return ptr_node;
}

/**
 *  @b Description
 *  @n  
 *      The function is called to remove the specified node from the list. 
 *
 *  @param[in]  ptr_list
 *      This is the pointer to the list from where node will be removed.
 *  @param[in]  ptr_remove
 *      This is the node which is to be removed.
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   -1
 */
int list_remove_node (LIST_NODE **ptr_list, LIST_NODE *ptr_remove)
{
	LIST_NODE*	ptr_next;
	LIST_NODE*	ptr_prev;

    /* Are there any nodes in the list? */
    if (*ptr_list == NULL)
		return -1;

    /* Are we removing the head? */
    if (ptr_remove == *ptr_list)
    {
        /* Use the other API to acheive the needful. */
        list_remove (ptr_list);
        return 0;
    }

    /* OK; we are trying to remove a non head element; so lets get the
     * previous and next pointer of the elements that needs to be removed. */
    ptr_prev = ptr_remove->p_prev;
    ptr_next = ptr_remove->p_next;

    /* Kill the Links for element that is being removed. */
    ptr_remove->p_prev = NULL;
    ptr_remove->p_next = NULL;

    /* Are we removing the last element */
    if (ptr_next == NULL)
    {
        /* The last element points to nothing. */
        ptr_prev->p_next = NULL;
        return 0;
    }

    /* We are trying to remove an element in the middle of the list. */
	ptr_prev->p_next = ptr_next;
    ptr_next->p_prev = ptr_prev;

	/* Successful. */
	return 0;
}

/**
 *  @b Description
 *  @n  
 *      The function is used to get the head of the specific list
 *
 *  @param[in]  ptr_list
 *      This is the pointer to the list. 
 *
 *  @retval
 *      Head of the list (could be NULL if the list is empty)
 */
LIST_NODE* list_get_head (LIST_NODE **ptr_list)
{
	return *ptr_list;
}

/**
 *  @b Description
 *  @n  
 *      The function is used to get the next element in the list.
 *
 *  @param[in]  ptr_list
 *      This is the pointer to the node in the list. 
 *
 *  @retval
 *      Next element in the list. (could be NULL if this is the last element)
 */
LIST_NODE* list_get_next (LIST_NODE *ptr_list)
{	
	return ptr_list->p_next;
}

/**
 *  @b Description
 *  @n  
 *      The function is used to clean a list which has been replicated.
 *  @sa
 *      list_replicate
 *
 *  @param[in]  ptr_list
 *      This is the pointer to list which has been replicated and now needs
 *      to be cleaned up. 
 *  @param[in]  free
 *      This is the memory cleanup API which is invoked to clean the nodes in
 *      the list.
 *          
 *  @retval
 *      Not Applicable.
 */
void list_clean (LIST_NODE* ptr_list, void free (void *ptr))
{
    LIST_NODE*  ptr_node;

    /* Remove the head of the list. */
    ptr_node = list_remove (&ptr_list);
    while (ptr_node != NULL)
    {
        /* Cleanup the memory */
        free (ptr_node);

        /* Remove the next head of the list. */
        ptr_node = list_remove (&ptr_list);
    }

    /* Work has been done. */
    return;
}

/**
 *  @b Description
 *  @n  
 *      The function is used to replicate a list. Replicating a list
 *      implies that each node in the source list is copied into the
 *      destination node and added to a destination list. This API
 *      involves memory allocation and callees are responsible for 
 *      cleaning up the memory.
 *  @sa
 *      list_clean
 *
 *  @param[in]  ptr_srcList
 *      This is the pointer to source list which needs to be replicated.
 *  @param[in]  size
 *      Size of the Node which is to be copied.
 *  @param[in]  alloc
 *      Memory Allocation API which is to be used.
 *  @param[in]  free
 *      Memory cleanup API which is to be used.
 *          
 *  @retval
 *      Pointer to the head of the 'new' replicated list.
 */
LIST_NODE* list_replicate (LIST_NODE* ptr_srcList, int size, void* alloc(UINT32 size), void free (void *ptr))
{
    LIST_NODE*  ptr_dstList;
    LIST_NODE*  ptr_dstNode;
    LIST_NODE*  ptr_srcNode;

    /* Initialize the destination list. */
    ptr_dstList = NULL;

    /* Cycle through the src list. */
    ptr_srcNode = list_get_head (&ptr_srcList);
    while (ptr_srcNode != NULL)
    {
        /* Allocate memory for the destination node. */
        ptr_dstNode = alloc(size);
        if (ptr_dstNode == NULL)
        {
            /* Error: Unable to allocate memory. Cleanup any elements which have been added
             * to the destination list. */
            list_clean (ptr_dstList, free); 
            return NULL;
        }

        /* Initialize the allocated block of memory. */
        mmCopy ((void *)ptr_dstNode, (void *)ptr_srcNode, size);

        /* Add to the list. */
        list_add (&ptr_dstList, ptr_dstNode);

        /* Get the next element in the list. */
        ptr_srcNode = list_get_next (ptr_srcNode);
    }

    /* Return the replicated list. */
    return ptr_dstList;
}

