#include "header.h"

void doctor (int shift_length) {
	clock_t start = clock();
	clock_t end = clock();
	int shift_time = (end - start) / CLOCKS_PER_SEC;

 while (/*getPatient() && */((int)shift_time < shift_length)) {
	 end = clock();
	 shift_time = (end - start) / CLOCKS_PER_SEC;
	 (*shared_var).total_treated++;

	 /*TODO: solve patient*/

     int time_doc = end / CLOCKS_PER_SEC;
//	 (*shared_var).average_after_triage = ((*shared_var).average_after_triage * ((*shared_var).total_treated-1) + time_doc-patient.end_triage)/(*shared_var).total_treated;
//	 (*shared_var).average_all = ((*shared_var).average_all * ((*shared_var).total_treated-1) + time_doc-patient.start)/(*shared_var).total_treated;

    #ifdef DEBUG
  //   printf("DOCTOR - start: %d\n", patient.end_triage);
     printf("DOCTOR - end: %d\n", time_doc);
     printf("DOCTOR - shift duration: %d\n", shift_time);
     printf("DOCTOR - average_after_triage: %d\n", (*shared_var).average_after_triage);
     printf("DOCTOR - average_all: %d\n", (*shared_var).average_all);
    #endif
 }
}

void create_doctors (int doctors, int shmid, int shift_length) {

    //Create semaphores
    int i;
    int j = 0;
    for (i = 0; i < doctors; i++) {
        if (fork() == 0) {
            #ifdef DEBUG
            printf("DOCTOR - creating one doctor.....\n");
            #endif

            doctor(shift_length);
            exit(0);
        }
    }
    while (/*there is patient*/false) {
        j++;
        if (fork() == 0) {
            #ifdef DEBUG
            printf("DOCTOR - creating one additional doctor.....\n");
            #endif

            doctor(shift_length);
            exit(0);
        }

        for (i = 0; i < doctors + j; i++) {
            wait(NULL);
        }
        exit(0);
    }
}
