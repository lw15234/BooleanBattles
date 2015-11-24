#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "region.h"


ActionHandler* ActionHandlerNew(ActionType actionType, ActionCallback callback, void* data) {
	ActionHandler* ah = (ActionHandler*)malloc(sizeof(ActionHandler));
	ah->actionType = actionType;
	ah->callback = callback;
	ah->data = data;
	return ah;
}

void ActionHandlerFree(ActionHandler* ah) {
	free(ah);
}

Region* RegionNew(Rect rect) {
	Region* r = (Region*)malloc(sizeof(Region));
	memcpy(&r->rect, &rect, sizeof(Rect));
	r->actionHandlersCapacity = 1;
	r->actionHandlersCount = 0;
	r->actionHandlers = (ActionHandler**)malloc(sizeof(ActionHandler*));
	return r;
}

void RegionFree(Region* r) {
	int i;
	for(i = 0; i < r->actionHandlersCount; i++) {
		ActionHandlerFree(r->actionHandlers[i]);
	}
	free(r->actionHandlers);
	free(r);
}

void RegionAddActionHandler(Region* region, ActionHandler* actionHandler) {
	Region* r = region;
	if(r->actionHandlersCount == r->actionHandlersCapacity) {
		r->actionHandlersCapacity *= 2;
		r->actionHandlers = (ActionHandler**)realloc(r->actionHandlers, r->actionHandlersCapacity);
	}
	r->actionHandlers[r->actionHandlersCount] = actionHandler;
	r->actionHandlersCount++;
}

void RegionCheckAction(Region* region, ActionType actionType, float x, float y) {
	int i;
	if(PointInRect(region->rect, x, y)) {
		printf("Start region check\n");
		for(i = 0; i < region->actionHandlersCount; i++) {
			if(region->actionHandlers[i]->actionType == actionType) {
				printf("Callback!\n");
				region->actionHandlers[i]->callback(region->actionHandlers[i]->data);
			}
		}
	}	
}

RegionContainer* RegionContainerNew(void) {
	RegionContainer* container = (RegionContainer*)malloc(sizeof(RegionContainer));
	container->regionsCapacity = 1;
	container->regionsCount = 0;
	container->regions = (Region**)malloc(sizeof(Region*));
	return container;
}
void RegionContainerFree(RegionContainer* container) {
	int i;
	for(i = 0; i < container->regionsCount; i++) {
		RegionFree(container->regions[i]);
	}
	free(container->regions);
	free(container);
}

void RegionContainerAddRegion(RegionContainer* container, Region* region) {
	RegionContainer* c = container;
	if(c->regionsCapacity == c->regionsCount) {
		c->regionsCapacity *= 2;
		c->regions = (Region**)realloc(c->regions, c->regionsCapacity * sizeof(Region*));
	}
	c->regions[c->regionsCount] = region;
	c->regionsCount++;
}


void RegionContainerPassAction(RegionContainer* container, ActionType actionType, float x, float y) {
	int i;
	printf("Pass action start %x\n", container);
	for(i = 0; i < container->regionsCount; i++) {
		RegionCheckAction(container->regions[i], actionType, x, y);
	}
}
