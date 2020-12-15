/*
 * functions.c
 *
 * Created: 12/14/2020 2:43:37 PM
 *  Author: Kimsong Lor
 */ 

uint8_t calc_average(uint8_t arr[]) {
	uint16_t temp = 0;
	for(int i; i < arr->size();i++) {
		temp = temp + arr[i];
	}
	uint8_t result = uint8_t(temp/arr->size());
	return result;
}