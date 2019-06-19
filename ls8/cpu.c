#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DATA_LEN 6

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char i){
  return cpu->ram[i];
}

void cpu_ram_write(struct cpu *cpu, unsigned char value, unsigned char i) {
	 cpu->ram[i] = value;
 }



/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, int argc, char *argv[])
{
  if (argc < 2){
    printf("File does not exist.\n");
    exit(1);
  }
  

  char *file = argv[1];


  FILE *fp = fopen(file, "r");


  if (fp == NULL){
    printf("File does not exist");
    exit(1);
  }
  else
  {
    char file_line[1024];
    int address = 0;

    while (fgets(file_line, sizeof(file_line), fp) != NULL)
    {

      char *endptr;
      unsigned char value = strtol(file_line, &endptr, 2);


      if (file_line == NULL){
        continue;
      }

      cpu->ram[address] = value;
      address++;
    }
  }
  fclose(fp);
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
  unsigned char operandA;
  unsigned char operandB;

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC)
    unsigned char IR = cpu->ram[cpu->PC];
    // 2. Figure out how many operands this next instruction requires
    unsigned int operands = IR >> 6;
    // 3. Get the appropriate value(s) of the operands following this instruction
    if (operands == 2)
    {
      operandA = cpu_ram_read(cpu, (cpu->PC + 1) & 0xff);
      operandB = cpu_ram_read(cpu, (cpu->PC + 2) & 0xff);
    }
    else if (operands == 1)
    {
      operandA = cpu_ram_read(cpu, (cpu->PC + 1) & 0xff);
    }
    // 4. switch() over it to decide on a course of action.
    switch(IR){
      // 5. Do whatever the instruction should do according to the spec.
      case HLT:
        running = 0;
        break;

      case LDI:
        cpu->registers[operandA] = operandB;
        break;
      
      case PRN:
        printf("%d\n", cpu->registers[operandA]);
        break;
      
      default:
        break;
    }
    
    // 6. Move the PC to the next instruction.
    cpu->PC += operands + 1;
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
