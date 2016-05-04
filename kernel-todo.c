#include <stdio.h>
struct exception {
  // TODO
};
typedef struct exception exception;
/**
 * This function initializes the kernel and its data structures and leaves
 * the kernel in start-up mode. The init_kernel call must be made before any
 * other call is made to the kernel
 * @argument --> none
 * @return --> description of the function's status
 */
exception init_kernel() {
  // 1.  Set tick counter to zero
  // 2. Create necessary data structures
  exception status;
  // 3. Create an idle task
  // 4. Set the kernel in start up mode
  // 5. Return status
  return status;
}
typedef unsigned int uint;
/**
 * This function create a task. If the call is made in start-up mode, i.e.
 * the kernel is not running, only the necessary data structures will be created.
 * However, if the call is made in running mode , it will lead to a rescheduling
 * and possibly a context switch
 * @argument --> *task_body: A pointer to the c function holding the code of the task
 *           --> deadline  : The kernel will try to scheduling the task so it will meet this deadline
 * @return --> description of the function's status , i.e FAIL/OK
 */
exception create_task(void(*task_body)(), uint deadline) {
   // 1. Allocate memory for TCB
   // 2. Set deadline in TCB
   // 3. Set the TCB's PC to point to the task body
   // 4. Set TCB's SP to point to the stack segment
   // 5. if ( start-up mode ) {
   //       insert new task in ReadyList;
   //       return status;
   //    }
   //    else
   //    {
   //       Disable interrupts;
   //       save context;
   //       if( first execution ) {
   //         Set: "not first execution any more";
   //         insert new task in ReadyList;
   //         load context;
   //       }
   //    }
   // 6. return status
  task_body();
  exception status;
  if (deadline) {
    return status;
  }
  return status;
}
/**
 * This function starts the kernel and thus the system of created tasks. Since the call will start the
 * kernel it will leave control to the task with tightest deadline. Therefore, it must be placed last
 * in the application initialization code. After this call the system will be in running mode.
 * @argument --> none
 * @return --> none
 */
void run() {
   // 1. initializa interrupt times
   // 2. Set the kernel in running mode
   // 3. Enable interrupts
   // 4. Load context
}
/**
 * This call will terminate the running task. All data structures for the task will be removed.
 * Thereafter, another task will be scheduled for execution.
 * @argument --> none
 * @return  --> none
 */
void terminate() {
   // 1. remove running task from ReadyList
   // 2. Set next task to be the running task
   // 3. Load context
}
struct Mailbox {
  // TODO
};
//////////////////////////////////Inter-process Communication/////////////////////////////////////////
/**
 * This call will create a Mailbox. The Mailbox is a FIFO communication structure used for asynchronous
 * and synchronous communication between tasks.
 * @argument --> nof_msg: Maximum number of Messages the Mailbox can hold.
 *           --> size_of_msg: The size of one Message in the Mailbox.
 * @return --> Mailbox*: a pointer to the created mailbox or NULL.
 */
Mailbox* create_mailbox(int nof_msg, int size_of_msg) {
  // 1. Allocate memory for the Mailbox
  // 2. Initialize Mailbox structure
  // 3. return Mailbox
  if (nof_msg && size_of_msg) {
    return NULL;
  }
  return NULL;
}
/**
 * This call will remove the Mailbox if it is empty and return OK. Otherwise no action is taken and the
 * call will return NOT_EMPTY
 * @argument --> Mailbox* : A pointer to the Mailbox to be removed
 * @return   --> OK: The mailbox was removed
 *           --> NOT_EMPTY: The mailbox was not removed because it was not empty.
 */
exception remove_mailbox(Mailbox* mBox) {
  // 1. if (Mailbox is empty) {
  //      1.1. free the memory for the Mailbox;
  //      1.2. return OK;
  //    }
  //    else
  //    {
  //      1.3. return NOT_EMPTY;
  //    }
  Mailbox* mailbox = mBox;
  exception status;
  if (mailbox) {
    return status;
  }
  return status;
}
/**
 * This call will send a Message to the specified Mailbox. if there is a receiving task waiting for
 * a message on the specified Mailbox, send_wait will deliver it and the receiving task will be moved
 * to the ReadyList, Otherwise, if there is not a receiving task waiting for a message on the specified
 * Mailbox, the sending task will be blocked. In both cases(blocked or not blocked) a new task schedule
 * is done and possibly a context switch. During the blocking period of the task its deadline might be
 * reached. At that point in time the blocked task will be resumed with the exception:
 * DEADLINE_REACHED. Note: send_wait and send_no_wait Messages shall not be mixed in the same Mailbox.
 * @argument --> *mBox: a pointer to the specified Mailbox
 *           --> *Data: a pointer to a memory area where the data of the communication of the
 *                      communicated Message is residing.
 * @return --> OK: Normal behavior, no exception occurred.
 *         --> DEADLINE_REACHED: this return parameter is given if the sending tasks' deadline is reached
 *                                 while it is blocked by the send_wait call.
 */
