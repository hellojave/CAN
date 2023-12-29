#include "stm32f10x.h"
#include "CAN.h"
void CAN_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 使能CAN时钟 */
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_CAN1 , ENABLE );
	
	/* 使能CAN引脚相关的时钟 */
 	RCC_APB2PeriphClockCmd ( CAN_GPIO_CLK|RCC_APB2Periph_AFIO, ENABLE );
	
	//使用PA8 9引脚的第二功能
	GPIO_PinRemapConfig (GPIO_Remap1_CAN1 ,ENABLE);
	
  /* 配置CAN的 引脚，普通IO即可 */
  GPIO_InitStructure.GPIO_Pin = CAN_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(CAN_TX_GPIO_PROT, &GPIO_InitStructure);
	
	  /* 配置CAN的 引脚，普通IO即可 */
  GPIO_InitStructure.GPIO_Pin = CAN_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStructure);
	
}


void CAN_Mode_Config(void)	
{

	CAN_InitTypeDef CAN_InitTypeStruct;
	
	CAN_InitTypeStruct.CAN_ABOM = ENABLE;
	CAN_InitTypeStruct.CAN_AWUM = ENABLE;
	CAN_InitTypeStruct.CAN_Mode =CAN_Mode_LoopBack;//CAN_Mode_Normal;//调试时建议使用回环模式，调试完再改成NORMAL
	CAN_InitTypeStruct.CAN_NART = ENABLE; //错误重传
	CAN_InitTypeStruct.CAN_RFLM = ENABLE;
	CAN_InitTypeStruct.CAN_TTCM = DISABLE;
	CAN_InitTypeStruct.CAN_TXFP = DISABLE; //按ID优先级发送
	
	//配置成1Mbps
	CAN_InitTypeStruct.CAN_BS1 = CAN_BS1_5tq;
	CAN_InitTypeStruct.CAN_BS2 = CAN_BS2_3tq;
	CAN_InitTypeStruct.CAN_SJW = CAN_SJW_2tq;
	CAN_InitTypeStruct.CAN_Prescaler = 4;
	
	
	CAN_Init(CAN1,&CAN_InitTypeStruct);

}



void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitTypeStruct;
	
	CAN_FilterInitTypeStruct.CAN_FilterActivation = ENABLE;
	CAN_FilterInitTypeStruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0  ;
	CAN_FilterInitTypeStruct.CAN_FilterNumber = 0;
	CAN_FilterInitTypeStruct.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitTypeStruct.CAN_FilterMode = CAN_FilterMode_IdMask  ;
	
	CAN_FilterInitTypeStruct.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitTypeStruct.CAN_FilterIdLow = 0x0000;
	
	CAN_FilterInitTypeStruct.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitTypeStruct.CAN_FilterMaskIdLow =0x0000;	

	CAN_FilterInit(&CAN_FilterInitTypeStruct);

	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
	
}	

void CAN_NVIC_Config(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);


  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 配置子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


  void RECIVE_CAN(CanRxMsg *RxMessage)
{
	/*读取报文*/

	
  uint8_t ubCounter = 0;


	/*把接收结构体清零*/
  RxMessage->StdId = 0;
  //RxMessage->ExtId = 0x203;
  RxMessage->IDE = CAN_ID_STD;
  RxMessage->DLC = 0x08;
  RxMessage->FMI = 0;
  for (ubCounter = 0; ubCounter < 8; ubCounter++)
  {
    RxMessage->Data[ubCounter] = 0;
  }
	
}


void CAN_Config(void)	
{
	CAN_GPIO_Config();
  CAN_Mode_Config();
	CAN_Filter_Config();
	CAN_NVIC_Config();
}
   
/*********************************************END OF FILE**********************/
