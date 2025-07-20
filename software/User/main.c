#include "debug.h"
#include "ch32v00x.h"
#include "ch32v00x_gpio.h"
#include "ch32v00x_rcc.h"

// LED pin definitions (PC0-PC5)
#define LED_PORT GPIOC
#define LED0_PIN GPIO_Pin_0
#define LED1_PIN GPIO_Pin_1
#define LED2_PIN GPIO_Pin_2
#define LED3_PIN GPIO_Pin_3
#define LED4_PIN GPIO_Pin_4
#define LED5_PIN GPIO_Pin_5

// Button pin definition (PC6)
#define BUTTON_PORT GPIOC
#define BUTTON_PIN GPIO_Pin_6

// Dice patterns for LEDs (6 LEDs can represent dice faces 1-6)
// Alternative dice patterns (more dice-like representation)
const uint8_t dice_patterns[7] = {
    0b000000,  // 0 - Not used
    0b000100,  // 1 - Center LED (LED2)
    0b001001,  // 2 - LED0 and LED3
    0b001101,  // 3 - LED0, LED2, LED3
    0b011011,  // 4 - LED0, LED1, LED3, LED4
    0b011111,  // 5 - LED0, LED1, LED2, LED3, LED4
    0b111111   // 6 - All LEDs
};

// Global variables
volatile uint32_t delay_counter = 0;

// Function prototypes
void GPIO_Configuration(void);
void Display_Dice(uint8_t number);
void Clear_LEDs(void);
uint8_t Generate_Random_Dice(void);
void Simple_Delay_ms(uint32_t ms);
void Dice_Animation(void);

// GPIO Configuration
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    // Enable GPIOC clock
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOC, ENABLE);
    
    // Configure PC0-PC5 as output push-pull for LEDs (inverted logic)
    GPIO_InitStructure.GPIO_Pin = LED0_PIN | LED1_PIN | LED2_PIN | 
                                  LED3_PIN | LED4_PIN | LED5_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    
    // Configure PC6 as input with pull-up for button
    GPIO_InitStructure.GPIO_Pin = BUTTON_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(BUTTON_PORT, &GPIO_InitStructure);
    
    // Initialize all LEDs as OFF (HIGH for common cathode)
    Clear_LEDs();
}

// Clear all LEDs (turn OFF - set HIGH for common cathode)
void Clear_LEDs(void)
{
    GPIO_SetBits(LED_PORT, LED0_PIN | LED1_PIN | LED2_PIN | 
                 LED3_PIN | LED4_PIN | LED5_PIN);
}

// Display dice number on LEDs (inverted logic for common cathode)
void Display_Dice(uint8_t number)
{
    if (number < 1 || number > 6) return;
    
    Clear_LEDs(); // Turn all LEDs OFF (HIGH)
    
    uint8_t pattern = dice_patterns[number];
    
    // Turn ON LEDs by setting pins LOW
    if (pattern & 0x01) GPIO_ResetBits(LED_PORT, LED0_PIN);
    if (pattern & 0x02) GPIO_ResetBits(LED_PORT, LED1_PIN);
    if (pattern & 0x04) GPIO_ResetBits(LED_PORT, LED2_PIN);
    if (pattern & 0x08) GPIO_ResetBits(LED_PORT, LED3_PIN);
    if (pattern & 0x10) GPIO_ResetBits(LED_PORT, LED4_PIN);
    if (pattern & 0x20) GPIO_ResetBits(LED_PORT, LED5_PIN);
}

// Simple delay function (blocking)
void Simple_Delay_ms(uint32_t ms)
{
    // Rough delay for 24MHz clock
    for (uint32_t i = 0; i < ms; i++) {
        for (volatile uint32_t j = 0; j < 6000; j++) {
            delay_counter++; // Add randomness to the counter
        }
    }
}

// Generate random dice number (1-6)
uint8_t Generate_Random_Dice(void)
{
    // Simple pseudo-random using delay counter
    static uint32_t seed = 0xACE1;
    
    // Mix in the delay counter for randomness
    seed ^= delay_counter;
    seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
    
    return (seed % 6) + 1;
}

// Dice rolling animation
void Dice_Animation(void)
{
    const uint8_t animation_cycles = 15;
    const uint32_t animation_delay = 80; // ms between changes
    
    for (uint8_t i = 0; i < animation_cycles; i++) {
        uint8_t random_num = Generate_Random_Dice();
        Display_Dice(random_num);
        Simple_Delay_ms(animation_delay);
    }
}

// Main function
int main(void)
{
    SystemCoreClockUpdate();
    
    // Initialize USART for debugging (optional)
    USART_Printf_Init(115200);
    printf("CH32V006 Dice Application Started (24MHz HSI)\r\n");
    
    // Configure GPIO
    GPIO_Configuration();
    
    // LED test sequence to verify all LEDs work
    printf("Testing all LEDs...\r\n");
    for (uint8_t i = 1; i <= 6; i++) {
        printf("Testing dice face: %d\r\n", i);
        Display_Dice(i);
        Simple_Delay_ms(500);
    }
    
    // Initial display - show "1"
    Display_Dice(1);
    
    printf("Press button on PC6 to roll the dice!\r\n");
    printf("Button: PC6 → Button → GND (with pull-up)\r\n");
    
    uint8_t last_button_state = 1;  // Button not pressed initially
    
    while(1)
    {
        // Read button state directly
        uint8_t button_state = GPIO_ReadInputDataBit(BUTTON_PORT, BUTTON_PIN);
        
        // Detect button press (transition from HIGH to LOW)
        if (last_button_state == 1 && button_state == 0) {
            printf("Button pressed! Rolling dice...\r\n");
            
            // Simple debounce delay
            Simple_Delay_ms(50);
            
            // Play dice animation
            Dice_Animation();
            
            // Generate final random number
            uint8_t dice_result = Generate_Random_Dice();
            
            // Display result
            Display_Dice(dice_result);
            
            printf("Dice result: %d\r\n", dice_result);
            
            // Wait for button release to prevent multiple triggers
            while (GPIO_ReadInputDataBit(BUTTON_PORT, BUTTON_PIN) == 0) {
                Simple_Delay_ms(10);
            }
            
            // Additional delay after release
            Simple_Delay_ms(200);
        }
        
        last_button_state = button_state;
        
        // Small delay in main loop to add randomness
        Simple_Delay_ms(1);
    }
}