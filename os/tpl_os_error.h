/**
 * @file tpl_os_error.h
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005+
 * Trampoline est prot�g� par la loi sur la propri�t� intellectuelle
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 *
 * @section descr File description
 *
 * Trampoline Errors macros, functions and datatypes header
 *
 */

#ifndef __TPL_OS_ERROR_H__
#define __TPL_OS_ERROR_H__

#include "tpl_os.h"

/*
 * Remember (see "The design of Trampoline") :
 * NO_TASK means there is no task defined in the system
 * OS_EXTENDED means extended error checking is done
 * WITH_ERROR_HOOK means an error hook routine is called when
 * an error occurs.
 */

#ifdef WITH_ERROR_HOOK

/**
 * @union ID_PARAM_BLOCK
 *
 * This union is used in error hook parameter (#PARAM_BLOCK) to specify
 * the related OS element's identifier. An OS element can be either a task
 * or a resource or an alarm.
 *
 * Of course, it is an union because the kinds of identifier are mutually exclusive.
 *
 * @see #PARAM_BLOCK
 * @see #tpl_service
 */
union ID_PARAM_BLOCK {
        TaskType        task_id;        /**< used by #ActivateTask, #ChainTask, #GetTaskState, #SetEvent, #GetEvent */
        TaskRefType     task_id_ref;    /**< used by #GetTaskID */
        ResourceType    res_id;         /**< used by #GetResource, #ReleaseResource */
        AlarmType       alarm_id;       /**< @todo document this */
};

/**
 * @union PARAM_PARAM_BLOCK
 *
 * This union describes the parameter of the param block (#PARAM_BLOCK).
 *
 * @see #PARAM_BLOCK
 * @see #tpl_service
 */
union PARAM_PARAM_BLOCK {
        TaskStateRefType    state;          /**< used by #GetTaskState */
        TickType            tick;           /**< used by #SetRelAlarm, #SetAbsAlarm */
        TickRefType         tick_ref;       /**< used by #GetAlarm */
        AlarmBaseRefType    alarm_base_ref; /**< used by #GetAlarmBase */
        EventMaskType       mask;           /**< used by #SetEvent, #ClearEvent, #WaitEvent */
        EventMaskRefType    mask_ref;       /**< used by #GetEvent */
};

/**
 * @struct PARAM_BLOCK 
 *
 * This structure gathers all parameters for an error hook
 */
struct PARAM_BLOCK {
    union ID_PARAM_BLOCK    id;     /**< identifies the OS element concerned by the error*/
    union PARAM_PARAM_BLOCK param;  /**< gives more information about the reason of the error */
    TickType                cycle;  /**< cycle set for a relative alarm */
};

/**
 * @struct SERVICE_CALL_DESCRIPTOR
 * 
 * This structure gathers the os service identifier and its parameters
 */
struct SERVICE_CALL_DESCRIPTOR {
    struct PARAM_BLOCK  parameters; /**< information about conditions seen when error has been detected */
    unsigned char       service_id; /**< identifier of the service which raised the error */
};

/**
 * @typedef tpl_service_call_desc
 *
 * This is an alias for the structure #SERVICE_CALL_DESCRIPTOR
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 */
typedef struct SERVICE_CALL_DESCRIPTOR tpl_service_call_desc;

