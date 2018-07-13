
#include "Menu.h"
#include "oled.h"









class MyRenderer : public MenuComponentRenderer {
public:
	void render(Menu const &menu) const {
		
		Serial.println(menu.get_name());
		if (menu.get_name() != "   Keyboards") {
			MenuComponent const* curr = menu.get_current_component();
			oled.clear();

			oled.println("===== MAIN MENU =====");//21

			if (curr->get_name() == "   Scripts") { oled.println("-> Scripts"); oled.println("   Keyboards"); oled.println("   Info"); }
			if (curr->get_name() == "   Keyboards") { oled.println("   Scripts"); oled.println("-> Keyboards"); oled.println("   Info"); }
			if (curr->get_name() == "   Info") { oled.println("   Scripts"); oled.println("   Keyboards"); oled.println("-> Info"); }
		}

		else if (menu.get_name() == "   Keyboards") {
		
			MenuComponent const* curr = menu.get_current_component();
			oled.clear();

			oled.println("===== KEYBOARDS =====");//21
			oled.println("");

			if (curr->get_name() == "   PT-PT") { oled.println("-> PT-PT"); oled.println("   EN"); }
			if (curr->get_name() == "   EN") { oled.println("   PT-PT"); oled.println("-> EN"); }
		
		
		}


		//oled.print(menu.get_name());
		//menu.get_current_component()->render(*this);
	}

	void render_menu_item(MenuItem const& menu_item) const {
		oled.print(menu_item.get_name());
	}

	void render_back_menu_item(BackMenuItem const& menu_item) const {
		oled.print(menu_item.get_name());
	}

	void render_numeric_menu_item(NumericMenuItem const& menu_item) const {
		oled.print(menu_item.get_name());
	}

	void render_menu(Menu const& menu) const {
		//oled.print(menu.get_name());
	}
};


MyRenderer my_renderer;


void on_scripts_selected(MenuComponent* p_menu_component);
void on_keyboards_selected(MenuComponent* p_menu_component);
void on_info_selected(MenuComponent* p_menu_component);


MenuSystem ms(my_renderer);
MenuItem scripts("   Scripts", &on_scripts_selected);
Menu keyboards("   Keyboards");
MenuItem info("   Info", &on_info_selected);
MenuItem mu1_mi1("   PT-PT", on_keyboards_selected);
MenuItem mu1_mi2("   EN", on_keyboards_selected);




//------------------------------NUMERIC TEST----------------
//NumericMenuItem nmmi1('s', &on_item1_selected,1, 1, 3, 1,"1");
//----------------------------------------------------------


// Menu callback function

void on_scripts_selected(MenuComponent* p_menu_component) {
	oled.print("Item1 Selected  ");
	delay(1500); // so we can look the result on the LCD
}

void on_keyboards_selected(MenuComponent* p_menu_component) {
	oled.print("Item2 Selected  ");
	delay(1500); // so we can look the result on the LCD
}

void on_info_selected(MenuComponent* p_menu_component) {
	oled.print("Item3 Selected  ");
	delay(1500); // so we can look the result on the LCD
}

void setupMenu() {

	ms.get_root_menu().add_item(&scripts);
	ms.get_root_menu().add_menu(&keyboards);
	ms.get_root_menu().add_item(&info);
	keyboards.add_item(&mu1_mi1);
	keyboards.add_item(&mu1_mi2);

	
	ms.display();
	
}

void checkHardware() {

	if (digitalRead(left) == 0) {
		ms.next();
		ms.display();
		delay(50);
	}

	if (digitalRead(center) == 0) {
		ms.select();
		ms.display();
		delay(50);
	}

	if (digitalRead(right) == 0) {
		ms.prev();
		ms.display();
		delay(50);
	}

}

