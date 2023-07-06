#include "GUI.h"

GUI::GUI()
{
    lcd.begin(2);
    lcd.invertDisplay(false);
    lcd.setRotation(1);
    lcd.fillScreen(MY_WHITE);
    lcd.setSwapBytes(true);   
}

/**Shows the UAM logo and the letter "LCAR" on the tft screen 
 * Muestra el logo de la UAM y las letras "LCAR" en la patanlla tft
*/
void GUI::show_UAM_logo()
{
    int32_t logoX = 65,logoY = 10,txtX = 120, txtY = 200;
	lcd.pushImage(logoX, logoY, logoWidth, logoHeight, logoUAM);
	lcd.setFreeFont(FF47);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("LCAR", txtX, txtY, GFXFF);
	delay(3000);
	lcd.fillScreen(TFT_SKYBLUE);
}

void GUI::show_main_menu_background_elements()
{
    lcd.fillScreen(MY_SKYBLUE);
    lcd.fillRect(45, 10, 240, 60, MY_BLACK);
    lcd.fillRect(45, 80, 240, 60, MY_BLACK);
    lcd.fillRect(45, 150, 240, 60, MY_BLACK);

    lcd.fillTriangle(35, 230, 45, 230, 40, 220, MY_BLACK);
    lcd.fillTriangle(135, 220, 145, 220, 140, 230, MY_BLACK);
    lcd.setFreeFont(FMB9);
    lcd.setTextColor(MY_BLACK);
    lcd.drawString("C:", 15, 218);
    lcd.drawString("D:", 115, 218);
    lcd.drawString("A:ELEGIR", 215, 218);
}

void GUI::highlight_current_option_in_main_menu(const uint8_t &option)
{
    uint32_t posX = 50,posY = 15, width = 230, height = 50, spacing = 0, color;

	for(uint8_t i = 1; i <= 3; ++i, spacing += 70) {
		if(i == option) {
			color = MY_YELLOW;
		} else {
			color = MY_WHITE;
		} 
      	lcd.fillRect(posX,posY + spacing, width, height, color);
	}

    lcd.setFreeFont(FMB9);
    lcd.fillTriangle(241, 25, 243, 21, 246, 21, MY_BLACK);
    lcd.drawString("CONFIG. AGITACION", 70, 25);
    lcd.drawString("Y CALENTAMIENTO", 80, 40);

    lcd.drawString("MONITOREAR", 110, 95);
    lcd.drawString("MULTIPARRILLA", 95, 110);

    lcd.drawString("ESTADO DEL ENLACE",70, 165);
	lcd.drawString("Y SALIDA DE DATOS",70, 180);
}

void GUI::show_select_places_menu_background_elements(const bool selectedPlaces[], const uint8_t numPlaces)
{
	lcd.fillScreen(MY_SKYBLUE);
	show_selected_places(selectedPlaces, numPlaces);
	lcd.fillRect(40, 85, 250, 40, MY_YELLOW);
	lcd.fillTriangle(223, 222, 223, 232, 233, 227, MY_BLACK);
	lcd.fillTriangle(220, 222, 220, 232, 210, 227, MY_BLACK);
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("SELECCIONE AL MENOS UNA PLAZA", 50, 90, FONT2);
	lcd.drawString("PARA CONTINUAR", 110, 105, FONT2);
	lcd.drawString("A: SELEC./DESELEC.", 10, 205, FONT2);
	lcd.drawString("B: REGRESAR", 10, 220, FONT2);
	lcd.drawString("C: CONTINUAR", 190, 205, FONT2);
	lcd.drawString("D:", 190, 220, FONT2);
}

void GUI::show_selected_places(const bool selectedPlaces[], const uint8_t numPlaces)
{
	int32_t imageX = 10,imageY = 0, posX = 17, color;
	lcd.pushImage(imageX, imageY, imageWidth, imageHeight, multiHeaterStirrerImage);
	lcd.setTextColor(MY_BLACK);
	lcd.setFreeFont(FF47);
	for(uint8_t currentPlace = 0; currentPlace < numPlaces; ++currentPlace, posX+=50) {
		if(selectedPlaces[currentPlace]) {
			color = MY_GREEN;
		} else {
			color = MY_SILVER;
		}
		lcd.fillRect(posX, 3, 36, 36, color);
		lcd.drawString((String)(currentPlace+1),posX + 7, 6);
	}
}

