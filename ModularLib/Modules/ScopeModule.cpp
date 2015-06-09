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
     , m_GrabSize(4096)
     , m_Buffer(m_GrabSize)
     , m_NumRead(0)
    {}

    void OnTick()
    {
        if(m_BufferHandler)
        {
            m_Buffer.resize(m_GrabSize);
            bool Done = false;
            while(!Done)
            {
                m_NumRead += m_BufferingFilter->ReadBuffer(0, m_Buffer.data()+m_NumRead, m_Buffer.size()-m_NumRead);
                Done = m_NumRead<m_Buffer.size();
                if(!Done)
                {
                    m_BufferHandler->HandleBuffer(m_Buffer.data(), m_Buffer.size());
                    m_NumRead = 0;
                }
            }
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
    std::vector<float> m_Buffer;
    int m_NumRead;
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
    const int GrabFrequency = 100;//100 Hz
    m_ThreadRunner->SetPeriod(1000/GrabFrequency);
    const int DisplayFrequency = 10;
    int GrabSize = m_IOManager->SamplingFrequency()/DisplayFrequency;
    m_Runnable->SetGrabSize(GrabSize);
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
