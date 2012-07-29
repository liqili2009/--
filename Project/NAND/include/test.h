/*-----------------------------------------------------------------------
/  Low level disk interface modlue include file
/-----------------------------------------------------------------------*/
#ifndef __test_H
#define __test_H

#define BUFFER_SIZE         0x800
void Fill_Buffer(u8 *pBuffer, u16 BufferLenght, u32 Offset);
void test_nandflsh_write_and_read(void);
void test_Fatfs_write_and_read(void);
#endif
