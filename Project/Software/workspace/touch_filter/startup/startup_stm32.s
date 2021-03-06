/**
  ******************************************************************************
  * @file      startup_stm32.s
  * @author    Ac6
  * @version   V1.0.0
  * @date      12-June-2014
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m4
  .thumb

.global	g_pfnVectors
.global	Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word	_sidata
/* start address for the .data section. defined in linker script */
.word	_sdata
/* end address for the .data section. defined in linker script */
.word	_edata
/* start address for the .bss section. defined in linker script */
.word	_sbss
/* end address for the .bss section. defined in linker script */
.word	_ebss

.equ  BootRAM,        0xF1E0F85F
/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section	.text.Reset_Handler
	.weak	Reset_Handler
	.type	Reset_Handler, %function
Reset_Handler:

/* Copy the data segment initializers from flash to SRAM */
  movs	r1, #0
  b	LoopCopyDataInit

CopyDataInit:
	ldr	r3, =_sidata
	ldr	r3, [r3, r1]
	str	r3, [r0, r1]
	adds	r1, r1, #4

LoopCopyDataInit:
	ldr	r0, =_sdata
	ldr	r3, =_edata
	adds	r2, r0, r1
	cmp	r2, r3
	bcc	CopyDataInit
	ldr	r2, =_sbss
	b	LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
	movs r3, #0
 	str  r3, [r2]
	adds r2, r2, #4

LoopFillZerobss:
	ldr	r3, = _ebss
	cmp	r2, r3
	bcc	FillZerobss

/* Call the clock system intitialization function.*/
    bl  SystemInit
/* Call static constructors */
    bl __libc_init_array
/* Call the application's entry point.*/
	bl	main

LoopForever:
    b LoopForever

.size	Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section	.text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
	b	Infinite_Loop
	.size	Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex-M.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
 	.section	.isr_vector,"a",%progbits
	.type	g_pfnVectors, %object
	.size	g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
	.word	_estack                 /* 0x0000 0000 */
	.word	Reset_Handler           /* 0x0000 0004 */
	.word	NMI_Handler             /* 0x0000 0008 */
	.word	HardFault_Handler       /* 0x0000 000C */
	.word	MemManage_Handler       /* 0x0000 0010 */
	.word	BusFault_Handler        /* 0x0000 0014 */
	.word	UsageFault_Handler      /* 0x0000 0018 */
	.word	0                       /* 0x0000 001C */
	.word	0                       /* 0x0000 0020 */
	.word	0                       /* 0x0000 0024 */
	.word	0                       /* 0x0000 0028 */
	.word	SVC_Handler             /* 0x0000 002C */
	.word	DebugMon_Handler        /* 0x0000 0030 */
	.word	0                       /* 0x0000 0034 */
	.word	PendSV_Handler          /* 0x0000 0038 */
	.word	SysTick_Handler         /* 0x0000 003C */
	.word	dummy_Handler           /* 0x0000 0040 */
	.word	dummy_Handler           /* 0x0000 0044 */
	.word	dummy_Handler           /* 0x0000 0048 */
	.word	dummy_Handler           /* 0x0000 004C */
	.word	dummy_Handler           /* 0x0000 0050 */
	.word	dummy_Handler           /* 0x0000 0054 */
	.word	dummy_Handler           /* 0x0000 0058 */
	.word	dummy_Handler           /* 0x0000 005C */
	.word	dummy_Handler           /* 0x0000 0060 */
	.word	dummy_Handler           /* 0x0000 0064 */
	.word	dummy_Handler           /* 0x0000 0068 */
	.word	DMA1_Stream0_IRQHandler /* 0x0000 006C */
	.word	DMA1_Stream1_IRQHandler /* 0x0000 0070 */
	.word	DMA1_Stream2_IRQHandler /* 0x0000 0074 */
	.word	DMA1_Stream3_IRQHandler /* 0x0000 0078 */
	.word	DMA1_Stream4_IRQHandler /* 0x0000 007C */
	.word	DMA1_Stream5_IRQHandler /* 0x0000 0080 */
	.word	DMA1_Stream6_IRQHandler /* 0x0000 0084 */
	.word	dummy_Handler           /* 0x0000 0088 */
	.word	dummy_Handler           /* 0x0000 008C */
	.word	dummy_Handler           /* 0x0000 0090 */
	.word	dummy_Handler           /* 0x0000 0094 */
	.word	dummy_Handler           /* 0x0000 0098 */
	.word	dummy_Handler           /* 0x0000 009C */
	.word	dummy_Handler           /* 0x0000 00A0 */
	.word	dummy_Handler           /* 0x0000 00A4 */
	.word	dummy_Handler           /* 0x0000 00A8 */
	.word	dummy_Handler           /* 0x0000 00AC */
	.word	dummy_Handler           /* 0x0000 00B0 */
	.word	dummy_Handler           /* 0x0000 00B4 */
	.word	dummy_Handler           /* 0x0000 00B8 */
	.word	dummy_Handler           /* 0x0000 00BC */
	.word	dummy_Handler           /* 0x0000 00C0 */
	.word	dummy_Handler           /* 0x0000 00C4 */
	.word	dummy_Handler           /* 0x0000 00C8 */
	.word	dummy_Handler           /* 0x0000 00CC */
	.word	dummy_Handler           /* 0x0000 00D0 */
	.word	dummy_Handler           /* 0x0000 00D4 */
	.word	dummy_Handler           /* 0x0000 00D8 */
	.word	dummy_Handler           /* 0x0000 00DC */
	.word	dummy_Handler           /* 0x0000 00E0 */
	.word	dummy_Handler           /* 0x0000 00E4 */
	.word	dummy_Handler           /* 0x0000 00E8 */
	.word	dummy_Handler           /* 0x0000 00EC */
	.word	dummy_Handler           /* 0x0000 00F0 */
	.word	dummy_Handler           /* 0x0000 00F4 */
	.word	dummy_Handler           /* 0x0000 00F8 */
	.word	dummy_Handler           /* 0x0000 00FC */
	.word	dummy_Handler           /* 0x0000 0100 */
	.word	dummy_Handler           /* 0x0000 0104 */
	.word	dummy_Handler           /* 0x0000 0108 */
	.word	dummy_Handler           /* 0x0000 010C */
	.word	UART4_IRQHandler        /* 0x0000 0110 */
	.word	dummy_Handler           /* 0x0000 0114 */
	.word	dummy_Handler           /* 0x0000 0118 */
	.word	dummy_Handler           /* 0x0000 011C */
	.word	DMA2_Stream0_IRQHandler /* 0x0000 0120 */
	.word	DMA2_Stream1_IRQHandler /* 0x0000 0124 */
	.word	DMA2_Stream2_IRQHandler /* 0x0000 0128 */
	.word	DMA2_Stream3_IRQHandler /* 0x0000 012C */
	.word	DMA2_Stream4_IRQHandler /* 0x0000 0130 */
	.word	dummy_Handler           /* 0x0000 0134 */
	.word	dummy_Handler           /* 0x0000 0138 */
	.word	dummy_Handler           /* 0x0000 013C */
	.word	dummy_Handler           /* 0x0000 0140 */
	.word	dummy_Handler           /* 0x0000 0144 */
	.word	dummy_Handler           /* 0x0000 0148 */
	.word	dummy_Handler           /* 0x0000 014C */
	.word	dummy_Handler           /* 0x0000 0150 */
	.word	dummy_Handler           /* 0x0000 0154 */
	.word	dummy_Handler           /* 0x0000 0158 */
	.word	dummy_Handler           /* 0x0000 015C */
	.word	dummy_Handler           /* 0x0000 0160 */
	.word	dummy_Handler           /* 0x0000 0164 */
	.word	dummy_Handler           /* 0x0000 0168 */
	.word	dummy_Handler           /* 0x0000 016C */
	.word	dummy_Handler           /* 0x0000 0170 */
	.word	dummy_Handler           /* 0x0000 0174 */
	.word	dummy_Handler           /* 0x0000 0178 */
	.word	dummy_Handler           /* 0x0000 017C */
	.word	dummy_Handler           /* 0x0000 0180 */
	.word	dummy_Handler           /* 0x0000 0184 */
