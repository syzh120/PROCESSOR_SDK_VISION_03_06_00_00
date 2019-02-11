/*
 *  Copyright (C) 2013 - 2017 Texas Instruments Incorporated - http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_GPIO GPIO
 *
 *  @{
 */
 /**
 * \file   gpio_v2.h
 *
 * \brief  GPIO Device Abstraction Layer APIs
 *
 *         This file contains the prototypes of the APIs present in the
 *         device abstraction layer file of GPIO.
 *         This also contains some related macros.
 *
 * \details  The detailed description of gpio is:
 *            -# Each GPIO module provides 32 dedicated general-purpose pins
 *               with input and output capabilities.These pins can be configured
 *               for the following applications:
 *                -# Data input (capture)/output (drive)
 *                -# Keyboard interface with a debounce cell
 *                -# Interrupt generation in active mode upon the detection of
 *                   external events. Detected events are processed by two
 *                   parallel independent interrupt-generation sub modules
 *                   to support bi processor operations.
 *            -# Programming sequence of gpio module is:
 *               -# Enable the functional clocks for the required GPIO instance.
 *               -# Perform a pin multiplexing for the required GPIO pin.
 *               -# Enable the GPIO module using the API #GPIOModuleEnable.
 *               -# Perform a module reset of the GPIO module using the API
 *                  #GPIOModuleReset.
 *               -# When GPIO is input pin, following configuration is used
 *                  -# Enable/disable debouncing feature for the specified input GPIO
 *                     pin if required, using the API #GPIODebounceFuncControl.
 *                  -# Program the debouncing time, if required using the API
 *                     #GPIODebounceTimeConfig.
 *                  -# Interrupt trigger conditions need to be configured using
 *                     the API #GPIOIntTypeSet.
 *                  -# Enable GPIO to generate interrupts on detection of the
 *                     specified transitions on the decided GPIO pin using the
 *                     API #GPIOPinIntEnable.
 *               -# When GPIO is output pin, following configuration is used
 *                  -# A logic HIGH or a logic LOW could be driven on the
 *                     specified GPIO pin by invoking the API #GPIOPinWrite.
 *            -# Note: If GPIO peripheral interrupts will be used, then the
 *               system interrupt settings need to be performed prior to
 *               enabling the GPIO peripheral interrupts.
 **/

