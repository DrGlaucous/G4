#pragma once

extern unsigned long MillisecondTicks;
extern unsigned long MicrosecondTicks;
extern unsigned long LastMillisecondTicks;
extern unsigned long LastMicrosecondTicks;
void GetTicks(void);
void InitPins(void);
int GetUserInput();
void BeepBuzzer(int millis);
void TickBuzzer();