/**
 * This global variable is where all informations about the error are store.
 *
 * This global variable must not be accessed directly, neither by application
 * nor by OS services.
 *
 * Application (via ErrorHook function) should use some of these macros :
 * - #OSError_ActivateTask_TaskID
 * - #OSError_ChainTask_TaskID
 * - #OSError_GetTaskID_TaskID
 * - #OSError_GetTaskState_TaskID
 * - #OSError_GetTaskState_State
 * - #OSError_GetResource_ResID
 * - #OSError_ReleaseResource_ResID
 * - #OSError_SetEvent_TaskID
 * - #OSError_SetEvent_Mask
 * - #OSError_ClearEvent_Mask
 * - #OSError_GetEvent_TaskID
 * - #OSError_GetEvent_Event
 * - #OSError_WaitEvent_Mask
 * - #OSError_GetAlarmBase_AlarmID
 * - #OSError_GetAlarmBase_Info
 * - #OSError_GetAlarm_AlarmID
 * - #OSError_GetAlarm_Tick
 * - #OSError_SetRelAlarm_AlarmID
 * - #OSError_SetRelAlarm_increment
 * - #OSError_SetRelAlarm_cycle
 * - #OSError_SetAbsAlarm_AlarmID
 * - #OSError_SetAbsAlarm_start
 * - #OSError_SetAbsAlarm_cycle
 * - #OSError_CancelAlarm_AlarmID  
 *
 * Within OS services, these macros should be used to modify this variable :
 * - #STORE_SERVICE
 * - #STORE_TASK_ID
 * - #STORE_TASK_ID_REF
 * - #STORE_TASK_STATE_REF
 * - #STORE_RESOURCE_ID
 * - #STORE_ALARM_ID
 * - #STORE_ALARM_BASE_REF
 * - #STORE_TICK_REF
 * - #STORE_TICK_1
 * - #STORE_TICK_2
 * - #STORE_EVENT_MASK
 * - #STORE_EVENT_MASK_REF
 */
extern tpl_service_call_desc tpl_service;

/**
 * this function is used to call the ErrorHook callback
 * 
 * @param tpl_status The error code which causes the call back
 */
void tpl_call_error_hook(tpl_status);

/************************
 * Services identifiers *
 ************************/

/**
 * @def OSServiceId_ActivateTask
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #ActivateTask
 */
#define OSServiceId_ActivateTask                1

/**
 * @def OSServiceId_TerminateTask
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #TerminateTask
 */
#define OSServiceId_TerminateTask               2

/**
 * @def OSServiceId_ChainTask
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #ChainTask
 */
#define OSServiceId_ChainTask                   3

/**
 * @def OSServiceId_Schedule
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #Schedule
 */
#define OSServiceId_Schedule                    4

/**
 * @def OSServiceId_GetTaskID
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #GetTaskID
 */
#define OSServiceId_GetTaskID                   5

/**
 * @def OSServiceId_GetTaskState
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #GetTaskState
 */
#define OSServiceId_GetTaskState                6

/**
 * @def OSServiceId_EnableAllInterrupts
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #EnableAllInterrupts
 */
#define OSServiceId_EnableAllInterrupts         7

/**
 * @def OSServiceId_DisableAllInterrupts
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #DisableAllInterrupts
 */
#define OSServiceId_DisableAllInterrupts        8

/**
 * @def OSServiceId_ResumeAllInterrupts
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #ResumeAllInterrupts
 */
#define OSServiceId_ResumeAllInterrupts         9

/**
 * @def OSServiceId_SuspendAllInterrupts
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #SuspendAllInterrupts
 */
#define OSServiceId_SuspendAllInterrupts        10

/**
 * @def OSServiceId_ResumeOSInterrupts
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #ResumeOSInterrupts
 */
#define OSServiceId_ResumeOSInterrupts          11

/**
 * @def OSServiceId_SuspendOSInterrupts
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #SuspendOSInterrupts
 */
#define OSServiceId_SuspendOSInterrupts         12


/**
 * @def OSServiceId_GetResource
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #GetResource
 */
#define OSServiceId_GetResource                 13

/**
 * @def OSServiceId_ReleaseResource
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #ReleaseResource
 */
#define OSServiceId_ReleaseResource             14

/**
 * @def OSServiceId_SetEvent
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #SetEvent
 */
#define OSServiceId_SetEvent                    15

/**
 * @def OSServiceId_ClearEvent
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #ClearEvent
 */
#define OSServiceId_ClearEvent                  16

/**
 * @def OSServiceId_GetEvent
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #GetEvent
 */
#define OSServiceId_GetEvent                    17

/**
 * @def OSServiceId_WaitEvent
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #WaitEvent
 */
#define OSServiceId_WaitEvent                   18

/**
 * @def OSServiceId_GetAlarmBase
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #GetAlarmBase
 */
#define OSServiceId_GetAlarmBase                19

/**
 * @def OSServiceId_GetAlarm
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #GetAlarm
 */
#define OSServiceId_GetAlarm                    20

/**
 * @def OSServiceId_SetRelAlarm
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #SetRelAlarm
 */
#define OSServiceId_SetRelAlarm                 21

