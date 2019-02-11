/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/


//---
// Variable initialization section
//---

#define UINT32 unsigned int
#define UINT8  char
uint32_t TestCaseStatus = 1;

//---
// Register Write fn call
//---
void
reg_write_32 (UINT32 addr, UINT32 write_data)
{
  (*(UINT32 *) (addr)) = write_data;
}

UINT32
reg_read_32 (UINT32 addr)
{
  UINT32 read_data;
  read_data = (*(UINT32 *) (addr));
  return read_data;
}

void
cc_reg_write (UINT32 addr, UINT32 write_data)
{
  reg_write_32 (addr, write_data);
}

//---
// Register Read fn call
//---

void
cc_reg_read (UINT32 addr)
{
  reg_read_32 (addr);
}

//---
// Register addr computation fn call
//---

UINT32
cc_reg_addr_trans (UINT32 base, UINT32 offset)
{
  UINT32 reg_addr;
  reg_addr = base + offset;
  return reg_addr;
}

//---
// No operation timing loop fn call
//---

void
cc_no_op (UINT32 noopcount)
{
  int i;
  for (i = 0; i < noopcount; i++)
    {
      ;
    }
}

//---
// Function adds the base add and offset add and stores the result into a new mem_addr
//---

UINT32
cc_mem_addr_trans (UINT32 base, UINT32 offset)
{
  UINT32 mem_addr;
  mem_addr = base + offset;
  return mem_addr;
}

// ---
// This function compares the value of the memory location with the value provided in the parameter and the bits compared are the bits provided in the second parameter.
// ---

void
cc_poll_reg (UINT32 src, UINT32 comparedata, UINT32 maskbits)
{
  volatile UINT32 temp;
  volatile UINT32 *rd_addr_ptr;

  rd_addr_ptr = (UINT32 *) src;

  temp = *rd_addr_ptr;

  while (comparedata != (temp & maskbits))
    {
      temp = *rd_addr_ptr;

    }
}

//---
// This function compares the data in the memory with the array. The comparision is done for the size count provided.
//---
//
// This function compares the content of memory with data pattern provided in array

void
register_check_32 (UINT32 addr, UINT32 expected_data)
{
  UINT32 read_data;
  read_data = (*(UINT32 *) (addr));
  if (read_data == expected_data)
    {
      //RES_Set(RES_OK);
    }
  else
    {
      //RES_Set(RES_BAD);
    }
}

void
reg_check_32 (UINT32 addr, UINT32 expected_data)
{
  volatile UINT32 read_data;
  read_data = (*(volatile UINT32 *) (addr));

  if (read_data == expected_data)
    {
      //RES_Set(RES_OK);
      TestCaseStatus = TestCaseStatus & 1;
    }
  else
    {
      //RES_Set(RES_BAD);
      TestCaseStatus = TestCaseStatus & 0;
    }
}

void
memory_check (unsigned int strt_addr, unsigned char *ptr, unsigned int sz)
{
  /* Data are in bytes */
  int i;
  for (i = 0; i < (sz); i += 4)
    {
      reg_check_32 ((strt_addr + i),
          (ptr[i] + (ptr[i + 1] << 8) + (ptr[i + 2] << 16) +
           (ptr[i + 3] << 24)));
    }            //for_loop
}


//---
// This function writes the memory locations with the data pointer passed. It also receives the number of bytes to be written.
//---

void
cc_mem_write (UINT32 strt_addr, UINT8 ptr[], UINT32 sz)
{
  UINT32 write_data;
  int i;
  for (i = 0; i < (sz); i += 4)
    {
      write_data =
   ptr[i] + (ptr[i + 1] << 8) + (ptr[i + 2] << 16) + (ptr[i + 3] << 24);
      (*(UINT32 *) (strt_addr + i)) = write_data;
    }
}

//----
// Expected data that'll be compared with the data written into receive memory to confirm if tx and rx data r same.
//----

