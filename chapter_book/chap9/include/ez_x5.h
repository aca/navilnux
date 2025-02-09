/*------------------------------------------------------------------------------
 파 일 명 : ez_x5.h
 프로젝트 : ezboot for PXA255
 설    명 : ez-x5 보드에 사용되는 PXA255 레지스터 주소와 설정, 메모리 맵핑등 
            하드웨어와 관련된 것을 정의 한다.
 작 성 자 : 푸지
 작 성 일 : 2003년 4월 18일 
 수 정 일 : 2003년 8월 11일  over clock 을 위해 수정  - 푸지
 주    의 : 
------------------------------------------------------------------------------*/

#ifndef _EZ_X5_HEADER_
#define _EZ_X5_HEADER_

//----------------------------------------------
//	CCLKCFG 비트
#define	PXA_COP_CCLKCFG_FCS	(1 <<1)
#define	PXA_COP_CCLKCFG_TURBO	(1 <<0)
//----------------------------------------------

//----------------------------------------------
//	Core Clock (PLL)
#define	PXA_REG_CCCR 		0x41300000
//----------------------------------------------

#define	CCCR_BF_L_X27		(0x1 <<0)	// 3.6864MHz x 27
#define	CCCR_BF_L_X36		(0x3 <<0)	// 3.6864MHz x 36
#define	CCCR_BF_L_X45		(0x5 <<0)	// 3.6864MHz x 45

#define	CCCR_BF_M_X1		(0x1 <<5)	// x1
#define	CCCR_BF_M_X2		(0x2 <<5)	// x2
#define	CCCR_BF_M_X4		(0x3 <<5)	// x4

#define	CCCR_BF_N_RUN_X10	(0x2 <<7)	// Turbo x1
#define	CCCR_BF_N_TBO_X15	(0x3 <<7)	// Turbo x1.5
#define	CCCR_BF_N_TBO_X20	(0x4 <<7)	// Turbo x2
#define	CCCR_BF_N_TBO_X30	(0x6 <<7)	// Turbo x3

// 	PXBus=50     MEM=99.5   SDRAM=99.5
#define	PXA_CCCR_CPU_99M	(CCCR_BF_L_X27 | CCCR_BF_M_X1 | CCCR_BF_N_RUN_X10 )
#define	PXA_CCCR_CPU_199M_T20	(CCCR_BF_L_X27 | CCCR_BF_M_X1 | CCCR_BF_N_TBO_X20 )
#define	PXA_CCCR_CPU_298M_T30	(CCCR_BF_L_X27 | CCCR_BF_M_X1 | CCCR_BF_N_TBO_X30 )

// 	PXBus=66     MEM=132.7  SDRAM=66
#define	PXA_CCCR_CPU_132M	(CCCR_BF_L_X36 | CCCR_BF_M_X1 | CCCR_BF_N_RUN_X10 )

// 	PXBus=99.5   MEM=99.5   SDRAM=99.5
#define	PXA_CCCR_CPU_199M	(CCCR_BF_L_X27 | CCCR_BF_M_X2 | CCCR_BF_N_RUN_X10 )
#define	PXA_CCCR_CPU_298M_T15	(CCCR_BF_L_X27 | CCCR_BF_M_X2 | CCCR_BF_N_TBO_X15 )
#define	PXA_CCCR_CPU_398M_T20	(CCCR_BF_L_X27 | CCCR_BF_M_X2 | CCCR_BF_N_TBO_X20 )

// 	PXBus=132.7  MEM=132.7  SDRAM=66
#define	PXA_CCCR_CPU_265M	(CCCR_BF_L_X36 | CCCR_BF_M_X2 | CCCR_BF_N_RUN_X10 )

// 	PXBus=165.9  MEM=165.9  SDRAM=83
#define	PXA_CCCR_CPU_331M	(CCCR_BF_L_X45 | CCCR_BF_M_X2 | CCCR_BF_N_RUN_X10 )

// 	PXBus=196    MEM=99.5   SDRAM=99.5
#define	PXA_CCCR_CPU_398M	(CCCR_BF_L_X27 | CCCR_BF_M_X4 | CCCR_BF_N_RUN_X10 )