/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  	.weak	NMI_Handler
	.thumb_set NMI_Handler,Default_Handler

  	.weak	HardFault_Handler
	.thumb_set HardFault_Handler,Default_Handler

  	.weak	MemManage_Handler
	.thumb_set MemManage_Handler,Default_Handler

  	.weak	BusFault_Handler
	.thumb_set BusFault_Handler,Default_Handler

	.weak	UsageFault_Handler
	.thumb_set UsageFault_Handler,Default_Handler

	.weak	SVC_Handler
	.thumb_set SVC_Handler,Default_Handler

	.weak	DebugMon_Handler
	.thumb_set DebugMon_Handler,Default_Handler

	.weak	PendSV_Handler
	.thumb_set PendSV_Handler,Default_Handler

	.weak	SysTick_Handler
	.thumb_set SysTick_Handler,Default_Handler

	.weak	SystemInit

	.weak	DMA1_Stream0_IRQHandler
	.thumb_set DMA1_Stream0_IRQHandler,Default_Handler

	.weak	DMA1_Stream1_IRQHandler
	.thumb_set DMA1_Stream1_IRQHandler,Default_Handler

	.weak	DMA1_Stream2_IRQHandler
	.thumb_set DMA1_Stream2_IRQHandler,Default_Handler

	.weak	DMA1_Stream3_IRQHandler
	.thumb_set DMA1_Stream3_IRQHandler,Default_Handler

	.weak	DMA1_Stream4_IRQHandler
	.thumb_set DMA1_Stream4_IRQHandler,Default_Handler

	.weak	DMA1_Stream5_IRQHandler
	.thumb_set DMA1_Stream5_IRQHandler,Default_Handler

	.weak	DMA1_Stream6_IRQHandler
    .thumb_set DMA1_Stream6_IRQHandler,Default_Handler

	.weak	UART4_IRQHandler
	.thumb_set UART4_IRQHandler,Default_Handler

	.weak	DMA2_Stream0_IRQHandler
	.thumb_set DMA2_Stream0_IRQHandler,Default_Handler

	.weak	DMA2_Stream1_IRQHandler
	.thumb_set DMA2_Stream1_IRQHandler,Default_Handler

	.weak	DMA2_Stream2_IRQHandler
	.thumb_set DMA2_Stream2_IRQHandler,Default_Handler

	.weak	DMA2_Stream3_IRQHandler
	.thumb_set DMA2_Stream3_IRQHandler,Default_Handler

	.weak	DMA2_Stream4_IRQHandler
	.thumb_set DMA2_Stream4_IRQHandler,Default_Handler

	.weak	dummy_Handler
	.thumb_set dummy_Handler,Default_Handler
/************************ (C) COPYRIGHT Ac6 *****END OF FILE****/
