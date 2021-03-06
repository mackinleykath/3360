#ifndef MENU_H_
#define MENU_H_

extern uint32_t state;

//------------------------------------------------------
//    Print out the menus
//------------------------------------------------------


void print_arm_periph_menu(){
  char* message = "\n\rARM Peripheral Control\n\r  1. Control LED\n\r  2. Control ADC\n\r";
    UARTSend( (uint8_t*)message, strlen(message));
}

void print_led_ctrl_menu(){
  char* message = "\n\rLED Control Menu\n\r  1. Blink ON\n\r  2. Blink OFF\n\r  3. Set Frequency\n\r  4. Set Duty Cycle\n\r  5. Go Back\n\r";
  UARTSend((uint8_t*)message, strlen(message));
}

void print_led_freq_menu(){
  char* message = "\n\rLED Frequency Menu\n\r  1. Slow\n\r  2. Medium\n\r  3. Fast\n\r  4. Very Fast\n\r  5. Go Back\n\r";
  UARTSend((uint8_t*)message, strlen(message));
}

void print_led_duty_menu(){
  char* message = "\n\rLED Duty Cycle Menu\n\r  1. 10%\n\r  2. 25%\n\r  3. 50%\n\r  4. 75%\n\r  5. 90%\n\r  6. Go Back\n\r";
  UARTSend((uint8_t*)message, strlen(message));
}

void print_adc_ctrl_menu(){
  char* message = "\n\rADC Control Menu\n\r  1. ADC Reporting ON\n\r  2. ADC Reporting OFF\n\r  3. Set Reporting Frequency\n\r  4. Go Back\n\r";
  UARTSend((uint8_t*)message, strlen(message));
}

void print_adc_report_menu(){
  char* message = "\n\rADC Reporting Frequency Menu\n\r  1. Slow\n\r  2. Medium\n\r  3.  Fast\n\r  4. Very Fast\n\r  5. Go Back\n\r";
  UARTSend((uint8_t*)message, strlen(message));
}

void print_error(){
  char* errmessage = "\n\r\n\rNot a valid option\n\r\n\r";
  UARTSend((uint8_t*)errmessage, strlen(errmessage));
}

//------------------------------------------------------
//    Menu-Specific Functions
//------------------------------------------------------
// Main Control Menu
void arm_periph_menu(uint8_t input){
  switch(input){
    case '1':
      print_led_ctrl_menu();
      state = 1;
      break;
    case '2':
      // For later
      state = 4;
      break;
    default: 
      print_error();
      state = 0;
//      print_arm_periph_menu();
      break;
  }
}
// LED Control Menu
void led_ctrl_menu(uint8_t input){
  switch(input){
    case '1':
      //start led blink
      led_on();
      print_led_ctrl_menu();
      break;
    case '2':
      //stop led blink
      led_off();
      print_led_ctrl_menu();
      break;
    case '3':
      print_led_freq_menu();
      state = 2;
      break;
    case '4':
      print_led_duty_menu();
      state = 3;
      break;
    case '5':
      state = 0;
      print_arm_periph_menu();
/*    default:
      print_error();
      print_led_duty_menu();
      break;*/
  }
}
// LED Frequency Menu
void led_freq_menu(uint8_t input){
  switch(input){
    case '1':
      led_period = 1000;
      print_led_freq_menu();
      break;
    case '2':
      led_period = 500;
      print_led_freq_menu();
      break;
    case '3':
      led_period = 200;
      print_led_freq_menu();
      break;
    case '4':
      led_period = 100;
      print_led_freq_menu();
      break;
    case '5':
      print_led_ctrl_menu();
      state = 1;
      break;
    default:
      print_error();
      print_led_freq_menu();
      break;
  }
}
// LED Duty Cycle Menu
void led_duty_menu(uint8_t input){
  switch(input){
    case '1':
      led_duty = 10;
      print_led_duty_menu();
      break;
    case '2':
      led_duty = 25;
      print_led_duty_menu();
      break;
    case '3':
      led_duty = 50;
      print_led_duty_menu();
      break;
    case '4':
      led_duty = 75;
      print_led_duty_menu();
      break;
    case '5':
      led_duty = 90;
      print_led_duty_menu();
      break;
    case '6':
      print_led_ctrl_menu();
      state = 1;
      break;
    default:
      print_error();
      print_led_duty_menu();
      break;
  }
}

// ADC Control Menu
void adc_ctrl_menu(input){
  switch(input){
    case '1':
      print_adc_ctrl_menu();
      adc_en = 1;
      // enable ADC reporting
      break;
    case '2':
      print_adc_ctrl_menu();
      adc_en = 0;
      // disable ADC reporting
      break;
    case '3':
      // Set reporting frequency
      print_adc_report_menu();
      state = 5;
      break;
    case '4':
      print_arm_periph_menu();
      state = 1;
      break;
    default:
      print_error();
      print_adc_ctrl_menu();
      break;
  }
}

// ADC Reporting Menu
void adc_report_menu(input){
  switch(input){
    case '1':
      adc_period = 1000;
      print_adc_report_menu();
      break;
    case '2':
      adc_period = 800;
      print_adc_report_menu();
      break;
    case '3':
      adc_period = 400;
      print_adc_report_menu();
      break;
    case '4':
      adc_period = 300;
      print_adc_report_menu();
      break;
    case '5':
      print_adc_ctrl_menu();
      print_adc_report_menu();
      state = 4;
      break;
    default:
      print_error();
      print_adc_report_menu();
      break;
  }
}

//------------------------------------------------------
//    Main FSM
//------------------------------------------------------
void menuControl(char choice){
  //arm_periph_menu(choice);
  switch(state){
    case 0: // Main Control
      arm_periph_menu(choice);
      break;
    case 1: // LED Control
      led_ctrl_menu(choice);
      break;
    case 2: // LED Frequency
      led_freq_menu(choice);
      break;
    case 3: // LED Duty Cycle
      led_duty_menu(choice);
      break;
    case 4: // ADC Control
      adc_ctrl_menu(choice);
      break;
    case 5: // ADC Report
      adc_report_menu(choice);
      break;
  }
}
#endif
