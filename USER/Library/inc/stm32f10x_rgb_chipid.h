#ifndef __CHIPID_H
#define	__CHIPID_H

#include "stm32f10x.h"

#define ChipUniqueid0  *(__IO u32 *)(0X1FFFF7F0);
#define ChipUniqueid1  *(__IO u32 *)(0X1FFFF7EC);
#define ChipUniqueid2  *(__IO u32 *)(0X1FFFF7E8);

void Get_ChipID(void);

#endif /* __CHIPID_H */
