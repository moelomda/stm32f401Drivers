#include "Switch.h"
#include "SwitchCfg.h"

/**
 * @brief   Array of switch configurations.
 * @details This array contains the configurations for each switch defined in the
 *          `Switchcfg_t` enumeration. Each element in the array corresponds to a
 *          switch and its associated configuration. The array should have as many
 *          elements as there are switches defined in the `Switchcfg_t` enumeration.
 */
const Switchcfg_t Switches[_Switch_num] = {
[Switch_Led] =
{
 .Port = PORT_A,
 .Pin = GPIO_PIN_3,
 .PhysicalState = GPIO_PULL_UP,
},
[Switch_Buzzer] =
{
.Port = PORT_B,
.Pin = GPIO_PIN_10,
.PhysicalState = GPIO_PULL_DOWN,
}
};