/**
 * @def OSServiceId_SetAbsAlarm
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #SetAbsAlarm
 */
#define OSServiceId_SetAbsAlarm                 22

/**
 * @def OSServiceId_CancelAlarm
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #CancelAlarm
 */
#define OSServiceId_CancelAlarm                 23

/**
 * @def OSServiceId_GetActiveApplicationMode
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #GetActiveApplicationMode
 */
#define OSServiceId_GetActiveApplicationMode    24

/**
 * @def OSServiceId_StartOS
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #StartOS
 */
#define OSServiceId_StartOS                     25

/**
 * @def OSServiceId_ShutdownOS
 *
 * @see #SERVICE_CALL_DESCRIPTOR
 * @see #ShutdownOS
 */
#define OSServiceId_ShutdownOS                  26

/************************************************************************
 * macros to access the service id and its parameters from hook routine *
 ************************************************************************/

/**
 * @def OSErrorGetServiceId
 *
 * Gives identifier of the OS service which raised the error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 */
#define OSErrorGetServiceId()   (tpl_service.service_id)

/**
 * @def OSError_ActivateTask_TaskID
 *
 * ActivateTask service error parameter
 *
 * Returns the identifier (#TaskType) of the task which caused the error.
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 */
#define OSError_ActivateTask_TaskID()   \
    (tpl_service.parameters.id.task_id)
    
/**
 * @def OSError_ChainTask_TaskID
 *
 * ChainTask service error parameter
 *
 * Returns the identifier (#TaskType) of the task which caused the error.
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 */
#define OSError_ChainTask_TaskID()      \
    (tpl_service.parameters.id.task_id)
    
/**
 * @def OSError_GetTaskID_TaskID
 *
 * GetTaskID service error parameter
 *
 * Returns the identifier (#TaskType) of the task which caused the error.
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 */
#define OSError_GetTaskID_TaskID()             \
    (tpl_service.parameters.id.task_id_ref)
    
/**
 * @def OSError_GetTaskState_TaskID
 *
 * One of GetTaskState service error parameters
 *
 * Returns the identifier (#TaskType) of the task which caused the error.
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see #OSError_GetTaskState_State
 */
#define OSError_GetTaskState_TaskID()   \
    (tpl_service.parameters.id.task_id)

/**
 * @def OSError_GetTaskState_State
 *
 * One of GetTaskState service error parameters
 *
 * Returns the state (#TaskStateRefType) of the task when the error occured.
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see #OSError_GetTaskState_TaskID
 */
#define OSError_GetTaskState_State()    \
    (tpl_service.parameters.param.state)

/**
 * @def OSError_GetResource_ResID
 *
 * GetResource service error parameter 
 *
 * Returns the identifier (#ResourceType) of the resource which caused the error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 */
#define OSError_GetResource_ResID()     \
    (tpl_service.parameters.id.res_id)

/**
 * @def OSError_ReleaseResource_ResID
 *
 * ReleaseResource service error parameter 
 *
 * Returns the identifier (#ResourceType) of the resource which caused the error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 */
#define OSError_ReleaseResource_ResID() \
    (tpl_service.parameters.id.res_id)

/**
 * @def OSError_SetEvent_TaskID
 *
 * One of the SetEvent service error parameters
 *
 * Returns the identifier (#TaskType) of the task which caused the error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see #OSError_SetEvent_Mask
 */
#define OSError_SetEvent_TaskID()       \
    (tpl_service.parameters.id.task_id)

/**
 * @def OSError_SetEvent_Mask
 *
 * One of the SetEvent service error parameters
 *
 * Returns the mask (#EventMaskType) of the event when error occurred
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see #OSError_SetEvent_TaskID
 */
#define OSError_SetEvent_Mask()         \
    (tpl_service.parameters.param.mask)

/**
 * @def OSError_ClearEvent_Mask
 *
 * ClearEvent service error parameter
 *
 * Returns the mask (#EventMaskType) of the event when error occurred
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 */
#define OSError_ClearEvent_Mask()       \
    (tpl_service.parameters.param.mask)
    
/**
 * @def OSError_GetEvent_TaskID
 *
 * One of GetEvent service error parameters
 *
 * Returns the identifier (#TaskType) of the task which caused the error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see #OSError_GetEvent_Event
 */
