/*
 * TypeBase.h
 *
 *  Created on: Nov 15, 2019
 *      Author: root
 */

#ifndef TYPEBASE_H_
#define TYPEBASE_H_

#include <string.h>

#define DEBUG(format, ...) \
	do { \
		if (*(format+strlen(format)-1) == '\n') \
			printf( "%s:%d, " format, __FILE__, __LINE__, ##__VA_ARGS__); \
		else \
			printf( "%s:%d, " format"\n", __FILE__, __LINE__, ##__VA_ARGS__); \
	} while (0)


// iterator loop
#define FOR_EACH_FROWARD(it, container) \
    for( auto it = (container).begin(); it != (container).end(); ++it )

#endif /* TYPEBASE_H_ */
