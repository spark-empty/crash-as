/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#include <stdio.h>

class father {
private:
	const char* name;
public:
	explicit father(const  char* name): name(name) {
		printf("father(%s)\n",name);
	}

	~father() {
		printf("~father(%s)\n",name);
	}

	const char* get_name() {
		return name;
	}

	void sayHello() {
		/* Yes, Father's last name is Wang */
		printf("Hello, I am Wang %s!\n",name);
	}
};

class son : public father {
public:
	explicit son(const char* name) : father(name) {
		printf("son(%s)\n",name);
	}

	~son() {
		printf("~son(%s)\n",get_name());
	}
};

extern "C" void cppapp_start(void) {
	father f("Guangtoubaba");
	son* s = new son("Xiaoming");

	f.sayHello();
	s->sayHello();
	delete s;

}