#define OSError_GetEvent_TaskID()       \
    (tpl_service.parameters.id.task_id)
	
/**
 * @def OSError_GetEvent_Event
 *
 * One of GetEvent service error parameters
 *
 * Returns the mask (#EventMaskType) of the event when error occurred
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see #OSError_GetEvent_TaskID
 */
#define OSError_GetEvent_Event()        \
    (tpl_service.parameters.param.mask)
    
/**
 * @def OSError_WaitEvent_Mask
 *
 * WaitEvent service error parameter
 *
 * Returns the mask (#EventMaskType) of the event when error occurred
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 */
#define OSError_WaitEvent_Mask()        \
    (tpl_service.parameters.param.mask)

/**
 * @def OSError_GetAlarmBase_AlarmID
 *
 * One of GetAlarmBase service error parameters 
 *
 * Returns the identifier (#AlarmType) of the alarm which caused error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see #OSError_GetAlarmBase_Info
 */
#define OSError_GetAlarmBase_AlarmID()  \
    (tpl_service.parameters.id.alarm_id)
/**
 * @def OSError_GetAlarmBase_Info
 *
 * One of GetAlarmBase service error parameters
 *
 * Returns the basic characteristics (#AlarmBaseRefType) of the alarm which caused the error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see #AlarmBaseType
 * @see #AlarmBaseRefType
 * @see #OSError_GetAlarmBase_AlarmID
 */
#define OSError_GetAlarmBase_Info()     \
    (tpl_service.parameters.param.alarm_base_ref)
    
/**
 * @def OSError_GetAlarm_AlarmID
 *
 * One of GetAlarm service error parameters
 *
 * Returns the identifier (#AlarmType) of the alarm which caused error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see OSError_GetAlarm_Tick
 */
#define OSError_GetAlarm_AlarmID()      \
    (tpl_service.parameters.id.alarm_id)

/**
 * @def OSError_GetAlarm_Tick
 *
 * One of GetAlarm service error parameters
 *
 * Returns the number of ticks (#TickRefType) on which the alarm which caused error should trigger
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see OSError_GetAlarm_AlarmID
 */
#define OSError_GetAlarm_Tick()         \
    (tpl_service.parameters.param.tick_ref)

/**
 * @def OSError_SetRelAlarm_AlarmID
 *
 * One of SetRelAlarm service error parameters 
 *
 * Returns the identifier (#AlarmType) of the alarm which caused the error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 * 
 * @see #OSError_SetRelAlarm_increment
 * @see #OSError_SetRelAlarm_cycle
 */
#define OSError_SetRelAlarm_AlarmID()   \
    (tpl_service.parameters.id.alarm_id)

/**
 * @def OSError_SetRelAlarm_increment
 *
 * One of SetRelAlarm service error parameters
 *
 * Returns the number of ticks (#TickType) on which the alarm which caused error should trigger
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see OSError_SetRelAlarm_AlarmID
 * @see OSError_SetRelAlarm_cycle
 */
#define OSError_SetRelAlarm_increment() \
    (tpl_service.parameters.param.tick)

/**
 * @def OSError_SetRelAlarm_cycle
 *
 * One of SetRelAlarm service error parameters
 *
 * Returns the cycle in ticks (#TickType) of the alarm which caused error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see OSError_SetRelAlarm_AlarmID
 * @see #OSError_SetRelAlarm_increment
 */
#define OSError_SetRelAlarm_cycle()     \
    (tpl_service.parameters.cycle)

/**
 * @def OSError_SetAbsAlarm_AlarmID
 *
 * One of SetAbsAlarm service error parameters
 *
 * Returns the identifier (#AlarmType) of the alarm which caused the error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see OSError_SetAbsAlarm_start
 * @see OSError_SetAbsAlarm_cycle
 */
#define OSError_SetAbsAlarm_AlarmID()   \
    (tpl_service.parameters.id.alarm_id)

/**
 * @def OSError_SetAbsAlarm_start
 *
 * One of SetAbsAlarm service error parameters
 *
 * Returns the ticks (#TickType) of the alarm which caused the error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see OSError_SetAbsAlarm_AlarmID
 * @see OSError_SetAbsAlarm_cycle
 */
