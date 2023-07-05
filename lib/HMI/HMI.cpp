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
void HMI::initialize_execution_specifications_struct()
{
    // Initialize the array of selected places as false for all places
    // Inicizaliza el arreglo de plazas seleccionadas como falso
    for (uint8_t i = 0; i < NUMBER_OF_PLACES; ++i) {
        executionSpecifications.selectedPlaces[i] = false;
    }

    // Initialize the temperature setpoints and stirring setpoints
    // Inicializa los setpoints de temeperatura y agitación en 0
    for (uint8_t i = 0; i < TASK; ++i) {
        executionSpecifications.temperatureSetpoint[i].temperature = 0;
        executionSpecifications.temperatureSetpoint[i].tempFunction = TemperatureFunctionType::constant;
        executionSpecifications.stirringSetpoints[i] = 0;
    }

    // Set the configured task to zero
    // Asigna cero a las tareas configuradas
    executionSpecifications.configuredTask = 0;
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
                option--;
                break;
            
            case 'D':
                option++;
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
    initialize_execution_specifications_struct();
    uint8_t currentMenu = 0;
    MenuNavigationOptions action;
    while(action != MenuNavigationOptions::Exit)
    {
         switch(currentMenu)
        {
            case 0:
                action = select_places();
                if(action == MenuNavigationOptions::Forward) {
                    currentMenu= 1;
                } else if(action == MenuNavigationOptions::Backward) {
                    action = MenuNavigationOptions::Exit;
                }
            break;

            case 1:
                action = set_up_setpoints_and_times();
                if(action == MenuNavigationOptions::Forward) {
                    currentMenu = 2;
                } else if(action == MenuNavigationOptions::Backward) {
                    currentMenu = 0;
                }
            break;

            case 2:
                action = summarize_the_defined_execution_specifications();
                if(action == MenuNavigationOptions::Backward) {
                    currentMenu = 1;
                } else if(action == MenuNavigationOptions::Forward) {
                    action = MenuNavigationOptions::Exit;
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
    gui.show_select_places_background_elements(executionSpecifications.selectedPlaces, NUMBER_OF_PLACES);
    while (currentPlace >= 0 && currentPlace < NUMBER_OF_PLACES)
    {
        gui.highlight_current_place_in_select_places_menu(executionSpecifications.selectedPlaces, currentPlace, NUMBER_OF_PLACES);
        keyPressed = keyboard.get_valid_key(validKeys);

        switch (keyPressed)
        {
            case 'A':
                if(executionSpecifications.selectedPlaces[currentPlace]) {
                    executionSpecifications.selectedPlaces[currentPlace] = false;
                } else {
                    executionSpecifications.selectedPlaces[currentPlace] = true;
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
                currentPlace++;
                if(currentPlace >= NUMBER_OF_PLACES) {
                    currentPlace = 0;
                }
            break;
        }
    }
    
    return MenuNavigationOptions();
}

bool HMI::validate_selected_places_array()
{
    bool validArray = false;
    for(uint8_t currentPlace = 0; currentPlace < NUMBER_OF_PLACES; ++currentPlace)
    {
        if(executionSpecifications.selectedPlaces[currentPlace]) {
            validArray = true;
            break;
        }
    }
    return validArray;
}


MenuNavigationOptions HMI::set_up_setpoints_and_times()
{
    
    return MenuNavigationOptions();
}

MenuNavigationOptions HMI::summarize_the_defined_execution_specifications()
{
return MenuNavigationOptions();
}
