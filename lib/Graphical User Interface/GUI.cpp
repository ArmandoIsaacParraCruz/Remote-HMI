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
    uint32_t posX = 45, posY = 10, width = 240, height = 60, spacing = 10,
    x1_1 = 35, y1_1 = 230, x2_1 = 45, y2_1 = 230, x3_1 = 40, y3_1 = 220,
    x1_2 = 135, y1_2 = 220, x2_2 = 145, y2_2 = 220, x3_2 = 140, y3_2 = 230;
    lcd.fillScreen(MY_SKYBLUE);
    lcd.fillRect(posX, posY, width, height, MY_BLACK);
    lcd.fillRect(posX, posY + height + spacing, width, height, MY_BLACK);
    lcd.fillRect(posX, posY + 2*height + 2*spacing, width, height, MY_BLACK);

    lcd.fillTriangle(x1_1, y1_1, x2_1, y2_1, x3_1, y3_1, MY_BLACK);
    lcd.fillTriangle(x1_2, y1_2, x2_2, y2_2, x3_2, y3_2, MY_BLACK);
    lcd.setFreeFont(FMB9);
    lcd.setTextColor(MY_BLACK);
    lcd.drawString("C:", x1_1 - 2 * spacing, y3_1 - 2);
    lcd.drawString("D:", x1_2 - 2 * spacing, y1_2 - 2);
    lcd.drawString("A: ELEGIR", x1_2 + 8 * spacing, y1_2 - 2);
}

void GUI::highlight_current_option_in_main_menu(uint8_t option)
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
