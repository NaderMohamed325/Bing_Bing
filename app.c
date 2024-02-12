#include "app.h"

// Global variables
Std_ReturnType ret = E_OK;

// Function prototypes
void Application_initialize(void);

typedef enum {
    Right = 0,
    Left,
} Ball_Direction_x;

typedef enum {
    Up = 0,
    Down
} Ball_Direction_y;

static Ball_Direction_x xDirection = Right;
static Ball_Direction_y yDirection = Up;

// Function prototypes
void Player_one_move(void);
void Player_two_move(void);
void start_message(void);
void ball_move(void);

uint8 player_one_row = 2;
uint8 player_two_row = 2;
uint8 ball_x = 10;
uint8 ball_y = 2;

interrupt_INTx_t Player1 = {
    .Edge = INTERRUPT_RISING_EDGE,
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .Source = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.pin = PIN0,
    .mcu_pin.port = PORTB_INDEX,
    .External_CallBack = Player_one_move,
};

interrupt_INTx_t Player2 = {
    .Edge = INTERRUPT_RISING_EDGE,
    .Priority = INTERRUPT_HIGH_PRIORITY,
    .Source = INTERRUPT_EXTERNAL_INT1,
    .mcu_pin.direction = GPIO_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.pin = PIN1,
    .mcu_pin.port = PORTB_INDEX,
    .External_CallBack = Player_two_move,
};

int main(void) {
    // Initialize the application
    Application_initialize();

    while (1) {
        ball_move();
    }

    return 0;
}

// Function to initialize the application
/**
 * @brief Initializes the application by setting up the necessary components.
 */
void Application_initialize(void) {
    ecu_layer_initialize();
    ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
    ret = lcd_4bit_send_char_data_pos(&lcd, player_one_row, 1, '|');
    ret = lcd_4bit_send_char_data_pos(&lcd, player_two_row, 20, '|');
    ret = lcd_4bit_send_char_data_pos(&lcd, ball_y, ball_x, 'o');
    ret = Seven_Segm_Display_Number(&seg2, player_two_row);
    ret = Seven_Segm_Display_Number(&seg1, player_one_row);
    ret = Interrupt_INTx_Init(&Player1);
    ret = Interrupt_INTx_Init(&Player2);
    start_message();
}

/**
 * @brief Moves the paddle of player one.
 * @param None
 * @return None
 */
void Player_one_move(void) {
    ret = lcd_4bit_send_char_data_pos(&lcd, player_one_row, 1, ' '); // Clear the old character

    if (player_one_row > 0 && player_one_row < 4) {
        player_one_row++;
    } else if (player_one_row == 4) {
        player_one_row = 1;
    }

    ret = Seven_Segm_Display_Number(&seg1, player_one_row);
    ret = lcd_4bit_send_char_data_pos(&lcd, player_one_row, 1, '|'); // Display the new character
}

/**
 * @brief Moves the paddle of player two.
 * @param None
 * @return None
 */
void Player_two_move(void) {
    ret = lcd_4bit_send_char_data_pos(&lcd, player_two_row, 20, ' '); // Clear the old character

    if (player_two_row > 0 && player_two_row < 4) {
        player_two_row++;
    } else if (player_two_row == 4) {
        player_two_row = 1;
    }

    ret = Seven_Segm_Display_Number(&seg2, player_two_row);
    ret = lcd_4bit_send_char_data_pos(&lcd, player_two_row, 20, '|'); // Display the new character
}

/**
 * @brief Displays the start message of the game.
 * @param None
 * @return None
 */
void start_message(void) {
    for (int i = 3; i > 0; i--) {
        char message[20];
        sprintf(message, "Game starts in %d", i);
        ret = lcd_4bit_send_string_pos(&lcd, 4, 4, (uint8*)message);
        __delay_ms(1000);
        ret = lcd_4bit_send_string_pos(&lcd, 4, 4, (uint8*)"                ");
    }

    ret = lcd_4bit_send_string_pos(&lcd, 4, 1, (uint8*)"         GO !     ");
    __delay_ms(500);
    ret = lcd_4bit_send_string_pos(&lcd, 4, 4, (uint8*)"                ");
}

/**
 * @brief Moves the ball and handles collisions.
 * @param None
 * @return None
 */
void ball_move(void) {
    // Clear the old ball position
    ret = lcd_4bit_send_char_data_pos(&lcd, ball_y, ball_x, ' ');

    if (ball_x == 10 && ball_y == 2) {
        // Randomly set xDirection to Left or Right
        xDirection = rand() % 2 == 0 ? Left : Right;
        // Randomly set yDirection to Up or Down
        yDirection = rand() % 2 == 0 ? Up : Down;
    }

    // Update x-coordinate
    if (xDirection == Right) {
        ball_x++;
        if (ball_x == 20 && player_two_row == ball_y) {
            xDirection = Left;
            ball_x = 19;
        } else if (ball_x == 20 && player_two_row != ball_y) {
            // Player One wins
            ret = lcd_4bit_send_command(&lcd, _LCD_RETURN_HOME);
            ret = lcd_4bit_send_string_pos(&lcd, 2, 4, "                    ");
            ret = lcd_4bit_send_string_pos(&lcd, 2, 4, "Player one won !");
            __delay_ms(2000);
            ret = lcd_4bit_send_command(&lcd, _LCD_RETURN_HOME);
            Reset();
        }
    } else {
        ball_x--;
        if (ball_x == 1 && player_one_row == ball_y) {
            xDirection = Right;
            ball_x = 2;
        } else if (ball_x == 1 && player_one_row != ball_y) {
            // Player Two wins
            ret = lcd_4bit_send_command(&lcd, _LCD_RETURN_HOME);
            ret = lcd_4bit_send_string_pos(&lcd, 2, 4, "                    ");
            ret = lcd_4bit_send_string_pos(&lcd, 2, 4, "Player two won !");
            __delay_ms(2000);
            ret = lcd_4bit_send_command(&lcd, _LCD_RETURN_HOME);
            Reset();
        }
    }

    // Update y-coordinate
    if (yDirection == Up) {
        ball_y++;
        if (ball_y == 4) {
            yDirection = Down;
        }
    } else {
        ball_y--;
        if (ball_y == 1) {
            yDirection = Up;
        }
    }

    // Display the new ball position
    ret = lcd_4bit_send_char_data_pos(&lcd, ball_y, ball_x, 'o');
    __delay_ms(300);
}
