#include "screen.h"


LCD5110_display lcd1;


void LCD_INIT(void) {

	lcd1.hw_conf.spi_handle = &hspi2;
	  lcd1.hw_conf.spi_cs_pin =  LCD1_CS_Pin;
	  lcd1.hw_conf.spi_cs_port = LCD1_CS_GPIO_Port;
	  lcd1.hw_conf.rst_pin =  LCD1_RST_Pin;
	  lcd1.hw_conf.rst_port = LCD1_RST_GPIO_Port;
	  lcd1.hw_conf.dc_pin =  LCD1_DC_Pin;
	  lcd1.hw_conf.dc_port = LCD1_DC_GPIO_Port;
	  lcd1.def_scr = lcd5110_def_scr;
	  LCD5110_init(&lcd1.hw_conf, LCD5110_NORMAL_MODE, 0x40, 2, 3);
}

void LCD_PRINT_UI() {


	  rect_t left_border={0,0, 18, 48};
	  rect_t right_border={66,0, 18, 48};
	  rect_t center_v={42,22, 1, 1};
//	  rect_t center_h={40,24, 6, 2};


	 	  	LCD5110_rect_fill(&left_border, BLACK, &lcd1);
	 	 	LCD5110_rect_fill(&right_border, BLACK, &lcd1);
	 	 	LCD5110_rect_fill(&center_v, BLACK, &lcd1);
	// 	 	LCD5110_rect_fill(&center_h, BLACK, &lcd1);
	 	  LCD5110_refresh(&lcd1);

}
double scale_distance(double dist) {
	return dist/50*22;
}

void u_LCD_DRAWPOINT(double angle, double distance) {
	double pi = 3.14159265358979323846;



	int x = (int) (cos(angle * pi / 180)*scale_distance(distance) + 42.5);
	int y = (int) (sin(angle * pi / 180)*scale_distance(distance) + 22.5);


	rect_t point = {x,y, 1, 1};
	LCD5110_rect_fill(&point, BLACK, &lcd1);
	LCD5110_refresh(&lcd1);
}
