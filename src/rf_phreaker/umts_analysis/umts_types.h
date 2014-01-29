#pragma once

#define N_SLOTS_PER_FRAME	(15)
#define FRAME_PERIOD_SEC	(0.01)					// Frame duration in seconds
#define SLOT_PERIOD_SEC		(FRAME_PERIOD_SEC/N_SLOTS_PER_FRAME)	// Slot duration in seconds
#define N_CHIPS_PER_TIMESLOT	2560
#define N_TOTAL_CHIPS_CPICH		N_CHIPS_PER_TIMESLOT * N_SLOTS_PER_FRAME
#define N_CPICH_CODES 512
#define N_CHIPS_PER_PSCH 256

#define N_CODE_GROUPS 64
#define N_PSCHSSCH_SAMPLES 325
#define N_SECSYNC_CHANNELS 16

#define UMTS_BCCH_TTI_BITSIZE        270