// * 새롭게 추가된 조합, 인텔에서 보장하지는 않는다.
// 	PXBus=132.7  MEM=132.7  SDRAM=66
#define	PXA_CCCR_CPU_398M_T15	(CCCR_BF_L_X36 | CCCR_BF_M_X2 | CCCR_BF_N_TBO_X15 )

// * 이하는 over-clock 이므로 동작을 보장하지 않는다.
// 	PXBus=165.9  MEM=165.9  SDRAM=83
#define	PXA_CCCR_CPU_496M_T15	(CCCR_BF_L_X45 | CCCR_BF_M_X2 | CCCR_BF_N_TBO_X15 )
// 	PXBus=132.7  MEM=132.7  SDRAM=66
#define	PXA_CCCR_CPU_530M	(CCCR_BF_L_X36 | CCCR_BF_M_X4 | CCCR_BF_N_RUN_X10 )

//##################################################
// CPU 의 속도를 설정한다.
#define	CPU_SPEED		PXA_CCCR_CPU_398M
#define	SDRAM_CLK_DIV2		0			// 0 or 1
//##################################################

#if   ( CPU_SPEED & 0x7 ) == CCCR_BF_L_X27 
  #define					MEM_CLK		100
#elif ( CPU_SPEED & 0x7 ) == CCCR_BF_L_X36
  #define					MEM_CLK		133
#elif ( CPU_SPEED & 0x7 ) == CCCR_BF_L_X45
  #define					MEM_CLK		166
#else
  #define					MEM_CLK		0
#endif


//----------------------------------------------
//	Clock Enable Register 
//      c 루틴에서 이것을 변경해도 된다. 여기서는 중요하지 않다.
#define	PXA_REG_CKEN 		0x41300004
//----------------------------------------------

#define	CKEN_PWM0		(0 <<0 )	// PWM0   Clock Enable
#define	CKEN_PWM1		(0 <<1 )	// PWM1   Clock Enable
#define	CKEN_AC97		(0 <<2 )	// AC97   Clock Enable
#define	CKEN_SSP		(0 <<3 )	// SSP    Clock Enable
#define	CKEN_HWUART		(0 <<4 )	// HWUART Clock Enable
#define	CKEN_STUART		(1 <<5 )	// STUART Clock Enable
#define	CKEN_FFUART		(1 <<6 )	// FFUART Clock Enable
#define	CKEN_BTUART		(1 <<7 )	// BTUART Clock Enable
#define	CKEN_I2S		(0 <<8 )	// I2S	  Clock Enable
#define	CKEN_NSSP		(0 <<9 )	// NSSP	  Clock Enable
#define	CKEN_USB		(0 <<11)	// USB	  Clock Enable
#define	CKEN_MMC		(0 <<12)	// MMC	  Clock Enable
#define	CKEN_FICP		(0 <<13)	// FICP	  Clock Enable
#define	CKEN_I2C		(0 <<14)	// I2C	  Clock Enable
#define	CKEN_LCD		(0 <<16)	// LCD	  Clock Enable

#define	CKEN_VALUE		( CKEN_PWM0   | CKEN_PWM1   | CKEN_AC97   | CKEN_SSP    \
				| CKEN_HWUART | CKEN_STUART | CKEN_FFUART | CKEN_BTUART	\
				| CKEN_I2S    | CKEN_NSSP   | CKEN_USB    | CKEN_MMC	\
				| CKEN_FICP   | CKEN_I2C    | CKEN_LCD )             


//----------------------------------------------
//	OSC Configuration Register
#define	PXA_REG_OSCC 		0x41300008
//----------------------------------------------

#define	OSCC_OOK		(0 <<0 )	// use 32.768khz = 1  read-only  
#define	OSCC_OON		(0 <<1 )	// use 32.768khz = 1  write-only 

#define	OSCC_VALUE		OSCC_OON

//----------------------------------------------
//	SDRAM config 
#define	PXA_REG_MDCNFG		0x48000000	
//----------------------------------------------

//##############################################
// 사용하는 SDRAM 파티션(뱅크)을 활성화 한다.
#define	MDCNFG_DE0		(1 <<0 )	// SDRAM 0   Partition  Enable = 1
#define	MDCNFG_DE1		(1 <<1 )	// SDRAM 1   Partition 
//##############################################