#define OSError_SetAbsAlarm_start()     \
    (tpl_service.parameters.param.tick)

/**
 * @def OSError_SetAbsAlarm_cycle
 *
 * One of SetAbsAlarm service error parameters
 *
 * Returns the cycle (#TickType) of the alarm which caused the error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 *
 * @see OSError_SetAbsAlarm_AlarmID
 * @see OSError_SetAbsAlarm_start
 */
#define OSError_SetAbsAlarm_cycle()     \
    (tpl_service.parameters.cycle)

/**
 * @def OSError_CancelAlarm_AlarmID
 *
 * CancelAlarm service error parameter 
 *
 * Returns the identifier (#AlarmType) of the alarm which caused error
 *
 * @warning this macro does only make sense when used within #ErrorHook function
 */
#define OSError_CancelAlarm_AlarmID()   \
    (tpl_service.parameters.id.alarm_id)

#endif /* defined WITH_ERROR_HOOK  */

/**
 * @def STORE_SERVICE
 *
 * Stores the service identifier into service error variable
 *
 * @see #tpl_service
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_SERVICE(service)   \
    tpl_service.service_id = (service);
#else
#   define STORE_SERVICE(service)
#endif

/*
 * STORE_TASK_ID
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_TASK_ID(task_id)   \
    tpl_service.parameters.id.task_id = (task_id);
#else
#   define STORE_TASK_ID(task_id)
#endif 

/*
 * STORE_TASK_ID_REF
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_TASK_ID_REF(task_id_ref)  \
    tpl_service.parameters.id.task_id_ref;
#else
#   define STORE_TASK_ID_REF(task_id_ref)
#endif

/*
 * STORE_TASK_STATE_REF
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_TASK_STATE_REF(state)  \
    tpl_service.parameters.param.state = state;
#else
#   define STORE_TASK_STATE_REF(state)
#endif

/*
 * STORE_RESOURCE_ID
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_RESOURCE_ID(res_id)    \
    tpl_service.parameters.id.res_id = res_id;
#else
#   define STORE_RESOURCE_ID(res_id)
#endif

/*
 * STORE_ALARM_ID
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_ALARM_ID(alarm_id)     \
    tpl_service.parameters.id.alarm_id = alarm_id;
#else
#   define STORE_ALARM_ID(alarm_id)
#endif

/*
 * STORE_ALARM_BASE_REF
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_ALARM_BASE_REF(ref)     \
    tpl_service.parameters.param.alarm_base_ref = ref;
#else
#   define STORE_ALARM_BASE_REF(ref)
#endif

/*
 * STORE_TICK_REF
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_TICK_REF(ref)     \
    tpl_service.parameters.param.tick_ref = ref;
#else
#   define STORE_TICK_REF(tick_ref)
#endif

/*
 * STORE_TICK_1
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_TICK_1(t)     \
    tpl_service.parameters.param.tick = t;
#else
#   define STORE_TICK_1(t)
#endif

/*
 * STORE_TICK_2
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_TICK_2(t)     \
    tpl_service.parameters.cycle = t;
#else
#   define STORE_TICK_2(t)
#endif

/*
 * STORE_EVENT_MASK
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_EVENT_MASK(m)     \
    tpl_service.parameters.param.mask = m;
#else
#   define STORE_EVENT_MASK(m)
#endif

/*
 * STORE_EVENT_MASK_REF
 */
#ifdef WITH_ERROR_HOOK
#   define STORE_EVENT_MASK_REF(ref)     \
    tpl_service.parameters.param.mask_ref = ref;
#else
#   define STORE_EVENT_MASK_REF(ref)
#endif

/*-----------------------------------------------------------------------------
 * PROCESS_ERROR
 * This maccro generates the code to call the error hook, when
 * an error occured, if the WITH_ERROR_HOOK flag is on and no
 * code at all if the flag is off.
 */
#ifdef WITH_ERROR_HOOK
#define PROCESS_ERROR(error)        \
    if (error != E_OK) {            \
        tpl_call_error_hook(error); \
    }                               
#else
#define PROCESS_ERROR(error)
#endif

