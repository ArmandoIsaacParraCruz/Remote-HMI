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

void GUI::show_select_places_background_elements(const bool selected_places[], const uint8_t numPlaces)
{
    int32_t imageX = 10,imageY = 0, posX = 17, color;
	lcd.fillScreen(MY_SKYBLUE);
	lcd.pushImage(imageX, imageY, imageWidth, imageHeight, multiHeaterStirrerImage);
	lcd.setTextColor(MY_BLACK);
    
	lcd.setFreeFont(FF47);
	for(uint8_t i = 0; i < numPlaces; ++i, posX+=50) {
		if(selected_places[i]) {
			color = MY_GREEN;
		} else {
			color = MY_SILVER;
		}
		lcd.fillRect(posX, 3, 36, 36, color);
		lcd.drawString((String)(i+1),posX + 7, 6);
	}
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

