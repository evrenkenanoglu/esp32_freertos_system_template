/** @file       process.h
 *  @brief      Process
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Deniz Fer 
 *              Evren Kenanoglu
 *  @date       07/08/2021
 */
#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H

/** INCLUDES ******************************************************************/
#include "system.h"
/** CONSTANTS *****************************************************************/

///@brief Process_t Object Structure
///@ingroup PROCESS
typedef struct _Process_t Process_t;

///@brief    Process number used for defining a process throughout the system
///@ingroup   PROCESS
typedef uint8_t _eProcessID_t;

/** TYPEDEFS ******************************************************************/

typedef enum
{
    eProcessStateIdle,
    eProcessStateRunning,
    eProcessStateSuspended,
    eProcessStateTerminated,
} eProcessState_t;

/** MACROS ********************************************************************/

//** PROCESS Definitions **//

/** @brief      Process init function prototype
 *  @param      _name   Name of the function
 *  @details    process Pointer to tsProcess structure that holds the process information
 */
#define PROCESS_INIT_FUNC(_name)                      void _name(Process_t* process)

/** @brief      Process suspend function prototype
 *  @param      _name   Name of the function
 *  @details    process Pointer to tsProcess structure that holds the process information
 */
#define PROCESS_SUSPEND_FUNC(_name)                   void _name(Process_t* process)

/** @brief      Process resume function prototype
 *  @param      _name   Name of the function
 *  @details    process Pointer to tsProcess structure that holds the process information
 */
#define PROCESS_RESUME_FUNC(_name)                    void _name(Process_t* process)

/** @brief      Process terminate function prototype
 *  @param      _name   Name of the function
 *  @details    process Pointer to tsProcess structure that holds the process information
 */
#define PROCESS_TERMINATE_FUNC(_name)                 void _name(Process_t* process)

/** @brief      Process event handler function prototype
 *  @details    Process can change its event handler depending on the state.
 *              process Pointer to tsProcess structure that holds the process information
 *  @param      _name           Name of the function
 */
#define PROCESS_HANDLER_PROTO(_name)                  void _name(Process_t* process)

/** @brief      Process state change macro
 *  @param      _processPtr   pointer of process object
 *  @param      _stateEnum    enumeration of state
 */
#define PROCESS_STATE_CHANGE(_processPtr, _stateEnum) _processPtr->state = _stateEnum

/** @brief      Process state change macro
 *  @param      _processPtr   pointer of process object
 *  @param      _stateEnum    enumeration of state
 */
// #define PROCESS_STATE_CURRENT(_eProcessID)
// {
//     do{
//         _eProcessID =
//     }while()
// }

struct _Process_t
{
    _eProcessID_t ID;
    PROCESS_INIT_FUNC((*init));
    PROCESS_SUSPEND_FUNC((*suspend));
    PROCESS_RESUME_FUNC((*resume));
    PROCESS_TERMINATE_FUNC((*terminate));
    void*       parameters;
    const void* constants;
    uint8_t     state;
    uint8_t*    childProcessList;
};

/** @brief  Macro to create a generic process object with _name
 *  @param  _name           Name of process object
 *  @param  _initFunc       Name of initialization function
 *  @param  _suspendFunc    Name of suspending function
 *  @param  _terminateFunc  Name of termination function
 *  @param  _enum           System-wide process enumeration of current object(ID)
 *  @param  _params         Pointer to process specific parameters structure
 *  @param  _consts         Pointer to process specific constants structure
 *  @param _state           State of process object
 */

#define PROCESS_CREATE(_name, _enum, _initFunc, _suspendFunc, _resumeFunc, _terminateFunc, _params, _consts)                                                                                           \
    extern PROCESS_INIT_FUNC(_initFunc);                                                                                                                                                               \
    extern PROCESS_SUSPEND_FUNC(_suspendFunc);                                                                                                                                                         \
    extern PROCESS_RESUME_FUNC(_resumeFunc);                                                                                                                                                           \
    extern PROCESS_TERMINATE_FUNC(_terminateFunc);                                                                                                                                                     \
    Process_t _name = {                                                                                                                                                                                \
        .ID               = _enum,                                                                                                                                                                     \
        .init             = _initFunc,                                                                                                                                                                 \
        .suspend          = _suspendFunc,                                                                                                                                                              \
        .resume           = _resumeFunc,                                                                                                                                                               \
        .terminate        = _terminateFunc,                                                                                                                                                            \
        .parameters       = (_params),                                                                                                                                                                 \
        .constants        = (_consts),                                                                                                                                                                 \
        .state            = eProcessStateIdle,                                                                                                                                                         \
        .childProcessList = NULL,                                                                                                                                                                      \
    };

#ifndef FILE_PROCESS_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

/** VARIABLES *****************************************************************/

/** FUNCTIONS *****************************************************************/

/** @brief      Start a Process
 *  @param[in]  Process_t Pointer to target object
 *  @retval     EXIT_FAILURE
 *  @retval     EXIT_SUCCESS
 */
INTERFACE uint8_t processStart(Process_t* process);

/** @brief      Suspend a Process
 *  @param[in]  Process_t Pointer to target object
 *  @retval     EXIT_FAILURE
 *  @retval     EXIT_SUCCESS
 */
INTERFACE uint8_t processSuspend(Process_t* process);

/** @brief      Suspend a Process
 *  @param[in]  Process_t Pointer to target object
 *  @retval     EXIT_FAILURE
 *  @retval     EXIT_SUCCESS
 */
INTERFACE uint8_t processResume(Process_t* process);

/** @brief      Terminate a Process
 *  @param[in]  Process_t Pointer to target object
 *  @retval     EXIT_FAILURE
 *  @retval     EXIT_SUCCESS
 */
INTERFACE uint8_t processTerminate(Process_t* process);

#undef INTERFACE // Should not let this roam free

#endif // FILE_PROCESS_H
