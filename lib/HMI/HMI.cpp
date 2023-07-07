#include "HMI.h"

/**Initialize the main program
 * Inicializa el programa principal
*/
HMI::HMI()
{
    
}

/**This function initializes the executionSpecifications structure with default values
 * Esta función inicializa la estructura executionSpecifications con valores por defecto
*/
void HMI::initialize_processes_specifications_struct()
{
    // Initialize the array of selected places as false for all places
    // Inicizaliza el arreglo de plazas seleccionadas como falso
    for (uint8_t i = 0; i < NUMBER_OF_PLACES; ++i) {
        processesSpecifications.selectedPlaces[i] = false;
    }

    // Initialize the temperature setpoints and stirring setpoints
    // Inicializa los setpoints de temeperatura y agitación en 0
    for (uint8_t i = 0; i < NUMBER_OF_PROCESS; ++i) {
        processesSpecifications.temperatureSetpoints[i].initialTemperature = 0;
        processesSpecifications.temperatureSetpoints[i].finalTemperature = 0;
        processesSpecifications.temperatureSetpoints[i].tempFunction = TemperatureFunctionType::constant;
        processesSpecifications.stirringSetpoints[i] = 0;
        processesSpecifications.processDuration[i] = 0;
    }

    // Set the configured task to zero
    // Asigna cero a las tareas configuradas
    processesSpecifications.configuredTask = 0;
}

/**This is the main loop program in the project
 * Este es el bucle principal del proyecto 
*/
void HMI::HMI_main_loop()
{
    gui.show_UAM_logo();
    while(true)
    {
       main_menu();
    }
}

/**It executes the main menu of the HMI
 * Ejecuta el menú principal del HMI
*/
void HMI::main_menu()
{
    uint8_t option = 1;
    char keyPressed = NO_KEY;
    bool continue_menu = true;
    std::vector<char> validKeys = {'A', 'C', 'D'};
     std::vector<char> invalidKeys =  {'1','2','3','4','5','6','B','7','8','9','*','0','#'};
    // Display the background elements of the main menu
    gui.show_main_menu_background_elements();

    while (continue_menu) {
        // Highlight the current option in the main menu
        gui.highlight_current_option_in_main_menu(option);

        // Wait for a key press
        keyPressed = keyboard.get_valid_key(validKeys);
        Serial.println(keyPressed);
        switch(keyPressed)
        {
            case 'A':
                if (option == 1) {
                    // Go to menu: configure_execution_specifications();
                    // Ir al menu: configure_execution_specifications();
                    define_execution_specifications();
                    continue_menu = false;
                } else if (option == 2) {
                    // Go to menu: monitor_stirring_and_temperature();
                    // Ir al menu: monitor_stirring_and_temperature();
                    //monitor_stirring_and_temperature();
                    continue_menu = false;
                } else if (option == 3) {
                    // Go to menu: communication settings();
                    // Ir al menu: communication settings();
                    // communication settings();
                    continue_menu = false;
                }
                break;

            case 'C':
                --option;
                break;
            
            case 'D':
                ++option;
                break;
        }

        // Handle option boundaries
        // Manejar límites de opciones
        if (option > 3) {
            option = 1;
        } else if (option < 1) {
            option = 3;
        }
    }
}

/**This function implements the menus to define the execution specifications
 * Esta función implementa los menús para definir las especificaciones de ejecución
*/
void HMI::define_execution_specifications()
{
    initialize_processes_specifications_struct();
    uint8_t currentMenu = 0;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    while(menuOption != MenuNavigationOptions::Exit)
    {
         switch(currentMenu)
        {
            case 0:
                menuOption = select_places();
                if(menuOption == MenuNavigationOptions::Forward) {
                    currentMenu= 1;
                } else {
                    menuOption = MenuNavigationOptions::Exit;
                }
            break;

            case 1:
                menuOption = set_up_processes();
                if(menuOption == MenuNavigationOptions::Forward) {
                    currentMenu = 2;
                } else if(menuOption == MenuNavigationOptions::Backward) {
                    currentMenu = 0;
                }
            break;

            case 2:
                menuOption = summarize_the_defined_execution_specifications();
                if(menuOption == MenuNavigationOptions::Backward) {
                    currentMenu = 1;
                } else {
                    menuOption = MenuNavigationOptions::Exit;
                }
            break;
        }

    }
}

