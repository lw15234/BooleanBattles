#ifndef _REGION_H_INCLUDED
#define _REGION_H_INCLUDED

#include "util.h"

typedef enum {
	ACTION_CLICK,
	ACTION_ENTER,
} ActionType;

typedef void (*ActionCallback)(void*);
/*Represents function that will be called when certain action happens
 * actionType - type of action to happen
 * callback - function that will be called when action happen
 * data - user data that will be passed to callback function (can be ommited)
 */
typedef struct ActionHandler ActionHandler;
struct ActionHandler {
	ActionType actionType;
	ActionCallback callback;
	void* data;
};

typedef struct Region Region;
/*Represents region on map that can recieve actions
 * rect - position and size of region
 * actionHandlersCapacity/
 * actionHandlersCount////Dynamic array with action handlers
 * actionHandlers/////////
 */
struct Region {
	Rect rect;
	int actionHandlersCapacity;
	int actionHandlersCount;
	ActionHandler** actionHandlers;
};

typedef struct RegionContainer RegionContainer;
/*Represents container of all regions on map
 * regionCapacity/
 * regionCount////Dynamic array with regions
 * regions////////
 */
struct RegionContainer {
	int regionsCapacity;
	int regionsCount;
	Region** regions;
};

/*Create and initialize new action handler*/
ActionHandler* ActionHandlerNew(ActionType actionType, ActionCallback callback, void* data);

/*Free action handler*/
void ActionHandlerFree(ActionHandler* ah);

/*Create and initialize new Region*/
Region* RegionNew(Rect rect);

/*Free region*/
void RegionFree(Region* region);

/*Add action handler for region*/
void RegionAddActionHandler(Region* region, ActionHandler* actionHandler);

/*Check if action happend in region and if it did - execute handler callback*/
void RegionCheckAction(Region* region, ActionType actionType, float x, float y);

/*Create and initialize region container*/
RegionContainer* RegionContainerNew(void);

/*Free region container*/
void RegionContainerFree(RegionContainer* container);

/*Add region to region container*/
void RegionContainerAddRegion(RegionContainer* container, Region* region);

/*Pass action to regions in region container*/
void RegionContainerPassAction(RegionContainer* container, ActionType actionType, float x, float y);

#endif
