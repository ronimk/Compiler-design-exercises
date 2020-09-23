#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "heap_lock_monitor.h"

#include "ParsedGdata.h"
#include "GcodePipe.h"
#include "SimpleUARTWrapper.h"
#include "Parser.h"
#include "MockPipe.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
SemaphoreHandle_t mutex;
ParsedGdata data;
/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	Board_Init();
	heap_monitor_setup();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}

/* The parser task */
static void vParserTask(void *pvParameters) {
	data.canvasLimits.Y = 380;
	data.canvasLimits.X = 310;
	data.penDown = 90;
	data.penUp = 160;
	data.speed = 80;
	SimpleUART_Wrapper pipe(mutex);
	//MockPipe pipe;
	Parser parser(&pipe);
  ParsedGdata parsedData;
	char str[50];
	int c;
	while (1) {
            parser.parse(&parsedData);

            // process the parsed data in parsedData...
	}

}

/* the following is required if runtime statistics are to be collected */
extern "C" {

void vConfigureTimerForRunTimeStats(void) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

}
/* end runtime statictics collection */

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void) {
	prvSetupHardware();

	mutex = xSemaphoreCreateMutex();
	xTaskCreate(vParserTask, "vParserTask",
	configMINIMAL_STACK_SIZE + 256, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t*) NULL);
	vTaskStartScheduler();

	return 1;
}