#define	MDCNFG_DWID0		(0 <<2 )	// SDRAM 0/1 BusWidth 32bit  = 0
#define	MDCNFG_DCAC0		(1 <<3 )	// SDRAM 0/1 colume address count
#define	MDCNFG_DRAC0_128	(1 <<5 )	// SDRAM 0/1 row address count
#define	MDCNFG_DRAC0_256	(2 <<5 )	// SDRAM 0/1 row address count						
#define	MDCNFG_DNB0		(1 <<7 )	// SDRAM 0/1 bank count
#define	MDCNFG_DTC0		(3 <<8 )	// SDRAM 0/1 Timing 
#define	MDCNFG_DADDR0		(0 <<10)	// SDRAM 0/1 Address match mode
#define	MDCNFG_DLATCH0		(1 <<11)	// SDRAM 0/1 must be set
#define	MDCNFG_DSA1111_0        (1 <<12)	// SDRAM 0/1 use sa1111 = 0

#define	MDCNFG_DE2		(0 <<(0 +16))	// SDRAM 2   Partition  Enable = 1
#define	MDCNFG_DE3		(0 <<(1 +16))	// SDRAM 3   Partition  
#define	MDCNFG_DWID2		(0 <<(2 +16))	// SDRAM 2/3 BusWidth 32bit  = 0
#define	MDCNFG_DCAC2		(1 <<(3 +16))	// SDRAM 2/3 colume address count
#define	MDCNFG_DRAC2_128	(1 <<(5 +16))	// SDRAM 2/3 row address count
#define	MDCNFG_DRAC2_256	(2 <<(5 +16))	// SDRAM 2/3 row address count						
#define	MDCNFG_DNB2		(1 <<(7 +16))	// SDRAM 2/3 bank count
#define	MDCNFG_DTC2		(3 <<(8 +16))	// SDRAM 2/3 Timing 
#define	MDCNFG_DADDR2		(0 <<(10+16))	// SDRAM 2/3 Address match mode
#define	MDCNFG_DLATCH2		(1 <<(11+16))	// SDRAM 2/3 must be set
#define	MDCNFG_DSA1111_2        (1 <<(12+16))	// SDRAM 2/3 use sa1111 = 0
                                     
#define	MDCNFG_STD_VALUE	( MDCNFG_DE0  | MDCNFG_DE1    | MDCNFG_DWID0   | MDCNFG_DCAC0 | MDCNFG_DNB0 \
				| MDCNFG_DTC0 | MDCNFG_DADDR0 | MDCNFG_DLATCH0 | MDCNFG_DSA1111_0           \
				| MDCNFG_DE2  | MDCNFG_DE3    | MDCNFG_DWID2   | MDCNFG_DCAC2 | MDCNFG_DNB2 \
				| MDCNFG_DTC2 | MDCNFG_DADDR2 | MDCNFG_DLATCH2 | MDCNFG_DSA1111_2           )

#define	MDCNFG_128_VALUE	( MDCNFG_DRAC0_128 | MDCNFG_DRAC2_128 | MDCNFG_STD_VALUE )
#define	MDCNFG_256_VALUE        ( MDCNFG_DRAC0_256 | MDCNFG_DRAC2_256 | MDCNFG_STD_VALUE )


//##############################################
// 사용하는 SDRAM 하나의 용량을 선택한다.(16Mbyte == 128Mbit)
#define	MDCNFG_VALUE		MDCNFG_256_VALUE
//##############################################
                                 
//----------------------------------------------
//	SDRAM refresh, clock cfg
#define	PXA_REG_MDREFR		0x48000004	
//----------------------------------------------

#if   MEM_CLK == 166 
#define 	     MDREFR_DRI	    33		// MEM-Clock SDRAM refresh interval
#elif MEM_CLK == 133
#define 	     MDREFR_DRI	    29		
#elif MEM_CLK == 100
#define 	     MDREFR_DRI	    24
#else
#error	"PAX255의 속도를 설정하세요"
#endif

#define MDREFR_E0PIN		( 0 <<12)	// SDCKE0 Enable
#define MDREFR_K0RUN		( 0 <<13)	// SDCLK0 Enable
#define MDREFR_K0DB2		( 0 <<14)	// SDCLK0 divide-2