/*-----------------------------------------------------------------------------
 * IF_NO_EXTENDED_ERROR
 * This macro generate a if (result == E_OK) {
 * when OS_EXTENDED is on and no code at all if it is off
 */
#ifdef OS_EXTENDED
#   define IF_NO_EXTENDED_ERROR(result) \
    if (result == E_OK) {
#else
#   define IF_NO_EXTENDED_ERROR(result)
#endif

/*-----------------------------------------------------------------------------
 * END_IF_NO_EXTENDED_ERROR
 * See above
 */
#ifdef OS_EXTENDED
#   define END_IF_NO_EXTENDED_ERROR() \
    }
#else
#   define END_IF_NO_EXTENDED_ERROR()
#endif

/*-----------------------------------------------------------------------------
 * LOCK_WHEN_HOOK
 * Lock when WITH_ERROR_HOOK is defined. Used for some services
 * that does not require locking in standard mode since they do not
 * access globals
 */
#ifdef WITH_ERROR_HOOK
#   define LOCK_WHEN_HOOK()     \
    tpl_get_task_lock();
#   define UNLOCK_WHEN_HOOK()   \
    tpl_release_task_lock();
#else
#   define LOCK_WHEN_HOOK()
#   define UNLOCK_WHEN_HOOK()
#endif

/*-----------------------------------------------------------------------------
 * LOCK_WHEN_NO_HOOK
 * Lock when WITH_ERROR_HOOK is not defined. Used for some services
 * that require a different locking scheme according to hook use
 */
#ifdef WITH_ERROR_HOOK
#   define LOCK_WHEN_NO_HOOK()
#   define UNLOCK_WHEN_NO_HOOK()
#else
#   define LOCK_WHEN_NO_HOOK()     \
    tpl_get_task_lock();
#   define UNLOCK_WHEN_NO_HOOK()   \
    tpl_release_task_lock();
#endif

/*-----------------------------------------------------------------------------
 * LOCK_WHEN_TASK
 * Lock when NO_TASK is not defined. Used for task services
 * that does not require locking in standard mode since there is no
 * task to operate on
 */
#ifdef NO_TASK
#   define LOCK_WHEN_TASK()
#   define UNLOCK_WHEN_TASK()
#else
#   define LOCK_WHEN_TASK()     \
    tpl_get_task_lock();
#   define UNLOCK_WHEN_TASK()   \
    tpl_release_task_lock();
#endif

/*-----------------------------------------------------------------------------
 * LOCK_WHEN_RESOURCE
 * Lock when NO_RESOURCE is not defined. Used for resource services
 * that does not require locking in standard mode since there is no
 * resource to operate on
 */
#ifdef NO_RESOURCE
#   define LOCK_WHEN_RESOURCE()
#   define UNLOCK_WHEN_RESOURCE()
#else
#   define LOCK_WHEN_RESOURCE()     \
    tpl_get_task_lock();
#   define UNLOCK_WHEN_RESOURCE()   \
    tpl_release_task_lock();
#endif

/*-----------------------------------------------------------------------------
 * CHECK_TASK_ID_ERROR macro definition
 * This macro defines the appropriate error program
 * for out of range task_id. It is used in os services
 * that use task_id as parameter.
 */

/* No extended error checking (! OS_EXTENDED)  */
#if !defined(OS_EXTENDED)
    /* Does not check the task_id in this case */
#   define CHECK_TASK_ID_ERROR(task_id,result)
#endif

/* NO_TASK and extended error checking (OS_EXTENDED)        */
#if defined(NO_TASK) && defined(OS_EXTENDED)
    /* E_OS_ID is returned in this case  */
#   define CHECK_TASK_ID_ERROR(task_id,result) \
    if (result == E_OK) {                      \
        result = E_OS_ID;                      \
    }
#endif

/* !NO_TASK and extended error checking (OS_EXTENDED)   */
#if !defined(NO_TASK) && defined(OS_EXTENDED)
    /* E_OK or E_OS_LIMIT   */
#   define CHECK_TASK_ID_ERROR(task_id,result)      \
    if (result == E_OK && task_id >= TASK_COUNT) {  \
        result = E_OS_ID;                           \
    }
#endif

/*-----------------------------------------------------------------------------
 * CHECK_TASK_CALL_LEVEL_ERROR macro definition
 * This macro defines the appropriate error program
 * that check for call level
 */

