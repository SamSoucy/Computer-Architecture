#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DATA_LEN 6

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char i){
  return cpu->ram[i];
}

unsigned char cpu_ram_write(struct cpu *cpu, unsigned char i, unsigned char value){
  cpu->ram[i] = value;
  return 0;
}



/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, int argc, char **argv)
{
  FILE *fp;

	char line[256];

  if (argc != 2) {
		printf("usage: fileio filename\n");
		return 1;
  }
  fp = fopen(argv[1], "r");

  if (fp == NULL) {
		printf("Error opening file %s\n", argv[1]);
		return 2;
  }
  int address = 0; 

	while (fgets(line, 1024, fp) != NULL) {
    char *endptr;
    unsigned char value = strtoul(line, &endptr, 10);

		if (line == endptr) {
			printf("SKIPPING: %s", line);
			continue;
		}
    printf("%02x\n", value);

    cpu_ram_write(cpu, value, address++);

    // TODO: Replace this with something less hard-coded
  }
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC)
    unsigned char IR = cpu->ram[cpu->PC];
    // 2. Figure out how many operands this next instruction requires
    unsigned char operands = IR >> 6;
    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned char operandA = cpu_ram_read(cpu, cpu->PC + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->PC + 2);
    // 4. switch() over it to decide on a course of action.
    switch(IR){
      // 5. Do whatever the instruction should do according to the spec.
      case HLT:
        return;
      case LDI:
        cpu->registers[operandA] = operandB;
        break;
      case PRN:
        printf("%d\n", cpu->registers[operandA]);
        break;
    }
    
    // 6. Move the PC to the next instruction.
    cpu->PC += (operands + 1);
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
   
  // TODO: Initialize the PC and other special registers
  cpu->PC = 0;
  
  memset(cpu->registers, 0, sizeof(cpu->registers));
  memset(cpu->ram, 0, sizeof(cpu->ram));
}