unsigned char expec_data0[] = { 0xff, 0xff, 0xff, 0xff };
unsigned char expec_data1[] = { 0xff, 0xff, 0x10, 0x32 };
unsigned char expec_data2[] = { 0x54, 0x56, 0x98, 0xba };
unsigned char expec_data3[] = { 0x00, 0x2e, 0x01, 0x02 };
unsigned char expec_data4[] = { 0x03, 0x04, 0x05, 0x06 };
unsigned char expec_data5[] = { 0x07, 0x08, 0x09, 0x0a };
unsigned char expec_data6[] = { 0x0b, 0x0c, 0x0d, 0x0e };
unsigned char expec_data7[] = { 0x0f, 0x10, 0x11, 0x12 };
unsigned char expec_data8[] = { 0x13, 0x14, 0x15, 0x16 };
unsigned char expec_data9[] = { 0x17, 0x18, 0x19, 0x1a };
unsigned char expec_data10[] = { 0x1b, 0x1c, 0x1d, 0x1e };
unsigned char expec_data11[] = { 0x1f, 0x20, 0x21, 0x22 };
unsigned char expec_data12[] = { 0x23, 0x24, 0x25, 0x26 };
unsigned char expec_data13[] = { 0x27, 0x28, 0x29, 0x2a };
unsigned char expec_data14[] = { 0x2b, 0x2c, 0x2d, 0x2e };
unsigned char expec_data15[] = { 0x85, 0xe0, 0x73, 0x3d };

unsigned char expec_2pkt_data0[] = { 0xff, 0xff, 0xff, 0xff };
unsigned char expec_2pkt_data1[] = { 0xff, 0xff, 0x10, 0x32 };
unsigned char expec_2pkt_data2[] = { 0x54, 0x56, 0x98, 0xba };
unsigned char expec_2pkt_data3[] = { 0x00, 0x2e, 0x01, 0x02 };
unsigned char expec_2pkt_data4[] = { 0x03, 0x04, 0x05, 0x06 };
unsigned char expec_2pkt_data5[] = { 0x07, 0x08, 0x09, 0x0a };
unsigned char expec_2pkt_data6[] = { 0x0b, 0x0c, 0x0d, 0x0e };
unsigned char expec_2pkt_data7[] = { 0x0f, 0x10, 0x11, 0x12 };
unsigned char expec_2pkt_data8[] = { 0x13, 0x14, 0x15, 0x16 };
unsigned char expec_2pkt_data9[] = { 0x17, 0x18, 0x19, 0x1a };
unsigned char expec_2pkt_data10[] = { 0x1b, 0x1c, 0x1d, 0x1e };
unsigned char expec_2pkt_data11[] = { 0x1f, 0x20, 0x21, 0x22 };
unsigned char expec_2pkt_data12[] = { 0x23, 0x24, 0x25, 0x26 };
unsigned char expec_2pkt_data13[] = { 0x27, 0x28, 0x29, 0x2a };
unsigned char expec_2pkt_data14[] = { 0x2b, 0x2c, 0x2d, 0x2e };
unsigned char expec_2pkt_data15[] = { 0x2f, 0x30, 0x31, 0x32 };
unsigned char expec_2pkt_data16[] = { 0x33, 0x34, 0x35, 0x36 };
unsigned char expec_2pkt_data17[] = { 0x37, 0x38, 0x39, 0x3a };
unsigned char expec_2pkt_data18[] = { 0x3b, 0x3c, 0x3d, 0x3e };
unsigned char expec_2pkt_data19[] = { 0x3f, 0x40, 0x41, 0x42 };
unsigned char expec_2pkt_data20[] = { 0x43, 0x44, 0x45, 0x46 };
unsigned char expec_2pkt_data21[] = { 0x47, 0x48, 0x49, 0x4a };
unsigned char expec_2pkt_data22[] = { 0x4b, 0x4c, 0x4d, 0x4e };
unsigned char expec_2pkt_data23[] = { 0x4f, 0x50, 0x51, 0x52 };
unsigned char expec_2pkt_data24[] = { 0x53, 0x54, 0x55, 0x56 };
unsigned char expec_2pkt_data25[] = { 0x57, 0x58, 0x59, 0x5a };
unsigned char expec_2pkt_data26[] = { 0x5b, 0x5c, 0x74, 0xe2 };
unsigned char expec_2pkt_data27[] = { 0x6d, 0x96, 0x00, 0x00 };

unsigned char expec_rdata[] = { 0x01, 0x00, 0x00, 0x00 };
unsigned char expec_rdata_zeros[] = { 0x00, 0x00, 0x00, 0x00 };
unsigned char expec_rdata_0f[] = { 0x0f, 0x00, 0x00, 0x00 };