/*  NO_TASK and extended error checking (OS_EXTENDED).
    Since there is no task, there is no task level calling  */
#if defined(NO_TASK) && defined(OS_EXTENDED)
#   define CHECK_TASK_CALL_LEVEL_ERROR(result)      \
    if (result == E_OK) {                           \
        result = E_OS_CALLEVEL;                     \
    }
#endif

/*  !NO_TASK and extended error checking (OS_EXTENDED). */
#if !defined(NO_TASK) && defined(OS_EXTENDED)
#   define CHECK_TASK_CALL_LEVEL_ERROR(result)          \
    if (result == E_OK && tpl_os_state != OS_TASK) {    \
        result = E_OS_CALLEVEL;                         \
    }
#endif
    
/*  no extended error checking !(OS_EXTENDED).    */
#if !defined(OS_EXTENDED)
#   define CHECK_TASK_CALL_LEVEL_ERROR(result)
#endif

/*-----------------------------------------------------------------------------
 * CHECK_NOT_EXTENDED_TASK_ERROR macro definition
 * This macro defines the appropriate error program
 * that check the task is an extended one
 */
#ifdef OS_EXTENDED
#   define CHECK_NOT_EXTENDED_TASK_ERROR(task_id,result)                            \
    if (tpl_task_table[task_id]->exec_desc.static_desc->type != EXTENDED_TASK) {    \
        result = E_OS_ACCESS;                                                       \
    }
#else
#   define CHECK_NOT_EXTENDED_TASK_ERROR(task_id,result)
#endif

/*-----------------------------------------------------------------------------
 * CHECK_NOT_EXTENDED_RUNNING_ERROR macro definition
 * This macro defines the appropriate error program
 * that check the running task is an extended one
 */
#ifdef OS_EXTENDED
#   define CHECK_NOT_EXTENDED_RUNNING_ERROR(result)                                     \
    if (((tpl_task *)tpl_running_obj)->exec_desc.static_desc->type != EXTENDED_TASK) {  \
        result = E_OS_ACCESS;                                                           \
    }
#else
#   define CHECK_NOT_EXTENDED_RUNNING_ERROR(result)
#endif

/*-----------------------------------------------------------------------------
 * CHECK_SUSPENDED_TASK_ERROR macro definition
 * This macro defines the appropriate error program
 * that check the task is not in the suspended state
 */
#ifdef OS_EXTENDED
#   define CHECK_SUSPENDED_TASK_ERROR(task_id,result)                      \
    if (tpl_task_table[task_id]->exec_desc.state == SUSPENDED) {    \
        result = E_OS_STATE;                                        \
    }
#else
#   define CHECK_SUSPENDED_TASK_ERROR(task_id,result)
#endif


/*--------------------------------------------------------------------------------
 * CHECK_RUNNING_OWNS_REZ_ERROR macro definition
 * This macro defines the appropriate error program
 * that check for the running object owning a resource
 */

/*  If NO_TASK, this error cannot happen    */
#if defined(NO_TASK)
#   define CHECK_RUNNING_OWNS_REZ_ERROR(result)
#endif

/*  If !NO_TASK and not extended error checking !(OS_EXTENDED)
    the occurence is not tested                                 */
#if !defined(NO_TASK) && !defined(OS_EXTENDED)
#   define CHECK_RUNNING_OWNS_REZ_ERROR(result)
#endif

/*  If !NO_TASK and extended error checking (OS_EXTENTED)   */
#if !defined(NO_TASK) && defined(OS_EXTENDED)
#   define CHECK_RUNNING_OWNS_REZ_ERROR(result)       \
    if (result == E_OK && tpl_running_obj->resources != NULL) {   \
        result = E_OS_RESOURCE;                 \
    }
#endif

/*-----------------------------------------------------------------------------
 * CHECK_ALARM_ID_ERROR macro definition
 * This macro defines the appropriate error program
 * for out of range alarm_id. It is used in os services
 * that use task_id as parameter.
 */

/* No extended error checking (! OS_EXTENDED)  */
#if !defined(OS_EXTENDED)
    /* Does not check the task_id in this case */
