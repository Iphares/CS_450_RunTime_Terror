#define P_OPEN 0
#define P_CLOSED 1
#define COMPLETE 0
#define STARTING 1
#define I_STATUS 0
#define R_STATUS 1
#define W_STATUS 2

typedef struct DCB	{
  int portFlag;
  int* eventPtr;
  int status; // Use I,R,W _STATUS for this variable
  u32int inBuffAddress;
  int inBuffCounter;
  u32int outBufAddress;
  int outBuffCounter;
  char ringBuffer[100]; //This is supposed to be a circular array
  //These are the variables associated with the ringBuffer
  int inIndex;
  int outIndex;
  int rbCounter;
} DCB;
