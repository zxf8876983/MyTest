#include<stdio.h>
#include<obliv.h>

#include"mult.h"
#include"../../common/util.h"

int main(int argc,char *argv[])
{
  ProtocolDesc pd;
  protocolIO io;
  if(argc<4)
  { if(argc<2) fprintf(stderr,"Port number missing\n");
    else if(argc<3) fprintf(stderr,"Server location missing\n");
    else fprintf(stderr,"string missing\n");
    fprintf(stderr,"Usage: %s <port> <--|remote_host> <int>\n",argv[0]);
    return 1;
  }
  sscanf(argv[3],"%f",&io.value);
  const char* remote_host = (strcmp(argv[2],"--")?argv[2]:NULL);
  ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);
  int currentParty = (remote_host?2:1);
  setCurrentParty(&pd,currentParty);
  execYaoProtocol(&pd,multiply,&io);
  cleanupProtocol(&pd);
  fprintf(stderr,"Result: %f\n",io.res);
  return 0;
}