/**Implement the menu for selecting the places where the specifications will be executed
 * Returns MenuNavigationOptions::Forward to continue to the next menu. MenuNavigationOptions::Backward to backward.
 * Implementa el menú para seleccionar las plazas en donde se ejecutarán las especificaciones
 * Devuelve MenuNavigationOptions::Forward para continuar con el siguiente menú. MenuNavigationOptions::Backward para retroceder.
*/
MenuNavigationOptions HMI::select_places()
{
    uint8_t currentPlace = 0;
    char keyPressed = NO_KEY;
    std::vector<char> validKeys = {'A', 'B', 'C', 'D'};
    gui.show_select_places_menu_background_elements(processesSpecifications.selectedPlaces, NUMBER_OF_PLACES);
    while (true)
    {
        gui.highlight_current_place_in_select_places_menu(processesSpecifications.selectedPlaces, currentPlace, NUMBER_OF_PLACES);
        keyPressed = keyboard.get_valid_key(validKeys);

        switch (keyPressed)
        {
            case 'A':
                if(processesSpecifications.selectedPlaces[currentPlace]) {
                    processesSpecifications.selectedPlaces[currentPlace] = false;
                } else {
                   processesSpecifications.selectedPlaces[currentPlace] = true;
                }
            break;
            
            case 'B' :
                return MenuNavigationOptions::Exit;
            break;

            case 'C':
                if(validate_selected_places_array()) {
                    return MenuNavigationOptions::Forward;
                }
                break;
            case 'D':
                ++currentPlace;
                if(currentPlace >= NUMBER_OF_PLACES) {
                    currentPlace = 0;
                }
            break;
        }
    }
}

bool HMI::validate_selected_places_array()
{
    bool validArray = false;
    for(uint8_t currentPlace = 0; currentPlace < NUMBER_OF_PLACES; ++currentPlace)
    {
        if(processesSpecifications.selectedPlaces[currentPlace]) {
            validArray = true;
            break;
        }
    }
    return validArray;
}


MenuNavigationOptions HMI::set_up_processes()
{
    uint8_t currentProcess = 0;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    while (true)
    {
        menuOption = set_up_setpoints_and_times(currentProcess);

        switch (menuOption)
        {
            case MenuNavigationOptions::Forward:
                ++currentProcess;
                if(currentProcess > 20) {
                    return MenuNavigationOptions::Forward;
                }
            break;

            case MenuNavigationOptions::Backward:
                if(currentProcess <= 0) {
                    return MenuNavigationOptions::Backward;
                } else {
                    --currentProcess;
                }  
            break;

            case MenuNavigationOptions::Exit:
                return MenuNavigationOptions::Forward;
            break;
        }
    }
}

MenuNavigationOptions HMI::set_up_setpoints_and_times(const uint8_t &currentProcess)
{
    uint8_t option = 1;
    char keyPressed = NO_KEY;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> validKeys = {'A', 'B', 'C', 'D'};
    gui.show_set_up_setpoints_and_times_menu_background_elements(processesSpecifications.selectedPlaces, NUMBER_OF_PLACES, currentProcess);
    while(menuOption != MenuNavigationOptions::Exit)
    {
        update_specifications_current_process(currentProcess);
        gui.show_current_option_set_up_setpoints_and_times_menu(option);
        keyPressed = keyboard.get_valid_key(validKeys);
        switch (keyPressed)
        {
            case 'A':
                switch (option)
                {
                    case 1:
                        set_up_temperatura_function_type(currentProcess);
                    break;

                    case 2:
                        set_up_temperature_setpoints(currentProcess);
                    break;

                    case 3:
                        set_up_stirring_setpoints(currentProcess);
                    break;

                    case 4:
                        set_up_process_duration(currentProcess);
                    break;
                }
            break;

            case 'B':
                return MenuNavigationOptions::Backward;
            break;

            case 'C':
                if(verify_specifications_current_process(currentProcess)) {
                    
                }
            break;

            case 'D':
                ++option;
                if(option > 4) {
                    option = 1;
                }
               
            break;
        }
    }
}

void HMI::update_specifications_current_process(const uint8_t &currentProcess)
{
    if(processesSpecifications.temperatureSetpoints[currentProcess].tempFunction == constant) {
        gui.update_function_temperature_type_current_process(true);
    } else {
        gui.update_function_temperature_type_current_process(false);
    }

    gui.update_temperatures_setpoints_current_process(processesSpecifications.temperatureSetpoints[currentProcess].initialTemperature,
                                                        processesSpecifications.temperatureSetpoints[currentProcess].finalTemperature);

    gui.update_stirring_setpoints_current_process(processesSpecifications.stirringSetpoints[currentProcess]);
    gui.update_duration_current_process(processesSpecifications.processDuration[currentProcess]);
}

