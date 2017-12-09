#include "header.h"
void create_MQ() {
  if( (MQ_id=msgget(IPC_PRIVATE, IPC_CREAT|0700)) == -1) {
    perror("error creating MQ!!!\n");
    exit(1);
  }
  printf("id: %d\n", MQ_id);
}
void add_to_MQ(Patient patient) {
  MQ_patient new_node;
  new_node.priority = (long)patient.priority;
  new_node.info = patient;
  if(msgsnd(MQ_id, &new_node,sizeof(MQ_patient)-sizeof(long), 0) == -1) {
    perror("error sending to MQ\n");
    exit(1);
  }
  printf("%s added to MQ!\n", new_node.info.name);
}