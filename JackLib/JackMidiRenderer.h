#ifndef JACKMIDIRENDERER_H
#define JACKMIDIRENDERER_H

#include "MidiRendererI.h"

class CJackMidiRenderer : public IMidiRenderer
{
public:
    CJackMidiRenderer(void* SrcBuffer);

    void Accept(IMidiHandler &Handler) override;

private:
    void* m_SrcBuffer;
};

#endif // JACKMIDIRENDERER_H
