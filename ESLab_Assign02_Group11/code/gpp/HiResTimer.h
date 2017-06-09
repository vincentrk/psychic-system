/************** Timing routine (for performance measurements) ***********/
/* unfortunately, this is generally assembly code and not very portable */


void Timer_Init(void)
{
#if defined(__arm__)
    int user_enable;
#if defined(__GNUC__)
#define COMPILER_ID "GCC"
asm ("mrc p15, 0, %0, c9, c14, 0" : "=r"(user_enable));
#elif defined(__CC_ARM)
#define COMPILER_ID "ARMCC"
#error "ARMCC not implemented"
#else
#error  "Unknown ARM compiler"
#endif
    if (!user_enable)
        printf("User mode enable is not set, no access to cycle counter\n");

#if defined(__GNUC__)
    /* Reset and enable */
    asm volatile ("mcr p15, 0, %0, c9, c12, 0" :: "r"(5));
    /* Enable cycle counter */
    asm volatile ("mcr p15, 0, %0, c9, c12, 1" :: "r"(0x80000000));
    /* Reset overflow flags */
    asm volatile ("mcr p15, 0, %0, c9, c12, 3" :: "r"(0x80000000));
#endif

#else
    printf("No support for RDTSC on this CPU platform\n");
#endif /* defined(__arm__) */
}

void Timer_DeInit(void)
{
#if defined(__GNUC__)
    /* Disable */
    asm volatile ("mcr p15, 0, %0, c9, c12, 0" :: "r"(0));
#endif
}

long HiResTime(void)
{
    long cycles;
#if defined(__arm__)
#if defined(__GNUC__)
asm volatile ("mrc p15, 0, %0, c9, c13, 0": "=r"(cycles));
#endif
    return cycles;
#else
    return 0;
#endif
}
