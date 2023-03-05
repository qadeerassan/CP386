#include <stdio.h>

#define MAX_THREADS 10
//turn around time is calculated as the difference between the completion time of thread I and its arrival time.

struct threadInfo{
    int thread_id; //thread_id: An integer identifier for the thread.
    int arrival_time; //arrival_time: The time at which the thread arrives.
    int burst_time; //burst_time: The time required for the thread to complete its execution.
    int waiting_time; //waiting_time: The time that the thread spends waiting to be executed.
    int turn_around_time; //turn_around_time: The time between the thread's arrival and completion.
};

int main() {
    struct threadInfo threads[MAX_THREADS];
    //Depending on the number of chapters in the input file, the application dynamically builds the "GradTA" and "TA" processes.
    int num_threads = 0;
    int time_quantum = 1;
    int total_waiting_time = 0;
    int total_turn_around_time = 0;
    //Every "GradTA" process spawns "TA" processes and gives each of them an assignment.
    FILE *fp = fopen("sample_in_schedule.txt", "r");
    if (fp == NULL) {
        printf("Error opening input file\n");
        return 1;
        //The "GradTA" processes are then developed by the instructor process, each of which handles a chapter's solution.
    }
    // read the input file's thread information
    while (fscanf(fp, "%d,%d,%d", &threads[num_threads].thread_id,
                  &threads[num_threads].arrival_time, &threads[num_threads].burst_time) != EOF) {
                     //The "TA" procedures compute and report the assignment's average grade.
        threads[num_threads].waiting_time = 0;
        threads[num_threads].turn_around_time = 0;
        num_threads++;
        //By summing together the separate numbers, the overall turnaround time and waiting time are also determined.
    }
    fclose(fp);
    //The instructor process, which reads the grades from the input file and generates a 
    //two-dimensional matrix of grades, is where the program begins.

    int completion_time[MAX_THREADS];
    int remaining_burst_time[MAX_THREADS];
    //A text file called "sample in grades.txt" with 10 students' grades for three chapters and two assignments for 
    //each chapter serves as the program's input.
    for (int i = 0; i < num_threads; i++) {
        remaining_burst_time[i] = threads[i].burst_time;
    }
    int current_time = 0;
    while (1) {
        int all_threads_completed = 1;
        for (int i = 0; i < num_threads; i++) {
            if (remaining_burst_time[i] > 0) {
               //For each chapter, it generates a "GradTA" process, which generates "TA" 
               //processes to determine the mean grade for each assignment.
                all_threads_completed = 0;
                if (remaining_burst_time[i] > time_quantum) {
                  //Thus, threads[i].waiting time is computed as the difference between the turn-around time and the burst time of thread I and threads[i].
                    current_time += time_quantum;
                    remaining_burst_time[i] -= time_quantum;
                    //Depending on the number of chapters in the input file
                    //the application dynamically builds the "GradTA" and "TA" processes.
                } else {
                    current_time += remaining_burst_time[i];
                    completion_time[i] = current_time;
                    remaining_burst_time[i] = 0;
                    //The output would be the average grades for each of the six assignments 
                    //if the input file contained grades for three chapters and two assignments for each chapter.
                }
            }
        }
        //The average grades for each assignment across all chapters are what the program is anticipated to provide.
        if (all_threads_completed) {
            break;
            //the program outputs the turn-around time and waiting time for each thread, 
            //as well as the average turn-around time and waiting time for all threads.
        }
    }
    //Determine the turn around and waiting times.