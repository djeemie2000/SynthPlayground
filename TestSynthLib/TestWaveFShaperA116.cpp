#include "UnitTest++.h"
#include "WaveFolder2.h"

namespace
{

TEST(Stage)
{
    CWaveFolderStage<float> Folder;

    CHECK_CLOSE(1.0f, Folder(1.0f, 0.0f), 0.00001f);
    CHECK_CLOSE(0.6f, Folder(0.6f, 0.0f), 0.00001f);
    CHECK_CLOSE(0.5f, Folder(0.5f, 0.0f), 0.00001f);
    CHECK_CLOSE(0.2f, Folder(0.2f, 0.0f), 0.00001f);
    CHECK_CLOSE(0.0f, Folder(0.0f, 0.0f), 0.00001f);

    CHECK_CLOSE(0.0f, Folder(1.0f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.2f, Folder(0.9f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.4f, Folder(0.8f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.8f, Folder(0.6f, 1.0f), 0.00001f);

    CHECK_CLOSE(1.0f, Folder(0.5f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.8f, Folder(0.4f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.2f, Folder(0.1f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.0f, Folder(0.0f, 1.0f), 0.00001f);

}

TEST(OneStage)
{
    CMultiStageWaveFolder<float> Folder;
    Folder.SetNumStages(1);

    CHECK_CLOSE(1.0f, Folder(1.0f, 0.0f), 0.00001f);
    CHECK_CLOSE(0.6f, Folder(0.6f, 0.0f), 0.00001f);
    CHECK_CLOSE(0.5f, Folder(0.5f, 0.0f), 0.00001f);
    CHECK_CLOSE(0.2f, Folder(0.2f, 0.0f), 0.00001f);
    CHECK_CLOSE(0.0f, Folder(0.0f, 0.0f), 0.00001f);

    CHECK_CLOSE(0.0f, Folder(1.0f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.2f, Folder(0.9f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.4f, Folder(0.8f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.8f, Folder(0.6f, 1.0f), 0.00001f);

    CHECK_CLOSE(1.0f, Folder(0.5f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.8f, Folder(0.4f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.2f, Folder(0.1f, 1.0f), 0.00001f);
    CHECK_CLOSE(0.0f, Folder(0.0f, 1.0f), 0.00001f);
}

}
