/******************************************************************************
* TtsEngObj.h *
*-------------*
*  This is the header file for the sample CTTSEngObj class definition.
*------------------------------------------------------------------------------
*  Copyright (c) Microsoft Corporation. All rights reserved.
*
******************************************************************************/
#ifndef TtsEngObj_h
#define TtsEngObj_h

//--- Additional includes
#ifndef __TtsEng_h__
#include "ttseng.h"
#endif

#ifndef SPDDKHLP_h
#include <spddkhlp.h>
#endif

#ifndef SPCollec_h
#include <spcollec.h>
#endif

#include "resource.h"

#include "ekho_dict.h"
#include "sonic.h"
#include "ekho_typedef.h"
#include "audio.h"
//#define ENABLE_FESTIVAL

using namespace ekho;

//=== Constants ====================================================

//=== Class, Enum, Struct and Union Declarations ===================

//=== Enumerated Set Definitions ===================================

//=== Function Type Definitions ====================================

//=== Class, Struct and Union Definitions ==========================

/*** CSentItem
*   This object is a helper class
*/
class CSentItem
{
  public:
    CSentItem() { memset( this, 0, sizeof(*this) ); }
    CSentItem( CSentItem& Other ) { memcpy( this, &Other, sizeof( Other ) ); }

  /*--- Data members ---*/
    const SPVSTATE* pXmlState;
    LPCWSTR         pItem;
    ULONG           ulItemLen;
    ULONG           ulItemSrcOffset;        // Original source character position
    ULONG           ulItemSrcLen;           // Length of original source item in characters
};

typedef CSPList<CSentItem,CSentItem&> CItemList;

/*** CTTSEngObj COM object ********************************
*/
class ATL_NO_VTABLE CTTSEngObj : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CTTSEngObj, &CLSID_SampleTTSEngine>,
	public ISpTTSEngine,
    public ISpObjectWithToken
{
  /*=== ATL Setup ===*/
  public:
    DECLARE_REGISTRY_RESOURCEID(IDR_SAMPLETTSENGINE)
    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CTTSEngObj)
	    COM_INTERFACE_ENTRY(ISpTTSEngine)
	    COM_INTERFACE_ENTRY(ISpObjectWithToken)
    END_COM_MAP()

  /*=== Methods =======*/
  public:
    /*--- Constructors/Destructors ---*/
    HRESULT FinalConstruct();
    void FinalRelease();

  /*=== Interfaces ====*/
  public:
    //--- ISpObjectWithToken ----------------------------------
    STDMETHODIMP SetObjectToken( ISpObjectToken * pToken );
    STDMETHODIMP GetObjectToken( ISpObjectToken ** ppToken )
        { return SpGenericGetObjectToken( ppToken, m_cpToken ); }


    //--- ISpTTSEngine --------------------------------------------
    STDMETHOD(Speak)( DWORD dwSpeakFlags,
                      REFGUID rguidFormatId, const WAVEFORMATEX * pWaveFormatEx,
                      const SPVTEXTFRAG* pTextFragList, ISpTTSEngineSite* pOutputSite );
    STDMETHOD(GetOutputFormat)( const GUID * pTargetFormatId, const WAVEFORMATEX * pTargetWaveFormatEx,
                                GUID * pDesiredFormatId, WAVEFORMATEX ** ppCoMemDesiredWaveFormatEx );

    void setEnglishVoice(const char *voice) { mEnglishVoice = voice; }

    ISpTTSEngineSite *mOutputSite;
    static int writePcm(short* pcm, int frames, void* arg, OverlapType type,
      bool tofile);
    static int writePcm(short* pcm, int frames, void* arg, OverlapType type) {
      return writePcm(pcm, frames, arg, type, true);
    }

  private:
    /*--- Non interface methods ---*/
    HRESULT MapFile(const WCHAR * pszTokenValName, HANDLE * phMapping, void ** ppvData );
    HRESULT GetNextSentence( CItemList& ItemList );
    BOOL    AddNextSentItem( CItemList& ItemList );
    HRESULT OutputSentence( CItemList& ItemList, ISpTTSEngineSite* pOutputSite );

  /*=== Member Data ===*/
  private:
    CComPtr<ISpObjectToken> m_cpToken;
    HANDLE                  m_hVoiceData;
    void*                   m_pVoiceData;
    //--- Voice (word/audio data) list
    //  Note: You will probably have something more sophisticated here
    //        we are just trying to keep it simple for the example.
    VOICEITEM*          m_pWordList;
    ULONG               m_ulNumWords;

    //--- Working variables to walk the text fragment list during Speak()
    const SPVTEXTFRAG*  m_pCurrFrag;
    const WCHAR*        m_pNextChar;
    const WCHAR*        m_pEndChar;
    ULONGLONG           m_ullAudioOff;

	Dict                mDict;
	sonicStream         mSonicStream;
	short mPendingPcm[819200];
  int mPendingFrames;
	CSpDynamicString	m_dstrDirPath;
	CSpDynamicString	m_dstrVoice;
	const char *mEnglishVoice;
  bool mPcmCache;
  int mOverlap;
  SNDFILE *mSndFile;
  EkhoPuncType mPuncMode;
  Audio *audio;
  bool mSpeakIsolatedPunctuation;
  bool mDebug;
  char *mDebugFile;
  bool supportSsml;
  bool isPaused;
  bool isStopped;
  const char* mAlphabetPcmCache[26];
  int mAlphabetPcmSize[26];

  void translatePunctuations(string &text, EkhoPuncType mode);

  const char *getEnglishPcm(string text, int &size);
	const char* getPcmFromFestival(string text, int& size);
	int initEnglish(void);
	string genTempFilename();
	int writeToSonicStream(short *pcm, int frames, OverlapType type);

  static SpeechdSynthCallback *speechdSynthCallback;
  void setSpeechdSynthCallback(SpeechdSynthCallback *callback);
  void synthWithEspeak(string text);
};

typedef int(SynthCallback)(short *pcm, int frames, void *arg, OverlapType type);

#endif //--- This must be the last line in the file