#   define CHECK_ALARM_ID_ERROR(alarm_id,result)
#endif

/* NO_ALARM and extended error checking (OS_EXTENDED)        */
#if defined(NO_ALARM) && defined(OS_EXTENDED)
    /* E_OS_ID is returned in this case  */
#   define CHECK_ALARM_ID_ERROR(alarm_id,result) \
    if (result == E_OK) {                      \
        result = E_OS_ID;                      \
    }
#endif

/* !NO_ALARM and extended error checking (OS_EXTENDED)   */
#if !defined(NO_ALARM) && defined(OS_EXTENDED)
    /* E_OK or E_OS_LIMIT   */
#   define CHECK_ALARM_ID_ERROR(alarm_id,result)      \
    if (result == E_OK && alarm_id >= ALARM_COUNT) {  \
        result = E_OS_ID;                           \
    }
#endif

/*-----------------------------------------------------------------------------
 * CHECK_RESOURCE_ID_ERROR macro definition
 * This macro defines the appropriate error program
 * for out of range res_id. It is used in os services
 * that use res_id as parameter.
 */

/* No extended error checking (! OS_EXTENDED)  */
#if !defined(OS_EXTENDED)
    /* Does not check the task_id in this case */
#   define CHECK_RESOURCE_ID_ERROR(res_id,result)
#endif

/* NO_TASK and extended error checking (OS_EXTENDED)        */
#if defined(NO_RESOURCE) && defined(OS_EXTENDED)
    /* E_OS_ID is returned in this case  */
#   define CHECK_RESOURCE_ID_ERROR(res_id,result)   \
    if (result == E_OK && res_id != -1) {           \
        result = E_OS_ID;                           \
    }
#endif

/* !NO_TASK and extended error checking (OS_EXTENDED)   */
#if !defined(NO_RESOURCE) && defined(OS_EXTENDED)
    /* E_OK or E_OS_LIMIT   */
#   define CHECK_RESOURCE_ID_ERROR(res_id,result)                   \
    if (result == E_OK && (res_id >= RES_COUNT || res_id < -1)) {   \
        result = E_OS_ID;                                           \
    }
#endif

/*-----------------------------------------------------------------------------
 * CHECK_RESOURCE_PRIO_ERROR_ON_GET macro definition
 * This macro defines the appropriate error program
 * for a resource that has a lower priority than the task that
 * attempt to get it. It is used in GetResource.
 */

#ifdef OS_EXTENDED
#   define CHECK_RESOURCE_PRIO_ERROR_ON_GET(res,result)                                                 \
    if (result == E_OK &&                                                                               \
        (res->owner != NULL || tpl_running_obj->static_desc->base_priority > res->ceiling_priority)) {  \
        result = E_OS_ACCESS;                                                                           \
    }
#else
#   define CHECK_RESOURCE_PRIO_ERROR_ON_GET(res,result)
#endif

/*-----------------------------------------------------------------------------
 * CHECK_RESOURCE_PRIO_ERROR_ON_RELEASE macro definition
 * This macro defines the appropriate error program
 * for a resource that has a higher priority than the task that
 * attempt to release it. It is used in ReleaseResource.
 */

#ifdef OS_EXTENDED
#   define CHECK_RESOURCE_PRIO_ERROR_ON_RELEASE(res,result)                         \
    if (result == E_OK &&                                                           \
        tpl_running_obj->static_desc->base_priority > res->ceiling_priority) {      \
        result = E_OS_ACCESS;                                                       \
    }
#else
#   define CHECK_RESOURCE_PRIO_ERROR_ON_RELEASE(res,result)
#endif

/*-----------------------------------------------------------------------------
 * CHECK_RESOURCE_ORDER_ON_RELEASE macro definition
 * This macro defines the appropriate error program
 * for a resource that is not released in the correct order.
 * It is used in ReleaseResource.
 */

#ifdef OS_EXTENDED
#   define CHECK_RESOURCE_ORDER_ON_RELEASE(res,result)                                  \
    if (result == E_OK && (res->owner == NULL || tpl_running_obj->resources != res)) {  \
        result = E_OS_NOFUNC;                                                           \
    }
#else
#   define CHECK_RESOURCE_ORDER_ON_RELEASE(res,result)
#endif

#endif
