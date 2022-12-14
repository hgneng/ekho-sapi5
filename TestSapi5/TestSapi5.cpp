
#include "stdafx.h"
#include <iostream>
#include <sapi.h>
#include <sphelper.h>
#include <atlcom.h>

using namespace std;

int main ( int NumOfArguments, char** Argument )
{
HRESULT                             hr = S_OK;
CComPtr<IEnumSpObjectTokens>        cpEnum;
ULONG                               ulCount = 0;

/*
CComPtr<ISpVoice>                   cpVoice;
CComPtr<ISpObjectToken>             cpVoiceToken;

// Initialize COM
    CoInitialize(NULL);

// Create the SAPI voice
if(SUCCEEDED(hr))
    hr = cpVoice.CoCreateInstance( CLSID_SpVoice ); 


//Enumerate the available voices 
if(SUCCEEDED(hr))
    hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum);

//Get the number of voices
if(SUCCEEDED(hr))
    hr = cpEnum->GetCount(&ulCount);

// Obtain a list of available voice tokens, set the voice to the token, and call Speak
while (SUCCEEDED(hr) && ulCount -- )
{
    cpVoiceToken.Release();
    if(SUCCEEDED(hr))
        hr = cpEnum->Next( 1, &cpVoiceToken, NULL );

    if(SUCCEEDED(hr))
        hr = cpVoice->SetVoice(cpVoiceToken);

    if(SUCCEEDED(hr))
        hr = cpVoice->Speak( L"123", SPF_DEFAULT, NULL); 
}

return 0;
*/

for (int i = 0; i < 1; i++) {
	// Initialize COM
    CoInitialize(NULL);
 
    ISpVoice * pSpVoice = NULL;
	CComPtr<ISpObjectToken>	cpToken;

	// Create the voice interface object
    if (FAILED(CoCreateInstance(CLSID_SpVoice, NULL, 
        CLSCTX_INPROC_SERVER, IID_ISpVoice, (void **)&pSpVoice)))
    {
        cerr << "Fail to create instance of ISpVoice!" << endl;
        return -1;
    }

	hr = pSpVoice->SetInterest( SPFEI(SPEI_WORD_BOUNDARY),SPFEI(SPEI_WORD_BOUNDARY) );
	if (FAILED(hr))	{
		cerr << "Fail to make event notifications!" << endl;
        return -1;
	}

	//====================== Test case for Spanish ==========================
	if (FAILED(SpEnumTokens(SPCAT_VOICES, L"Name=Ekho Cantonese", NULL, &cpEnum))) {
		cerr << "Fail to get voices!" << endl;
		return -1;
	}

	//Get the closest token
	cpToken.Release();
	if (FAILED(cpEnum->Next(1, &cpToken, NULL))) {
		cerr << "Fail to get voice EkhoVoice!" << endl;
		return -1;
	}

	//set the voice 
	if (FAILED(pSpVoice->SetVoice(cpToken))) {
		cerr << "Fail to set voice EkhoVoice!" << endl;
		return -1;
	}

	// set rate
	pSpVoice->SetRate(0);

	// set volume
	pSpVoice->SetVolume(90);

	cout << "speak in Spanish ... ";
	pSpVoice->Speak(L"[[jyut6 ping3]]", SPF_DEFAULT, NULL);
	pSpVoice->SetRate(-5);
	pSpVoice->Speak(L"pingüino español típico único solución árbol tupé", SPF_DEFAULT, NULL);
	pSpVoice->SetRate(0);
	pSpVoice->Speak(L"m", SPF_DEFAULT, NULL);
	pSpVoice->Speak(L"el soñador", SPF_DEFAULT, NULL);
	pSpVoice->Speak(L"6 W 2 1", SPF_DEFAULT, NULL);
	cout << "done" << endl;

	//======================= Test case for Tibetan ==============================
	if (FAILED(SpEnumTokens(SPCAT_VOICES, L"Name=Ekho Tibetan", NULL, &cpEnum))) {
		cerr << "Fail to get voices!" << endl;
		return -1;
	}

	//Get the closest token
	cpToken.Release();
	if (FAILED(cpEnum->Next(1, &cpToken, NULL))) {
		cerr << "Fail to get voice EkhoVoice!" << endl;
		return -1;
	}

	//set the voice 
	if (FAILED(pSpVoice->SetVoice(cpToken))) {
		cerr << "Fail to set voice EkhoVoice!" << endl;
		return -1;
	}

	cout << "speak hello in Tibetan ... ";
	pSpVoice->Speak(L"123 English is easy.中文很简单。་སྐད་སླ་བོ་རེད།", SPF_DEFAULT, NULL);

	//====================== Test case for Cantonese ==========================
	if (FAILED(SpEnumTokens(SPCAT_VOICES, L"Name=Ekho Cantonese", NULL, &cpEnum))) {
		cerr << "Fail to get voices!" << endl;
		return -1;
	}

	//Get the closest token
	cpToken.Release();
	if (FAILED(cpEnum ->Next(1, &cpToken, NULL))) {
		cerr << "Fail to get voice EkhoVoice!" << endl;
		return -1;
	}
	
	//set the voice 
	if (FAILED(pSpVoice->SetVoice( cpToken))) {
		cerr << "Fail to set voice EkhoVoice!" << endl;
		return -1;
	}

	// set rate
	pSpVoice->SetRate(0);

	// set volume
	pSpVoice->SetVolume(90);

	cout << "speak 123\r\n321 in Cantonese ... ";
	pSpVoice->Speak(L"Folder View  列表  D: nvda 20161  状态栏 就绪   行 66 列 14 Ch 14   Ins  ", SPF_ASYNC, NULL);
	pSpVoice->Speak(L"123你好\r\n321", SPF_PURGEBEFORESPEAK, NULL);
	pSpVoice->Speak(L"<Bookmark mark=\"12\" />我挥一挥衣袖", SPF_IS_XML, NULL);
	pSpVoice->Speak(L"<spell>为什么hello world</spell>", SPF_IS_XML, NULL);
	pSpVoice->Speak(L"<pitch absmiddle=\"10\">为												,什么hello world</pitch>", SPF_IS_XML, NULL);
	pSpVoice->Speak(L"<pitch absmiddle=\"-10\">为,,,,,,,,,,什么hello world</pitch>", SPF_IS_XML, NULL);
	cout << "done" << endl;

	//======================= Test case for English ==============================
	if (FAILED(SpEnumTokens(SPCAT_VOICES, L"Name=Ekho English", NULL, &cpEnum))) {
		cerr << "Fail to get voices!" << endl;
		return -1;
	}

	//Get the closest token
	cpToken.Release();
	if (FAILED(cpEnum ->Next(1, &cpToken, NULL))) {
		cerr << "Fail to get voice EkhoVoice!" << endl;
		return -1;
	}
	
	//set the voice 
	if (FAILED(pSpVoice->SetVoice( cpToken))) {
		cerr << "Fail to set voice EkhoVoice!" << endl;
		return -1;
	}

	cout << "speak hello in Mandarin ... ";
	pSpVoice->Speak(L"hello", SPF_DEFAULT, NULL);

	//======================= Test case for Mandarin ==============================
	if (FAILED(SpEnumTokens(SPCAT_VOICES, L"Name=Ekho Mandarin", NULL, &cpEnum))) {
		cerr << "Fail to get voices!" << endl;
		return -1;
	}

	//Get the closest token
	cpToken.Release();
	if (FAILED(cpEnum ->Next(1, &cpToken, NULL))) {
		cerr << "Fail to get voice EkhoVoice!" << endl;
		return -1;
	}
	
	//set the voice 
	if (FAILED(pSpVoice->SetVoice( cpToken))) {
		cerr << "Fail to set voice EkhoVoice!" << endl;
		return -1;
	}

	cout << "speak 123 in Mandarin ... ";
	pSpVoice->Speak(L"hello 123 . 大。\n\n也可以", SPF_DEFAULT, NULL);
	pSpVoice->Speak(L"Á, á, é, í, ó, ú and ü, hola mundo. 为什么", SPF_DEFAULT, NULL);
	cout << "done" << endl;

	if (FAILED(SpEnumTokens(SPCAT_VOICES, L"Name=Ekho Mandarin", NULL, &cpEnum))) {
		cerr << "Fail to get voices!" << endl;
		return -1;
	}

	//Get the closest token
	cpToken.Release();
	if (FAILED(cpEnum ->Next(1, &cpToken, NULL))) {
		cerr << "Fail to get voice EkhoVoice!" << endl;
		return -1;
	}
	
	//set the voice 
	if (FAILED(pSpVoice->SetVoice( cpToken))) {
		cerr << "Fail to set voice EkhoVoice!" << endl;
		return -1;
	}

	cout << "speak 123 with rate 5... ";
	// set rate
	pSpVoice->SetRate(5);
	pSpVoice->Speak(L"为什么", SPF_DEFAULT, NULL);
  pSpVoice->SetRate(0);
	cout << "done" << endl;

	//======================= Test case for Korean ==============================
	if (FAILED(SpEnumTokens(SPCAT_VOICES, L"Name=Ekho Korean", NULL, &cpEnum))) {
		cerr << "Fail to get voices!" << endl;
		return -1;
	}

	//Get the closest token
	cpToken.Release();
	if (FAILED(cpEnum ->Next(1, &cpToken, NULL))) {
		cerr << "Fail to get voice EkhoVoice!" << endl;
		return -1;
	}
	
	//set the voice 
	if (FAILED(pSpVoice->SetVoice( cpToken))) {
		cerr << "Fail to set voice EkhoVoice!" << endl;
		return -1;
	}

	cout << "speak 사랑을 나누면 부러울것이 없습니다 in Korean ... ";
	pSpVoice->Speak(L"사랑을 나누면 부러울것이 없습니다", SPF_DEFAULT, NULL);
	pSpVoice->Speak(L"사랑을hello world", SPF_DEFAULT, NULL);

	//===================== Test case for Hakka ==============================
	if (FAILED(SpEnumTokens(SPCAT_VOICES, L"Name=Ekho Hakka", NULL, &cpEnum))) {
		cerr << "Fail to get voices!" << endl;
		return -1;
	}

	//Get the closest token
	cpToken.Release();
	if (FAILED(cpEnum ->Next(1, &cpToken, NULL))) {
		cerr << "Fail to get voice EkhoVoice!" << endl;
		return -1;
	}
	
	//set the voice 
	if (FAILED(pSpVoice->SetVoice( cpToken))) {
		cerr << "Fail to set voice EkhoVoice!" << endl;
		return -1;
	}

	cout << "speak 123 in Hakka ... ";

	pSpVoice->Speak(L"123", SPF_DEFAULT, NULL);
	cout << "done" << endl;

	// Shutdown the voice
	cpToken.Release();
	cpEnum.Release();
	pSpVoice->Release();
	pSpVoice = NULL;

	// Shutdown COM
	CoUninitialize ();
}
	cout << "press 1<ENTER> to continue";
	int a;
	cin >> a;

	return 0;
	
}
