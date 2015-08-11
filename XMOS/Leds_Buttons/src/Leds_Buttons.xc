#include <xs1.h>
#include <platform.h>
#include <gpio.h>

// GPIO port declarations
on tile[0] : in port explorer_buttons = XS1_PORT_4E;
on tile[0] : out port explorer_leds = XS1_PORT_4F;

// GPIO handler routine
void gpio_handler(client input_gpio_if button_1, client input_gpio_if button_2,
    client output_gpio_if led_green, client output_gpio_if rgb_led_blue,
    client output_gpio_if rgb_led_green, client output_gpio_if rgb_led_red)
{

    // LED state
    unsigned int green_led_state = 0;
    unsigned int rgb_led_state = 0;
    // Initial button event state, active low
    button_1.event_when_pins_eq(0);
    button_2.event_when_pins_eq(0);

    while (1) {
/*
 * This statement will pause until either of the events occur and then execute
 * the code within the relevant case. Although the select waits on several events,
 * only one of the events is handled by the statement when an event occurs.
 * Often when programming other microcontrollers your program will react to external
 * events via interrupts. A function will be registered against an interrupt that
 * occurs when a certain event happens (e.g. a timeout or an external I/O event).
 * This function provides an interrupt service routine (ISR) that handles the event.
 * Interrupts are not used to handle events in xC, the select construct provides
 * all that is needed. The equivalent of an ISR is a separate task that executes a
 * select. The advantages of the XMOS approach are:
 * Response time to events can be drastically improved (in conjunction with the multi-core xCORE architecture)
 * Reasoning about worst case execution time (WCET) is easier since code cannot
 * be interrupted during its execution.
 */
        select {
            // Triggered by events on button 1
            case button_1.event():
                if (button_1.input() == 0) {
                    green_led_state = ~green_led_state;
                    led_green.output(green_led_state);
                    // Set button event state to active high for debounce
                    button_1.event_when_pins_eq(1);
                } else {
                    // Debounce button
                    delay_milliseconds(50);
                    button_1.event_when_pins_eq(0);
                }
                break;
            // Triggered by events on button 2
            case button_2.event():
                if (button_2.input() == 0) {
                    rgb_led_red.output(0);
                    rgb_led_green.output(0);
                    rgb_led_blue.output(0);
                    rgb_led_state++;
                    rgb_led_state %= 8;
                switch (rgb_led_state) {
                    case 1:
                        rgb_led_red.output(1);
                        break;
                    case 2:
                        rgb_led_green.output(1);
                        break;
                    case 3:
                        rgb_led_blue.output(1);
                        break;
                    case 4:
                        rgb_led_red.output(1);
                        rgb_led_green.output(1);
                        break;
                    case 5:
                        rgb_led_red.output(1);
                        rgb_led_blue.output(1);
                        break;
                    case 6:
                        rgb_led_green.output(1);
                        rgb_led_blue.output(1);
                        break;
                    case 7:
                        rgb_led_red.output(1);
                        rgb_led_blue.output(1);
                        rgb_led_green.output(1);
                        break;
                }
                // Set button event state to active high for debounce
                button_2.event_when_pins_eq(1);
                } else {
                    // Debounce button
                    delay_milliseconds(50);
                    button_2.event_when_pins_eq(0);
                }
            break;
        }
    // end of event select
    }
}
// The main() function runs a single task which takes the gpio interfaces as parameters
int main() {
    input_gpio_if i_explorer_buttons[2];
    output_gpio_if i_explorer_leds[4];

    par {
        on tile[0] : input_gpio_with_events(i_explorer_buttons, 2, explorer_buttons, null);
        on tile[0] : output_gpio(i_explorer_leds, 4, explorer_leds, null);
        on tile[0] : gpio_handler(i_explorer_buttons[0], i_explorer_buttons[1],
            i_explorer_leds[0], i_explorer_leds[1],
            i_explorer_leds[2], i_explorer_leds[3]);
    }

    return 0;
}
