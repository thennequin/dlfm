#include <wx/wx.h>
#include <curl\curl.h>
//#include "DLManager.h"

#include "StateData.h"
#include "Parser.h"
#include "error.h"

//#include "StateData.h"

#ifndef _FILEDOWNLOADER_
#define _FILEDOWNLOADER_

class DLManager;

class FileDownloader : public wxThread
{
public:
	FileDownloader(wxString link,wxString filename,DLManager *manager);
	FileDownloader(FileDownloader& copy);
	~FileDownloader(void);

	bool IsOK() { if (Status==FFD_ERROR /*&& Error==ERROR_THREAD_NOT_CREATE*/) return false; return true; }

	enum FFD_State
	{
		FFD_STOP,
		FFD_START,
		FFD_WAIT,
		FFD_FINISH,
		FFD_ERROR,
		FFD_RETRY,
		//FFD_CHECK,
		FFD_MAX
	};

	virtual wxString GetClass() { return wxString("FileDownloader"); }

	virtual void StartDownload();	// Commence ou reprend le t�l�chargement
	virtual void StopDownload();	// Stop (met en pause) le t�l�chargement

	virtual curl_off_t GetFileSize() { return iFileSize;}
	virtual curl_off_t GetDownloadedSize() { return iDataPos;}
	inline wxString GetFilename() { /*pMutex->Lock()*/;wxString tem = pFileName;/*pMutex->Unlock()*/;return tem; }
	inline wxString GetLink() { /*pMutex->Lock();*/wxString tem = pLink;/*pMutex->Unlock();*/return tem; }
	virtual float GetSpeed() { return fSpeed; }
	virtual float GetMoySpeed() { return fMoySpeed; }

	static size_t WriteData(void *buffer, size_t size, size_t nmemb, void *userp);

	//Thread
	virtual void *Entry();
	/*{
		wxLogMessage("Entry\n");
		return 0;
	}*/
	virtual void OnExit();
	/*{
		wxLogMessage("Exit\n");
	}*/


	void SetLink(wxString link) { pLink=link; }
	void SetFilename(wxString file) { pFileName=file; }
	void SetFileSize(long size) { iFileSize=size; }
	void SetDownloadedSize(long size) { iDataPos=size; }

	//FFD_State GetStatus();
	int GetStatus() { return Status; }
	int GetErrorCode() { return Error; }

	void SetStatus(FFD_State status) { Status=status; }

	bool AlreadyRun() { return bAlreadyRun; }

	//wxMutex *pMutex;

	int			RetryCount;
	long		GetErrorTime() { return ErrorTime; }
protected:
	DLManager	*Manager;
	wxString	pLink;				// Adresse du fichier free (exemple : http://dl.free.fr/2f5g3ds)
	wxString	pFileName;			// Nom du fichier
	wxString	pLinkPageRef;		// Page du lien free de ref�rence (exemple : <html>...)
	wxString	pHeader;			// Header du fichier � t�l�charger (pour r�cup�rer la taille du fichier, ...)
	wxString	pFinalLink;			// Adresse finale du fichier � t�l�charger
	//byte *data;					// Donn�es du fichier � t�l�charger
	FILE		*pOutput;			// Fichier de sortie
	CURL		*pCurl;				// Connection

	//long long = __int64
	curl_off_t	iFileSize;			// Taille du fichier � t�l�charger
	curl_off_t	iDataPos;			// Taille des donn�es t�l�charger
	//long iMaxSpeed;				// Vitesse max pour t�l�charger ce fichier

	Page		pStatePage;
	Header		pStateHeader; 
	FileData	pStateData;
	StateData	pStateNone;

	FFD_State	Status;
	ERROR_CODE	Error;
	long		ErrorTime;

	bool		bAlreadyRun;
	bool		bStartDL;

	long		iTime;
	curl_off_t	iByteDL;
	float		fSpeed;
	float		fMoySpeed;

	char		Buffer[2048];
	int			BufferPos;
};

#endif