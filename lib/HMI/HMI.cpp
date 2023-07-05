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

    // Set the temperature sensor type as thermocouples
    // Asigna termopar como tipo de sensor
    executionSpecifications.sensor = TemperatureSensorType::thermocouples;

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
    std::vector<char> validKeys = {'C', 'D', 'A'};

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
    uint8_t current_menu = 0;
    MenuAction action;
    while(action != MenuAction::Exit)
    {
         switch(current_menu)
        {
            case 0:
                action = select_places();
                if(action == MenuAction::Forward) {
                    current_menu++;
                } else if(action == MenuAction::Backward) {
                    action = MenuAction::Exit;
                }
                break;

            case 1:
                action = set_up_setpoints_and_times();
                if(action == MenuAction::Forward) {
                    current_menu++;
                } else if(action == MenuAction::Backward) {
                    current_menu--;
                }
                break;

            case 2:
                action = summarize_the_defined_execution_specifications();
                if(action == MenuAction::Backward) {
                    current_menu--;
                } else if(action == MenuAction::Forward) {
                    action = MenuAction::Exit;
                }
                break;
        }

    }
}

/**Implement the menu for selecting the places where the specifications will be executed
 * Returns MenuAction::Forward to continue to the next menu. MenuAction::Backward to backward.
 * Implementa el menú para seleccionar las plazas en donde se ejecutarán las especificaciones
 * Devuelve MenuAction::Forward para continuar con el siguiente menú. MenuAction::Backward para retroceder.
*/
MenuAction HMI::select_places()
{
    
    
}

MenuAction HMI::set_up_setpoints_and_times()
{
    return MenuAction();
}

MenuAction HMI::summarize_the_defined_execution_specifications()
{
return MenuAction();
}