#include <stdio.h>

// These are application methods we need to access from the gfn interface
// They're just put here to indicate that they're application specific and should come from the application developer.
extern void Quit();
extern void Pause();
extern void SaveData();
extern void LockUserGraphicsOptions();
extern bool SetLocale(const char* locale);
extern bool IsCriticalUpdateRequired();