#define MDREFR_E1PIN		( 1 <<15)		   // SDCKE1 Enable
#define	MDREFR_K1RUN		( 1 <<16)		   // SDCLK1 Enable
#define MDREFR_K1DB2		( (SDRAM_CLK_DIV2&1) <<17) // SDCLK1 divide-2

#define	MDREFR_K2RUN		( 0 <<18)	// SDCLK2 Enable
#define MDREFR_K2DB2		( 0 <<19)	// SDCLK2 divide-2

#define MDREFR_APD		( 0 <<20)	// SDRAM/Static-Memory Auto-Power-Down enable 
#define MDREFR_SLFRSH		( 0 <<22)	// Self Refresh  (must be clear when reset)

#define MDREFR_K0FREE		( 0 <<23)	// SDCLK0 Free
#define MDREFR_K1FREE		( 1 <<24)	// SDCLK1 Free
#define MDREFR_K2FREE		( 0 <<25)	// SDCLK2 Free

#define	MDREFR_VALUE		( MDREFR_DRI   | MDREFR_SLFRSH \
				| MDREFR_E0PIN | MDREFR_K0RUN | MDREFR_K0DB2 | MDREFR_K0FREE \
				| MDREFR_E1PIN | MDREFR_K1RUN | MDREFR_K1DB2 | MDREFR_K1FREE \
				| MDREFR_APD   | MDREFR_K2RUN | MDREFR_K2DB2 | MDREFR_K2FREE )


//----------------------------------------------
//	SDRAM MRS command
#define	PXA_REG_MDMRS		0x48000040	 
//----------------------------------------------
    
#define	MDMRS_P01_CMD_BURST_CFG	(0x00 <<7 )	// burst-length / burst-type / cas-lnatncy
#define	MDMRS_P23_CMD_BURST_CFG	(0x00 <<16)	// burst-length / burst-type / cas-lnatncy

#define	MDMRS_VALUE		(MDMRS_P01_CMD_BURST_CFG | MDMRS_P23_CMD_BURST_CFG)


//----------------------------------------------
//	nCS 1:0 Timing
#define	PXA_REG_MSC0		0x48000008
//----------------------------------------------

#define	MSC_CS0_RT		( 0 <<0 )	// nCS0 Device Type  	0:non-burst Flash  1:SRAM  4:latency I/O 
#define	MSC_CS0_RBW		( 1 <<3 )	// nCS0 Bus Width  	0:32-bit   1:16-bit
#define	MSC_CS0_RDF		(13 <<4 )	// nCS0 nOE/nWE assert 	0 ~ 15	 0~11 :10~120 nsec  12~15 :130/150/180/230 nsec for 100MHz
#define	MSC_CS0_RDN		( 2 <<8 )	// nCS0 next assert 	0 ~ 15
#define	MSC_CS0_RRR		( 2 <<12)	// nCS0 cs to cs period	0 ~ 7
#define	MSC_CS0_RBUFF		( 0 <<15)	// nCS0 faster device = 1

#define	MSC_CS1_RT		( 0 <<(0 +16))	// nCS1 Device Type   	0:non-burst Flash  1:SRAM  4:latency I/O 
#define	MSC_CS1_RBW		( 1 <<(3 +16))	// nCS1 Bus Width     	0:32-bit   1:16-bit
#define	MSC_CS1_RDF		( 4 <<(4 +16))	// nCS1 nOE/nWE assert 	0 ~ 15	 0~11 :10~120 nsec  12~15 :130/150/180/230 nsec for 100MHz
#define	MSC_CS1_RDN		( 2 <<(8 +16))	// nCS1 next assert 	0 ~ 15                                                 
#define	MSC_CS1_RRR		( 2 <<(12+16))	// nCS1 cs to cs period 0 ~ 7
#define	MSC_CS1_RBUFF		( 0 <<(15+16))	// nCS1 faster device = 1

// 133M, 166M 속도에 대해 RDF폭을 재조정한다.
#if   MEM_CLK == 133
  #undef	MSC_CS0_RDF
  #undef	MSC_CS1_RDF
  #define	MSC_CS0_RDF	(15 << 4     )
  #define	MSC_CS1_RDF	(5  <<(4 +16))
#elif MEM_CLK == 166
  #undef	MSC_CS0_RDF
  #undef	MSC_CS1_RDF
  #define	MSC_CS0_RDF	(15 << 4     )
  #define	MSC_CS1_RDF	(5  <<(4 +16))
