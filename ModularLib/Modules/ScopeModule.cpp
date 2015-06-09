#include "ScopeModule.h"
#include "BufferingFilter.h"
#include "ModuleParameterVisitorI.h"
#include "JackIOManager.h"
#include "PeriodicThreadRunner.h"
#include "BufferHandlerI.h"

class CScopeRunnable
{
public:
    CScopeRunnable(std::shared_ptr<CBufferingFilter> BufferingFilter, std::shared_ptr<IBufferHandler<float>> BufferHandler)
     : m_BufferingFilter(BufferingFilter)
     , m_BufferHandler(BufferHandler)
     , m_GrabSize(2048)
    {}

    void OnTick()
    {
        if(m_BufferHandler)
        {
            std::vector<float> GrabbedBuffer(m_GrabSize);
            int NumRead = m_BufferingFilter->ReadBuffer(0, GrabbedBuffer.data(), GrabbedBuffer.size());
            if(NumRead==GrabbedBuffer.size())
            {
                m_BufferHandler->HandleBuffer(GrabbedBuffer.data(), GrabbedBuffer.size());
            }
            //TODO handle non-complete buffer
        }
    }

    void SetGrabSize(int GrabSize)
    {
        m_GrabSize = GrabSize;
    }

private:
    std::shared_ptr<CBufferingFilter> m_BufferingFilter;
    std::shared_ptr<IBufferHandler<float>> m_BufferHandler;
    int m_GrabSize;
};

CScopeModule::CScopeModule(const std::string& Name, CCommandStackController& CommandStackController, std::shared_ptr<IBufferHandler<float> > BufferHandler)
 : m_Name(Name)
 , m_CommandStackController(CommandStackController)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
 , m_Runnable()
 , m_ThreadRunner()
{
    Open();
    // register parameters

    //
    m_Runnable.reset(new CScopeRunnable(m_Filter, BufferHandler));
    m_ThreadRunner.reset(new CPeriodicThreadRunner<CScopeRunnable>(*m_Runnable));
    m_ThreadRunner->SetPeriod(100);//10 Hz
    m_ThreadRunner->Start();
}

CScopeModule::~CScopeModule()
{
    m_ThreadRunner.reset();
    //unregister parameters
    Close();
}

std::string CScopeModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CScopeModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CScopeModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CScopeModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

IModularModule::Names CScopeModule::GetMidiOutputNames() const
{
    return m_Filter->GetMidiOutputNames();
}

void CScopeModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    //TODO
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CScopeModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CBufferingFilter(m_IOManager->SamplingFrequency(), 1000, {"In"}));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CScopeModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
