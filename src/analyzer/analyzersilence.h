#pragma once

#include "analyzer/analyzer.h"
#include "preferences/usersettings.h"

class CuePointer;

class AnalyzerSilence : public Analyzer {
  public:
    explicit AnalyzerSilence(UserSettingsPointer pConfig);
    ~AnalyzerSilence() override = default;

    bool initialize(TrackPointer pTrack,
            mixxx::audio::SampleRate sampleRate,
            int totalSamples) override;
    bool processSamples(const CSAMPLE* pIn, SINT iLen) override;
    void storeResults(TrackPointer pTrack) override;
    void cleanup() override;

    /// returns the index of the first sample in the buffer that is above -60 dB
    /// or -1 if no sample is found
    static SINT findFirstSound(const CSAMPLE* pIn, SINT iLen);
    /// returns the index of the last sample in the buffer that is above -60 dB
    /// or -1 if no sample is found. signalStart can be set to a known sample above
    /// -60 dB or -1 to start with the following index.
    static SINT findLastSound(const CSAMPLE* pIn, SINT iLen, SINT signalStart);

  private:
    UserSettingsPointer m_pConfig;
    int m_iFramesProcessed;
    int m_iSignalStart;
    int m_iSignalEnd;
};