void HMI::set_up_temperatura_function_type(const uint8_t &currentProcess)
{
    uint8_t option = 1;
    char keyPressed = NO_KEY;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> validKeys = {'A', 'D'};
    gui.show_set_up_temperature_function_type_menu_background_elements();
    while (menuOption != MenuNavigationOptions::Exit) 
    {
        gui.show_current_option_set_up_temperature_function_type_menu(option);
        keyPressed = keyboard.get_valid_key(validKeys);
        switch (keyPressed)
        {
            case 'A':
                if(option == 1) {
                    processesSpecifications.temperatureSetpoints[currentProcess].tempFunction = TemperatureFunctionType::constant;
                } else {
                    processesSpecifications.temperatureSetpoints[currentProcess].tempFunction  = TemperatureFunctionType::ramp;
                }
                menuOption = MenuNavigationOptions::Exit;
            break;
        
            case 'D':
                ++option;
                if(option > 2) {
                    option = 1;
                }
            break;
        }
    }
    gui.clean_set_up_setpoints_and_times_menu_space();
}
void HMI::set_up_temperature_setpoints(const uint8_t &currentProcess)
{
    if(processesSpecifications.temperatureSetpoints[currentProcess].tempFunction == constant) {
        set_up_constant_temperature(currentProcess);
    } else {
        set_up_ramp_temperature(currentProcess);
    }
    gui.clean_set_up_setpoints_and_times_menu_space();
}

void HMI::set_up_constant_temperature(const uint8_t &currentProcess)
{
    String temperatureSetpoint = "0";
    char keyPressed = NO_KEY;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> invalidKeys = {'*', '#', 'C', 'D'};
    gui.show_set_up_constant_temperature_menu_background_elements();

    while (menuOption != MenuNavigationOptions::Exit) 
    {
        gui.show_temp_value_set_up_constant_temperature_menu(temperatureSetpoint);
        keyPressed = keyboard.ignore_invalid_keys(invalidKeys);
        Serial.println(keyPressed);
        if(isdigit(keyPressed)) {
            temperatureSetpoint = process_value_string(temperatureSetpoint, keyPressed, MAX_TEMPERATURE_DIGIT);
        } else {
            switch (keyPressed)
            {
                case 'A':
                    if(temperatureSetpoint.toInt() <= MAX_TEMPERATURE) {
                        processesSpecifications.temperatureSetpoints[currentProcess].initialTemperature = (uint16_t)(temperatureSetpoint.toInt());
                        processesSpecifications.temperatureSetpoints[currentProcess].finalTemperature = (uint16_t)(temperatureSetpoint.toInt());
                        menuOption = MenuNavigationOptions::Exit;
                    }
                break;
            
                case 'B':
                    temperatureSetpoint = "0";
                break;
            }
        }
       
    }
}

void HMI::set_up_ramp_temperature(const uint8_t &currentProcess)
{
    String initialTemperature = "0", finalTemperature = "0";
    char keyPressed = NO_KEY;
    uint8_t option = 1;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> invalidKeys = {'*', '#', 'C'};
    gui.show_set_up_ramp_temperature_menu_background_elements();
    while (menuOption != MenuNavigationOptions::Exit) 
    {
        gui.show_current_option_set_up_ramp_temperature_menu(option);
        gui.show_rmp_value_set_up_ramp_temperature_menu(initialTemperature, finalTemperature);
        keyPressed = keyboard.ignore_invalid_keys(invalidKeys);
        Serial.println(keyPressed);
        if(isdigit(keyPressed)) {
            if(option == 1) {
                initialTemperature = process_value_string(initialTemperature, keyPressed, MAX_TEMPERATURE_DIGIT);
            } else {
                finalTemperature =  process_value_string(finalTemperature, keyPressed, MAX_TEMPERATURE_DIGIT);
            }
        } else {
            switch (keyPressed)
            {
                case 'A':
                    if(initialTemperature.toInt() <= MAX_TEMPERATURE && finalTemperature.toInt() <= MAX_TEMPERATURE && finalTemperature.toInt() > initialTemperature.toInt()) {
                        processesSpecifications.temperatureSetpoints[currentProcess].initialTemperature = (uint16_t)(initialTemperature.toInt());
                        processesSpecifications.temperatureSetpoints[currentProcess].finalTemperature = (uint16_t)(finalTemperature.toInt());
                        menuOption = MenuNavigationOptions::Exit;
                    }
                break;
            
                case 'B':
                    if(option == 1) {
                        initialTemperature = "0";
                    } else {
                        finalTemperature = "0";
                    }
                break;

                case 'D':
                    option++;
                    if(option > 2) {
                        option = 1;
                    }
                break;
            }
        }
    }

}

