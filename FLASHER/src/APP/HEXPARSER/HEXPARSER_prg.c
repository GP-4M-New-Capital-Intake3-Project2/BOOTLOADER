/*
 * HEXPARSER_prg.c
 *
 *  Created on: Sep 26, 2023
 *      Author: admin
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/FMI/FMI_Interface.h"

#define BASE_ADDRESS    0x08000000
//'0' --> 0   '0'-'0' = 0;   //'0' = 48  '1' = 49
//'1' --> 1   '1'-'0' = 1;
//'9' --> 9   '9'-'0' = 9;

//'A' --> 10  'A'-'A'+10=10;
//'B' --> 11  'B'-'A'+10=11;
//'f'

extern FMI_WriteOperationData mydata;

u8 HEXPARSER_su8AsciiToHex(u8 A_u8Ascii)
{
	u8 L_u8ReturnHex=0;
	/*0-->9*/
	if(A_u8Ascii>='0' && A_u8Ascii<='9')
	{
		L_u8ReturnHex = A_u8Ascii-'0';
	}
	/*A-->F*/ //10-->15
	else if(A_u8Ascii>='A' && A_u8Ascii<='F')
	{
		L_u8ReturnHex = A_u8Ascii - 'A' +10 ;
	}
	else if(A_u8Ascii>='a' && A_u8Ascii<='f')
	{
		L_u8ReturnHex = A_u8Ascii - 'a' +10 ;
	}
	return L_u8ReturnHex;
}
////////////////////////////////////////////////////
//parse Data   (string to hex)+write on flash
//u32 address =  lower address | (higher address<<16);
//u16 arr_data[10]={0x0000,0x0120,0x6142,...,etc};
//NO_element = 0x10/2; //8
//flashwrite(address,u16 arr_data,NO_element);
//////////////////////////////////////////////////
//u8 arr[]=": 10 4000 00 0000 0120 614200086542000867420008 84" string--> hex/decimal
//0x00  one byte
//hexdecimal
//: 10 4000 00 0000 0120 6142 0008 6542 0008 6742 0008 84
//Record
//arr[0] --> : start of record
//arr[1,2]  --> CC  chracter count(u8 hex) 0x10 --> 16 character(hex) ok
//arr[3-->6] --> lower address  ok
//arr[7,8] --> Data type
//00   data,instruction
//01   End of file (EOF)   ok
//04   higher address arr[9--->12]  ok    ":020000 04 0800 F2"
//05   absolute address
//arr[9-->etc]  --> Data   ok
//last two indexes (Check sum)
//////////////////////////////////////////////////////////////
u32 G_u32Higher=0 ;
void HEXPARESR_vParseRecordAndFlashIt(u8* A_pu8Record)
{
	u8  L_u8NOElementInRecord ; // arr[1,2]
	u8  CC_L , CC_H ;
	u32 L_AddressOfRecord=0,LowerAddress;
	u8 digit3 , digit2, digit1, digit0 ;
	u8 L_u16DataOfRecord[16]; // arr[9,....]
if(A_pu8Record[8] == '4')
{
	     G_u32Higher=0;
	     digit0 =  HEXPARSER_su8AsciiToHex(A_pu8Record[9]);
		 digit1 =  HEXPARSER_su8AsciiToHex(A_pu8Record[10]);
		 digit2 =  HEXPARSER_su8AsciiToHex(A_pu8Record[11]);
		 digit3 =  HEXPARSER_su8AsciiToHex(A_pu8Record[12]);
		G_u32Higher = (digit0<<12) |(digit1<<8)|(digit2<<4)|(digit3);
}
else if(A_pu8Record[8] == '0'){
	// 0x10 =0xCC_H CC_L
		CC_H = HEXPARSER_su8AsciiToHex(A_pu8Record[1]); // 1
		CC_L = HEXPARSER_su8AsciiToHex(A_pu8Record[2]);
		L_u8NOElementInRecord = CC_L | (CC_H<<4);//ok // 0x10  --> 0b 0001 0000 = 0b0000 0000 | (0b0000 0001<<4)
		// 0x4000 = 0100 0000 0000 0000    12,8,4,0
		//indexInArr  3   4    5    6
		//         digit0 , digit1, digit2, digit3
		 digit0 =  HEXPARSER_su8AsciiToHex(A_pu8Record[3]);
		 digit1 =  HEXPARSER_su8AsciiToHex(A_pu8Record[4]);
		 digit2 =  HEXPARSER_su8AsciiToHex(A_pu8Record[5]);
		 digit3 =  HEXPARSER_su8AsciiToHex(A_pu8Record[6]);
		 LowerAddress=0;
		 LowerAddress = (digit0<<12) |(digit1<<8)|(digit2<<4)|(digit3); // 0x4000
//		 L_AddressOfRecord = LowerAddress | BASE_ADDRESS ; //ok
		 mydata.StartAddress &= ~(0x0000ffff);
		 mydata.StartAddress |= LowerAddress;
		 // OR
		 if(G_u32Higher == 0)
		 {
			 G_u32Higher = 0x800;
		 }
		 L_AddressOfRecord = LowerAddress | (G_u32Higher<<16) ; //ok
		 /*
		 //Data of record index 9 ---> 9+L_u8NOElementInRecord
		 //0 0  0 0    0120 6142 0008 6542 0008 6742 0008  // 12 35   0x  3512
		 //9 10 11 12 , 13,  17 , 21
		 //digit0 ,1,2,3
		  * */
//		 if((L_u8NOElementInRecord %2) == 1){
//			 A_pu8Record[L_u8NOElementInRecord*2+9] = 'F';
//			 A_pu8Record[L_u8NOElementInRecord*2+10] = 'F';
//			 L_u8NOElementInRecord++;
//		 }
		 for(u8  L_u8Counter=0;L_u8Counter<L_u8NOElementInRecord;L_u8Counter++) // u16
		 {
			 digit0 =  HEXPARSER_su8AsciiToHex(A_pu8Record[L_u8Counter*2+9]);
			 digit1 =  HEXPARSER_su8AsciiToHex(A_pu8Record[L_u8Counter*2+10]);
//			 digit2 =  HEXPARSER_su8AsciiToHex(A_pu8Record[L_u8Counter*4+11]);
//			 digit3 =  HEXPARSER_su8AsciiToHex(A_pu8Record[L_u8Counter*4+12]);
			 L_u16DataOfRecord[L_u8Counter]= (digit0<<4) |(digit1);
//			 L_u16DataOfRecord[L_u8Counter]= (digit2<<12) |(digit3<<8)|(digit0<<4)|(digit1);
		 }
//		 MFMI_vFlashWrite(L_AddressOfRecord,L_u16DataOfRecord,L_u8NOElementInRecord/2);
		 mydata.Data = L_u16DataOfRecord;
		 mydata.DataSize = (L_u8NOElementInRecord);
		 MFMI_vFlashWrite(&mydata);
}

}



