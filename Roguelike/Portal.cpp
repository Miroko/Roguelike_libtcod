#include "Portal.h"
#include "StaticObject.h"

std::shared_ptr<Portal> Portal::newPortal(Portal &portalTemplate){
	return std::shared_ptr<Portal>(new Portal(portalTemplate));
}