#ifndef  GPIO_V2_H_
#define  GPIO_V2_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_gpio.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/*
** \name Values used to configure the direction of GPIO pins.
* @{
*/
#define GPIO_DIR_INPUT                   (uint32_t) (0x1U)
#define GPIO_DIR_OUTPUT                  (uint32_t) (0x0U)
/* @} */

/*
** \name Values helping to decide the value on a GPIO pin.
* @{
*/
#define GPIO_PIN_LOW                     (uint32_t) (0x0U)
#define GPIO_PIN_HIGH                    (uint32_t) (0x1U)
/* @} */

/*
** \name Values denoting the Interrupt Line number to be used.
* @{
*/
#define GPIO_INT_LINE_1                  (uint32_t) (0x0U)
#define GPIO_INT_LINE_2                  (uint32_t) (0x1U)
/* @} */

/*
** \name Values used to enable/disable interrupt generation due to level
** detection on an input GPIO pin.
* @{
*/
#define GPIO_INT_TYPE_NO_LEVEL           (uint32_t) (0x01U)
#define GPIO_INT_TYPE_LEVEL_LOW          (uint32_t) (0x04U)
#define GPIO_INT_TYPE_LEVEL_HIGH         (uint32_t) (0x08U)
#define GPIO_INT_TYPE_BOTH_LEVEL         (uint32_t) (0x0CU)
/* @} */

/*
** \name Values used to enable/disable interrupt generation due to edge
** detection on an input GPIO pin.
* @{
*/
#define GPIO_INT_TYPE_NO_EDGE            (uint32_t) (0x80U)
#define GPIO_INT_TYPE_RISE_EDGE          (uint32_t) (0x10U)
#define GPIO_INT_TYPE_FALL_EDGE          (uint32_t) (0x20U)
#define GPIO_INT_TYPE_BOTH_EDGE          (uint32_t) (0x30U)
/* @} */

/*
** \name Values used for Idle Mode configurations.
* @{
*/
#define GPIO_IDLE_MODE_FORCE_IDLE        (uint32_t) (0x0U)
#define GPIO_IDLE_MODE_NO_IDLE           (uint32_t) (0x1U)
#define GPIO_IDLE_MODE_SMART_IDLE        (uint32_t) (0x2U)
#define GPIO_IDLE_MODE_SMART_IDLE_WAKEUP (uint32_t) (0x3U)
/* @} */

/*
** \name Values used to enable/disable Auto-Idle mode.
* @{
*/
#define GPIO_AUTO_IDLE_MODE_ENABLE       (uint32_t) (0x1U)
#define GPIO_AUTO_IDLE_MODE_DISABLE      (uint32_t) (0x0U)
/* @} */

/*
** \name Values used to configure the Gating Ratio.
* @{
*/
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_1  (uint32_t) (0x0U)
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_2  (uint32_t) (0x1U)
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_4  (uint32_t) (0x2U)
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_8  (uint32_t) (0x3U)
/* @} */

/*
** \name Values used to enable/disable Debouncing feature for an input pin.
* @{
*/
#define GPIO_DEBOUNCE_FUNC_ENABLE        (0x1U)
#define GPIO_DEBOUNCE_FUNC_DISABLE       (0x0U)
/* @} */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief This API performs the module reset of the GPIO module. It also
 * waits until the reset process is complete.
 *
 * \param  baseAdd   GPIO base address
 *
 * \return None
 */
void GPIOModuleReset(uint32_t baseAdd);

/**
 * \brief This API is used to enable the GPIO module. When the GPIO module
 *         is enabled, the clocks to the module are not gated.
 *
 * \param  baseAdd   GPIO base address
 *
 * \return None
 *
 * \note   Enabling the GPIO module is a primary step before any other
 *         configurations can be done.
 */
void GPIOModuleEnable(uint32_t baseAdd);

/**
 * \brief This API is used to disable the GPIO module. When the GPIO module
 *         is disabled, the clocks to the module are gated.
 *
 * \param  baseAdd   GPIO base address
 *
 * \return None
 */
void GPIOModuleDisable(uint32_t baseAdd);

/**
 * \brief This API configures the direction of a specified GPIO pin as being
 *         either input or output.
 *
 * \param  baseAdd   GPIO base address
 * \param  pinNumber     The number of the pin in the GPIO instance
 * \param  pinDirection  The required direction for the GPIO pin
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * 'pinDirection' can take one of the following values:
 * - GPIO_DIR_INPUT - to configure the pin as an input pin\n
 * - GPIO_DIR_OUTPUT - to configure the pin as an output pin\n
 *
 * \return None
 */
void GPIODirModeSet(uint32_t baseAdd,
                    uint32_t pinNumber,
                    uint32_t pinDirection);

/**
 * \brief This API determines the direction of a specified GPIO pin.
 *
 * \param  baseAdd   GPIO base address
 * \param   pinNumber    The number of the pin in the GPIO instance
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * \return  The direction of the specified pin. This returns one of the
 *          following two values:
 *          - GPIO_DIR_INPUT - signifying that the pin is an input pin\n
 *          - GPIO_DIR_OUTPUT - signifying that the pin is an output pin\n
 *
 */
uint32_t GPIODirModeGet(uint32_t baseAdd,
                        uint32_t pinNumber);

/**
 * \brief This API drives an output GPIO pin to a logic HIGH or a logic LOW
 *         state.
 *
 * \param  baseAdd   GPIO base address
 * \param  pinNumber   The number of the pin in the GPIO instance
 * \param  pinValue    This specifies whether a logic HIGH or a logic LOW
 *                     should be driven on the output pin
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * 'pinValue' can take one of the following values:
 * - GPIO_PIN_LOW - indicating to drive a logic LOW(logic 0) on the pin.
 * - GPIO_PIN_HIGH - indicating to drive a logic HIGH(logic 1) on the pin.
 *
 * \return None
 *
 */
void GPIOPinWrite(uint32_t baseAdd,
                  uint32_t pinNumber,
                  uint32_t pinValue);

/**
 * \brief This API determines the logic level(value) on a specified
 *          GPIO pin.
 *
 * \param  baseAdd   GPIO base address
 * \param   pinNumber   The number of the pin in the GPIO instance
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * \return  The pin value (0 or 1) << pinNumber of the specified pin of the GPIO instance.
 */
uint32_t GPIOPinRead(uint32_t baseAdd,
                     uint32_t pinNumber);

/**
 * \brief This API determines the logic level(value) on a specified
 *          GPIO pin.
 *
 * \param  baseAdd     GPIO base address
 * \param  pinNumber   The number of the pin in the GPIO instance
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * \return  The pin value (0 or 1) of the specified pin of the GPIO instance.
 */
uint32_t GPIOPinRead2(uint32_t baseAdd,
                      uint32_t pinNumber);
/**
 * \brief This API is used to collectively set and collectively clear the
 *         specified output pins of a GPIO instance.
 *
 * \param  baseAdd   GPIO base address
 * \param  setMask    The bit mask of the bits which have to be set in the
 *                    GPIO Data Output Register(GPIO_DATAOUT)
 * \param  clrMask    The bit mask of the bits which have to cleared in the
 *                    GPIO Data Output Register(GPIO_DATAOUT)
 *
 * \return None
 */
void GPIOMultiplePinsWrite(uint32_t baseAdd,
                           uint32_t setMask,
                           uint32_t clrMask);

/**
 * \brief This API reads the pin values of the specified pins of the GPIO
 *          instance.
 *
 * \param  baseAdd   GPIO base address
 * \param   readMask   The bit mask of the bits whose values have to be read
 *                     from the Data Input Register(GPIO_DATAIN).
 *
 * \return  The pin values of the specified pins of the GPIO instance.
 */
uint32_t GPIOMultiplePinsRead(uint32_t baseAdd,
                              uint32_t readMask);

/**
 * \brief This API enables the configured interrupt event on a specified input
 *         GPIO pin to trigger an interrupt request.
 *
 * \param  baseAdd   GPIO base address
 * \param  intLine     This specifies the interrupt request line on which the
 *                     interrupt request due to the transitions on a specified
 *                     pin be propagated
 * \param  pinNumber   The number of the pin in the GPIO instance
 *
 * 'intLine' can take one of the following two values:
 * - GPIO_INT_LINE_1 - interrupt request be propagated over interrupt line 1\n
 * - GPIO_INT_LINE_2 - interrupt request be propagated over interrupt line 2\n
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * \return None
 */
void GPIOPinIntEnable(uint32_t baseAdd,
                      uint32_t intLine,
                      uint32_t pinNumber);

/**
 * \brief This API disables interrupt generation due to the detection
 *         of any event on a specified input GPIO pin.
 *
 * \param  baseAdd   GPIO base address
 * \param  intLine    This specifies the interrupt requeset line which has to
 *                    disabled to transmit interrupt requests due to transitions
 *                    on a specified pin
 * \param  pinNumber  The number of the pin in the GPIO instance
 *
 * 'intLine' can take one of the following two values:
 * - GPIO_INT_LINE_1 - signifying that the Interrupt Line 1 be disabled to
 *   transmit interrupt requests due to transitions on specified pin\n
 * - GPIO_INT_LINE_2 - signifying that the Interrupt Line 2 be disabled to
 *   transmit interrupt requests due to transitions on specified pin\n
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * \return  None
 */
void GPIOPinIntDisable(uint32_t baseAdd,
                       uint32_t intLine,
                       uint32_t pinNumber);

/**
 * \brief This API configures the event type for a specified input GPIO pin
 *         so as to trigger an interrupt request. Whenever the selected event
 *         occurs on that GPIO pin, an interrupt request will be sent to the
 *         CPU.
 *
 * \param  baseAdd   GPIO base address
 * \param  pinNumber  The number of the pin in the GPIO instance
 * \param  eventType  This specifies the event type on occurence of which an
 *                    interrupt request is generated
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * 'eventType' can take one of the following values:
 * - GPIO_INT_TYPE_NO_LEVEL - no interrupt request on occurence of either a
 *   logic LOW or a logic HIGH on the input GPIO pin\n
 * - GPIO_INT_TYPE_LEVEL_0 - interrupt request on occurence of a LOW level
 *   (logic 0) on the input GPIO pin\n
 * - GPIO_INT_TYPE_LEVEL_1 - interrupt request on occurence of a HIGH level
 *   (logic 1) on the input GPIO pin\n
 * - GPIO_INT_TYPE_BOTH_LEVEL - interrupt request on the occurence of both the
 *   LOW level and HIGH level on the input GPIO pin\n
 * - GPIO_INT_TYPE_NO_EDGE -  no interrupt request on either rising or
 *   falling edges on the pin\n
 * - GPIO_INT_TYPE_RISE_EDGE - interrupt request on occurence of a rising edge
 *   on the input GPIO pin\n
 * - GPIO_INT_TYPE_FALL_EDGE - interrupt request on occurence of a falling edge
 *   on the input GPIO pin\n
 * - GPIO_INT_TYPE_BOTH_EDGE - interrupt request on occurence of both a rising
 *   and a falling edge on the pin\n
 *
 * \return  None
 *
 * \note  A typical use case of this API is explained below:
 *
 *        If it is initially required that interrupt should be generated on
 *        LOW level only, then this API can be called with GPIO_INT_TYPE_LEVEL_0
 *        as the parameter. At a later point of time, if logic HIGH level only
 *        should be made as the interrupt generating event, then this API has to
 *        be first called with GPIO_INT_TYPE_NO_LEVEL as the parameter and
 *        later with GPIO_INT_TYPE_LEVEL_1 as the parameter. Doing this
 *        ensures that logic LOW level trigger for interrupts is disabled.
 */
void GPIOIntTypeSet(uint32_t baseAdd,
                    uint32_t pinNumber,
                    uint32_t eventType);

/**
 * \brief This API determines the programmed event type for a specified input
 *         GPIO pin on occurence of which an interrupt request will be sent to
 *         the CPU.
 *
 * \param  baseAdd   GPIO base address
 * \param  pinNumber  The number of the pin in the GPIO instance
 *
 * \return This returns one or a combination of the following values:
 *
 * - GPIO_INT_TYPE_NO_LEVEL - level trigger for interrupt request is disabled\n
 * - GPIO_INT_TYPE_LEVEL_0 - logic LOW level event for interrupt request is
 *   enabled\n
 * - GPIO_INT_TYPE_LEVEL_1 - logic HIGH level event for interrupt request is
 *   enabled\n
 * - GPIO_INT_TYPE_BOTH_LEVEL - both logic LOW and logic HIGH level events
 *   for interrupt request are enabled\n
 * - GPIO_INT_TYPE_NO_EDGE - edge trigger for interrupt request is disabled\n
 * - GPIO_INT_TYPE_RISE_EDGE - rising edge event for interrupt request is
 *   enabled\n
 * - GPIO_INT_TYPE_FALL_EDGE - falling edge event for interrupt request
 *   is enabled\n
 * - GPIO_INT_TYPE_BOTH_EDGE - both rising and falling edge events for
 *   interrupt request are enabled\n
 */
uint32_t GPIOIntTypeGet(uint32_t baseAdd,
                        uint32_t pinNumber);

/**
 * \brief This API determines the enabled interrupt status of a specified pin.
 *
 * \param  baseAdd   GPIO base address
 * \param  intLine    This specifies the interrupt line whose corresponding
 *                    enabled interrupt status register has to be accessed.
 *                    The status of the specified pin is returned in this API.
 * \param  pinNumber  The number of the pin in the GPIO instance
 *
 * 'intLine' can take one of the following two values:
 * - GPIO_INT_LINE_1 - to read the enabled interrupt status register
 *   corresponding to interrupt line 1\n
 * - GPIO_INT_LINE_2 - to read the enabled interrupt status register
 *   corresponding to interrupt line 2\n
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * \return The enabled interrupt status of the pin on the specified interrupt
 *         line. This could either be a non-zero or a zero value.
 *
 */
uint32_t GPIOPinIntStatus(uint32_t baseAdd,
                          uint32_t intLine,
                          uint32_t pinNumber);

/**
 * \brief This API clears the enabled interrupt status of a specified GPIO
 *         pin.
 *
 * \param  baseAdd   GPIO base address
 * \param  intLine    This specifies the interrupt line whose corresponding
 *                    enabled interrupt status register has to be accessed.
 *                    The status of the specified bit in it is cleared in this
 *                    API.
 * \param  pinNumber  The number of the pin in the GPIO instance
 *
 * 'intLine' can take one of the following two values:
 * - GPIO_INT_LINE_1 - to access the enabled interrupt status register
 *   corresponding to interrupt line 1\n
 * - GPIO_INT_LINE_2 - to access the enabled interrupt status register
 *   corresponding to interrupt line 2\n
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * \return None
 */
void GPIOPinIntClear(uint32_t baseAdd,
                     uint32_t intLine,
                     uint32_t pinNumber);

/**
 * \brief This API determines the raw interrupt status of the specified GPIO
 *         pins in the instance corresponding to the specified interrupt line.
 *
 * \param  baseAdd   GPIO base address
 * \param  intLine    This specifies the interrupt line whose corresponding
 *                    raw interrupt status register has to be read.
 * \param  readMask   The bit mask of the bits whose values have to be read
 *                    from the Raw Interrupt Status Register
 *                    (GPIO_IRQSTATUS_RAW).
 *
 * 'intLine' can take one of the following two values:
 * - GPIO_INT_LINE_1 - to read the raw interrupt status register corresponding
 *   to interrupt line 1\n
 * - GPIO_INT_LINE_2 - to read the raw interrupt status register corresponding
 *   to interrupt line 2\n
 *
 * \return  The raw interrupt status of the specified pins of the GPIO instance
 *          corresponding to a specified interrupt line.
 */
uint32_t GPIORawIntStatus(uint32_t baseAdd,
                          uint32_t intLine,
                          uint32_t readMask);

/**
 * \brief This API manually triggers an interrupt request due to a specified
 *         GPIO pin.
 *
 * \param  baseAdd   GPIO base address
 * \param  intLine    This specifies the interrupt line over which the
 *                    manually triggered interrupt request has to be
 *                    propogated
 * \param  pinNumber  The number of the pin in the GPIO instance.
 *
 * 'intLine' can take one of the following values:
 * - GPIO_INT_LINE_1 - to propogate the interrupt request over interrupt
 *   line 1\n
 * - GPIO_INT_LINE_2 - to propogate the interrupt request over interrupt
 *   line 2\n
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * \return None
 *
 * \note  Here an interrupt request is manually triggered by writing to a
 *        specified bit in the Raw Interrupt Status register. As a
 *        pre-requisite, the interrupt generation should be enabled for the
 *        GPIO pin.
 */
void GPIOTriggerPinInt(uint32_t baseAdd,
                       uint32_t intLine,
                       uint32_t pinNumber);

/**
 * \brief  This API enables the GPIO Wakeup Generation feature for all
 *         the pins of the GPIO module.
 *
 * \param  baseAdd    The memory address of the GPIO instance being used.
 *
 * \return None
 *
 * \note   1> A Wakeup signal is generated by an Input GPIO pin when an
 *            expected transition happens on that GPIO pin.\n
 *         2> For any Input pin of the GPIO module to generate Wakeup
 *            signal, the respective global feature for the module has
 *            to be enabled by invoking this API.\n
 */

void GPIOWakeupGlobalEnable(uint32_t baseAdd);

/**
 * \brief  This API disables the GPIO Wakeup generation feature for all
 *         the pins of the GPIO module.
 *
 * \param  baseAdd    The memory address of the GPIO instance being used.
 *
 * \return None
 */

void GPIOWakeupGlobalDisable(uint32_t baseAdd);

/**
 * \brief  This API enables the feature for the specified Input GPIO Pin
 *         (Interrupt Request Source) to generate an asynchronous wakeup
 *         signal to the CPU.
 *
 * \param  baseAdd     The memory address of the GPIO instance being used.
 * \param  swakeupLine This specifies the Smart Wakeup Interrupt Line over
 *                     which the asynchrounous wakeup signal has to be
 *                     propogated due to the specified Input GPIO pin.
 * \param  pinNumber   The number of the pin in the GPIO instance.
 *
 * 'swakeupLine' can take one of the following values:
 * - GPIO_INT_SWAKEUP_LINE_1 - to propogate the wakeup request over Smart
 *   Wakeup Interrupt Line 1\n
 * - GPIO_INT_SWAKEUP_LINE_2 - to propagate the wakeup request over Smart
 *   Wakeup Interrupt Line 2\n
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * \return None
 *
 * \note  1> Make sure that the GPIO instance in context is allowed to generate
 *           Wakeup interrupts to the CPU. If allowed, then enable Wakeup
 *           interrupt generation feature for that GPIO instance in the
 *           Interrupt Controller.\n
 *        2> Usually an Input GPIO Pin acts as an Interrupt Request(IRQ) Source.
 *           An expected transition on an Input GPIO Pin can generate a Wakeup
 *           request.\n
 */

void GPIOPinIntWakeUpEnable(uint32_t baseAdd,
                            uint32_t swakeupLine,
                            uint32_t pinNumber);

/**
 * \brief  This API disables the feature for the specified Input GPIO Pin
 *         (Interrupt Request Source) to generate an asynchronous wakeup
 *         signal to the CPU.
 *
 * \param  baseAdd     The memory address of the GPIO instance being used.
 * \param  swakeupLine This specifies the Smart Wakeup Interupt Line which has
 *                     to be disabled to propogate any asynchrounous wakeup
 *                     signal due to the specified input GPIO Pin.
 * \param  pinNumber   The number of the pin in the GPIO instance.
 *
 * 'swakeupLine' can take one of the following values:
 * - GPIO_INT_SWAKEUP_LINE_1 - to propogate the wakeup request over Smart
 *   Wakeup Interrupt Line 1\n
 * - GPIO_INT_SWAKEUP_LINE_2 - to propagate the wakeup request over Smart
 *   Wakeup Interrupt Line 2\n
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * \return None
 */

void GPIOPinIntWakeUpDisable(uint32_t baseAdd,
                             uint32_t swakeupLine,
                             uint32_t pinNumber);

/**
 * \brief This API is used to control(enable/disable) the Auto-Idle mode
 *          for GPIO.
 *
 * \param  baseAdd   GPIO base address
 * \param  modeFlag   This specifies whether to enable or disable the
 *                    Auto-Idle mode for the GPIO instance
 *
 * 'modeFlag' can take one of the following two values:
 * - GPIO_AUTO_IDLE_MODE_ENABLE - to enable the Auto-Idle mode\n
 * - GPIO_AUTO_IDLE_MODE_DISABLE - to disable the Auto-Idle mode\n
 *
 * \return  None
 */
void GPIOAutoIdleModeControl(uint32_t baseAdd,
                             uint32_t modeFlag);

/**
 * \brief This API is used to configure the Power Management
 *         Request/Acknowledgement process for GPIO.
 *
 * \param  baseAdd   GPIO base address
 * \param  modeFlag   This specifies the Power Management Request/Acknowledge
 *                    mode(Idle Mode Request and Response) to be enabled for
 *                    the GPIO instance
 *
 * 'modeFlag' can take one of the following values:
 * - GPIO_IDLE_MODE_FORCE_IDLE - to enable Force-Idle mode\n
 * - GPIO_IDLE_MODE_NO_IDLE - to enable No-Idle mode\n
 * - GPIO_IDLE_MODE_SMART_IDLE - to enable Smart-Idle mode\n
 * - GPIO_IDLE_MODE_SMART_IDLE_WAKEUP - to enable Smart-Idle-Wakeup mode\n
 *
 * \return None
 */
void GPIOIdleModeConfigure(uint32_t baseAdd,
                           uint32_t modeFlag);

/**
 * \brief This API configures the clock gating ratio for the event detection
 *         logic.
 *
 * \param  baseAdd   GPIO base address
 * \param  configFlag This specifies the clock gating ratio value to be
 *                    programmed
 *
 * 'configFlag' can take one of the following values:
 *
 * - GPIO_GR_FUNC_CLK_INTER_CLK_BY_1 - to program the functional clock as
 * interface clock frequeny divided by 1\n
 * - GPIO_GR_FUNC_CLK_INTER_CLK_BY_2 - to program the functional clock as
 * interface clock frequency divided by 2\n
 * - GPIO_GR_FUNC_CLK_INTER_CLK_BY_4 - to program the functional clock as
 * interface clock frequency divided by 4\n
 * - GPIO_GR_FUNC_CLK_INTER_CLK_BY_8 - to program the functional clock as
 * interface clock frequency divided by 8\n
 *
 * \return None
 */
void GPIOGatingRatioConfigure(uint32_t baseAdd,
                              uint32_t configFlag);

/**
 * \brief This API enables/disables debouncing feature for a specified input
 *         GPIO pin.
 *
 * \param  baseAdd   GPIO base address
 * \param  pinNumber    The number of the pin in the GPIO instance
 * \param  controlFlag  This specifies whether to enable/disable Debouncing
 *                      feature for the specified input pin
 *
 * 'pinNumber' can take one of the following values:
 * (0 <= pinNumber <= 31)\n
 *
 * 'controlFlag' can take one of the following values:
 * - GPIO_DEBOUNCE_FUNC_ENABLE - to enable the debouncing feature for the
 *   specified input GPIO pin\n
 * - GPIO_DEBOUNCE_FUNC_DISABLE - to disable the debouncing feature for the
 *   specified input GPIO pin\n
 *
 * \return None
 */
void GPIODebounceFuncControl(uint32_t baseAdd,
                             uint32_t pinNumber,
                             uint32_t controlFlag);

/**
 * \brief This API configures the debouncing time for all the input pins of
 *         a GPIO instance.
 *
 * \param  baseAdd   GPIO base address
 * \param  debounceTime  This specifies the number of debouncing clock pulses
 *                       each of 31 microseconds int32_t to be used for
 *                       debouncing time. The formula for debouncing time is:
 *                       debounce time = ((debounceTime + 1)* 31) microseconds
 *
 * 'debounceTime' can take a value as per below limits:
 * - (0x00 <= debounceTime <= 0xFF)
 *
 * \return None
 */
void GPIODebounceTimeConfig(uint32_t baseAdd,
                            uint32_t debounceTime);

/**
 * \brief This API reads the contents in the Revision register of the GPIO
 *         module.
 *
 * \param  baseAdd   GPIO base address
 *
 * \return The contents of the GPIO_REVISION register.
 */
uint32_t GPIORevisionInfoGet(uint32_t baseAdd);

/**
 * \brief  This API clears the enabled interrupt status of a specified GPIO
 *         pin.
 *
 * \param  baseAddr   The memory address of the GPIO instance being used
 * \param  intrLine   This specifies the interrupt line whose corresponding
 *                    enabled interrupt status register has to be accessed.
 *                    The status of the specified bit in it is cleared in this
 *                    API.
 *         'intrLine' can take one of the following two values:
 *         -# 0 - Interrupt line 0
 *         -# 1 - Interrupt line 1
 * \param  pinMask  Mask of pins whose interrupts need to be cleared.
 */
void GPIOIntrClearMask(uint32_t baseAddr, uint32_t intrLine, uint32_t pinMask);

/**
 * \brief   This API reads the output logic level(value) on a specified
 *          GPIO pin.
 *
 * \param   baseAddr    The memory address of the GPIO instance being used
 * \param   pinNumber   The number of the pin in the GPIO instance
 *          'pinNumber' can take one of the following values:
 *          (0 <= pinNumber <= 31)
 *
 * \retval  GPIO_PIN_LOW  - indicating to drive a logic LOW(0) on the pin.
 * \retval  GPIO_PIN_HIGH - indicating to drive a logic HIGH(1) on the pin.
 */
uint32_t GPIOPinOutValueRead(uint32_t baseAddr, uint32_t pinNumber);

#ifdef __cplusplus
}
#endif

#endif
 /** @} */
/********************************* End Of File ******************************/