#endif

#define MSC0_VALUE		( MSC_CS0_RT  | MSC_CS0_RBW				  \
				| MSC_CS0_RDF | MSC_CS0_RDN | MSC_CS0_RRR | MSC_CS0_RBUFF \
                		| MSC_CS1_RT  | MSC_CS1_RBW  				  \
                		| MSC_CS1_RDF | MSC_CS1_RDN | MSC_CS1_RRR | MSC_CS1_RBUFF )

//----------------------------------------------
//	nCS 3:2 Timing
#define	PXA_REG_MSC1		0x4800000C	
//----------------------------------------------

#define	MSC_CS2_RT		( 0 <<0 )	// nCS2 Device Type  	0:non-burst Flash  1:SRAM  4:latency I/O 
#define	MSC_CS2_RBW		( 1 <<3 )	// nCS2 Bus Width  	0:32-bit   1:16-bit
#define	MSC_CS2_RDF		(15 <<4 )	// nCS2 nOE/nWE assert 	0 ~ 15	 0~11 :10~120 nsec  12~15 :130/150/180/230 nsec for 100MHz
#define	MSC_CS2_RDN		( 2 <<8 )	// nCS2 next assert 	0 ~ 15                                                 
#define	MSC_CS2_RRR		( 2 <<12)	// nCS2 cs to cs period	0 ~ 7
#define	MSC_CS2_RBUFF		( 1 <<15)	// nCS2 faster device = 1

#define	MSC_CS3_RT		( 0 <<(0 +16))	// nCS3 Device Type   	0:non-burst Flash  1:SRAM  4:latency I/O 
#define	MSC_CS3_RBW		( 1 <<(3 +16))	// nCS3 Bus Width     	0:32-bit   1:16-bit
#define	MSC_CS3_RDF		(15 <<(4 +16))	// nCS3 nOE/nWE assert 	0 ~ 15	 0~11 :10~120 nsec  12~15 :130/150/180/230 nsec for 100MHz
#define	MSC_CS3_RDN		( 2 <<(8 +16))	// nCS3 next assert 	0 ~ 15                                                 
#define	MSC_CS3_RRR		( 2 <<(12+16))	// nCS3 cs to cs period 0 ~ 7
#define	MSC_CS3_RBUFF		( 0 <<(15+16))	// nCS3 faster device = 1

#define MSC1_VALUE		( MSC_CS2_RT  | MSC_CS2_RBW 				  \
				| MSC_CS2_RDF | MSC_CS2_RDN | MSC_CS2_RRR | MSC_CS2_RBUFF \
                		| MSC_CS3_RT  | MSC_CS3_RBW  				  \
                		| MSC_CS3_RDF | MSC_CS3_RDN | MSC_CS3_RRR | MSC_CS3_RBUFF )

//----------------------------------------------
//	nCS 5:4 Timming
#define	PXA_REG_MSC2		0x48000010	
//----------------------------------------------

#define	MSC_CS4_RT		( 0 <<0 )	// nCS4 Device Type  	0:non-burst Flash  1:SRAM  4:latency I/O 
#define	MSC_CS4_RBW		( 1 <<3 )	// nCS4 Bus Width  	0:32-bit   1:16-bit
#define	MSC_CS4_RDF		(15 <<4 )	// nCS4 nOE/nWE assert 	0 ~ 15	 0~11 :10~120 nsec  12~15 :130/150/180/230 nsec for 100MHz
#define	MSC_CS4_RDN		( 2 <<8 )	// nCS4 next assert 	0 ~ 15                                                 
#define	MSC_CS4_RRR		( 2 <<12)	// nCS4 cs to cs period	0 ~ 7
#define	MSC_CS4_RBUFF		( 0 <<15)	// nCS4 faster device = 1

#define	MSC_CS5_RT		( 0 <<(0 +16))	// nCS5 Device Type   	0:non-burst Flash  1:SRAM  4:latency I/O 
#define	MSC_CS5_RBW		( 1 <<(3 +16))	// nCS5 Bus Width     	0:32-bit   1:16-bit
#define	MSC_CS5_RDF		(15 <<(4 +16))	// nCS5 nOE/nWE assert 	0 ~ 15	 0~11 :10~120 nsec  12~15 :130/150/180/230 nsec for 100MHz
#define	MSC_CS5_RDN		( 2 <<(8 +16))	// nCS5 next assert 	0 ~ 15                                                 
#define	MSC_CS5_RRR		( 2 <<(12+16))	// nCS5 cs to cs period 0 ~ 7
#define	MSC_CS5_RBUFF		( 0 <<(15+16))	// nCS5 faster device = 1