void GUI::highlight_current_place_in_select_places_menu(const bool selectedPlaces[], const uint8_t &currentPlace, const uint8_t numPlaces)
{
	uint32_t boxColorNumber, boxColorText;
	uint8_t previousPlace, spacing;
	String textOption, textPlaceStatus;

	lcd.setFreeFont(FF47);

	if(currentPlace == 0) {
		previousPlace = numPlaces - 1;
	} else {
		previousPlace = currentPlace - 1;
	}

    if(selectedPlaces[previousPlace]) {
		 boxColorNumber = MY_GREEN;
	} else {
		boxColorNumber = MY_SILVER;
	}

	lcd.fillRect(17 + 50 * previousPlace, 3, 36, 36, boxColorNumber);
	lcd.drawString((String)(previousPlace + 1), 24 + 50 * previousPlace, 6);
	lcd.fillRect(17 + 50 * currentPlace, 3, 36, 36, MY_RED);

    if(selectedPlaces[currentPlace]) {
		boxColorNumber= MY_GREEN;
		boxColorText = MY_SILVER;
		textOption = "DESELECCIONAR";
		textPlaceStatus = "SELECCIONADA";
		spacing = 20;
	} else {
		boxColorNumber = MY_SILVER;
		boxColorText = MY_GREEN;
		textOption = "SELECCIONAR";
		textPlaceStatus = "NO SELECCIONADA";
		spacing = 0;
	}
	
	lcd.fillRect(20 + 50*currentPlace, 6, 30, 30, boxColorNumber);
	lcd.fillRect(40, 169, 250, 20, boxColorText);
	lcd.drawString((String)(currentPlace + 1), 24 + 50 * currentPlace, 6);
	lcd.fillRect(40, 139, 250, 20, boxColorNumber);
	lcd.setFreeFont(TT1);
	lcd.drawString("PLAZA", 85, 140, FONT2);
	lcd.drawString((String)(currentPlace + 1) + ":", 130, 140, FONT2);
	lcd.drawString(textPlaceStatus, 150, 140, FONT2);
	lcd.drawString("PRESIONE 'A' PARA", 55, 170, FONT2);
	lcd.drawString(textOption, 180, 170, FONT2);
}

void GUI::show_set_up_setpoints_and_times_menu_background_elements(const bool selectedPlaces[], const uint8_t numPlaces, const uint8_t &currentProcess)
{
	lcd.fillScreen(MY_SKYBLUE);
	show_selected_places(selectedPlaces, numPlaces);
	lcd.fillRect(10, 100, 300, 100, MY_WHITE);
	lcd.fillRect(65, 80, 170, 20, MY_WHITE);
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("PROCESO: " + (String)(currentProcess + 1) + " DE 20", 70, 80, FONT2);
	clean_set_up_setpoints_and_times_menu_space();
}


void GUI::clean_set_up_setpoints_and_times_menu_space()
{
	lcd.fillRect(10, 100, 300, 100, MY_WHITE);
	lcd.fillRect(0, 200, 320, 40, MY_SKYBLUE);
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("A: CONFIGURAR", 10, 205, FONT2);
	lcd.drawString("B: REGRESAR", 10, 220, FONT2);
	lcd.drawString("C: CONTINUAR", 190, 205, FONT2);
	lcd.drawString("D:", 190, 220, FONT2);
	lcd.fillTriangle(213, 222, 223, 222, 218, 232, MY_BLACK);
}

void GUI::update_function_temperature_type_current_process(bool tempFunction)
{
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("FUNC. DE TEMPERATURA:", 30, 100, FONT2);
	if(tempFunction) {
		lcd.drawString("CONSTANTE", 200, 100, FONT2);
	} else {
		lcd.drawString("RAMPA", 230, 100, FONT2);
	}
}

 void GUI::show_set_up_temperature_function_type_menu_background_elements()
 {
	lcd.fillRect(10, 100, 300, 100, MY_WHITE);
	lcd.fillRect(0, 200, 320, 40, MY_SKYBLUE);
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("A: SELECCIONAR", 10, 205, FONT2);
	lcd.drawString("D:", 190, 205, FONT2);
	lcd.fillTriangle(213, 207, 223, 207, 218, 217, MY_BLACK);
	lcd.drawString("ESCOJA UNA FUNC. DE TEMPERATURA", 50, 100, FONT2);
	lcd.drawString("Y PRESIONE 'A' PARA SELECCIONARLA", 50, 120, FONT2);
	lcd.drawString("CONSTANTE", 70, 150, FONT2);
	lcd.drawString("RAMPA", 70, 170, FONT2);
 }

 void GUI::show_current_option_set_up_temperature_function_type_menu(const uint8_t &currentOption)
 {
	uint8_t currentPosition, previousPosition;
	switch (currentOption)
	{
		case 1:
			previousPosition = 170;
			currentPosition = 150;
		break;

		case 2:
			previousPosition = 150;
			currentPosition = 170;
		break;
	}

	lcd.fillRect(50, previousPosition, 20, 20, MY_WHITE);
	lcd.fillTriangle(50, currentPosition, 50, currentPosition + 10, 60, currentPosition + 5, MY_BLACK);
 }

