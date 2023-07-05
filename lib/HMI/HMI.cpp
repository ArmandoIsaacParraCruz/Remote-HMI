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

    // Display the background elements of the main menu
    gui.show_main_menu_background_elements();

    while (continue_menu) {
        // Highlight the current option in the main menu
        gui.highlight_current_option_in_main_menu(option);

        // Wait for a key press
        keyPressed = keyboard.get_valid_key(validKeys);

        Serial.print("Key: ");
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
    while (currentPlace >= 0 && currentPlace < NUMBER_OF_PLACES)
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
    
    return MenuNavigationOptions::Exit;
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
    while (menuOption != MenuNavigationOptions::Exit)
    {
        menuOption = set_up_setpoints_and_times(currentProcess);
        if(menuOption == MenuNavigationOptions::Forward) {
            ++currentProcess;
        } else if(menuOption == MenuNavigationOptions::Backward) {
            if(currentProcess == 0) {
                return MenuNavigationOptions::Backward;
            } else {
             --currentProcess;
            }
            
        }
    }
    
    return MenuNavigationOptions::Exit;
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
                        set_up_stirrering_setpoints(currentProcess);
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
                
            break;

            case 'D':
                ++option;
                if(option > 4) {
                    option = 1;
                }
               
            break;
        }

        
    }
    return MenuNavigationOptions();
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
    
    gui.clean_set_up_setpoints_and_times_menu_space();
}
void HMI::set_up_stirrering_setpoints(const uint8_t &currentProcess)
{

    gui.clean_set_up_setpoints_and_times_menu_space();
}
void HMI::set_up_process_duration(const uint8_t &currentProcess)
{

    gui.clean_set_up_setpoints_and_times_menu_space();
}

MenuNavigationOptions HMI::summarize_the_defined_execution_specifications()
{
return MenuNavigationOptions();
}