#define MSC2_VALUE		( MSC_CS4_RT  | MSC_CS4_RBW 				  \
				| MSC_CS4_RDF | MSC_CS4_RDN | MSC_CS4_RRR | MSC_CS4_RBUFF \
                		| MSC_CS5_RT  | MSC_CS5_RBW  				  \
                		| MSC_CS5_RDF | MSC_CS5_RDN | MSC_CS5_RRR | MSC_CS5_RBUFF )
                		

//----------------------------------------------
//	PCMCIA slot
#define	PXA_REG_MECR		0x48000014	 
//----------------------------------------------
#define	MECR_NOS		( 0 <<0 )	// used count of PCMCIA Slot  0:1-slot  1:2-slot
#define	MECR_CIT		( 0 <<1 )	// exist card  0:none  1:exist

#define	MECR_VALUE		(MECR_NOS | MECR_CIT)


//----------------------------------------------
//	Slot 1:0 Timming
#define	PXA_REG_MCMEM_S0	0x48000028	// PCMCIA Slot0 mem-region Access Timimg
#define	PXA_REG_MCMEM_S1	0x4800002C	// PCMCIA Slot1 mem-region Access Timimg
#define	PXA_REG_MCATT_S0	0x48000030	// PCMCIA Slot0 attribute-region Access Timimg
#define	PXA_REG_MCATT_S1	0x48000034	// PCMCIA Slot1 attribute-region Access Timimg
#define	PXA_REG_MCIO_S0		0x48000038	// PCMCIA Slot0 I/O-region Access Timimg
#define	PXA_REG_MCIO_S1		0x4800003C	// PCMCIA Slot1 I/O-region Access Timimg
//----------------------------------------------
                		
#define	MCMEM_S0_SET		( 5 <<0 )	// 0 ~ 127  10~1280-nsec for 100MHz
#define	MCMEM_S0_ASST		(15 <<7 )	// 0 ~ 31   10~320-nsec  for 100Mhz
#define	MCMEM_S0_HOLD		( 3 <<14)	// 0 ~ 63   10~640-nsec  for 100Mhz
				
#define	MCATT_S0_SET		( 5 <<0 )	// 0 ~ 127  10~1280-nsec for 100MHz
#define	MCATT_S0_ASST		(15 <<7 )	// 0 ~ 31   10~320-nsec  for 100Mhz
#define	MCATT_S0_HOLD		( 3 <<14)	// 0 ~ 63   10~640-nsec  for 100Mhz
				
#define	MCIO_S0_SET		( 5 <<0 )	// 0 ~ 127  10~1280-nsec for 100MHz
#define	MCIO_S0_ASST		(15 <<7 )	// 0 ~ 31   10~320-nsec  for 100Mhz
#define	MCIO_S0_HOLD		( 3 <<14)	// 0 ~ 63   10~640-nsec  for 100Mhz
                		
#define	MCMEM_S1_SET		( 5 <<0 )	// 0 ~ 127  10~1280-nsec for 100MHz
#define	MCMEM_S1_ASST		(15 <<7 )	// 0 ~ 31   10~320-nsec  for 100Mhz
#define	MCMEM_S1_HOLD		( 3 <<14)	// 0 ~ 63   10~640-nsec  for 100Mhz
				
#define	MCATT_S1_SET		( 5 <<0 )	// 0 ~ 127  10~1280-nsec for 100MHz
#define	MCATT_S1_ASST		(15 <<7 )	// 0 ~ 31   10~320-nsec  for 100Mhz
#define	MCATT_S1_HOLD		( 3 <<14)	// 0 ~ 63   10~640-nsec  for 100Mhz
				
#define	MCIO_S1_SET		( 5 <<0 )	// 0 ~ 127  10~1280-nsec for 100MHz
#define	MCIO_S1_ASST		(15 <<7 )	// 0 ~ 31   10~320-nsec  for 100Mhz
#define	MCIO_S1_HOLD		( 3 <<14)	// 0 ~ 63   10~640-nsec  for 100Mhz

