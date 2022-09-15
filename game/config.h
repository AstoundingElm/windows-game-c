#pragma once
#include "input.h"
#include "input_types.h"
#include "file_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char* CONFIG_DEFAULT = 
	"[controls]\n"
	"left = A\n"
	"right = D\n"
	"up = W\n"
	"down = S\n"
	"escape = Escape\n"
	 "\n";

static char* tmp_buffer[20] = { 0 };
static char* config_get_value(const char* config_buffer, const char* value) {


	char* line = strstr(config_buffer, value);
	if (!line)
		ERROR_EXIT("could not find config value%s\n try deleting config.ini and restarting\n", value);
	size_t len = strlen(line);
	char* end = line + len;
	char* curr = line;
	char* tmp_ptr = &tmp_buffer[0];
	while (*curr != '=' && curr != end)
		++curr;

	++curr;
	while (*curr == ' ')
		++curr;
	while (*curr != '\n' && *curr != 0 && curr != end)
		*tmp_ptr++ = *curr++;

	*(tmp_ptr + 1) = 0;

	return tmp_buffer;

}

PINLINE void config_key_bind(input_key key, const char* key_name) {

	
}

PINLINE void load_controls(const char * config_buffer){

	//config_key_bind(INPUT_KEY_LEFT, config_get_value(config_buffer, "left"));
}

PINLINE int config_load() {

	File file_config = io_file_read("./config.ini");
	if (!file_config.is_valid);
	return 1;

	load_controls(file_config.data);
	free(file_config.data);
	return 0;

}

struct config{

  u8 keybinds[5];

};	

void config_init(){

	if (config_load() == 0){

		return;
	}
	io_file_write((void*)CONFIG_DEFAULT, strlen(CONFIG_DEFAULT), "./config.ini");
	if (config_load() != 0)
		ERROR_EXIT("coul not create or laod config file");
};

void config_key_bind(input_key key, const char * key_name){

}
