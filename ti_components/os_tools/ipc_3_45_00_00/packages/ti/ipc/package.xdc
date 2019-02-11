/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 */
/*
 *  ======== package.xdc ========
 *
 */

/*!
 *  ======== ti.ipc ========
 *  Inter processor communication common headers
 *
 *  This is a package that serves as a container for common header files
 *  for various IPC modules supplied with the IPC product.
 *
 *  @p(html)
 *  Documentation for all runtime APIs, instance configuration parameters,
 *  error codes macros and type definitions available to the application
 *  integrator can be found in the
 *  <A HREF="../../../doxygen/html/files.html">Doxygen documentation</A>
 *  for the IPC product.  However, the documentation presented in RTSC cdoc
 *  should be referred to for information specific to the RTSC module, such as
 *  module configuration, Errors, and Asserts.
 *  @p
 *
 *  The following table shows a list of all IPC modules that have common header
 *  files.  Follow the corresponding links for doxygen or cdoc documentation
 *  for each of the modules.
 *
 *  @p(html)
 *  <TABLE BORDER="1">
 *  <COLGROUP STYLE="font-weight: bold; color: rgb(0,127,102);"></COLGROUP>
 *  <COLGROUP></COLGROUP>
 *  <COLGROUP></COLGROUP>
 *  <COLGROUP></COLGROUP>
 *  <TR>
 *      <TD>GateMP</TD>
 *      <TD>Multiple processor gate that provides local and remote context protection</TD>
 *      <TD><A HREF="../../../doxygen/html/_gate_m_p_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/ipc/GateMP.html">cdoc</A></TD>
 *  </TR>
 *  <TR>
 *      <TD>HeapBufMP</TD>
 *      <TD>Multi-processor fixed-size buffer heap</TD>
 *      <TD><A HREF="../../../doxygen/html/_heap_buf_m_p_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/ipc/heaps/HeapBufMP.html">cdoc</A></TD>
 *  </TR>
 *  <TR>
 *      <TD>HeapMemMP</TD>
 *      <TD>Multi-processor variable size buffer heap </TD>
 *      <TD><A HREF="../../../doxygen/html/_heap_mem_m_p_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/ipc/heaps/HeapMemMP.html">cdoc</A></TD>
 *  </TR>
 *  <TR>
 *      <TD>HeapMultiBufMP</TD>
 *      <TD>Multiple fixed size buffer heap</TD>
 *      <TD><A HREF="../../../doxygen/html/_heap_multi_buf_m_p_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/ipc/heaps/HeapMultiBufMP.html">cdoc</A></TD>
 *  </TR>
 *  <TR>
 *      <TD>Ipc</TD>
 *      <TD>Ipc Manager</TD>
 *      <TD><A HREF="../../../doxygen/html/_ipc_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/ipc/Ipc.html">cdoc</A></TD>
 *  </TR>
 *  <TR>
 *      <TD>ListMP</TD>
 *      <TD>Multiple processor shared memory list</TD>
 *      <TD><A HREF="../../../doxygen/html/_list_m_p_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/ipc/ListMP.html">cdoc</A></TD>
 *  </TR>
 *  <TR>
 *      <TD>MessageQ</TD>
 *      <TD>Message-passing with queuing</TD>
 *      <TD><A HREF="../../../doxygen/html/_message_q_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/ipc/MessageQ.html">cdoc</A></TD>
 *  </TR>
 *  <TR>
 *      <TD>MultiProc</TD>
 *      <TD>Processor id manager</TD>
 *      <TD><A HREF="../../../doxygen/html/_multi_proc_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/utils/MultiProc.html">cdoc</A></TD>
 *  </TR>
 *  <TR>
 *      <TD>NameServer</TD>
 *      <TD>Name manager</TD>
 *      <TD><A HREF="../../../doxygen/html/_name_server_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/utils/NameServer.html">cdoc</A></TD>
 *  </TR>
 *  <TR>
 *      <TD>Notify</TD>
 *      <TD>Notification manager for IPC</TD>
 *      <TD><A HREF="../../../doxygen/html/_notify_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/ipc/Notify.html">cdoc</A></TD>
 *  </TR>
 *  <TR>
 *      <TD>SharedRegion</TD>
 *      <TD>Shared memory manager and address translator </TD>
 *      <TD><A HREF="../../../doxygen/html/_shared_region_8h.html">Doxygen</A></TD>
 *      <TD><A HREF="../sdo/ipc/SharedRegion.html">cdoc</A></TD>
 *  </TR>
 *
 *  </TABLE>
 *  @p
 *
 */

package ti.ipc [1,0,0,0] {

}
