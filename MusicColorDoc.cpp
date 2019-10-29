
// MusicColorDoc.cpp : implementation of the CMusicColorDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MusicColor.h"
#endif

#include "MusicColorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMusicColorDoc

IMPLEMENT_DYNCREATE(CMusicColorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMusicColorDoc, CDocument)
END_MESSAGE_MAP()


// CMusicColorDoc construction/destruction

CMusicColorDoc::CMusicColorDoc() noexcept
{
	// TODO: add one-time construction code here
}

CMusicColorDoc::~CMusicColorDoc()
{
}

BOOL CMusicColorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


bool CMusicColorDoc::isValid()
{
	return (this->musicSheet.size() > 0);
}

// CMusicColorDoc serialization

void CMusicColorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
		std::ifstream fs;
		string note32;
		int fileSize;
		fileName = ar.m_strFileName;

		try
		{
			if (loadFile(ar.m_strFileName, fs))
			{
				sheet mSheet(rowsFile(fs), 256);
				musicSheet = mSheet;

				string str;
				int row = 0, col;

				startFile(fs);

				while (getline(fs, str))
				{
					col = 0;
					int f = str.find(' ');
					while (f >= 0)
					{
						musicSheet[row][col] = stoi(str.substr(0, f));
						str = str.substr(f + 1);
						f = str.find(' ');
						col++;
					}
					musicSheet[row][col] = stoi(str);
					/*int sound = 0;
					for (int cnt = 1; cnt <= col; cnt++)
					{
						sound += musicSheet[row][cnt];
					}
					Beep(A49 * pow(2, (sound - col * 49.0000)) / 12.000, 1000.0000 * musicSheet[row][0] / TIMEBASE);*/
					row++;
				}
				fileSize = musicSheet.size();
				/*for (int cnt = 1; cnt < 89; cnt++)
				{
					color cl = getColor(cnt);
					if ((cl.r < 0) || (cl.g < 0) || (cl.b < 0) || (cl.r > 255) || (cl.g > 255) || (cl.b > 255))
					{
						cout << "Not working for " << cnt << endl;
					}
				}*/
			}
		}
		catch (exception ex)
		{
			AfxMessageBox(_T("Open Document Failed."));
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMusicColorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMusicColorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMusicColorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMusicColorDoc diagnostics

#ifdef _DEBUG
void CMusicColorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMusicColorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMusicColorDoc commands

int CMusicColorDoc::pictureSize()
{
	return ceil(sqrt((double)musicSheet.time_size() / TIMEBASE));
}
