//------------------------------------------------------------------------------
// 화일명 : serial.c
// 설  명 : ezBoot의 시리얼 제어 루틴이다. 
// 
// 작성자 : 유영창 (주)제이닷디엔티 frog@falinux.com
// 작성일 : 2003년 05월 20일
// 수  정 : 2003-06-07	오재경 (주)제이닷디엔티 freefrug@falinux.com  -- 푸지
//          
// 저작권 : (주)제이닷디엔티 
// 주  의 : 이 루틴의 대부분은 blob에서 가져왔다. 
//------------------------------------------------------------------------------

//******************************************************************************
//
// 헤더 정의
//
//******************************************************************************
#include <pxa255.h>
//#include <config.h>
#include <serial.h>
#include <time.h>
#include <stdio.h>
#include <gpio.h>

//******************************************************************************
//
// 광역 변수 정의
//
//******************************************************************************
// config.c 에 정의
static int SerialErrorFlag = 0;


#ifdef IN_GUMSTIX
static volatile Word *UART = (volatile Word*)(0x40100000); // UART 베이스 어드레스 
#else
static volatile Word *UART = (volatile Word*)(0x40700000); // UART 베이스 어드레스 
#endif

#define UART_DATA          	UART[0]   // 데이타  
#define UART_IER		((volatile Word) UART[1] )  // 인터럽트 허가 
#define UART_FCR		((volatile Word) UART[2] )  // 인터럽트 상태 
#define UART_LCR		((volatile Word) UART[3] )  // 라인 콘트롤 
#define UART_MCR		((volatile Word) UART[4] )  // 모뎀 콘트롤 
#define UART_LSR		((volatile Word) UART[5] )  // 라인 상태 
#define UART_MSR		((volatile Word) UART[6] )  // 모뎀 상태 
#define UART_SPR		((volatile Word) UART[7] )  // 
#define UART_ISR		((volatile Word) UART[8] )  // 적외선 포트 선택 
                                                
#define UART_DLL		((volatile Word) UART[0] )  // UART 라인 상태 
#define UART_DLH           	((volatile Word) UART[1] )  // UART 라인 상태 

//******************************************************************************
//
// 함수 정의
//
//******************************************************************************
//------------------------------------------------------------------------------
// 설명 : 시리얼 디바이스에 한 문자를 보낸다. 
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
void SerialOutChar( const char c  )
{
	// 전송 가능할때까지 기다린다. 
	while(( UART_LSR & LSR_TDRQ ) == 0 ); 

	// 시리얼에 데이타를 출력한다. 
	UART_DATA = c;
}

//------------------------------------------------------------------------------
// 설명 : 시리얼 디바이스에 한 문자를 보낸다. 
// 매계 : 없음 
// 반환 : 없음 
// 주의 : CR 의 LR CR 로 변경하여 출력한다. 
//------------------------------------------------------------------------------
void SerialOutChar_CheckCR( const char c  )
{
	SerialOutChar( c );
	if(c == '\n') SerialOutChar('\r');
}
//------------------------------------------------------------------------------
// 설명 : 시리얼 디바이스에 문자열을 보낸다. 
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
int SerialOutStr( char *str, int size )
{
	int	lp ;

	for (lp=0;lp<size;lp++) SerialOutChar(str[lp]) ;

	return lp;
}
//------------------------------------------------------------------------------
// 설명 : 시리얼 디바이스에 문자열을 보낸다. 
// 매계 : 없음 
// 반환 : 없음 
// 주의 : 없음 
//------------------------------------------------------------------------------
int SerialOutStr_CheckCR( char *str, int size )
{
	int	lp ;

	for (lp=0;lp<size;lp++) SerialOutChar_CheckCR(str[lp]) ;

	return lp;
}
//------------------------------------------------------------------------------
// 설명 : 시리얼 디바이스에서 수신된 데이타가 있는지 확인한다. 
// 매계 : 없음 
// 반환 : 수신된 데이타가 있으면 1 / 없으면 0
// 주의 : 없음 
//------------------------------------------------------------------------------
int SerialIsReadyChar( void )
{
	// 수신된 데이타가 있는가를 확인한다. 
	if( UART_LSR & LSR_DR ) return 1;
	return 0;
}

//------------------------------------------------------------------------------
// 설명 : 시리얼 상태를 돌려 준다. 
// 매계 : 없음 
// 반환 : 수신된 데이타가 있으면 1 / 없으면 0
// 주의 : 없음 
//------------------------------------------------------------------------------
int SeriallGet_LSR( void )
{
	return UART_LSR;
}
//------------------------------------------------------------------------------
// 설명 : 시리얼 디바이스에서 에러 상태를 읽어 온다. 
// 매계 : 없음 
// 반환 : 수신된 문자 
// 주의 : 없음 
//------------------------------------------------------------------------------
char SerialIsGetChar( void )
{
	// 에러를 가져 온다. 
    	SerialErrorFlag = UART_LSR & (LSR_PE | LSR_FE | LSR_OE);
    
	// 수신된 데이타를 가져 온다. 
	return (char) UART_DATA;
}
//------------------------------------------------------------------------------
// 설명 : 시리얼 디바이스의 수신 에러 플라그를 클리어 한다. 
// 매계 : 없음 
// 반환 : 수신된 문자 
// 주의 : 없음 
//------------------------------------------------------------------------------
char SerialIsClearError( void )
{
	SerialErrorFlag = 0;
	return (char)SerialErrorFlag;
}
//------------------------------------------------------------------------------
// 설명 : 시리얼 디바이스의 수신 에러 플라그 값을 얻는다. 
// 매계 : 없음 
// 반환 : 수신된 문자 
// 주의 : 없음 
//------------------------------------------------------------------------------
int SerialIsGetError( void )
{
	return SerialErrorFlag;
}


