#include "ModuleManager.h"

#include "Module.h"
#include "Path/Path.h"

namespace engine
{

ModuleManager::~ModuleManager() = default;

void ModuleManager::LoadModules(bool checkAutoLoad)
{
	for (auto& [_, module] : m_allModules)
	{
		if (!module->IsLoaded())
		{
			if (checkAutoLoad && module->GetAutoLoad())
			{
				module->Load();
			}
		}
	}
}

void ModuleManager::UnloadModules()
{
	for (auto& [_, module] : m_allModules)
	{
		if (module->IsLoaded())
		{
			module->Unload();
		}
	}
}

Module* ModuleManager::AddModule(const char* pFilePath)
{
	std::string moduleName = Path::GetFileNameWithoutExtension(pFilePath);
	StringCrc moduleCrc(moduleName);
	if (auto* pModule = GetModule(moduleCrc))
	{
		return pModule;
	}

	auto module = std::make_unique<Module>();
	Module* pModule = module.get();
	m_allModules[moduleCrc] = cd::MoveTemp(module);

	pModule->SetName(cd::MoveTemp(moduleName));
	pModule->SetFilePath(pFilePath);
	return pModule;
}

bool ModuleManager::FindModule(StringCrc moduleCrc) const
{
	return m_allModules.find(moduleCrc) != m_allModules.end();
}

Module* ModuleManager::GetModule(StringCrc moduleCrc) const
{
	auto itModule = m_allModules.find(moduleCrc);
	return itModule != m_allModules.end() ? itModule->second.get() : nullptr;
}

void ModuleManager::RemoveModule(StringCrc moduleCrc)
{
	if (auto itModule = m_allModules.find(moduleCrc); itModule != m_allModules.end())
	{
		m_allModules.erase(itModule);
	}
}

}