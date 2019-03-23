#ifndef CALCULATORTASK_H
#define CALCULATORTASK_H

#define CALCULATOR_TASK_STACK_SIZE 512
extern const UINT8 CalculatorTaskName[];

void CalculatorTaskInit(CALCULATOR_CONTORL *pCalculator);
void CalculatorTask(void);

#endif