void GUI::update_temperatures_setpoints_current_process(const uint16_t &initTemp, const uint16_t &finalTemp)
{
	String initTempText, finalTempText;
	if(initTemp == 0) {
		initTempText = "SIN CONFIGURAR";
	} else {
		lcd.drawCircle(250, 122, 2, MY_BLACK);
		lcd.drawString("C", 255, 120, FONT2);
		initTempText = (String)(initTemp);
	}

	if(finalTemp == 0) {
		finalTempText = "SIN CONFIGURAR";
	} else {
		finalTempText = (String)(finalTemp);
		lcd.drawCircle(250, 142, 2, MY_BLACK);
		lcd.drawString("C", 255, 140, FONT2);
	}
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("TEMPERATURAS:", 30, 120, FONT2);
	lcd.drawString("INICIAL: " + initTempText, 140, 120, FONT2);
	lcd.drawString("FINAL: " + finalTempText, 140, 140, FONT2);
}

void GUI::update_stirring_setpoints_current_process(const uint16_t &stirringSetpoint)
{
	String stirringSetpointText;
	if(stirringSetpoint == 0) {
		stirringSetpointText = "SIN CONFIGURAR";
	} else {
		stirringSetpointText = (String)(stirringSetpoint) + " " + "RPM";
	}

	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawLine(80,160,83,157, MY_BLACK);
	lcd.drawString("AGITACION: " + stirringSetpointText, 30, 160, FONT2);
}

void GUI::update_duration_current_process(const uint32_t &processDuration)
{
	String processDurationText;
	if(processDuration == 0) {
		processDurationText = "SIN CONFIGURAR";
	} else {
		processDurationText = (String)(processDuration) + " " +"MIN";
	}

	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawLine(80,180,83,177, MY_BLACK);
	lcd.drawString("DURACION: " + processDurationText, 30, 180, FONT2);
}

void GUI::show_current_option_set_up_setpoints_and_times_menu(uint8_t &currentOption)
{
	uint8_t currentPosition, previousPosition;
	switch (currentOption)
	{
		case 1:
			previousPosition = 180;
			currentPosition = 100;
		break;

		case 2:
			previousPosition = 100;
			currentPosition = 120;
		break;

		case 3:
			previousPosition = 120;
			currentPosition = 160;
		break;

		case 4:
			previousPosition = 160;
			currentPosition = 180;
		break;
	}

	lcd.fillRect(10, previousPosition, 20, 20, MY_WHITE);
	lcd.fillTriangle(10, currentPosition, 10, currentPosition + 10, 20, currentPosition + 5, MY_BLACK);
}

void GUI::show_set_up_stirring_setpoints_menu_background_elements()
{
	lcd.fillRect(10, 100, 300, 100, MY_WHITE);
	lcd.fillRect(0, 200, 320, 40, MY_SKYBLUE);
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("A: LISTO", 10, 205, FONT2);
	lcd.drawString("B: BORRAR VALOR", 190, 205, FONT2);
	lcd.drawString("INGRESE UN VALOR ENTRE 0 Y 1200 RPM", 30, 100, FONT2);
	lcd.drawString("Y LUEGO PRESIONE 'A'", 80, 120, FONT2);
	lcd.drawLine(122,160,125,157, MY_BLACK);
	lcd.drawString("AGITACION: ", 70, 160, FONT2);
}

void GUI::show_rmp_value_set_up_stirring_setpoints_menu(const String &stirringSetpoint)
{
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.fillRect(150, 160, 100, 20, MY_WHITE);
	if(stirringSetpoint.toInt() == 0) {
		lcd.drawString("SIN CONFIGURAR", 150, 160, FONT2);
	} else {
		lcd.drawString(stirringSetpoint + " RPM", 150, 160, FONT2);
	}
}

