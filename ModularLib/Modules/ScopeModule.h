#ifndef CSCOPEMODULE_H
#define CSCOPEMODULE_H

#include <string>
#include <memory>
#include "ModularModuleI.h"

class CJackIOManager;
class CCommandStackController;
class CBufferingFilter;
template<class T> class IBufferHandler;
class CScopeRunnable;
template<class T> class CPeriodicThreadRunner;

class CScopeModule : public IModularModule
{
public:
    CScopeModule(const std::string& Name, CCommandStackController& CommandStackController, std::shared_ptr<IBufferHandler<float>> BufferHandler);
    ~CScopeModule();

    std::string GetName() const override;
    Names GetInputNames() const override;
    Names GetOutputNames() const override;
    Names GetMidiInputNames() const override;
    Names GetMidiOutputNames() const override;
    void Accept(IModuleParameterVisitor& ParameterVisitor) const override;

private:
    bool Open();
    bool Close();

    std::string m_Name;
    CCommandStackController& m_CommandStackController;
    std::shared_ptr<CBufferingFilter> m_Filter;
    std::unique_ptr<CJackIOManager> m_IOManager;
    std::unique_ptr<CScopeRunnable> m_Runnable;
    std::unique_ptr<CPeriodicThreadRunner<CScopeRunnable>> m_ThreadRunner;
};

#endif // CSCOPEMODULE_H
