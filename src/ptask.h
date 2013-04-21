/*--------------------------------------------------------------*/
/*		PTASK LIBRARY - HEADER FILE			*/
/*--------------------------------------------------------------*/

#ifndef __PTASK_H__
#define __PTASK_H__

#include <pthread.h>
#include <semaphore.h>
#include <ptime.h>

/*--------------------------------------------------------------*/

#define	MAX_TASKS	50
#define	MAX_GROUPS	10

/* activation flag for task_create */
#define	NOACT		0
#define	ACT		1

/**
   This structure is used to simplify the creation of a task by
   setting standard arguments, 
 */
typedef struct _tst {
  tspec_t period; 
  tspec_t rdline;
  int priority;              // from 0 to 99
  int group_id;              // -1 if no group
  int processor;             // up to 16 processors are available
  int act_flag;              // ACT if the create activates the task
  int wait_flag;             /* if 1, the task waits for an act. *  
                              *      before starting             *
                              * if 0, the task starts right away */
  int measure;               /* if 1, activates measurement of   * 
			      *	exec time                        */
} task_spec_t;

extern const task_spec_t TASK_SPEC_DFL;

/* ------------------------------------------------------------- */
/*                     GLOBAL FUNCTIONS                          */
/* ------------------------------------------------------------- */
int     ptask_getnumcores(); /* returns number of available cores*/ 
void	ptask_init(int policy); /** Initializes the library      */

/*-----------------------------------------------------------------*/
/*			TASK FUNCTIONS                             */
/*-----------------------------------------------------------------*/
void	  wait_for_activation();  /** waits for an exp. activation */
void	  wait_for_period();      /** waits for next periodic act. */
void      set_activation(const tspec_t *off); /** sets the act. time */
int       get_taskindex();        /** returns the task own index   */
pthread_t get_threadid(int i);    /** returns the thread own id    */
int	  deadline_miss(int i);

void	  task_setdeadline(int i, int dline);
int       task_argument(void* arg);
void	  task_setwcet(int i, long wc);
long	  task_wcet(int i);
void	  task_setperiod(int i, int per);
int	  task_period(int i);
int	  task_deadline(int i);
void	  task_setdeadline(int i, int dline);
int	  task_dmiss(int i);
long	  task_atime(int i);
long	  task_absdl(int i);

int	  task_create(void (*task)(void), 
		      int period, int drel, int prio, int aflag);

int	  task_create_ex(task_spec_t *tp, void (*task)(void));

void	  task_activate(int i);
int       task_migrate_to(int core_id); 

#endif

/*--------------------------------------------------------------*/
