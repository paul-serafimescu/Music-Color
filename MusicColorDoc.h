
// MusicColorDoc.h : interface of the CMusicColorDoc class
//


#pragma once


class CMusicColorDoc : public CDocument
{
protected: // create from serialization only
	CMusicColorDoc() noexcept;
	DECLARE_DYNCREATE(CMusicColorDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	sheet musicSheet;
	int pictureSize();
	CString fileName;
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMusicColorDoc();
	bool isValid();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