void HMI::set_up_stirring_setpoints(const uint8_t &currentProcess)
{
    String stirringSetpoint = "0";
    char keyPressed = NO_KEY;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> invalidKeys = {'*', '#', 'C', 'D'};
    gui.show_set_up_stirring_setpoints_menu_background_elements();

    while (menuOption != MenuNavigationOptions::Exit) 
    {
        gui.show_rmp_value_set_up_stirring_setpoints_menu(stirringSetpoint);
        keyPressed = keyboard.ignore_invalid_keys(invalidKeys);
        Serial.println(keyPressed);
        if(isdigit(keyPressed)) {
            stirringSetpoint = process_value_string(stirringSetpoint, keyPressed, MAX_RPM_DIGITS);
        } else {
            switch (keyPressed)
            {
                case 'A':
                    if(stirringSetpoint.toInt() <= MAX_RPM) {
                        processesSpecifications.stirringSetpoints[currentProcess] = (uint16_t)(stirringSetpoint.toInt());
                        menuOption = MenuNavigationOptions::Exit;
                    }
                break;
            
                case 'B':
                    stirringSetpoint = "0";
                break;
            }
        }
       
    }
    gui.clean_set_up_setpoints_and_times_menu_space();
}


void HMI::set_up_process_duration(const uint8_t &currentProcess)
{
    String time = "0";
    char keyPressed = NO_KEY;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> invalidKeys = {'*', '#', 'C', 'D'};
    gui.show_set_up_process_duration_menu_background_elements();
    while (menuOption != MenuNavigationOptions::Exit) 
    {
        gui.show_duration_value_set_up_process_duration_menu(time);
        keyPressed = keyboard.ignore_invalid_keys(invalidKeys);
        Serial.println(keyPressed);
        if(isdigit(keyPressed)) {
           time = process_value_string(time, keyPressed, MAX_TIME_DIGITS);
        } else {
            switch (keyPressed)
            {
                case 'A':
                    if(time.toInt() <= MAX_TIME) {
                        processesSpecifications.processDuration[currentProcess] = (uint16_t)(time.toInt());
                        menuOption = MenuNavigationOptions::Exit;
                    }
                break;
            
                case 'B':
                    time = "0";
                break;
            }
        }
       
    }
    gui.clean_set_up_setpoints_and_times_menu_space();
}

String HMI::process_value_string(const String &value, const char keyPressed, const uint16_t maxValue)
{
    String valueToReturn = value;
    if(value == "0" || (value + keyPressed).toInt() > maxValue) {
        valueToReturn = keyPressed;
        } else {
        valueToReturn += keyPressed;
    }
    return valueToReturn;
}

bool HMI::verify_specifications_current_process(const uint8_t &currentProcess)
{
    bool stirringAndTempVerified = true, durationVerified = true;
    if(processesSpecifications.stirringSetpoints[currentProcess] == 0 && processesSpecifications.temperatureSetpoints[currentProcess].initialTemperature == 0) {
        stirringAndTempVerified = false;
    }

    if(processesSpecifications.processDuration[currentProcess] == 0) {
        durationVerified = false;
    }

    if(!(stirringAndTempVerified && durationVerified)) {
        error_in_specifications_current_process(stirringAndTempVerified, durationVerified);
    }

    return stirringAndTempVerified && durationVerified;
}

void HMI::error_in_specifications_current_process(const bool &stirringAndTemp, const bool &duration)
{
    char keyPressed = NO_KEY;
    std::vector<char> validKey = {'A'};
    gui.show_the_error_in_specifications_current_process(stirringAndTemp, duration);
    keyboard.get_valid_key(validKey);
    gui.clean_set_up_setpoints_and_times_menu_space();
}

bool HMI::add_or_summarize_processes()
{
    return false;
}

MenuNavigationOptions HMI::summarize_the_defined_execution_specifications()
{
return MenuNavigationOptions();
}
