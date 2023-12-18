#include "HMI.h"

/**Initialize the main program
 * Inicializa el programa principal
*/
HMI::HMI()
{
    
}

/**This is the main loop program in the project
 * Este es el bucle principal del proyecto 
*/
void HMI::runHMI()
{
    RemoteCommunication::beginRemoteCommunication();
    GraphicalUserInterface::beginGraphicalUserInterface();
    GraphicalUserInterface::displayUamLogo();
    Serial.println(WiFi.macAddress());
    while(true)
    {
       mainMenu();
    }
}

/**This function initializes the executionSpecifications structure with default values
 * Esta función inicializa la estructura executionSpecifications con valores por defecto
*/
void HMI::initializeProcessesSpecificationsStruct()
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
    processesSpecifications.configuredProcesses = 0;
}


/**
 * It executes the main menu of the HMI
 * Ejecuta el menú principal del HMI
 */
void HMI::mainMenu()
{
    uint8_t option = 1;
    char keyPressed = NO_KEY;
    bool continue_menu = true;
    std::vector<char> validKeys = {'A', 'C', 'D'};
    // Display the background elements of the main menu
    // Mostrar los elementos de fondo del menú principal
    GraphicalUserInterface::displayMainMenuBackgroundElements();

    while (continue_menu) {
        // Highlight the current option in the main menu
        // Resaltar la opción actual en el menú principal
        GraphicalUserInterface::highlightCurrentOptionInMainMenu(option);

        // Wait for a key press
        // Esperar una tecla presionada
        keyPressed = Keyboard::getValidKey(validKeys);
        Serial.println(keyPressed);
        switch(keyPressed)
        {
            case 'A':
                if (option == 1) {
                    // Go to menu: defineExecutionSpecifications();
                    // Ir al menú: defineExecutionSpecifications();
                    defineExecutionSpecifications();
                } else if (option == 2) {
                    // Go to menu: monitor_stirring_and_temperature();
                    // Ir al menú: monitor_stirring_and_temperature();
                    // monitor_stirring_and_temperature();
                } else if (option == 3) {
                    // Go to menu: displayManualAdjustmentMenu;
                    // Ir al menú: displayManualAdjustmentMenu();
                    manualUserAdjustment();
                }
                continue_menu = false;
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

/**
 * This function implements the menus to define the execution specifications
 * Esta función implementa los menús para definir las especificaciones de ejecución
*/
void HMI::defineExecutionSpecifications()
{
    initializeProcessesSpecificationsStruct();
    uint8_t currentMenu = 0;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    while(menuOption != MenuNavigationOptions::Exit)
    {
         switch(currentMenu)
        {
            case 0:
                menuOption = selectPlacesMenu();
                if(menuOption == MenuNavigationOptions::Forward) {
                    currentMenu= 1;
                } 
            break;

            case 1:
                menuOption = setUpProcessesMenus();
                if(menuOption == MenuNavigationOptions::Forward) {
                    currentMenu = 2;
                } else if(menuOption == MenuNavigationOptions::Backward) {
                    currentMenu = 0;
                }
            break;

            case 2:
                menuOption = summarizeDefinedExecutionSpecificationsMenu();
                if(menuOption == MenuNavigationOptions::Forward) {
                    currentMenu = 3;
                } else if(menuOption == MenuNavigationOptions::Backward) {
                    currentMenu = 1;
                }
            break;

            case 3:
                menuOption = confirmAndTransmitConfiguredProcessesMenu();
                 if(menuOption == MenuNavigationOptions::Backward) {
                    currentMenu = 2;
                } else {
                    menuOption = MenuNavigationOptions::Exit;
                }
        }

    }
}

/**
 * Implement the menu for selecting the places where the specifications will be executed
 * Returns MenuNavigationOptions::Forward to continue to the next menu. MenuNavigationOptions::Backward to backward.
 * Implementa el menú para seleccionar las plazas en donde se ejecutarán las especificaciones
 * Devuelve MenuNavigationOptions::Forward para continuar con el siguiente menú. MenuNavigationOptions::Backward para retroceder.
**/
MenuNavigationOptions HMI::selectPlacesMenu()
{
    uint8_t currentPlace = 0;
    char keyPressed = NO_KEY;
    std::vector<char> validKeys = {'A', 'B', 'C', 'D'};
    GraphicalUserInterface::displaySelectPlacesMenuBackgroundElements(processesSpecifications.selectedPlaces, NUMBER_OF_PLACES);
    while (true)
    {
        GraphicalUserInterface::highlightCurrentPlaceInSelectPlacesMenu(processesSpecifications.selectedPlaces, currentPlace, NUMBER_OF_PLACES);
        keyPressed = Keyboard::getValidKey(validKeys);

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
                return confirmExitSelectPlaces();
            break;

            case 'C':
                if(validateSelectedPlacesArray()) {
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

MenuNavigationOptions HMI::confirmExitSelectPlaces()
{
    MenuNavigationOptions menuOption;
    char keyPressed = NO_KEY;
    std::vector<char> validKeys = {'B', 'C'};
    GraphicalUserInterface::displayExitPromptForSelectPlacesMenu();
    keyPressed = Keyboard::getValidKey(validKeys);
    switch (keyPressed)
    {
        case 'B':
            menuOption = MenuNavigationOptions::Exit;
        break;
        case 'C':
            menuOption = MenuNavigationOptions::Continue;
        break;
    }
    return menuOption;
}

bool HMI::validateSelectedPlacesArray()
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


MenuNavigationOptions HMI::setUpProcessesMenus()
{
    uint8_t currentProcess = 0;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    while (true)
    {
        menuOption = setUpSetpointsAndTimesMenu(currentProcess);

        switch (menuOption)
        {
            case MenuNavigationOptions::Forward:
                if(processesSpecifications.configuredProcesses == currentProcess) {
                    ++processesSpecifications.configuredProcesses;
                }
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

MenuNavigationOptions HMI::setUpSetpointsAndTimesMenu(const uint8_t &currentProcess)
{
    uint8_t option = 1;
    char keyPressed = NO_KEY;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> validKeys = {'A', 'B', 'C', 'D'};
    GraphicalUserInterface::displaySetUpSetpointsAndTimesMenuBackgroundElements(processesSpecifications.selectedPlaces, NUMBER_OF_PLACES, currentProcess);
    while(true)
    {
        updateSpecificationsCurrentProcess(currentProcess);
        GraphicalUserInterface::positionPointerOnCurrentOptionInSetUpSetpointsAndTimesMenu(option);
        keyPressed = Keyboard::getValidKey(validKeys);
        switch (keyPressed)
        {
            case 'A':
                switch (option)
                {
                    case 1:
                        setUpTemperatureFunctionTypeMenu(currentProcess);
                    break;

                    case 2:
                        setUpTemperatureSetpointsMenus(currentProcess);
                    break;

                    case 3:
                        setUpStirringSetpointsMenu(currentProcess);
                    break;

                    case 4:
                        setUpProcessDurationMenu(currentProcess);
                    break;
                }
            break;

            case 'B':
                return MenuNavigationOptions::Backward;
            break;

            case 'C':
                if(verifySpecificationsCurrentProcess(currentProcess)) {
                    if(currentProcess == processesSpecifications.configuredProcesses) {
                        return addOrSummarizeProcessesMenu();
                    } else {
                        return MenuNavigationOptions::Forward;
                    }
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

void HMI::updateSpecificationsCurrentProcess(const uint8_t &currentProcess)
{
    if(processesSpecifications.temperatureSetpoints[currentProcess].tempFunction == constant) {
        GraphicalUserInterface::displayCurrentProcessTemperatureFunctionType(true);
    } else {
        GraphicalUserInterface::displayCurrentProcessTemperatureFunctionType(false);
    }

    GraphicalUserInterface::displayCurrentProcessTemperaturesSetpoints(processesSpecifications.temperatureSetpoints[currentProcess].initialTemperature,
                                                        processesSpecifications.temperatureSetpoints[currentProcess].finalTemperature);

    GraphicalUserInterface::displayCurrentProcessStirringSetpoint(processesSpecifications.stirringSetpoints[currentProcess]);
    GraphicalUserInterface::displayCurrentProcessDuration(processesSpecifications.processDuration[currentProcess]);
}

void HMI::setUpTemperatureFunctionTypeMenu(const uint8_t &currentProcess)
{
    uint8_t option = 1;
    char keyPressed = NO_KEY;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> validKeys = {'A', 'D'};
    GraphicalUserInterface::displaySetUpTemperatureFunctionTypeMenuBackgroundElements();
    while (menuOption != MenuNavigationOptions::Exit) 
    {
        GraphicalUserInterface::positionPointerOnCurrentOptionInSetUpTemperatureFunctionTypeMenu(option);
        keyPressed = Keyboard::getValidKey(validKeys);
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
    GraphicalUserInterface::clearMenuSpaceForSetUpSetpointsAndTimes();
}


void HMI::setUpTemperatureSetpointsMenus(const uint8_t &currentProcess)
{
    if(processesSpecifications.temperatureSetpoints[currentProcess].tempFunction == constant) {
        setUpConstantTemperatureMenu(currentProcess);
    } else {
        setUpRampTemperatureMenu(currentProcess);
    }
    GraphicalUserInterface::clearMenuSpaceForSetUpSetpointsAndTimes();
}

void HMI::setUpConstantTemperatureMenu(const uint8_t &currentProcess)
{
    String temperatureSetpoint = String(processesSpecifications.temperatureSetpoints[currentProcess].initialTemperature, DEC);
    char keyPressed = NO_KEY;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> invalidKeys = {'*', '#', 'C', 'D'};
    GraphicalUserInterface::displaySetUpConstantTemperatureMenuBackgroundElements();

    while (menuOption != MenuNavigationOptions::Exit) 
    {
        GraphicalUserInterface::displayTemperatureValueInSetUpConstantTemperatureMenu(temperatureSetpoint);
        keyPressed = Keyboard::ignoreIvalidKeys(invalidKeys);
        Serial.println(keyPressed);
        if(isdigit(keyPressed)) {
            temperatureSetpoint = processValueString(temperatureSetpoint, keyPressed, MAX_TEMPERATURE_DIGIT);
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

void HMI::setUpRampTemperatureMenu(const uint8_t &currentProcess)
{
    String initialTemperature = String(processesSpecifications.temperatureSetpoints[currentProcess].initialTemperature, DEC),
            finalTemperature = String(processesSpecifications.temperatureSetpoints[currentProcess].finalTemperature, DEC);
    char keyPressed = NO_KEY;
    uint8_t option = 1;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> invalidKeys = {'*', '#', 'C'};
    GraphicalUserInterface::displaySetUpRampTemperatureMenuBackgroundElements();
    while (menuOption != MenuNavigationOptions::Exit) 
    {
        GraphicalUserInterface::positionPointerOnCurrentOptionInSetUpRampTemperatureMenu(option);
        GraphicalUserInterface::displayTemperaturesValuesInSetUpRampTemperatureMenu(initialTemperature, finalTemperature);
        keyPressed = Keyboard::ignoreIvalidKeys(invalidKeys);
        Serial.println(keyPressed);
        if(isdigit(keyPressed)) {
            if(option == 1) {
                initialTemperature = processValueString(initialTemperature, keyPressed, MAX_TEMPERATURE_DIGIT);
            } else {
                finalTemperature = processValueString(finalTemperature, keyPressed, MAX_TEMPERATURE_DIGIT);
            }
        } else {
            switch (keyPressed)
            {
                case 'A':
                    if( initialTemperature.toInt() > 0 && 
                        finalTemperature.toInt() <= MAX_TEMPERATURE && 
                        finalTemperature.toInt() > initialTemperature.toInt()) {

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

void HMI::setUpStirringSetpointsMenu(const uint8_t &currentProcess)
{
    String stirringSetpoint = String(processesSpecifications.stirringSetpoints[currentProcess], DEC);
    char keyPressed = NO_KEY;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> invalidKeys = {'*', '#', 'C', 'D'};
    GraphicalUserInterface::displaySetUpStirringSetpointsMenuBackgroundElements();

    while (menuOption != MenuNavigationOptions::Exit) 
    {
        GraphicalUserInterface::displayRPMValueInSetUpStirringSetpointsMenu(stirringSetpoint);
        keyPressed = Keyboard::ignoreIvalidKeys(invalidKeys);
        Serial.println(keyPressed);
        if(isdigit(keyPressed)) {
            stirringSetpoint = processValueString(stirringSetpoint, keyPressed, MAX_RPM_DIGITS);
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
    GraphicalUserInterface::clearMenuSpaceForSetUpSetpointsAndTimes();
}


void HMI::setUpProcessDurationMenu(const uint8_t &currentProcess)
{
    String time = String(processesSpecifications.processDuration[currentProcess], DEC);
    char keyPressed = NO_KEY;
    MenuNavigationOptions menuOption = MenuNavigationOptions::Forward;
    std::vector<char> invalidKeys = {'*', '#', 'C', 'D'};
    GraphicalUserInterface::displaySetUpProcessDurationMenuBackgroundElements();
    while (menuOption != MenuNavigationOptions::Exit) 
    {
        GraphicalUserInterface::displayDurationValueInSetUpProcessDurationMenu(time);
        keyPressed = Keyboard::ignoreIvalidKeys(invalidKeys);
        Serial.println(keyPressed);
        if(isdigit(keyPressed)) {
           time = processValueString(time, keyPressed, MAX_TIME_DIGITS);
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
    GraphicalUserInterface::clearMenuSpaceForSetUpSetpointsAndTimes();
}

String HMI::processValueString(const String &value, const char keyPressed, const uint16_t maxValue)
{
    String valueToReturn = value;
    if(value == "0" || (value + keyPressed).toInt() > maxValue) {
        valueToReturn = keyPressed;
        } else {
        valueToReturn += keyPressed;
    }
    return valueToReturn;
}

bool HMI::verifySpecificationsCurrentProcess(const uint8_t &currentProcess)
{
    bool stirringAndTempVerified = true, durationVerified = true;
    if(processesSpecifications.stirringSetpoints[currentProcess] == 0 && 
        processesSpecifications.temperatureSetpoints[currentProcess].initialTemperature == 0) {

        stirringAndTempVerified = false;
    }

    if(processesSpecifications.processDuration[currentProcess] == 0) {
        durationVerified = false;
    }

    if(!(stirringAndTempVerified && durationVerified)) {
        handleSpecificationErrors(stirringAndTempVerified, durationVerified);
    }

    return stirringAndTempVerified && durationVerified;
}

void HMI::handleSpecificationErrors(const bool &stirringAndTemp, const bool &duration)
{
    char keyPressed = NO_KEY;
    std::vector<char> validKey = {'A'};
    GraphicalUserInterface::displayErrorInCurrentProcessSpecifications(stirringAndTemp, duration);
    Keyboard::getValidKey(validKey);
    GraphicalUserInterface::clearMenuSpaceForSetUpSetpointsAndTimes();
}

MenuNavigationOptions HMI::addOrSummarizeProcessesMenu()
{
    char keyPressed = NO_KEY;
    std::vector<char> validKeys = {'A', 'B', 'C'};
    GraphicalUserInterface::displayPromptToAddOrSummarizeConfiguredProcesses();
    keyPressed = Keyboard::getValidKey(validKeys);
    switch (keyPressed)
    {
        case 'A':
            return MenuNavigationOptions::Forward;
        break;
        case 'B':
            return MenuNavigationOptions::Continue;
        break;
        case 'C':
            return MenuNavigationOptions::Exit;
        break;
    
    }
    return MenuNavigationOptions::Exit;
}

MenuNavigationOptions HMI::summarizeDefinedExecutionSpecificationsMenu()
{
    char keyPressed = NO_KEY;
    uint8_t currentProcess = 0;
    std::vector<char> validKeys = {'B', 'C'};
    GraphicalUserInterface::displaySummarizedExecutionSpecificationsMenuBackgroundElements(processesSpecifications.selectedPlaces, NUMBER_OF_PLACES);
    while(true)
    {
        GraphicalUserInterface::displayNumberOfCurrentProcess(currentProcess, processesSpecifications.configuredProcesses);
        updateSpecificationsCurrentProcess(currentProcess);
        keyPressed = Keyboard::getValidKey(validKeys);
        switch (keyPressed)
        {
            case 'B':
                if(currentProcess > 0) {
                    --currentProcess;
                } else {
                    return MenuNavigationOptions::Backward;
                }
            break;
            
            case 'C':
                if(currentProcess >= processesSpecifications.configuredProcesses) {
                    return MenuNavigationOptions::Forward;
                } else {
                    ++currentProcess;
                }
            break;
        }
    }
}

MenuNavigationOptions HMI::confirmAndTransmitConfiguredProcessesMenu()
{
    char keyPressed = NO_KEY;
    std::vector<char> validKeys = {'B', 'C'};
    GraphicalUserInterface::displayConfirmAndTransmitConfiguredProcessesMenuBackgroundElements();
    while (true)
    {
        keyPressed = Keyboard::getValidKey(validKeys);

        if(keyPressed == 'B') {
            return MenuNavigationOptions::Backward;
        } else if(keyPressed == 'C') {
            if(RemoteCommunication::sendProcessesConfigurated(processesSpecifications)) {
                break;
            } else {
                GraphicalUserInterface::displayTransmissionErrorMessage();
            }
        }
    }
    GraphicalUserInterface::displayTransmissionSuccessMessage();
    validKeys = {'A'};
    Keyboard::getValidKey(validKeys);
    return MenuNavigationOptions::Exit;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////

void HMI::manualUserAdjustment()
{
    RemoteCommunication::sendProcessesConfigurated(processesSpecifications);
}