#define	MCMEM_S0_VALUE		(MCMEM_S0_SET | MCMEM_S0_ASST | MCMEM_S0_HOLD )
#define	MCATT_S0_VALUE		(MCATT_S0_SET | MCATT_S0_ASST | MCATT_S0_HOLD )
#define	MCIO_S0_VALUE		(MCIO_S0_SET  | MCIO_S0_ASST  | MCIO_S0_HOLD  )
#define	MCMEM_S1_VALUE		(MCMEM_S1_SET | MCMEM_S1_ASST | MCMEM_S1_HOLD )
#define	MCATT_S1_VALUE		(MCATT_S1_SET | MCATT_S1_ASST | MCATT_S1_HOLD )
#define	MCIO_S1_VALUE		(MCIO_S1_SET  | MCIO_S1_ASST  | MCIO_S1_HOLD  )


//----------------------------------------------
//	Sync ROM
#define	PXA_REG_SXCNFG		0x4800001C
//----------------------------------------------
#define	SXCNFG_VALUE		0x00


//----------------------------------------------
//	PSSR Power Mamager Sleep Status Register
#define	PXA_REG_PSSR 		0x40f00004
//----------------------------------------------

#define	_PSSR_RDH		(1<<5)		// GPIO input active = 1
#define	_PSSR_PH		(0<<4)		// Peripheral Control Hold = 1

#define	PSSR_VALUE		( _PSSR_RDH | _PSSR_PH )


//----------------------------------------------
//	GPIO Alternate Functions
#define	PXA_REG_GP_BASE		0x40E00000
#define	PXA_REG_OFFSET_GPDR0	0x0C
#define	PXA_REG_OFFSET_GPDR1	0x10
#define	PXA_REG_OFFSET_GPDR2	0x14
#define	PXA_REG_OFFSET_GAFR0_L	0x54
#define	PXA_REG_OFFSET_GAFR0_U	0x58
#define	PXA_REG_OFFSET_GAFR1_L	0x5C
#define	PXA_REG_OFFSET_GAFR1_U	0x60
#define	PXA_REG_OFFSET_GAFR2_L	0x64
#define	PXA_REG_OFFSET_GAFR2_U	0x68
#define PXA_REG_OFFSET_GPSR0	0x18
#define PXA_REG_OFFSET_GPCR0	0x24
//----------------------------------------------

#define GPIO_BIT(x)         	( 1 << ( x % 32 ) )

#define GPIO_ALT_FN_1_IN	0x1
#define GPIO_ALT_FN_1_OUT	0x1
#define GPIO_ALT_FN_2_IN	0x2
#define GPIO_ALT_FN_2_OUT	0x2
#define GPIO_ALT_FN_3_IN	0x3
#define GPIO_ALT_FN_3_OUT	0x3
#define GPIO_ALT_FN_(num,func)	( func << ( ( num % 16 ) * 2 ) )

// alternate functin nCS[1..5]
#define GP_nCS1_MD		GPIO_ALT_FN_(15, GPIO_ALT_FN_2_OUT)
#define GP_nCS5_MD		GPIO_ALT_FN_(33, GPIO_ALT_FN_2_OUT)
#define GP_nCS2_MD		GPIO_ALT_FN_(78, GPIO_ALT_FN_2_OUT)
#define GP_nCS3_MD		GPIO_ALT_FN_(79, GPIO_ALT_FN_2_OUT)
#define GP_nCS4_MD		GPIO_ALT_FN_(80, GPIO_ALT_FN_2_OUT)

// alternate functin RDY
#define	GP_RDY_MD		GPIO_ALT_FN_(18, GPIO_ALT_FN_1_IN)

