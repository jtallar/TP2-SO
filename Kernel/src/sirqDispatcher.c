// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <syscalls.h>
#include <stdint.h>

#define SYSCALL_COUNT	18


// Software handlers functions
static uint64_t syscall_00 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_01 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_02 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_03 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_04 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_05 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_06 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_07 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_08 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

static uint64_t syscall_09 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_10 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_11 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

static uint64_t syscall_12 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_13 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_14 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_15 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_16 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_17 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t syscall_18 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

uint64_t (* syscalls[]) (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) = 
																{syscall_00, syscall_01, syscall_02, syscall_03, 
																	syscall_04, syscall_05, syscall_06, syscall_07,
																	syscall_08,	syscall_09, syscall_10, syscall_11,
																	syscall_12, syscall_13, syscall_14, syscall_15,
																	syscall_16, syscall_17, syscall_18};

// Dispatcher for software interrupts
uint64_t handleSyscall(uint64_t sirq, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	if (sirq <= SYSCALL_COUNT) {
		return syscalls[sirq](rdi, rsi, rdx, rcx, r8, r9); 
	}
	return 1;
}

uint64_t syscall_00 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	read_handler(rdi, (char *)rsi, rdx);
	return 0;
}

uint64_t syscall_01 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	write_handler(rdi, (char *)rsi, rdx);
	return 0;
}

uint64_t syscall_02 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	return time_handler();
}

uint64_t syscall_03 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	clear_handler();
	return 0;
}

uint64_t syscall_04 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	return rtc_handler((char) rdi);
}

uint64_t syscall_05 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	sleep_handler(rdi);
	return 0;
}

uint64_t syscall_06 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	beep_handler(rdi, rsi);
	return 0;
}

uint64_t syscall_07 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	exit_handler();
	return 0;
}

uint64_t syscall_08 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	pixel_handler(rdi, rsi, rdx);
	return 0;
}

/* -----------------------------------------------------------------*/
uint64_t syscall_09 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	return (uint64_t) malloc_handler(rdi);
}

uint64_t syscall_10 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	free_handler((void *) rdi);
	return 0;
}

uint64_t syscall_11 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	printStatus_handler();
	return 0;
}

/* -----------------------------------------------------------------*/
//syscall(NEW_PROC_ID, (uint64_t) name, argc, (uint64_t) argv, ground, inFd, outFd)
uint64_t syscall_12 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	return create_handler((char *)rdi, rsi, (char **) rdx, rcx, r8, r9);
}

uint64_t syscall_13 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	return kill_handler(rdi);
}

uint64_t syscall_14 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	return getPid_handler();
}

uint64_t syscall_15 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	listAllProcess_handler();
	return 0;
}

// rdi = PID ; rsi = PRIORITY
uint64_t syscall_16 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	return setPriority_handler(rdi, rsi);
}

// rdi = PID
uint64_t syscall_17 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	return changeState_handler(rdi);
}

uint64_t syscall_18 (uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	halt_handler();
	return 0;
}