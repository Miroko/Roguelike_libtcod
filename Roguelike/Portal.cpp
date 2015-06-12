#include "Portal.h"

std::shared_ptr<Portal> Portal::newPortal(const Portal &portalTemplate){
	return std::shared_ptr<Portal>(new Portal(portalTemplate));
}