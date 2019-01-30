
#include <thread>
#include <chrono>
#include <iostream>

#include "aoi_orthogonal_linked_list.h"

static aoi_ol_obj * create_ol_obj(uint64_t id, int32_t x, int32_t y) {
	aoi_ol_obj * obj = new aoi_ol_obj(id);
	obj->set_pos(x, y, 0);
	obj->set_radius(20);
	return obj;
}

static void release_ol_obj(aoi_ol_obj *ol_obj) {
	if (ol_obj) {
		delete ol_obj;
	}
}

void test_add() {
	aoi_orthogonal_linked *aoi_ctrl = new aoi_orthogonal_linked();
	
	aoi_ol_obj *ol_obj1 = create_ol_obj(1, 100, 130);
	aoi_ol_obj *ol_obj2 = create_ol_obj(2, 110, 120);
	aoi_ol_obj *ol_obj3 = create_ol_obj(3, 120, 110);
	aoi_ol_obj *ol_obj4 = create_ol_obj(4, 130, 100);

	aoi_ctrl->aoi_add(ol_obj1);
	aoi_ctrl->aoi_add(ol_obj2);
	aoi_ctrl->aoi_add(ol_obj3);
	aoi_ctrl->aoi_add(ol_obj4);

	while (true) {
		static int tick = 0;
		aoi_ctrl->aoi_update();
		aoi_ctrl->debug_print_objects();
		aoi_ctrl->debug_print_x_axis();
		aoi_ctrl->debug_print_y_axis();

		std::cout << "************* tick" << tick++ << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	release_ol_obj(ol_obj4);
	release_ol_obj(ol_obj3);
	release_ol_obj(ol_obj2);
	release_ol_obj(ol_obj1);
	
	delete aoi_ctrl;
	aoi_ctrl = nullptr;
}

void test_remove() {
	aoi_orthogonal_linked *aoi_ctrl = new aoi_orthogonal_linked();
	
	aoi_ol_obj *ol_obj1 = create_ol_obj(1, 100, 130);
	aoi_ol_obj *ol_obj2 = create_ol_obj(2, 110, 120);
	aoi_ol_obj *ol_obj3 = create_ol_obj(3, 120, 110);
	aoi_ol_obj *ol_obj4 = create_ol_obj(4, 130, 100);

	aoi_ctrl->aoi_add(ol_obj1);
	aoi_ctrl->aoi_add(ol_obj2);
	aoi_ctrl->aoi_add(ol_obj3);
	aoi_ctrl->aoi_add(ol_obj4);

	while (true) {
		static int tick = 0;
		aoi_ctrl->aoi_update();
		aoi_ctrl->debug_print_objects();

		if (tick == 5) {
			aoi_ctrl->aoi_remove(ol_obj2);
			aoi_ctrl->aoi_remove(ol_obj3);
		}

		std::cout << "************* tick" << tick++ << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	release_ol_obj(ol_obj4);
	release_ol_obj(ol_obj3);
	release_ol_obj(ol_obj2);
	release_ol_obj(ol_obj1);
	
	delete aoi_ctrl;
	aoi_ctrl = nullptr;
}

void test_move() {
	aoi_orthogonal_linked *aoi_ctrl = new aoi_orthogonal_linked();
	
	aoi_ol_obj *ol_obj1 = create_ol_obj(1, 100, 100);
	aoi_ol_obj *ol_obj2 = create_ol_obj(2, 110, 100);
	aoi_ol_obj *ol_obj3 = create_ol_obj(3, 120, 100);
	aoi_ol_obj *ol_obj4 = create_ol_obj(4, 130, 100);
	aoi_ol_obj *ol_obj5 = create_ol_obj(5, 150, 100);
	aoi_ol_obj *ol_obj6 = create_ol_obj(6, 151, 100);

	aoi_ctrl->aoi_add(ol_obj1);
	aoi_ctrl->aoi_add(ol_obj2);
	aoi_ctrl->aoi_add(ol_obj3);
	aoi_ctrl->aoi_add(ol_obj4);
	aoi_ctrl->aoi_add(ol_obj5);
	aoi_ctrl->aoi_add(ol_obj6);

	while (true) {
		static int tick = 0;
		aoi_ctrl->aoi_update();
		aoi_ctrl->debug_print_x_axis();

		if (tick == 3) {
			aoi_ctrl->aoi_move(ol_obj2, 50, 130);
		}

		if (tick == 4) {
			aoi_ctrl->aoi_move(ol_obj2, 125, 130);
		}

		if (tick == 5) {
			aoi_ctrl->aoi_move(ol_obj2, 110, 120);
		}

		std::cout << "************* tick" << tick++ << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
		
	release_ol_obj(ol_obj4);
	release_ol_obj(ol_obj3);
	release_ol_obj(ol_obj2);
	release_ol_obj(ol_obj1);
	
	delete aoi_ctrl;
	aoi_ctrl = nullptr;
}

int main(int argc, char *argv[]) {
	//test_add();
	//test_remove();
	test_move();
	return 0;
}