// alternate functin pcmcia pins
#define	GP_nPOE_MD		GPIO_ALT_FN_(48, GPIO_ALT_FN_2_OUT)
#define	GP_nPWE_MD		GPIO_ALT_FN_(49, GPIO_ALT_FN_2_OUT)
#define	GP_nPIOR_MD		GPIO_ALT_FN_(50, GPIO_ALT_FN_2_OUT)
#define	GP_nPIOW_MD		GPIO_ALT_FN_(51, GPIO_ALT_FN_2_OUT)
#define	GP_nPCE1_MD		GPIO_ALT_FN_(52, GPIO_ALT_FN_2_OUT)
#define	GP_nPCE2_MD		GPIO_ALT_FN_(53, GPIO_ALT_FN_2_OUT)
#define	GP_PSKTSEL_MD		GPIO_ALT_FN_(54, GPIO_ALT_FN_2_OUT)
#define	GP_nPREG_MD		GPIO_ALT_FN_(55, GPIO_ALT_FN_2_OUT)
#define	GP_nPWAIT_MD		GPIO_ALT_FN_(56, GPIO_ALT_FN_1_IN )
#define	GP_nIOIS16_MD		GPIO_ALT_FN_(57, GPIO_ALT_FN_1_IN )
                        
//----- GAFR reg-value ---------  
#define	GAFR0_L_VALUE		( GP_nCS1_MD )
#define	GAFR0_U_VALUE		( GP_RDY_MD  )
#define	GAFR1_L_VALUE		( GP_nCS5_MD )
#define	GAFR1_U_VALUE		( GP_nPOE_MD   | GP_nPWE_MD  | GP_nPIOR_MD   | GP_nPIOW_MD \
				| GP_nPCE1_MD  | GP_nPCE2_MD | GP_PSKTSEL_MD | GP_nPREG_MD \
				| GP_nPWAIT_MD | GP_nIOIS16_MD )
#define	GAFR2_L_VALUE		( GP_nCS2_MD   | GP_nCS3_MD    )
#define	GAFR2_U_VALUE		( GP_nCS4_MD )
//------------------------------

// nCS[1..5] Dir OUT
#define GP_nCS1			GPIO_BIT(15)    // chip select 1  
#define GP_nCS5			GPIO_BIT(33)    // chip select 5  
#define GP_nCS2			GPIO_BIT(78)    // chip select 2  
#define GP_nCS3			GPIO_BIT(79)    // chip select 3  
#define GP_nCS4			GPIO_BIT(80)    // chip select 4  

// PCMICA Dir OUT
#define	GP_PCMCIA_PEP		(GPIO_BIT(48)|GPIO_BIT(49)|GPIO_BIT(50)|GPIO_BIT(51) \
				|GPIO_BIT(52)|GPIO_BIT(53)|GPIO_BIT(54)|GPIO_BIT(55) )

// Debug LED 4개 Dir OUT
#define	GP_LED0			GPIO_BIT(2)
#define	GP_LED1			GPIO_BIT(3)
#define	GP_LED2			GPIO_BIT(4)
#define	GP_LED3			GPIO_BIT(5)

//----- GPxx Value -------------
#define	GPDR0_VALUE		( GP_nCS1 | GP_LED0 | GP_LED1 | GP_LED2 | GP_LED3 )
#define	GPDR1_VALUE		( GP_nCS5 | GP_PCMCIA_PEP     )
#define	GPDR2_VALUE		( GP_nCS2 | GP_nCS3 | GP_nCS4 )
//------------------------------

//----------------------------------------------
//	Debug LED Status
//----------------------------------------------
#define	DEBUG_START		1
#define	DEBUG_READY_MEMTEST	2
#define	DEBUG_MEM_OK		3
#define	DEBUG_MEM_ERROR		4
#define	DEBUG_JUMP_C		5
#define	DEBUG_DATA_ABORT	6
#define	DEBUG_OTHER_EXCEPT	7

#define	_LED_0			GP_LED0
#define	_LED_1			GP_LED1
#define	_LED_2			GP_LED2
#define	_LED_3			GP_LED3
#define	ERROR_LED               LED_3


//----------------------------------------------
// 	boot 시의 메모리 맵
//----------------------------------------------
#define	EZ_X5_BASE_ROM		0x00000000      // 롬의 시작 위치
#define	EZ_X5_BASE_RAM		0xA0000000      // 램의 시작 위치
#define	EZ_X5_RAM_BOOT		0xA0F00000      // 부트 영역의 시작 위치
#define	EZ_X5_RAM_BOOT_END	0xA0F20000      // 부트 영역의 끝

#define	EZ_X5_C_MAIN_OFFSET	0x800		// C_MAIN 시작위치 2k-byte


#endif //_EZ_X5_HEADER_