void GUI::show_set_up_constant_temperature_menu_background_elements()
{
	lcd.fillRect(10, 100, 300, 100, MY_WHITE);
	lcd.fillRect(0, 200, 320, 40, MY_SKYBLUE);
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("A: LISTO", 10, 205, FONT2);
	lcd.drawString("B: BORRAR VALOR", 190, 205, FONT2);
	lcd.drawString("INGRESE UN VALOR QUE NO SUPERE LOS 300", 20, 100, FONT2);
	lcd.drawString("GRADOS CELSIOUS. LUEGO, PRESIONE 'A'.", 30, 120, FONT2);
	lcd.drawString("TEMPERATURA:", 50, 160, FONT2);
}

void GUI::show_temp_value_set_up_constant_temperature_menu(const String &temp)
{
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.fillRect(150, 160, 150, 20, MY_WHITE);
	if(temp.toInt() == 0) {
		lcd.drawString("SIN CONFIGURAR", 150, 160, FONT2);
	} else {
		lcd.drawString(temp + " GRADOS CELSIOUS", 150, 160, FONT2);
	}
}

void GUI::show_set_up_process_duration_menu_background_elements()
{
	lcd.fillRect(10, 100, 300, 100, MY_WHITE);
	lcd.fillRect(0, 200, 320, 40, MY_SKYBLUE);
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("A: LISTO", 10, 205, FONT2);
	lcd.drawString("B: BORRAR VALOR", 190, 205, FONT2);
	lcd.drawString("INGRESE UN VALOR ENTRE 1 Y 180 MINUTOS", 20, 100, FONT2);
	lcd.drawString("Y LUEGO PRESIONE 'A'", 80, 120, FONT2);
	lcd.drawLine(120,160,123,157, MY_BLACK);
	lcd.drawString("DURACION: ", 70, 160, FONT2);
}

void GUI::show_duration_value_set_up_process_duration_menu(const String &time)
{
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.fillRect(150, 160, 100, 20, MY_WHITE);
	if(time.toInt() == 0) {
		lcd.drawString("SIN CONFIGURAR", 150, 160, FONT2);
	} else {
		lcd.drawString(time + " MINUTOS", 150, 160, FONT2);
	}
}

void GUI::show_set_up_ramp_temperature_menu_background_elements()
{
	lcd.fillRect(10, 100, 300, 100, MY_WHITE);
	lcd.fillRect(0, 200, 320, 40, MY_SKYBLUE);
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.drawString("A: LISTO", 10, 205, FONT2);
	lcd.drawString("D:", 190, 205, FONT2);
	lcd.fillTriangle(213, 207, 223, 207, 218, 217, MY_BLACK);
	lcd.drawString("B: BORRAR VALOR", 10, 225, FONT2);
	lcd.drawString("INGRESE DOS VALORES QUE NO SUPERE LOS", 20, 100, FONT2);
	lcd.drawString("300 GRADOS CELSIOUS. LUEGO, PRESIONE 'A'.", 20, 120, FONT2);
	lcd.drawString("TEMP. INICIAL > TEMP. FINAL", 60, 140, FONT2);
	lcd.drawString("TEMP. INICIAL: ", 40, 160, FONT2);
	lcd.drawString("TEMP. FINAL: ", 40, 180, FONT2);
}

void GUI::show_rmp_value_set_up_ramp_temperature_menu(const String &initTemp, const String &finalTemp)
{
	lcd.setFreeFont(TT1);
	lcd.setTextColor(MY_BLACK);
	lcd.fillRect(150, 160, 150, 20, MY_WHITE);
	if(initTemp.toInt() == 0) {
		lcd.drawString("SIN CONFIGURAR", 150, 160, FONT2);
	} else {
		lcd.drawString(initTemp + " GRADOS CELSIOUS", 150, 160, FONT2);
	}

	lcd.fillRect(150, 180, 150, 20, MY_WHITE);
	if(finalTemp.toInt() == 0) {
		lcd.drawString("SIN CONFIGURAR", 150, 180, FONT2);
	} else {
		lcd.drawString(finalTemp + " GRADOS CELSIOUS", 150, 180, FONT2);
	}
}

void GUI::show_current_option_set_up_ramp_temperature_menu(const uint8_t &currentOption)
{
	uint8_t currentPosition, previousPosition;
	switch (currentOption)
	{
		case 1:
			previousPosition = 180;
			currentPosition = 160;
		break;

		case 2:
			previousPosition = 160;
			currentPosition = 180;
		break;
	}

	lcd.fillRect(10, previousPosition, 20, 20, MY_WHITE);
	lcd.fillTriangle(10, currentPosition, 10, currentPosition + 10, 20, currentPosition + 5, MY_BLACK);
}