exception send_wait(Mailbox* mBox, void* Data) {
  // 1. disable interrupt
  // 2. Save context
  // 3. if(first execution) {
  //        3.1 set: "not first execution any more"
  //        3.2 if(receiving task is waiting) {
  //              copy sender's data to the data area of the receivers Message;
  //              Remove receiving task's Message struct from the mailbox;
  //              move receiving task to ReadyList;
  //            }
  //            else
  //            {
  //              allocate a message structure;
  //              Set data pointer;
  //              Add Message to the mailbox;
  //              move sending task from ReadyList to waitingList;
  //            }
  //      load context;
  //    }
  //    else
  //    {
  //      if(deadline is reached){
  //        disable interrupt;
  //        remove send message;
  //        enable interrupt;
  //        return DEADLINE_REACHED;
  //      }
  //      else
  //      {
  //        return OK;
  //      }
  //    }
  exception status;
  if (mBox && Data) {
    return status;
  }
  return status;
}
/**
 * This call will attempt to receive a Message from the specified Mailbox. if there is a send_wait or
 * sen_no_wait Message waiting for a receive_wait or a receive_no_wait Message on the specified Mailbox,
 * receive_wait will collect it. if the Message was of send_wait type the sending task will will be moved to
 * the readyList. Otherwise, if there is not a send Message(of either type) waiting on the specified Mailbox
 * the receiving task will be blocked. In both cases (blocked or not blocked) a new task schedule is done
 * and possibly a context switch. During the blocking period of the task its deadline might be reached. At
 * that point in time the blocked task will be resumed with the exception: DEADLINE_REACHED.
 * @argument --> *mBox: a pointer to the specified Mailbox
 *           --> *Data: a pointer to a memory area where the data of the communicated Message is to be stored
 * @return exception: The exception return parameter can have two possible values.
 *           --> OK: Normal function, no exception occurred.
 *           -->DEADLINE_REACHED: This return parameter is given if the receiving tasks' deadline is reached
 *                                while it is blocked by the receive_wait call.
 */
exception receive_wait(Mailbox* mBox, void* Data) {
  // 1. disable interrupt
  // 2. save context
  // 3. if(first execution) {
  //      Set: "not first execution any more";
  //      if(send Message is waiting) {
  //        copy sender's data to receiving task's data area;
  //        remove sending task's Message struct from the Mailbox;
  //        if(Message was of wait type) {
  //          Move sending task to ReadyList;
  //        }else{
  //          free senders data area;
  //        }
  //      }
  //      else
  //      {
  //        Allocate a Message structure;
  //        add message to the mailbox;
  //        move receiving task from readyList to waitingList;
  //      }
  //      load context;
  //   }
  //   else
  //   {
  //     if(deadline is reached) {
  //       disable interrupt;
  //       remove receive message;
  //       enable interrupt;
  //       return DEADLINE_REACHED;
  //     }
  //     else
  //     {
  //       return OK;
  //     }
  //   }
  exception status;
  if (mBox && Data) {
    return status;
  }
  return status;
}
/**
 * This call will send a message to the specified Mailbox. The sending task will continue execution after
 * the call. When the Mailbox is full, the oldest Message will be overwriten. The send_no_wait call will
 * imply a new scheduling and possibly a context switch. Note: send_no_wait and send_wait Message shall not
 * be mixed in the same Mailbox.
 * @argument --> *mBox: a pointer to the specified Mailbox
 *           --> *Data: a pointer to a memory area where the data of the communicated Message is residing
 * @return Description of the function's status, i.e FAIL/OK
 */
exception send_no_wait(Mailbox* mBox, void* Data) {
  // 1. disable interrupt
  // 2. save context
  // 3. if (first execution) {
  //      set: "not first execution anymore"
  //      if(receiving task is waiting) {
  //        copy data to receiving tasks' data area;
  //        remove receiving task's Message struct from the Mailbox;
  //        Move receiving task to ReadyList;
  //        Load context;
  //      }
  //      else
  //      {
  //        allocate a message structure;
  //        copy data to the message;
  //        if (mailbox is full) {
  //          remove the oldest message struct;
  //        }
  //        add message to the Mailbox;
  //      }
  //    }
  //    return status;
  exception status;
  if (mBox && Data) {
    return status;
  }
  return status;
}
/**
 * This call will attempt to receive a Message from the specified Mailbox. The calling task will continue
 * execution after the call. when there is no send message available, or if the Mailbox is empty, the
 * function will return FAIL. Otherwise, OK is returned.The call might imply a new scheduling and possibly
 * a context switch.
 * @argument --> *mBox: a pointer to the specified Mailbox.
 *           --> *Data: a pointer to the Message
 * @return --> integer indicating whether or not a message was received(OK/FAIL).
 */
exception receive_no_wait(Mailbox* mBox, void* Data) {
  // 1. disable interrupt
  // 2. save context
  // 3. if(first execution) {
  //      set: "not first execution any more";
  //      if(send message is waiting) {
  //        copy sender's data to receiving task's data area;
  //        remove sending task's message struct from the mailbox;
  //        if(message was of wait type) {
  //          move sending task to readyList;
  //        }else {
  //          free sender's data area;
  //        }
  //      }
  //      load context;
  //    }
  // 4. return status on received message
  exception status;
  if (mBox && Data) {
    return status;
  }
  return status;
}
/////////////////////////////////////Timing function///////////////////////////////////////////////
