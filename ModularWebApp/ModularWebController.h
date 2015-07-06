#pragma once

#include <string>
#include <vector>
#include <memory>

class CWebPageManager;
class CModularController;
struct SWebRequest;


class CModularWebController
{
public:
    CModularWebController(const std::string& PatchDirectory);
    ~CModularWebController();

    std::string HandleWebRequest(const SWebRequest& Request);

private:
    bool Create(const std::string& Type, const std::string& Name);
    bool Remove(const std::string& Name);
    bool RemoveAll();
    void Restore(); //!< restore grabbed state

    void UpdateModuleWebPages();

    std::shared_ptr<CModularController> m_ModularController;
    std::shared_ptr<CWebPageManager> m_WebPageManager;
};
