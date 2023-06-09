
#include "patcher.hpp"
#include "patcherImplementation.h"
#include "pRegistry.h"
#include "../implementations/logImplementation.h"

using namespace YSE;

patcher::patcher()
  : pimpl(nullptr)
{

}

patcher::~patcher() {
  if (pimpl != nullptr) {
		INTERNAL::LogImpl().emit(E_DEBUG, "Deleting Patcher.");
    if (pimpl->controlledBySound) {
      pimpl->head.store(nullptr);
    }
    else {
      delete pimpl;
    }
  }
}

void patcher::create(int mainOutputs) {
  if (pimpl != nullptr) return;
  pimpl = new PATCHER::patcherImplementation(mainOutputs, this);
	if (pimpl != nullptr) {
		INTERNAL::LogImpl().emit(E_DEBUG, "Patcher Created.");
	}
	else {
		INTERNAL::LogImpl().emit(E_ERROR, "Patcher could not be Created.");
	}
}

pHandle * patcher::CreateObject(const std::string & type, const std::string & args) {
	if (pimpl == nullptr) {
		INTERNAL::LogImpl().emit(E_ERROR, "Unable to create object: " + type);
		return nullptr;
	}
  return pimpl->CreateObject(type, args);
}

void patcher::DeleteObject(pHandle * obj) {
  if (pimpl == nullptr) return;
  pimpl->DeleteObject(obj);
}

void patcher::Clear() {
  if (pimpl == nullptr) return;
  pimpl->Clear();
}

void patcher::Connect(pHandle * from, int outlet, pHandle * to, int inlet) {
  if (pimpl == nullptr) return;
  pimpl->Connect(from, outlet, to, inlet);
}

void patcher::Disconnect(pHandle * from, int outlet, pHandle * to, int inlet) {
  if (pimpl == nullptr) return;
  pimpl->Disconnect(from, outlet, to, inlet);
}

bool patcher::IsValidObject(const char * type) {
  return YSE::PATCHER::Register().IsValidObject(type);
}

std::string patcher::DumpJSON() {
  if (pimpl == nullptr) return "";
  std::string result = pimpl->DumpJSON();
  return result;
}

void patcher::ParseJSON(const std::string & content) {
  if (pimpl == nullptr) return;
  pimpl->ParseJSON(content);
}

unsigned int patcher::Objects() {
  if (pimpl == nullptr) return 0;
  return pimpl->Objects();
}

YSE::pHandle * patcher::GetHandleFromList(unsigned int obj) {
  if (pimpl == nullptr) return nullptr;
  return pimpl->GetHandleFromList(obj);
}

YSE::pHandle * patcher::GetHandleFromID(unsigned int objID) {
  if (pimpl == nullptr) return nullptr;
  return pimpl->GetHandleFromID(objID);
}

bool patcher::PassBang(const std::string & to) {
	if (pimpl == nullptr) {
		INTERNAL::LogImpl().emit(E_ERROR, "PassBang called on nullptr to " + to);
		return false;
	}
  return pimpl->PassBang(to, T_GUI);
}

bool patcher::PassData(int value, const std::string & to) {
  if (pimpl == nullptr) {
		INTERNAL::LogImpl().emit(E_ERROR, "PassData (int) called on nullptr to " + to);
		return false;
	}
  return pimpl->PassData(value, to, T_GUI);
}

bool patcher::PassData(float value, const std::string & to) {
  if (pimpl == nullptr) {
		INTERNAL::LogImpl().emit(E_ERROR, "PassData (float) called on nullptr to " + to);
		return false;
	}
  return pimpl->PassData(value, to, T_GUI);
}

bool patcher::PassData(const std::string & value, const std::string & to) {
  if (pimpl == nullptr) {
		INTERNAL::LogImpl().emit(E_ERROR, "PassData (string) called on nullptr to " + to);
		return false;
	}
  return pimpl->PassData(value, to, T_GUI);
}

void patcher::SetOscHandler(oscHandler * handler) {
	if (pimpl == nullptr) {
		INTERNAL::LogImpl().emit(E_ERROR, "SetOscHandler called on nullptr");
		return;
	}
	pimpl->SetHandler(handler);
}