#ifndef AUDIO_DEBUG_H
#define AUDIO_DEBUG_H
#include <stdint.h>
//#define AUDIO_DEBUG_ENABLE
extern uint8_t* audio_rx_debug_buffer;
extern uint8_t* audio_tx_debug_buffer;

extern uint8_t* audio_rx_aec_buffer;

extern int audio_rx_debug_len;
extern int audio_tx_debug_len;

extern int audio_rx_aec_len;

extern int audio_rx_debug_ena;
extern int audio_tx_debug_ena;

extern int audio_rx_aec_ena;

extern void audio_stdio_off(void);
extern void audio_stdio_on(void);
extern void audio_console_rx_off(void);
extern void audio_console_rx_on(void);
extern void audio_debug_buf_print(uint8_t *buf);

extern void audio_rx_debug_init(int time);
extern void audio_rx_debug_deinit(void);
extern void audio_rx_debug_start(int mode);
extern void audio_rx_debug_dump(void);
extern void audio_rx_aec_dump(void);
extern void audio_tx_debug_init(int time);
extern void audio_tx_debug_deinit(void);
extern void audio_tx_debug_start(void);
extern void audio_tx_debug_get(void);
#endif // AUDIO_DEBUG_H